#pragma once
#include <ranges>
#include <vector>

#include "battle_state.h"
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
    static_cast<int>(Move::Count)
>& all_move_infos = get_all_moves();


inline bool move_will_work(
    const BattleState& battle_state,
    const MoveInfo* move,
    const Who who_is_attacker
) {
    const bool is_player_attacker = who_is_attacker == Player;
    const auto move_type = move->type;

    const PokemonState* defender_state;
    if (is_player_attacker) {
        defender_state = &battle_state.opponent;
    } else {
        defender_state = &battle_state.player;
    }
    const CustomPokemon* defender = defender_state->pokemon;

    if (defender->ability == Ability::Levitate &&
        move_type == PokemonType::GROUND
    ) [[unlikely]] {
        return false;
    }

    return true;
}

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

inline void execute_moonlight(PokemonState& player, const Weather weather) {
    const uint16_t max_hp = player.pokemon->get_stat(Stat::HEALTH);
    uint16_t hp_gained;
    if (weather == None) [[likely]] {
        hp_gained = static_cast<uint16_t>(max_hp / 2);
    } else if (weather == Sun) {
        hp_gained = static_cast<uint16_t>(max_hp * 2 / 3);
    } else {
        hp_gained = static_cast<uint16_t>(max_hp / 4);
    }
    player.add_hp(hp_gained);
}

void roll_confusion(PokemonState& defender, int chance) {
    // TODO
}

void execute_power_move(
    PokemonState& attacker,
    PokemonState& defender,
    const MoveInfo* move
) {
    // TODO
}

inline void execute_move(
    BattleState& battle_state,
    const Who who,
    const MoveInfo* move
) {
    if (!move_will_work(battle_state, move, who)) {
        const bool is_player = who == Player;
        PokemonState& attacker = is_player
                                     ? battle_state.player
                                     : battle_state.opponent;
        PokemonState& defender = is_player
                                     ? battle_state.opponent
                                     : battle_state.player;
        if (move->move == Move::Moonlight) {
            execute_moonlight(attacker, battle_state.weather);
        } else if (move_has_flag(move->move, MoveFlag::HAS_POWER)) {
            execute_power_move(attacker, defender, move);
        }

        if (move_has_flag(move->move, MoveFlag::CONFUSES_DEFENDER_10)) {
            roll_confusion(defender, 10);
        }
    }
}

inline void apply_end_of_turn_1(PokemonState& pokemon_state) {
    // 1.0 Reflect wears off: "your team's reflect wore off"
    // 1.1 Light Screen wears off: "your team's light screen wore off"
    // 1.2 Mist wears off: "your team's mist wore off"
    // 1.3 Safeguard fades: "your team is no longer protected by safeguard"
    // 1.4 Tailwind ends: "your team's tailwind petered out"
    // 1.5 Lucky Chant: your team's lucky chant wore off"
}

inline void apply_end_of_turn_2(PokemonState& pokemon_state) {
    // 2.0 Wish: "pokemon's wish came true"
}

inline void apply_end_of_turn_3(PokemonState& pokemon_state) {
    // 3.0 Hail, Rain, Sandstorm, or Sun message
}

inline void apply_end_of_turn_4(PokemonState& pokemon_state) {
    // 4.0 Dry Skin, Hydration, Ice Body, Rain Dish
}

inline void apply_end_of_turn_5(PokemonState& pokemon_state) {
    // 5.0 Gravity
}

