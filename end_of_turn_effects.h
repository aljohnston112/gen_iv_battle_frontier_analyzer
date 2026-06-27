#ifndef GEN_IV_BATTLE_FRONTIER_ANALYZER_END_OF_TURN_EFFECTS_H
#define GEN_IV_BATTLE_FRONTIER_ANALYZER_END_OF_TURN_EFFECTS_H

#include "battle_state.h"
#include "policies.h"

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
    if (item == Leftovers) {
        const uint16_t hp_gained =
            std::max(
                static_cast<uint16_t>(1),
                static_cast<uint16_t>(
                    pokemon_state.pokemon->get_stat(Health) / 16
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

#endif //GEN_IV_BATTLE_FRONTIER_ANALYZER_END_OF_TURN_EFFECTS_H
