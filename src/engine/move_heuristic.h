#ifndef GEN_IV_BATTLE_FRONTIER_ANALYZER_MOVE_HEURISTIC_H
#define GEN_IV_BATTLE_FRONTIER_ANALYZER_MOVE_HEURISTIC_H

#include "move_execution.h"
#include "policies.h"
#include "turn_execution.h"

struct MoveDamage {
    Move move = Move::MoveCount;
    uint16_t damage = 0;
};

struct MoveResult {
    Move evaluated_move = Move::MoveCount;
    std::array<MoveDamage, 8> line{};
    uint8_t line_size = 0;
    uint16_t total_damage = 0;
    std::optional<uint16_t> hits_to_ko{};

    void add_line_item(const MoveDamage move_damage) {
        if (line_size < line.size()) {
            line[line_size++] = move_damage;
            total_damage += move_damage.damage;
        }
    }
};

inline int64_t get_hit_diff_of_move_results(
    const MoveResult& attacker_results,
    const MoveResult& defender_results
) {
    if (!defender_results.hits_to_ko) {
        int64_t attacker_hits;
        if (attacker_results.hits_to_ko) {
            attacker_hits =
                static_cast<int64_t>(INT16_MAX) + *attacker_results.hits_to_ko;
        } else {
            attacker_hits = static_cast<int64_t>(2) * INT16_MAX;
        }
        return static_cast<int64_t>(INT16_MAX) - attacker_hits;
    }

    const int64_t defender_hits = *defender_results.hits_to_ko;
    if (!attacker_results.hits_to_ko) {
        return static_cast<int64_t>(INT16_MIN) + defender_hits;
    }

    return defender_hits - *attacker_results.hits_to_ko;
}

template <typename... Policies>
MoveResult get_move_result(
    const PolicyContainer<Policies...>& policy_container,
    const BattleState& battle_state,
    const Who who_attacker_is,
    const Move attacker_move
) {
    uint16_t damage = get_damage_of_move(
        policy_container,
        battle_state,
        get_move_info(attacker_move),
        who_attacker_is
    );

    // Account for charging and recharging
    if ((attacker_move == Move::SolarBeam && !battle_state.has_weather(
            Weather::Sun)) ||
        attacker_move == Move::HyperBeam
    ) {
        damage = damage / 2;
    }

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

    MoveResult best{};
    best.evaluated_move = attacker_move;
    best.hits_to_ko = hits_to_ko;
    if (hits_to_ko.has_value()) {
        for (uint16_t i = 0; i < *hits_to_ko; i++) {
            best.add_line_item(MoveDamage{
                .move = attacker_move, .damage = damage
            });
        }
    }
    return best;
}

inline bool is_further_evaluation_needed(
    const BattleState& battle_state,
    const Move attacker_move,
    const Who who_attacker_is,
    const Move defender_move
) {
    const bool is_player_attacker = who_attacker_is == Who::Player;
    const PokemonState& attacker =
        is_player_attacker
            ? battle_state.player
            : battle_state.opponent;
    // const PokemonState& defender =
    //     is_player_attacker
    //         ? battle_state.opponent
    //         : battle_state.player;

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
    // TODO test one vs the other

    if ((attacker_move == Move::Hail &&
            !battle_state.has_weather(Weather::Hail)) ||
        (attacker_move == Move::SunnyDay &&
            !battle_state.has_weather(Weather::Sun)) ||
        (attacker_move == Move::RainDance &&
            !battle_state.has_weather(Weather::Rain)
        )
    ) [[unlikely]] {
        return true;
    }

    if (attacker_move == Move::SolarBeam) {
        return true;
    }

    if (attacker_move == Move::HyperBeam) {
        return true;
    }

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

        if (move_has_flag(
                attacker_move,
                MoveFlag::BURNS_DEFENDER_10
            )
        ) {
            return true;
        }
    }

    if (who_attacker_is == Who::Player &&
        move_has_flag(
            defender_move,
            MoveFlag::LOWERS_DEFENDER_SPECIAL_ATTACK_ONE_STAGE_50) &&
        get_move_info(attacker_move)->category == Category::SPECIAL
    )[[unlikely]] {
        return true;
    }

    return false;
}

