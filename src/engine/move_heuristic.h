#ifndef GEN_IV_BATTLE_FRONTIER_ANALYZER_MOVE_HEURISTIC_H
#define GEN_IV_BATTLE_FRONTIER_ANALYZER_MOVE_HEURISTIC_H

#include "move_execution.h"
#include "policies.h"
#include "turn_execution.h"

struct BestMoveResult {
    Move move;
    uint16_t damage;
    std::optional<uint16_t> number_of_hits_to_ko;
    uint16_t total_damage;
};

struct BestMoveResults {
    BestMoveResult attacker_results;
    BestMoveResult defender_results;
};

template <typename... Policies>
BestMoveResults get_best_move_result(
    const PolicyContainer<Policies...>& policy_container,
    const BattleState& battle_state,
    const std::vector<Move>& moves,
    Who who_attacker_is,
    std::optional<BestMoveResult> attacker_move_results,
    std::optional<BestMoveResult> defender_move_results,
    uint64_t depth = 0
);

inline int64_t get_hit_diff_of_move_results(
    const BestMoveResult& attacker_results,
    const BestMoveResult& defender_results
) {
    if (!defender_results.number_of_hits_to_ko) {
        int64_t attacker_hits;
        if (attacker_results.number_of_hits_to_ko) {
            attacker_hits = INT16_MAX + *attacker_results.number_of_hits_to_ko;
        } else {
            attacker_hits = 2 * INT16_MAX;
        }
        return INT16_MAX - attacker_hits;
    }

    const uint16_t defender_hits = *defender_results.number_of_hits_to_ko;
    if (!attacker_results.number_of_hits_to_ko) {
        return INT16_MIN + defender_hits;
    }

    return defender_hits - *attacker_results.number_of_hits_to_ko;
}

template <typename... Policies>
BestMoveResults get_move_results_when_choosing_move(
    const PolicyContainer<Policies...>& policy_container,
    const BattleState& battle_state,
    const Move attacker_move,
    BestMoveResult& defender_move_result,
    const Who who_attacker_is,
    uint64_t depth = 0
) {
    if (battle_state.is_battle_over()) {
        throw std::runtime_error(
            "Can't get move result on terminal state"
        );
    }

    BattleState temp_battle_state = battle_state;
    const bool attacker_is_player = who_attacker_is == Who::Player;
    const PokemonState& temp_attacker =
        attacker_is_player
            ? temp_battle_state.player
            : temp_battle_state.opponent;
    const PokemonState& temp_defender =
        attacker_is_player
            ? temp_battle_state.opponent
            : temp_battle_state.player;

    // policy_container.log(
    //     FORMAT_LAMBDA(
    //         "RE-EVAL at depth:{} move={} PP={}",
    //         depth,
    //         get_move_info(attacker_move)->name,
    //         temp_attacker.get_power_points(attacker_move)
    //     )
    // );

    const TurnResult turn_result = execute_turn(
        policy_container,
        temp_battle_state,
        attacker_is_player ? attacker_move : defender_move_result.move,
        attacker_is_player ? defender_move_result.move : attacker_move
    );
    // policy_container.log(FORMAT_LAMBDA(
    //     "AFTER TURN: defender asleep={} sleep_stage={}\n",
    //     temp_defender.has_status_with_stage(StatusWithStage::Asleep),
    //     temp_defender.get_status_stage(StatusWithStage::Asleep)
    // ));
    const Move attacker_move_used =
        attacker_is_player
            ? turn_result.player_move_used
            : turn_result.opponent_move_used;
    const uint16_t attacker_move_damage =
        static_cast<uint16_t>(
            attacker_is_player
                ? turn_result.player_move_damage
                : turn_result.opponent_move_damage
        );
    if (temp_battle_state.is_battle_over()) {
        const std::optional<uint16_t> attacker_hits_to_ko =
            temp_defender.get_current_stat(Stat::Health) <= 0
                ? std::optional<uint16_t>{1}
                : std::nullopt;
        return {
            .attacker_results = {
                .move = attacker_move_used,
                .damage = attacker_move_damage,
                .number_of_hits_to_ko = attacker_hits_to_ko,
                .total_damage = attacker_move_damage
            },
            .defender_results = defender_move_result
        };
    }

    const BestMoveResults best_move_results = get_best_move_result(
        policy_container,
        temp_battle_state,
        temp_attacker.get_moves(),
        who_attacker_is,
        std::nullopt,
        defender_move_result,
        depth + 1
    );
    const std::optional<uint16_t> attacker_hits_to_ko =
        best_move_results.attacker_results.number_of_hits_to_ko
            ? std::optional<uint16_t>{
                1 + *best_move_results.attacker_results.number_of_hits_to_ko
            }
            : std::nullopt;
    const uint16_t total_attacker_damage =
        attacker_move_damage +
        best_move_results.attacker_results.total_damage;
    return {
        .attacker_results = {
            .move = attacker_move_used,
            .damage = attacker_move_damage,
            .number_of_hits_to_ko = attacker_hits_to_ko,
            .total_damage = total_attacker_damage
        },
        .defender_results = defender_move_result
    };
}

