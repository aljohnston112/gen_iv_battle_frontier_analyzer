#ifndef GEN_IV_BATTLE_FRONTIER_ANALYZER_MOVE_HEURISTIC_H
#define GEN_IV_BATTLE_FRONTIER_ANALYZER_MOVE_HEURISTIC_H

#include "policies.h"

struct BestMoveResult {
    Move move;
    uint16_t damage;
    uint16_t number_of_hits_to_ko;
    uint16_t total_damage;
};

struct BestMoveResults {
    BestMoveResult attacker_results;
    BestMoveResult defender_results;
};

template <typename... Policies>
BestMoveResults choose_move_against_defender(
    PolicyContainer<Policies...> policy_container,
    const BattleState& battle_state,
    const PokemonState& attacker,
    const std::vector<Move>& attacker_moves,
    const PokemonState& defender,
    Who who_attacker_is,
    std::optional<BestMoveResult> attacker_move_results,
    std::optional<BestMoveResult> defender_move_results
);

template <typename... Policies>
BestMoveResults get_best_power_move(
    const PolicyContainer<Policies...>& policy_container,
    const BattleState& battle_state,
    const PokemonState& attacker,
    const PokemonState& defender,
    const Who who_attacker_is,
    const std::vector<Move>& moves,
    const Category category,
    std::optional<BestMoveResult> attacker_move_results,
    std::optional<BestMoveResult> defender_move_results
) {
    if (attacker_move_results.has_value() &&
        defender_move_results.has_value()
    ) {
        return {
            .attacker_results = *attacker_move_results,
            .defender_results = *defender_move_results
        };
    }

    const auto& all_move_infos =
        get_all_moves();
    auto best = BestMoveResult{
        Move::MoveCount,
        0,
        UINT16_MAX,
        0
    };
    const Who who_defender_is =
        who_attacker_is == Who::Player
            ? Who::Opponent
            : Who::Player;
    if (!defender_move_results.has_value()) {
        defender_move_results =
            choose_move_against_defender(
                policy_container,
                battle_state,
                defender,
                defender.get_moves(),
                attacker,
                who_defender_is,
                defender_move_results,
                best
            ).attacker_results;
    }
    BestMoveResult best_defender_move = *defender_move_results;
    int64_t diff = best_defender_move.number_of_hits_to_ko - UINT16_MAX -
        UINT16_MAX;

    const uint16_t defender_hp = defender.get_current_stat(Stat::Health);
    for (const auto move : moves) {
        const auto& move_info = &all_move_infos[to_int(move)];
        if (move_info->category == category) {
            uint16_t damage = get_damage_of_power_move(
                policy_container,
                battle_state,
                attacker,
                defender,
                move_info,
                who_attacker_is
            );
            uint16_t hits_to_ko = static_cast<uint16_t>(
                std::ceil(static_cast<double>(defender_hp) / damage)
            );
            uint16_t total_damage = damage * hits_to_ko;
            BestMoveResult current_move_result = {
                .move = move,
                .damage = damage,
                .number_of_hits_to_ko = hits_to_ko,
                .total_damage = total_damage
            };

            if (who_attacker_is == Who::Opponent) {
                if (move_has_flag(
                        move,
                        MoveFlag::LOWERS_DEFENDER_SPECIAL_DEFENSE_ONE_STAGE_10)
                ) [[unlikely]] {
                    BattleState temp_battle_state = battle_state;
                    PokemonState& temp_defender = temp_battle_state.player;
                    hits_to_ko = 1;
                    total_damage = execute_move(
                        policy_container,
                        temp_battle_state,
                        Who::Opponent,
                        move_info
                    );
                    damage = total_damage;
                    while (temp_defender.get_current_stat(Stat::Health) > 0) {
                        ++hits_to_ko;
                        total_damage += execute_move(
                            policy_container,
                            temp_battle_state,
                            Who::Opponent,
                            move_info
                        );
                    }
                }
                current_move_result = {
                    .move = move,
                    .damage = damage,
                    .number_of_hits_to_ko = hits_to_ko,
                    .total_damage = total_damage
                };
            }
            BestMoveResults temp_best_defender_move_results =
                choose_move_against_defender(
                    policy_container,
                    battle_state,
                    defender,
                    defender.get_moves(),
                    attacker,
                    Who::Player,
                    defender_move_results,
                    current_move_result
                );
            const auto temp_best_defender_move =
                temp_best_defender_move_results.attacker_results;
            uint16_t defender_hits =
                temp_best_defender_move.number_of_hits_to_ko;
            const auto temp_best_attacker_move_result =
                temp_best_defender_move_results.defender_results;
            const int64_t new_diff = defender_hits -
                temp_best_attacker_move_result.number_of_hits_to_ko;
            if (new_diff > diff) {
                best = temp_best_attacker_move_result;
                diff = new_diff;
                best_defender_move = temp_best_defender_move;
            }
        }
    }
    return {
        .attacker_results = best,
        .defender_results = best_defender_move
    };
}