struct MoveResults {
    MoveResult attacker_results;
    MoveResult defender_results;
};

template <typename... Policies>
MoveResults get_move_results_when_choosing_move(
    const PolicyContainer<Policies...>& policy_container,
    const BattleState& battle_state,
    const Move attacker_move,
    const MoveResult& defender_move_result,
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
    const TurnResult turn_result = execute_turn(
        policy_container,
        temp_battle_state,
        attacker_is_player
            ? attacker_move
            : defender_move_result.evaluated_move,
        attacker_is_player ? defender_move_result.evaluated_move : attacker_move
    );
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
        MoveResult attacker_results{
            .evaluated_move = attacker_move_used,
            .line_size = 0,
            .total_damage = 0,
            .hits_to_ko = attacker_hits_to_ko
        };
        if (attacker_hits_to_ko) {
            attacker_results.line_size = 1;
            attacker_results.line[0] = MoveDamage{
                .move = attacker_move_used,
                .damage = attacker_move_damage
            };
        }
        return MoveResults{
            .attacker_results = attacker_results,
            .defender_results = defender_move_result
        };
    }

    MoveResult attacker_results{
        .evaluated_move = attacker_move_used,
        .line_size = 0,
        .total_damage = 0,
        .hits_to_ko = 1
    };
    attacker_results.add_line_item(
        MoveDamage{
            .move = attacker_move_used,
            .damage = attacker_move_damage
        }
    );
    MoveResults best_move_results = get_best_move_result(
        policy_container,
        temp_battle_state,
        temp_attacker.get_moves(
            policy_container.can_use_less_accurate_moves(
                who_attacker_is
            )
        ),
        who_attacker_is,
        std::nullopt,
        defender_move_result,
        depth + 1
    );
    size_t i = 0;
    for (const auto line : best_move_results.attacker_results.line) {
        if (i < best_move_results.attacker_results.line_size) {
            attacker_results.add_line_item(line);
        } else {
            break;
        }
        i++;
    }
    attacker_results.hits_to_ko =
        best_move_results.attacker_results.hits_to_ko
            ? std::optional<uint16_t>{
                1 + *best_move_results.attacker_results.hits_to_ko
            }
            : std::nullopt;

    return
    {
        .attacker_results = attacker_results,
        .defender_results = defender_move_result
    };
}