inline bool is_further_evaluation_needed(
    const BattleState& battle_state,
    const Move attacker_move,
    const Who who_attacker_is,
    const BestMoveResult& best_defender_move
) {

    const bool is_player_attacker = who_attacker_is == Who::Player;
    const PokemonState& attacker =
        is_player_attacker
            ? battle_state.player
            : battle_state.opponent;
    const PokemonState& defender =
        is_player_attacker
            ? battle_state.opponent
            : battle_state.player;

    if (attacker.has_status_with_stage(StatusWithStage::Asleep)) {
        return false;
    }

    // RIP this takes too long; may try to bring back to life if depth is capped to less than 7
    // if (attacker.get_stat_stage(Stat::Health) <
    //     attacker.get_original_stat(Stat::Health) / 2 &&
    //     (attacker_move == Move::Moonlight || attacker_move == Move::Rest)
    // ) {
    //     return true;
    // }

    if (move_has_flag(
            attacker_move,
            MoveFlag::LOWERS_ATTACKERS_SPECIAL_ATTACK_TWO_STAGES
        ) ||
        (attacker_move == Move::Curse &&
            (attacker.get_stat_stage(Stat::Attack) < 6 ||
                attacker.get_stat_stage(Stat::Defense) < 6))
    ) [[unlikely]] {
        return true;
    }

    if (who_attacker_is == Who::Opponent) {
        if (move_has_flag(
                attacker_move,
                MoveFlag::OMNI_BOOSTS_ATTACKER)
        ) [[unlikely]] {
            return true;
        }

        if (move_has_flag(
                attacker_move,
                MoveFlag::LOWERS_DEFENDER_SPECIAL_DEFENSE_ONE_STAGE_10
            ) ||
            move_has_flag(
                attacker_move,
                MoveFlag::LOWERS_DEFENDER_SPECIAL_DEFENSE_ONE_STAGE_20
            ) ||
            move_has_flag(
                attacker_move,
                MoveFlag::BOOSTS_ATTACKERS_SPECIAL_ATTACK_ONE_STAGE_70
            )
        ) [[unlikely]] {
            return true;
        }
    }

    // TODO If defender uses a move that lowers the attacker's attack,
    // expected total damage is lower
    if (who_attacker_is == Who::Player &&
        move_has_flag(
            best_defender_move.move,
            MoveFlag::LOWERS_DEFENDER_SPECIAL_ATTACK_ONE_STAGE_50) &&
        get_move_info(attacker_move)->category == Category::SPECIAL
    )[[unlikely]] {
        return true;
    }

    return false;
}

template <typename... Policies>
BestMoveResult get_move_result(
    const PolicyContainer<Policies...>& policy_container,
    const BattleState& battle_state,
    const Who who_attacker_is,
    const Move move
) {
    const uint16_t damage = get_damage_of_move(
        policy_container,
        battle_state,
        get_move_info(move),
        who_attacker_is
    );

    std::optional<uint16_t> hits_to_ko{};
    if (damage != 0) {
        const bool is_player_attacker = who_attacker_is == Who::Player;
        const PokemonState& defender =
            is_player_attacker
                ? battle_state.opponent
                : battle_state.player;
        const uint16_t defender_hp = defender.get_current_stat(Stat::Health);
        hits_to_ko = static_cast<uint16_t>(
            std::ceil(static_cast<double>(defender_hp) / damage)
        );
    }

    const uint16_t total_damage =
        hits_to_ko.has_value()
            ? damage * hits_to_ko.value()
            : 0;
    return {
        .move = move,
        .damage = damage,
        .number_of_hits_to_ko = hits_to_ko,
        .total_damage = total_damage
    };
}

