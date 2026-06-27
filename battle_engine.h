#pragma once
#include <ranges>
#include <vector>

#include "battle_state.h"
#include "end_of_turn_effects.h"
#include "move_execution.h"
#include "pokemon.h"
#include "policies.h"
#include "thread_pool.h"
#include "serebii/serebii_pokemon_data_source.h"

template <IsEffectPolicy E, IsRNGPolicy R>
class BattleEngine {
public:
    const PolicyContainer<E, R> policy_container;
    const E& effect_policy;
    const R& rng_policy;

    explicit BattleEngine(
        const PolicyContainer<E, R>&& policy_container_in
    ) : policy_container(std::move(policy_container_in)),
        effect_policy(policy_container.effect_policy),
        rng_policy(policy_container.rng_policy) {}
};

inline const std::array<
    MoveInfo,
    MoveCount
>& all_move_infos = get_all_moves();

template <IsEffectPolicy T>
Who who_goes_first(
    const T& effect_policy,
    const BattleState& battle_state,
    const MoveInfo* player_move,
    const MoveInfo* opponent_move
) {
    const bool player_faster = effect_policy.is_player_faster(battle_state);
    if (player_faster) {
        return Player;
    } else {
        return Opponent;
    }
}

template <IsEffectPolicy T, IsRNGPolicy R>
TurnResult execute_turn(
    const PolicyContainer<T, R>& policy_container,
    const BattleState& battle_state,
    const MoveInfo* player_move,
    const MoveInfo* opponent_move,
    const size_t parent_index
) {
    BattleState mutable_state = battle_state;
    T effect_policy = policy_container.effect_policy;
    R rng_policy = policy_container.rng_policy;
    const bool player_goes_first =
        who_goes_first(effect_policy, battle_state, player_move,
                       opponent_move) == Player;
    const Who first = player_goes_first ? Player : Opponent;
    const Who second = player_goes_first ? Opponent : Player;
    const MoveInfo* first_move =
        player_goes_first ? player_move : opponent_move;
    const MoveInfo* second_move = player_goes_first
                                      ? opponent_move
                                      : player_move;

    execute_move(rng_policy, mutable_state, first, first_move);
    execute_move(rng_policy, mutable_state, second, second_move);
    apply_end_of_turn(effect_policy, mutable_state);

    return TurnResult{
        .battle_state = battle_state,
        .player_move_used = player_move->move,
        .player_move_damage = 0,
        .opponent_move_used = opponent_move->move,
        .opponent_move_damage = 0,
        .parent_index = parent_index
    };
}

inline bool is_battle_over(const BattleState& battle_state) {
    return true;
}

inline void update_best(
    const std::deque<TurnResult>& path,
    std::deque<TurnResult>& best
) {
    if (path.size() > best.size() ||
        (!path.empty() && path.back().battle_state.opponent.current_hp > 0)
    ) {
        return;
    }

    if (path.size() < best.size() ||
        (!path.empty() &&
            path.back().player_move_damage < best.back().player_move_damage)
    ) {
        best.clear();
        best.append_range(path);
    }

    // TODO tie breaker?
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

    BattleEngine battle_engine{
        std::move(PolicyContainer{
            .effect_policy = OpponentOptimizedEffectPolicy{},
            .rng_policy = NoRNGPolicy{}
        }),
    };

    bool won = false;
    std::deque<TurnResult> best_battle{};
    std::deque<TurnResult> path{};
    std::deque<TurnResult> children{};

    children.emplace_back(std::move(TurnResult{
        .battle_state = BattleState{
            PokemonState{&player_pokemon},
            PokemonState{&opponent_pokemon}
        },
        .player_move_used = MoveCount,
        .player_move_damage = 0,
        .opponent_move_used = MoveCount,
        .opponent_move_damage = 0,
        .parent_index = 0
    }));

    while (!children.empty()) {
        const auto& next = children.back();
        children.pop_back();

        size_t parent_index = next.parent_index;
        path.emplace_back(std::move(next));

        while (path.size() - 1 > parent_index) {
            path.pop_back();
        }
        const TurnResult& current = path.back();

        const auto& battle_state = current.battle_state;
        const std::vector<Move>& player_moves =
            battle_state.player.pokemon->moves;
        const std::vector<Move>& opponent_moves =
            battle_state.opponent.pokemon->moves;
        verify_moves_implemented(player_moves, opponent_moves);

        for (const auto& player_move : player_moves) {
            const auto player_move_info =
                &all_move_infos.at(player_move);
            if (move_will_work(
                    battle_state,
                    player_move_info,
                    Player
                )
            ) {
                for (const auto& opponent_move : opponent_moves) {
                    const auto opponent_move_info =
                        &all_move_infos.at(opponent_move);
                    if (path.size() >= best_battle.size()) {
                        continue;
                    }

                    if (move_will_work(
                            battle_state,
                            opponent_move_info,
                            Opponent
                        )
                    ) {
                        auto turn_result = execute_turn(
                            battle_engine.policy_container,
                            battle_state,
                            player_move_info,
                            opponent_move_info,
                            path.size()
                        );

                        if (is_battle_over(turn_result.battle_state)) {
                            path.emplace_back(std::move(turn_result));
                            update_best(path, best_battle);

                            continue;
                        }
                        children.emplace_back(std::move(turn_result));
                    }
                }
            }
        }
    }
    return BattleResultEntry{
        player_index,
        opponent_index,
        won,
        std::move(
            std::vector<TurnResult>{
                best_battle.begin(),
                best_battle.end()
            }
        )
    };
}