template <typename... Policies>
MoveResults get_best_move_result(
    const PolicyContainer<Policies...>& policy_container,
    const BattleState& battle_state,
    const Who who_attacker_is,
    const std::vector<Move>& moves,
    const Category category,
    std::optional<MoveResult> attacker_move_results,
    std::optional<MoveResult> defender_move_results,
    uint64_t depth = 0
) {
    if (attacker_move_results.has_value() &&
        defender_move_results.has_value()
    ) {
        return {
            .attacker_results = *attacker_move_results,
            .defender_results = *defender_move_results
        };
    }
    MoveResult best{
        .evaluated_move = Move::MoveCount,
        .line = {},
        .line_size = 0,
        .total_damage = 0,
        .hits_to_ko = std::nullopt
    };

    const Who who_defender_is =
        who_attacker_is == Who::Player
            ? Who::Opponent
            : Who::Player;
    // -2 * UINT16_MAX is the minimum possible diff
    int64_t diff = static_cast<int64_t>(0) - UINT32_MAX;
    MoveResult best_defender_move{
        .evaluated_move = Move::MoveCount,
        .line = {},
        .line_size = 0,
        .total_damage = 0,
        .hits_to_ko = std::nullopt
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

        if (move_info->category == category ||
            move_info->category == Category::STATUS
        ) {
            MoveResult current_move_result =
                get_move_result(
                    policy_container,
                    battle_state,
                    who_attacker_is,
                    move
                );
            if (!defender_move_results.has_value() ||
                !defender.has_power_points(
                    defender_move_results->evaluated_move)
            ) {
                // Attacker and defender are swapped
                // in order to get the move the defender will use
                // in response to this move
                best_defender_move =
                    choose_move_against_defender(
                        policy_container,
                        battle_state,
                        defender.get_moves(
                            policy_container.can_use_less_accurate_moves(
                                who_defender_is
                            )
                        ),
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
                    best_defender_move.evaluated_move
                ) &&
                attacker.get_moves(
                    policy_container.can_use_less_accurate_moves(
                        who_attacker_is
                    )
                ).size() > 1 && depth < 7;
            if (further_evaluation_needed &&
                !battle_state.is_battle_over()
            ) {
                MoveResults temp_best_move_results =
                    get_move_results_when_choosing_move(
                        policy_container,
                        battle_state,
                        move,
                        best_defender_move,
                        who_attacker_is,
                        depth
                    );
                if (temp_best_move_results.attacker_results.line_size > 1 ||
                    temp_best_move_results.attacker_results.total_damage >=
                    current_move_result.total_damage
                ) {
                    current_move_result =
                        temp_best_move_results.attacker_results;
                    best_defender_move = temp_best_move_results.
                        defender_results;
                }
            }

            int64_t new_diff = get_hit_diff_of_move_results(
                current_move_result,
                best_defender_move
            );

            if (new_diff > diff ||
                (new_diff == diff &&
                    ((best.hits_to_ko >
                            current_move_result.hits_to_ko
                        ) ||
                        (best.hits_to_ko ==
                            current_move_result.hits_to_ko &&
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
    return {
        .attacker_results = best,
        .defender_results = best_defender_move
    };
}

template <typename... Policies>
MoveResult get_best_defender_move_if_needed(
    const PolicyContainer<Policies...>& policy_container,
    const BattleState& battle_state,
    const PokemonState& defender,
    const Who who_defender_is,
    const Move defender_move,
    const std::optional<MoveResult> defender_move_results,
    uint64_t depth
) {
    if (defender_move_results.has_value() &&
        defender.has_power_points(
            defender_move_results->evaluated_move)
    ) {
        return *defender_move_results;
    }
    // Attacker and defender are swapped
    // in order to get the move the defender will use
    // in response to this move
    return choose_move_against_defender(
        policy_container,
        battle_state,
        defender.get_moves(
            policy_container.can_use_less_accurate_moves(
                who_defender_is
            )
        ),
        who_defender_is,
        std::nullopt,
        MoveResult{
            .evaluated_move = defender_move,
            .line_size = 0,
            .total_damage = 0,
            .hits_to_ko = std::nullopt
        },
        depth
    ).attacker_results;
}

template <typename... Policies>
MoveResults get_best_move_result(
    const PolicyContainer<Policies...>& policy_container,
    const BattleState& battle_state,
    const std::vector<Move>& moves,
    const Who who_attacker_is,
    const std::optional<MoveResult> attacker_move_results,
    std::optional<MoveResult> defender_move_results,
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
    if (attacker_move_results.has_value() &&
        defender_move_results.has_value()
    ) {
        return {
            .attacker_results = *attacker_move_results,
            .defender_results = *defender_move_results
        };
    }

    const Who who_defender_is =
        who_attacker_is == Who::Player
            ? Who::Opponent
            : Who::Player;
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

        MoveResult best_move_result = {
            .evaluated_move = Move::Struggle,
            .line = {},
            .line_size = 0,
            .total_damage = 0,
            .hits_to_ko = hits_to_ko
        };
        for (uint16_t i = 0; i < hits_to_ko; i++) {
            best_move_result.add_line_item(
                MoveDamage{
                    .move = Move::Struggle,
                    .damage = struggle_damage
                }
            );
        }
        const MoveResults defender_power_move =
            choose_move_against_defender(
                policy_container,
                battle_state,
                defender.get_moves(
                    policy_container.can_use_less_accurate_moves(
                        who_defender_is
                    )
                ),
                who_defender_is,
                defender_move_results,
                best_move_result,
                depth
            );
        return {
            .attacker_results = best_move_result,
            .defender_results = defender_power_move.attacker_results
        };
    }

    if (attacker.has_move_status_with_stage(MoveStatusWithStage::Charging)) {
        Move charge_move =
            attacker.get_move_status_move(MoveStatusWithStage::Charging);
        MoveResult best_defender_move =
            get_best_defender_move_if_needed(
                policy_container,
                battle_state,
                defender,
                who_defender_is,
                charge_move,
                defender_move_results,
                depth
            );
        return get_move_results_when_choosing_move(
            policy_container,
            battle_state,
            charge_move,
            best_defender_move,
            who_attacker_is,
            depth
        );
    }

    if (attacker.has_status_with_stage(StatusWithStage::Recharging)) {
        Move recharge_move = attacker.get_last_used_move();
        MoveResult best_defender_move =
            get_best_defender_move_if_needed(
                policy_container,
                battle_state,
                defender,
                who_defender_is,
                recharge_move,
                defender_move_results,
                depth
            );
        return get_move_results_when_choosing_move(
            policy_container,
            battle_state,
            recharge_move,
            best_defender_move,
            who_attacker_is,
            depth
        );
    }

    const MoveResults best_physical =
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
    const MoveResults best_special =
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

    if (!best_physical.attacker_results.hits_to_ko) {
        return best_special;
    }

    if (!best_special.attacker_results.hits_to_ko) {
        return best_physical;
    }

    const uint16_t physical_hits_taken =
        best_physical.defender_results.hits_to_ko
            ? *best_physical.defender_results.hits_to_ko
            : UINT16_MAX;
    const uint16_t physical_hits_given =
        best_physical.attacker_results.hits_to_ko
            ? *best_physical.attacker_results.hits_to_ko
            : UINT16_MAX;
    const int32_t physical_diff =
        static_cast<int32_t>(physical_hits_taken) - physical_hits_given;
    const uint16_t special_hits_taken =
        best_special.defender_results.hits_to_ko
            ? *best_special.defender_results.hits_to_ko
            : UINT16_MAX;
    const uint16_t special_hits_given =
        best_special.attacker_results.hits_to_ko
            ? *best_special.attacker_results.hits_to_ko
            : UINT16_MAX;
    const int32_t special_diff =
        static_cast<int32_t>(special_hits_taken) - special_hits_given;

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
MoveResults choose_move_against_defender(
    const PolicyContainer<Policies...>& policy_container,
    const BattleState& battle_state,
    const std::vector<Move>& attacker_moves,
    const Who who_attacker_is,
    std::optional<MoveResult> attacker_move_results,
    std::optional<MoveResult> defender_move_results,
    uint64_t depth = 0
) {
    if (attacker_move_results.has_value() &&
        defender_move_results.has_value()
    ) {
        return {
            .attacker_results = *attacker_move_results,
            .defender_results = *defender_move_results
        };
    }

    MoveResults best_move = get_best_move_result(
        policy_container,
        battle_state,
        attacker_moves,
        who_attacker_is,
        attacker_move_results,
        defender_move_results,
        depth
    );

    if (best_move.attacker_results.evaluated_move == Move::MoveCount) {
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
        }
        best_move.attacker_results.evaluated_move = attacker_moves[0];
        best_move.attacker_results.hits_to_ko = std::nullopt;
        best_move.attacker_results.line_size = 0;
        best_move.attacker_results.total_damage = 0;
    }
    if (best_move.defender_results.evaluated_move == Move::MoveCount) {
        const bool is_player_attacker = who_attacker_is == Who::Player;
        const Who who_defender_is =
            who_attacker_is == Who::Player
                ? Who::Opponent
                : Who::Player;
        const PokemonState& defender =
            is_player_attacker
                ? battle_state.opponent
                : battle_state.player;
        for (const auto move :
             defender.get_moves(
                 policy_container.can_use_less_accurate_moves(Who::Opponent)
             )
        ) {
            if (!move_does_nothing(
                    policy_container,
                    battle_state,
                    get_move_info(move),
                    who_defender_is
                )
            ) {
                throw std::runtime_error{"Usable move was not chosen"};
            }
        }
        best_move.defender_results.evaluated_move = attacker_moves[0];
        best_move.defender_results.hits_to_ko = std::nullopt;
        best_move.defender_results.line_size = 0;
        best_move.defender_results.total_damage = 0;
    }
    return best_move;
}

#endif //GEN_IV_BATTLE_FRONTIER_ANALYZER_MOVE_HEURISTIC_H