template <typename... Policies>
BestMoveResults get_best_move_result(
    const PolicyContainer<Policies...>& policy_container,
    const BattleState& battle_state,
    const Who who_attacker_is,
    const std::vector<Move>& moves,
    const Category category,
    std::optional<BestMoveResult> attacker_move_results,
    std::optional<BestMoveResult> defender_move_results,
    uint64_t depth = 0
) {
    // policy_container.log(
    //     FORMAT_LAMBDA("Entering get_best_move_result2\n"));
    if (attacker_move_results.has_value() &&
        defender_move_results.has_value()
    ) {
        // policy_container.
        //     log(FORMAT_LAMBDA("Exiting get_best_move_result2 early\n"));
        return {
            .attacker_results = *attacker_move_results,
            .defender_results = *defender_move_results
        };
    }
    auto best = BestMoveResult{
        .move = Move::MoveCount,
        .damage = 0,
        .number_of_hits_to_ko = std::nullopt,
        .total_damage = 0
    };
    const Who who_defender_is =
        who_attacker_is == Who::Player
            ? Who::Opponent
            : Who::Player;
    // -2 * UINT16_MAX is the minimum possible diff
    int64_t diff = static_cast<int64_t>(0) - UINT32_MAX;
    BestMoveResult best_defender_move{
        .move = Move::MoveCount,
        .damage = 0,
        .number_of_hits_to_ko = std::nullopt,
        .total_damage = 0
    };
    if (defender_move_results) {
        best_defender_move = *defender_move_results;
    }

    const bool is_player_attacker = who_attacker_is == Who::Player;
    const PokemonState& attacker =
        is_player_attacker
            ? battle_state.player
            : battle_state.opponent;
    const PokemonState& defender =
        is_player_attacker
            ? battle_state.opponent
            : battle_state.player;
    for (const auto move : moves) {
        const auto& move_info = get_move_info(move);
        if (move_does_nothing(
                policy_container,
                battle_state,
                move_info,
                who_attacker_is)
        ) {
            continue;
        }
        if (!attacker.has_power_points(move)) {
            continue;
        }

        // policy_container.log(
        //     FORMAT_LAMBDA(
        //         "EVAL at depth:{} move={} PP={}",
        //         depth,
        //         move_info->name,
        //         attacker.get_power_points(move)
        //     )
        // );

        if (move_info->category == category ||
            move_info->category == Category::STATUS
        ) {
            BestMoveResult current_move_result =
                get_move_result(
                    policy_container,
                    battle_state,
                    who_attacker_is,
                    move
                );
            if (!defender_move_results.has_value() ||
                !defender.has_power_points(defender_move_results->move)
            ) {
                // Attacker and defender are swapped
                // in order to get the move the defender will use
                // in response to this move
                best_defender_move =
                    choose_move_against_defender(
                        policy_container,
                        battle_state,
                        defender.get_moves(),
                        who_defender_is,
                        std::nullopt,
                        current_move_result,
                        depth
                    ).attacker_results;
            } else {
                best_defender_move = *defender_move_results;
            }

            const bool further_evaluation_needed =
                is_further_evaluation_needed(
                    battle_state,
                    move,
                    who_attacker_is,
                    best_defender_move
                ) && attacker.get_moves().size() > 1 && depth < 7;
            // policy_container.log(FORMAT_LAMBDA(
            //     "RECURSE attacker={} move={} PP={} defender_move={} PP={} "
            //     "attacker_HP={} defender_HP={} \n",
            //     who_attacker_is == Who::Player ? "Player" : "Opponent",
            //     get_move_info(move)->name,
            //     attacker.get_power_points(move),
            //     get_move_info(best_defender_move.move)->name,
            //     defender.get_power_points(best_defender_move.move),
            //     attacker.get_current_stat(Stat::Health),
            //     defender.get_current_stat(Stat::Health)
            // ));
            if (!move_does_nothing(
                    policy_container,
                    battle_state,
                    move_info,
                    who_attacker_is
                ) && further_evaluation_needed &&
                !battle_state.is_battle_over()
            ) {
                BestMoveResults temp_best_move_results =
                    get_move_results_when_choosing_move(
                        policy_container,
                        battle_state,
                        move,
                        best_defender_move,
                        who_attacker_is,
                        depth
                    );
                current_move_result =
                    temp_best_move_results.attacker_results;
                best_defender_move = temp_best_move_results.
                    defender_results;
            }

            int64_t new_diff = get_hit_diff_of_move_results(
                current_move_result,
                best_defender_move
            );

            if (new_diff > diff ||
                (new_diff == diff &&
                    ((best.number_of_hits_to_ko >
                            current_move_result.number_of_hits_to_ko
                        ) ||
                        (best.number_of_hits_to_ko ==
                            current_move_result.number_of_hits_to_ko &&
                            best.total_damage <
                            current_move_result.total_damage
                        )
                    )
                )
            ) {
                best = current_move_result;
                diff = new_diff;
            }
        }
    }

    // policy_container.log(FORMAT_LAMBDA(
    //     "attacker={}\n"
    //     "attacker_move={} | damage={} | hits_to_ko={} | total_damage={}\n"
    //     "defender_move={} | damage={} | hits_to_ko={} | total_damage={}\n",
    //     who_attacker_is == Who::Player ? "Player" : "Opponent",
    //     get_move_info(best.move)->name,
    //     best.damage,
    //     best.number_of_hits_to_ko
    //     ? *best.number_of_hits_to_ko
    //     : UINT16_MAX,
    //     best.total_damage,
    //     get_move_info(best_defender_move.move)->name,
    //     best_defender_move.damage,
    //     best_defender_move.number_of_hits_to_ko
    //     ? *best_defender_move.number_of_hits_to_ko
    //     : UINT16_MAX,
    //     best_defender_move.total_damage
    // ));

    // policy_container.
    //     log(FORMAT_LAMBDA("Exiting get_best_move_result2\n"));
    return {
        .attacker_results = best,
        .defender_results = best_defender_move
    };
}

