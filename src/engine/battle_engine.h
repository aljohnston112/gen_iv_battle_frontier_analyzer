#pragma once
#include <ranges>
#include <vector>

#include "battle_state.h"
#include "end_of_turn_effects.h"
#include "move_execution.h"
#include "move_heuristic.h"
#include "pokemon.h"
#include "policies.h"
#include "thread_pool.h"
#include "serebii_pokemon_data_source.h"

template <
    IsConfusionStatusPolicy ConfusionStatusPolicy,
    IsConfusionStatusRNGPolicy ConfusionStatusRNGPolicy,
    IsCritRNGPolicy CritRNGPolicy,
    IsDamageRandomFactorPolicy DamageRandomFactorPolicy,
    IsFreezeRNGPolicy FreezeRNGPolicy,
    IsOpponentKnowledgePolicy OpponentKnowledgePolicy,
    IsSpeedAdvantagePolicy SpeedAdvantagePolicy,
    IsStatChangePolicy StatChangePolicy
>
class BattleEngine {
public:
    const PolicyContainer<
        ConfusionStatusPolicy,
        ConfusionStatusRNGPolicy,
        CritRNGPolicy,
        DamageRandomFactorPolicy,
        FreezeRNGPolicy,
        OpponentKnowledgePolicy,
        SpeedAdvantagePolicy,
        StatChangePolicy
    > policy_container;
    ConfusionStatusPolicy confusion_status_policy;
    ConfusionStatusRNGPolicy confusion_status_rng_policy;
    CritRNGPolicy crit_rng_policy;
    DamageRandomFactorPolicy damage_random_factor_policy;
    FreezeRNGPolicy freeze_rng_policy;
    OpponentKnowledgePolicy opponent_knowledge_policy;
    SpeedAdvantagePolicy speed_advantage_policy;
    StatChangePolicy stat_change_policy;

    explicit BattleEngine(
        const PolicyContainer<
            ConfusionStatusPolicy,
            ConfusionStatusRNGPolicy,
            CritRNGPolicy,
            DamageRandomFactorPolicy,
            FreezeRNGPolicy,
            OpponentKnowledgePolicy,
            SpeedAdvantagePolicy,
            StatChangePolicy
        >&& policy_container_in
    ) : policy_container(std::move(policy_container_in)),
        confusion_status_policy(policy_container.confusion_status_policy),
        confusion_status_rng_policy(
            policy_container.confusion_status_rng_policy),
        crit_rng_policy(policy_container.crit_rng_policy),
        damage_random_factor_policy(
            policy_container.damage_random_factor_policy),
        freeze_rng_policy(policy_container.freeze_rng_policy),
        opponent_knowledge_policy(policy_container.opponent_knowledge_policy),
        speed_advantage_policy(policy_container.speed_advantage_policy),
        stat_change_policy(policy_container.stat_change_policy) {}
};

template <IsSpeedAdvantagePolicy SpeedAdvantagePolicy>
Who who_goes_first(
    const SpeedAdvantagePolicy& speed_advantage_policy,
    const BattleState& battle_state,
    [[maybe_unused]] const MoveInfo* player_move,
    [[maybe_unused]] const MoveInfo* opponent_move
) {
    const bool player_faster =
        speed_advantage_policy.is_player_faster(battle_state);
    if (player_faster) {
        return Who::Player;
    } else {
        return Who::Opponent;
    }
}

template <
    IsConfusionStatusPolicy ConfusioStatusPolicy,
    IsConfusionStatusRNGPolicy ConfusionStatusRNGPolicy,
    IsCritRNGPolicy CritRNGPolicy,
    IsDamageRandomFactorPolicy DamageRandomFactorPolicy,
    IsFreezeRNGPolicy FreezeRNGPolicy,
    IsOpponentKnowledgePolicy OpponentKnowledgePolicy,
    IsSpeedAdvantagePolicy SpeedAdvantagePolicy,
    IsStatChangePolicy StatChangePolicy
