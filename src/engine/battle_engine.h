#pragma once
#include <ranges>
#include <vector>

#include "battle_state.h"
#include "move_execution.h"
#include "move_heuristic.h"
#include "pokemon.h"
#include "policies.h"
#include "thread_pool.h"
#include "serebii_pokemon_data_source.h"

template <typename... Policies>
class BattleEngine {
public:
    const PolicyContainer<Policies...> policy_container;

    explicit BattleEngine(
        PolicyContainer<Policies...>&& policy_container_in
    ) : policy_container(std::move(policy_container_in)) {}
};

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
            PolicyContainer<
                NeverMissAccuracyEvasionFactorPolicy,
                OnlyOpponentCanUseLessAccurateMovesPolicy,
                OpponentOptimizedConfusionStatusPolicy,
                NeverConfuseRNGPolicy,
                NeverCritRNGPolicy,
                OpponentOptimizedRandomFactorPolicy,
                NeverFlinchRNGPolicy,
                NeverFreezeRNGPolicy,
                NeverParalyzeRNGPolicy,
                OpponentOptimizedKnowledgePolicy,
                OpponentOptimizedSpeedAdvantagePolicy,
                OpponentOptimizedStatChangePolicy,
                OpponentOptimizedBurnRNGPolicy,
                DebugLogging
            >{}
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

    auto battle_state = &path.back().battle_state;
    while (!battle_state->is_battle_over()) {
        const BestMoveResults player_move_results =
            choose_move_against_defender(
                battle_engine.policy_container,
                *battle_state,
                battle_state->player.get_moves(
                    battle_engine.policy_container.can_use_less_accurate_moves(
                        Who::Player
                    )
                ),
                Who::Player,
                std::nullopt,
                std::nullopt
            );
        if (player_move_results.attacker_results.move == Move::MoveCount) {
            throw std::runtime_error{"Player picked invalid move"};
        }

        const BestMoveResults opponent_move_results =
            choose_move_against_defender(
                battle_engine.policy_container,
                *battle_state,
                battle_state->opponent.get_moves(
                    battle_engine.policy_container.can_use_less_accurate_moves(
                        Who::Opponent
                    )
                ),
                Who::Opponent,
                std::nullopt,
                player_move_results.attacker_results
            );
        BattleState next_battle_state = *battle_state;
        auto turn_result =
            execute_turn(
                battle_engine.policy_container,
                next_battle_state,
                player_move_results.attacker_results.move,
                opponent_move_results.attacker_results.move
            );
        path.emplace_back(std::move(turn_result));
        battle_state = &path.back().battle_state;
    }

    if (battle_state->player.get_current_stat(Stat::Health) > 0) {
        won = true;
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

inline BattleResultEntry single_battle(
    const CustomPokemon& player_pokemon,
    const CustomPokemon& opponent_pokemon
) {
    return single_battle(
        std::array{player_pokemon, opponent_pokemon},
        std::array{player_pokemon, opponent_pokemon},
        0,
        1
    );
}