template <typename... Policies>
BestMoveResults get_best_move_result(
    const PolicyContainer<Policies...>& policy_container,
    const BattleState& battle_state,
    const std::vector<Move>& moves,
    const Who who_attacker_is,
    std::optional<BestMoveResult> attacker_move_results,
    std::optional<BestMoveResult> defender_move_results,
    uint64_t depth
) {
    const bool is_player_attacker = who_attacker_is == Who::Player;
    const PokemonState& attacker =
        is_player_attacker
            ? battle_state.player
            : battle_state.opponent;
    const PokemonState& defender =
        is_player_attacker
            ? battle_state.opponent
            : battle_state.player;
    // policy_container.
    //     log(FORMAT_LAMBDA("Entering get_best_move_result\n"));
    if (attacker_move_results.has_value() &&
        defender_move_results.has_value()
    ) {
        // policy_container.log(
        //     FORMAT_LAMBDA("Exiting get_best_move_result early\n"));
        return {
            .attacker_results = *attacker_move_results,
            .defender_results = *defender_move_results
        };
    }

    if (moves.size() == 1 && moves.front() == Move::Struggle) {
        const uint16_t struggle_damage = get_struggle_damage(
            policy_container,
            attacker,
            defender,
            who_attacker_is
        );
        const uint16_t hits_to_ko = static_cast<uint16_t>(
            std::ceil(
                defender.get_current_stat(Stat::Health) / struggle_damage
            )
        );

        const BestMoveResult best_move_result = {
            .move = Move::Struggle,
            .damage = struggle_damage,
            .number_of_hits_to_ko = hits_to_ko,
            .total_damage =
            static_cast<uint16_t>(struggle_damage * hits_to_ko)
        };
        const Who who_defender_is =
            who_attacker_is == Who::Player
                ? Who::Opponent
                : Who::Player;
        const BestMoveResults defender_power_move =
            choose_move_against_defender(
                policy_container,
                battle_state,
                defender.get_moves(),
                who_defender_is,
                defender_move_results,
                best_move_result,
                depth
            );
        // policy_container.log(
        //     FORMAT_LAMBDA(
        //         "Exiting get_best_move_result due to strugge\n")
        // );
        return {
            .attacker_results = best_move_result,
            .defender_results = defender_power_move.attacker_results
        };
    }

    const BestMoveResults best_physical =
        get_best_move_result(
            policy_container,
            battle_state,
            who_attacker_is,
            moves,
            Category::PHYSICAL,
            std::nullopt,
            defender_move_results,
            depth
        );
    const BestMoveResults best_special =
        get_best_move_result(
            policy_container,
            battle_state,
            who_attacker_is,
            moves,
            Category::SPECIAL,
            std::nullopt,
            defender_move_results,
            depth
        );

    if (!best_physical.attacker_results.number_of_hits_to_ko) {
        return best_special;
    }

    if (!best_special.attacker_results.number_of_hits_to_ko) {
        return best_physical;
    }

    const uint16_t physical_hits_taken =
        best_physical.defender_results.number_of_hits_to_ko
            ? *best_physical.defender_results.number_of_hits_to_ko
            : UINT16_MAX;
    const uint16_t physical_hits_given =
        best_physical.attacker_results.number_of_hits_to_ko
            ? *best_physical.attacker_results.number_of_hits_to_ko
            : UINT16_MAX;
    const int32_t physical_diff = physical_hits_taken - physical_hits_given;
    const uint16_t special_hits_taken =
        best_special.defender_results.number_of_hits_to_ko
            ? *best_special.defender_results.number_of_hits_to_ko
            : UINT16_MAX;
    const uint16_t special_hits_given =
        best_special.attacker_results.number_of_hits_to_ko
            ? *best_special.attacker_results.number_of_hits_to_ko
            : UINT16_MAX;
    const int32_t special_diff = special_hits_taken - special_hits_given;

    // policy_container.log(
    //     FORMAT_LAMBDA("Exiting get_best_move_result\n")
    // );

    if (physical_diff > special_diff ||
        (physical_diff == special_diff &&
            best_physical.attacker_results.total_damage >
            best_special.attacker_results.total_damage)
    ) {
        return best_physical;
    }
    return best_special;
}

