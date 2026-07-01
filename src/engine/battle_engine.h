#pragma once
#include <ranges>
#include <vector>

#include "battle_state.h"
#include "end_of_turn_effects.h"
#include "move_execution.h"
#include "pokemon.h"
#include "policies.h"
#include "thread_pool.h"
#include "serebii_pokemon_data_source.h"

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

template <IsEffectPolicy T>
Who who_goes_first(
    const T& effect_policy,
    const BattleState& battle_state,
    const MoveInfo* player_move,
    const MoveInfo* opponent_move
) {
    const bool player_faster = effect_policy.is_player_faster(battle_state);
    if (player_faster) {
        return Who::Player;
    } else {
        return Who::Opponent;
    }
}

template <IsEffectPolicy T, IsRNGPolicy R>
TurnResult execute_turn(
    const PolicyContainer<T, R>& policy_container,
    BattleState& battle_state,
    const MoveInfo* player_move,
    const MoveInfo* opponent_move,
    const size_t parent_index
) {
    const T& effect_policy = policy_container.effect_policy;
    const R& rng_policy = policy_container.rng_policy;
    const bool player_goes_first =
        who_goes_first(effect_policy, battle_state, player_move,
                       opponent_move) == Who::Player;
    const Who first = player_goes_first ? Who::Player : Who::Opponent;
    const Who second = player_goes_first ? Who::Opponent : Who::Player;
    const MoveInfo* first_move =
        player_goes_first ? player_move : opponent_move;
    const MoveInfo* second_move = player_goes_first
                                      ? opponent_move
                                      : player_move;

    const uint16_t first_move_damage =
        execute_move(
            effect_policy,
            rng_policy,
            battle_state,
            first,
            first_move
        );
    const uint16_t second_move_damage =
        execute_move(
            effect_policy,
            rng_policy,
            battle_state,
            second,
            second_move
        );
    apply_end_of_turn(effect_policy, battle_state);

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

struct BestMoveResult {
    Move move;
    uint16_t damage;
    uint16_t number_of_hits_to_ko;
    uint16_t total_damage;
};

template <IsEffectPolicy E, IsRNGPolicy R>
BestMoveResult get_best_special_move(
    const E& effect_policy,
    const R& rng_policy,
    const BattleState& battle_state,
    const std::vector<Move>& moves,
    const Who who_is_picking
) {
    const auto& all_move_infos =
        get_all_moves();

    auto best = BestMoveResult{
        Move::MoveCount,
        0,
        UINT16_MAX,
        0
    };

    const auto defender = who_is_picking == Who::Player
                              ? battle_state.opponent
                              : battle_state.player;
    const uint16_t defender_hp = defender.get_current_stat(Stat::Health);

    for (const auto move : moves) {
        const auto& move_info = &all_move_infos[to_int(move)];
        if (move_info->category == Category::SPECIAL) {
            const uint16_t damage = get_damage_of_power_move(
                effect_policy,
                rng_policy,
                battle_state,
                move_info,
                who_is_picking
            );
            uint16_t hits_to_ko;
            uint16_t total_damage;

            if (who_is_picking == Who::Opponent) {
                if (move_has_flag(
                        move,
                        MoveFlag::LOWERS_DEFENDER_SPECIAL_DEFENSE_ONE_STAGE_10)
                ) [[unlikely]] {
                    BattleState temp_battle_state = battle_state;
                    PokemonState& temp_defender = temp_battle_state.player;
                    hits_to_ko = 1;
                    total_damage = execute_move(
                        effect_policy,
                        rng_policy,
                        temp_battle_state,
                        who_is_picking,
                        move_info
                    );
                    while (temp_defender.get_current_stat(Stat::Health) > 0) {
                        hits_to_ko++;
                        total_damage += execute_move(
                            effect_policy,
                            rng_policy,
                            temp_battle_state,
                            who_is_picking,
                            move_info
                        );
                    }
                }
            } else {
                hits_to_ko =
                    std::ceil(static_cast<double>(defender_hp) / damage);
                total_damage = damage * hits_to_ko;
            }

            if (hits_to_ko < best.number_of_hits_to_ko ||
                (hits_to_ko == best.number_of_hits_to_ko && damage &&
                    damage > best.damage)
            ) {
                best.move = move;
                best.damage = damage;
                best.number_of_hits_to_ko = hits_to_ko;
                best.total_damage = total_damage;
            }
        }
    }
    return best;
}

template <IsEffectPolicy E, IsRNGPolicy R>
Move choose_move_against_defender(
    const E& effect_policy,
    const R& rng_policy,
    const BattleState& battle_state,
    const Who who_is_picking
) {
    const std::vector<Move>& moves =
        who_is_picking == Who::Player
            ? battle_state.player.get_moves()
            : battle_state.opponent.get_moves();
    BestMoveResult best_special = get_best_special_move(
        effect_policy,
        rng_policy,
        battle_state,
        moves,
        who_is_picking
    );


    return best_special.move;
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

    const BattleEngine battle_engine{
        std::move(PolicyContainer{
            .effect_policy = OpponentOptimizedEffectPolicy{},
            .rng_policy = FalseRNGPolicy{}
        }),
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
        const Move player_move =
            choose_move_against_defender(
                battle_engine.effect_policy,
                battle_engine.rng_policy,
                *battle_state,
                Who::Player
            );
        const Move opponent_move =
            choose_move_against_defender(
                battle_engine.effect_policy,
                battle_engine.rng_policy,
                *battle_state,
                Who::Opponent
            );
        auto turn_result =
            execute_turn(
                battle_engine.policy_container,
                *battle_state,
                &all_move_infos[to_int(player_move)],
                &all_move_infos[to_int(opponent_move)],
                path.size()
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