>
TurnResult execute_turn(
    const PolicyContainer<
        ConfusioStatusPolicy,
        ConfusionStatusRNGPolicy,
        CritRNGPolicy,
        DamageRandomFactorPolicy,
        FreezeRNGPolicy,
        OpponentKnowledgePolicy,
        SpeedAdvantagePolicy,
        StatChangePolicy
    >& policy_container,
    BattleState& battle_state,
    const MoveInfo* player_move,
    const MoveInfo* opponent_move
) {
    const bool player_goes_first =
        who_goes_first(
            policy_container.speed_advantage_policy,
            battle_state,
            player_move,
            opponent_move
        ) == Who::Player;
    const Who first = player_goes_first ? Who::Player : Who::Opponent;
    const Who second = player_goes_first ? Who::Opponent : Who::Player;
    const MoveInfo* first_move =
        player_goes_first ? player_move : opponent_move;
    const MoveInfo* second_move = player_goes_first
                                      ? opponent_move
                                      : player_move;

    const uint16_t first_move_damage =
        execute_move(
            policy_container.confusion_status_policy,
            policy_container.confusion_status_rng_policy,
            policy_container.crit_rng_policy,
            policy_container.damage_random_factor_policy,
            policy_container.freeze_rng_policy,
            policy_container.stat_change_policy,
            battle_state,
            first,
            first_move
        );
    const uint16_t second_move_damage =
        execute_move(
            policy_container.confusion_status_policy,
            policy_container.confusion_status_rng_policy,
            policy_container.crit_rng_policy,
            policy_container.damage_random_factor_policy,
            policy_container.freeze_rng_policy,
            policy_container.stat_change_policy,
            battle_state,
            second,
            second_move
        );
    apply_end_of_turn(policy_container.speed_advantage_policy, battle_state);

    return TurnResult{
        .battle_state = battle_state,
        .player_move_used = player_move->move,
        .player_move_damage =
        player_goes_first ? first_move_damage : second_move_damage,
        .opponent_move_used = opponent_move->move,
        .opponent_move_damage =
        player_goes_first ? second_move_damage : first_move_damage,
    };
}

inline bool is_battle_over(const BattleState& battle_state) {
    return battle_state.player.get_current_stat(Stat::Health) == 0 ||
        battle_state.opponent.get_current_stat(Stat::Health) == 0;
}

inline BattleResultEntry single_battle(
    const std::span<const CustomPokemon>& all_player_pokemon,
    const std::span<const CustomPokemon>& all_opponent_pokemon,
    const size_t player_index,
    const size_t opponent_index
) {
    const auto& player_pokemon = all_player_pokemon[player_index];
    const auto& opponent_pokemon = all_opponent_pokemon[opponent_index];

    verify_abilities_implemented(
        player_pokemon.ability,
        opponent_pokemon.ability
    );
    verify_items_implemented(
        player_pokemon.item,
        opponent_pokemon.item
    );

    verify_moves_implemented(
        player_pokemon.moves,
        opponent_pokemon.moves
    );

    const BattleEngine battle_engine{
        std::move(
            PolicyContainer{
                .confusion_status_policy =
                OpponentOptimizedConfusionStatusPolicy{},
                .confusion_status_rng_policy = NeverConfuseRNGPolicy{},
                .crit_rng_policy = NeverCritRNGPolicy{},
                .damage_random_factor_policy =
                OpponentOptimizedRandomFactorPolicy{},
                .freeze_rng_policy = NeverFreezeRNGPolicy{},
                .opponent_knowledge_policy =
                OpponentOptimizedKnowledgePolicy{},
                .speed_advantage_policy =
                OpponentOptimizedSpeedAdvantagePolicy{},
                .stat_change_policy = OpponentOptimizedStatChangePolicy{}
            }
        ),
    };

    bool won = false;
    std::deque<TurnResult> path{};
    path.emplace_back(
        TurnResult{
            .battle_state = BattleState{
                PokemonState{&player_pokemon},
                PokemonState{&opponent_pokemon}
            },
            .player_move_used = Move::MoveCount,
            .player_move_damage = 0,
            .opponent_move_used = Move::MoveCount,
            .opponent_move_damage = 0
        }
    );

    const auto& all_move_infos =
        get_all_moves();

    auto* battle_state = &path.back().battle_state;
    while (!is_battle_over(*battle_state)) {
        const BestMoveResults player_move_results =
            choose_move_against_defender(
                battle_engine.confusion_status_policy,
                battle_engine.confusion_status_rng_policy,
                battle_engine.crit_rng_policy,
                battle_engine.damage_random_factor_policy,
                battle_engine.freeze_rng_policy,
                battle_engine.stat_change_policy,
                *battle_state,
                battle_state->player,
                battle_state->player.get_moves(),
                battle_state->opponent,
                Who::Player,
                std::nullopt,
                std::nullopt
            );
        const BestMoveResults opponent_move_results =
            choose_move_against_defender(
                battle_engine.confusion_status_policy,
                battle_engine.confusion_status_rng_policy,
                battle_engine.crit_rng_policy,
                battle_engine.damage_random_factor_policy,
                battle_engine.freeze_rng_policy,
                battle_engine.stat_change_policy,
                *battle_state,
                battle_state->opponent,
                battle_state->opponent.get_moves(),
                battle_state->player,
                Who::Opponent,
                std::nullopt,
                player_move_results.attacker_results
            );
        auto turn_result =
            execute_turn(
                battle_engine.policy_container,
                *battle_state,
                &all_move_infos[
                    to_int(player_move_results.attacker_results.move)
                ],
                &all_move_infos[
                    to_int(opponent_move_results.attacker_results.move)
                ]
            );
        path.emplace_back(std::move(turn_result));
        battle_state = &path.back().battle_state;
    }

    return BattleResultEntry{
        player_index,
        opponent_index,
        won,
        std::move(
            std::vector<TurnResult>{
                path.begin(),
                path.end()
            }
        )
    };
}