template <typename... Policies>
BestMoveResults get_best_power_move(
    const PolicyContainer<Policies...>& policy_container,
    const BattleState& battle_state,
    const PokemonState& attacker,
    const PokemonState& defender,
    const std::vector<Move>& moves,
    const Who who_attacker_is,
    std::optional<BestMoveResult> attacker_move_results,
    std::optional<BestMoveResult> defender_move_results
) {
    if (attacker_move_results.has_value() &&
        defender_move_results.has_value()
    ) {
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
                defender,
                defender.get_moves(),
                attacker,
                who_defender_is,
                defender_move_results,
                best_move_result
            );
        return {
            .attacker_results = best_move_result,
            .defender_results = defender_power_move.attacker_results
        };
    }

    const BestMoveResults best_physical =
        get_best_power_move(
            policy_container,
            battle_state,
            attacker,
            defender,
            who_attacker_is,
            moves,
            Category::PHYSICAL,
            std::nullopt,
            defender_move_results
        );
    const BestMoveResults best_special =
        get_best_power_move(
            policy_container,
            battle_state,
            attacker,
            defender,
            who_attacker_is,
            moves,
            Category::SPECIAL,
            std::nullopt,
            defender_move_results
        );
    const uint16_t physical_hits_taken =
        best_physical.defender_results.number_of_hits_to_ko;
    const uint16_t physical_hits_given =
        best_physical.attacker_results.number_of_hits_to_ko;
    const int32_t physical_diff = physical_hits_taken - physical_hits_given;
    const uint16_t special_hits_taken =
        best_special.defender_results.number_of_hits_to_ko;
    const uint16_t special_hits_given =
        best_special.attacker_results.number_of_hits_to_ko;
    const int32_t special_diff = special_hits_taken - special_hits_given;
    if (physical_diff > special_diff) {
        return best_physical;
    }
    return best_special;
}