template <typename... Policies>
BestMoveResults choose_move_against_defender(
    const PolicyContainer<Policies...>& policy_container,
    const BattleState& battle_state,
    const std::vector<Move>& attacker_moves,
    const Who who_attacker_is,
    std::optional<BestMoveResult> attacker_move_results,
    std::optional<BestMoveResult> defender_move_results,
    uint64_t depth = 0
) {
    // policy_container.log(
    //     FORMAT_LAMBDA("Entering choose_move_against_defender\n")
    // );
    if (attacker_move_results.has_value() &&
        defender_move_results.has_value()
    ) {
        // policy_container.log(
        //     FORMAT_LAMBDA("Exiting choose_move_against_defender early\n")
        // );
        return {
            .attacker_results = *attacker_move_results,
            .defender_results = *defender_move_results
        };
    }

    BestMoveResults best_move = get_best_move_result(
        policy_container,
        battle_state,
        attacker_moves,
        who_attacker_is,
        attacker_move_results,
        defender_move_results,
        depth
    );

    if (best_move.attacker_results.move == Move::MoveCount) {
        for (const auto move : attacker_moves) {
            if (!move_does_nothing(
                    policy_container,
                    battle_state,
                    get_move_info(move),
                    who_attacker_is
                )
            ) {
                throw std::runtime_error{"Usable move was not chosen"};
            }
            best_move.attacker_results.move = attacker_moves[0];
        }
    }

    // policy_container.log(
    //     FORMAT_LAMBDA("Exiting choose_move_against_defender\n")
    // );
    return best_move;
}

#endif //GEN_IV_BATTLE_FRONTIER_ANALYZER_MOVE_HEURISTIC_H