inline void apply_end_of_turn_6(PokemonState& pokemon_state) {
    const Item item = pokemon_state.current_item;

    // 6.0 Ingrain
    // 6.1 Aqua Ring
    // 6.2 Speed Boost, Shed Skin
    // 6.3 Black Sludge, Leftovers: "pokémon restored a little HP using its leftovers"
    if (item == Item::Leftovers) {
        const uint16_t hp_gained =
            std::max(
                static_cast<uint16_t>(1),
                static_cast<uint16_t>(
                    pokemon_state.pokemon->get_stat(Stat::HEALTH) / 16
                )
            );
        pokemon_state.add_hp(hp_gained);
    }
    // 6.4 Leech Seed: "pokémon's health is sapped by leech seed"
    // 6.5 Burn, Nightmare, Poison Heal, Poison: "pokémon is hurt by poison"
    // 6.6 Flame Orb activation, Toxic Orb activation
    // 6.7 Curse (from a Ghost)
    // 6.8 Bind, Clamp, Fire Spin, Magma Storm, Sand Tomb, Whirlpool, Wrap
    // 6.9 Bad Dreams Damage
    // 6.10 End of Outrage, Petal Dance, Thrash, Uproar: "pokémon caused an uproar" & "pokémon calmed down"
    // 6.11 Disable ends: "pokémon is no longer disabled"
    // 6.12 Encore ends
    // 6.13 Taunt wears off
    // 6.14 Magnet Rise
    // 6.15 Heal Block: "the foe pokémon's heal block wore off"
    // 6.16 Embargo
    // 6.17 Yawn
    // 6.18 Sticky Barb
}

inline void apply_end_of_turn_7(PokemonState& pokemon_state) {
    // 7.0 Doom Desire, Future Sight
}

inline void apply_end_of_turn_8(PokemonState& pokemon_state) {
    // 8.0 Perish Song
}

inline void apply_end_of_turn_9(PokemonState& pokemon_state) {
    // 9.0 Trick Room
}

inline void apply_end_of_turn_10(PokemonState& pokemon_state) {
    // 10.0 Pokemon is switched in (if previous Pokemon fainted)
    // 10.1 Toxic Spikes
    // 10.2 Spikes
    // 10.3 Stealth Rock
}

template <IsEffectPolicy T>
void apply_end_of_turn(const T& effect_policy, BattleState& battle_state) {
    auto& player = battle_state.player;
    auto& opponent = battle_state.opponent;
    const bool player_faster = effect_policy.is_player_faster(battle_state);
    auto& first_state = player_faster ? player : opponent;
    auto& second_state = player_faster ? opponent : player;

    apply_end_of_turn_1(first_state);
    apply_end_of_turn_1(second_state);

    apply_end_of_turn_2(first_state);
    apply_end_of_turn_2(second_state);

    apply_end_of_turn_3(first_state);
    apply_end_of_turn_3(second_state);

    apply_end_of_turn_4(first_state);
    apply_end_of_turn_4(second_state);

    apply_end_of_turn_5(first_state);
    apply_end_of_turn_5(second_state);

    apply_end_of_turn_6(first_state);
    apply_end_of_turn_6(second_state);

    apply_end_of_turn_7(first_state);
    apply_end_of_turn_7(second_state);

    apply_end_of_turn_8(first_state);
    apply_end_of_turn_8(second_state);

    apply_end_of_turn_9(first_state);
    apply_end_of_turn_9(second_state);

    apply_end_of_turn_10(first_state);
    apply_end_of_turn_10(second_state);
}

template <IsEffectPolicy T>
TurnResult execute_turn(
    const T& effect_policy,
    const BattleState& battle_state,
    const MoveInfo* player_move,
    const MoveInfo* opponent_move,
    const size_t parent_index
) {
    BattleState mutable_state = battle_state;

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

    execute_move(mutable_state, first, first_move);
    execute_move(mutable_state, second, second_move);
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

inline bool battle_over(const BattleState& battle_state) {
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
        .player_move_used = Move::Count,
        .player_move_damage = 0,
        .opponent_move_used = Move::Count,
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
                &all_move_infos.at(static_cast<int>(player_move));
            if (move_will_work(
                    battle_state,
                    player_move_info,
                    Player
                )
            ) {
                for (const auto& opponent_move : opponent_moves) {
                    const auto opponent_move_info =
                        &all_move_infos.at(static_cast<int>(opponent_move));
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
                            battle_engine.effect_policy,
                            battle_state,
                            player_move_info,
                            opponent_move_info,
                            path.size()
                        );


                        if (battle_over(turn_result.battle_state)) {
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