template <typename... Policies>
BestMoveResults get_move_results_for_when_defender_lowers_special_attack(
    const PolicyContainer<Policies...>& policy_container,
    const BattleState& battle_state,
    const Who who_attacker_is
) {
    BattleState temp_battle_state = battle_state;
    const bool attacker_is_player = who_attacker_is == Who::Player;
    PokemonState& temp_attacker =
        attacker_is_player
            ? temp_battle_state.player
            : temp_battle_state.opponent;
    PokemonState& temp_defender =
        attacker_is_player
            ? temp_battle_state.opponent
            : temp_battle_state.player;
    const bool is_player_faster =
        policy_container.is_player_faster(battle_state);
    bool attack_dropped = false;
    if (!(is_player_faster && attacker_is_player)) {
        temp_attacker.decrease_stat_stage(Stat::SpecialAttack, 1);
        attack_dropped = true;
    }
    BestMoveResults temp_best_power_move = get_best_power_move(
        policy_container,
        temp_battle_state,
        temp_attacker,
        temp_defender,
        temp_attacker.get_moves(),
        who_attacker_is,
        std::nullopt,
        std::nullopt
    );
    execute_move(
        policy_container,
        temp_battle_state,
        who_attacker_is,
        get_move_info(temp_best_power_move.attacker_results.move)
    );

    BestMoveResults best_move_results = {};
    best_move_results.attacker_results.move =
        temp_best_power_move.attacker_results.move;
    best_move_results.attacker_results.damage =
        temp_best_power_move.attacker_results.damage;
    best_move_results.attacker_results.total_damage =
        temp_best_power_move.attacker_results.damage;
    best_move_results.attacker_results.number_of_hits_to_ko = 1;

    best_move_results.defender_results.move =
        temp_best_power_move.defender_results.move;
    best_move_results.defender_results.damage =
        temp_best_power_move.defender_results.damage;
    best_move_results.defender_results.total_damage =
        temp_best_power_move.defender_results.damage;
    best_move_results.defender_results.number_of_hits_to_ko = 1;
    if (!attack_dropped) {
        temp_attacker.decrease_stat_stage(Stat::SpecialAttack, 1);
    }

    while (temp_defender.get_current_stat(Stat::Health) > 0) {
        attack_dropped = false;
        if (!(is_player_faster && attacker_is_player)) {
            temp_attacker.decrease_stat_stage(Stat::SpecialAttack, 1);
            attack_dropped = true;
        }
        temp_best_power_move = get_best_power_move(
            policy_container,
            temp_battle_state,
            temp_attacker,
            temp_defender,
            temp_attacker.get_moves(),
            who_attacker_is,
            std::nullopt,
            std::nullopt
        );
        execute_move(
            policy_container,
            temp_battle_state,
            who_attacker_is,
            get_move_info(temp_best_power_move.attacker_results.move)
        );
        best_move_results.attacker_results.move =
            temp_best_power_move.attacker_results.move;
        best_move_results.attacker_results.total_damage +=
            temp_best_power_move.attacker_results.damage;
        best_move_results.attacker_results.number_of_hits_to_ko++;

        best_move_results.defender_results.move =
            temp_best_power_move.defender_results.move;
        best_move_results.defender_results.total_damage +=
            temp_best_power_move.defender_results.damage;
        best_move_results.defender_results.number_of_hits_to_ko++;

        if (!attack_dropped) {
            temp_attacker.decrease_stat_stage(Stat::SpecialAttack, 1);
        }
    }
    return best_move_results;
}

template <typename... Policies>
BestMoveResults choose_move_against_defender(
    const PolicyContainer<Policies...>& policy_container,
    const BattleState& battle_state,
    const PokemonState& attacker,
    const std::vector<Move>& attacker_moves,
    const PokemonState& defender,
    const Who who_attacker_is,
    std::optional<BestMoveResult> attacker_move_results,
    std::optional<BestMoveResult> defender_move_results
) {
    if (attacker_move_results.has_value() &&
        defender_move_results.has_value()
    ) {
        return {
            .attacker_results = *attacker_move_results,
            .defender_results = *defender_move_results
        };
    }
    BestMoveResults best_power_move = get_best_power_move(
        policy_container,
        battle_state,
        attacker,
        defender,
        attacker_moves,
        who_attacker_is,
        attacker_move_results,
        defender_move_results
    );
    if (!defender_move_results.has_value()) {
        defender_move_results = best_power_move.defender_results;
    }
    // TODO If defender uses a move that lowers the attacker's attack,
    // expected total damage is lower

    if (who_attacker_is == Who::Player &&
        move_has_flag(
            defender_move_results->move,
            MoveFlag::LOWERS_DEFENDER_SPECIAL_ATTACK_ONE_STAGE_50) &&
        get_move_info(best_power_move.attacker_results.move)->category ==
        Category::SPECIAL
    )[[unlikely]] {
        best_power_move =
            get_move_results_for_when_defender_lowers_special_attack(
                policy_container,
                battle_state,
                who_attacker_is
            );
    }
    return best_power_move;
}

#endif //GEN_IV_BATTLE_FRONTIER_ANALYZER_MOVE_HEURISTIC_H
