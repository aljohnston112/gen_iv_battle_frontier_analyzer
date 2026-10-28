#ifndef GEN_IV_BATTLE_FRONTIER_ANALYZER_END_OF_TURN_EFFECTS_H
#define GEN_IV_BATTLE_FRONTIER_ANALYZER_END_OF_TURN_EFFECTS_H

#include "battle_state.h"
#include "battle_state_proxy.h"
#include "policies.h"

inline void apply_end_of_turn_1([[maybe_unused]] PokemonState& pokemon_state) {
    // 1.0 Reflect wears off: "your team's reflect wore off"
    // 1.1 Light Screen wears off: "your team's light screen wore off"
    if (pokemon_state.has_status_with_stage(StatusWithStage::LightScreening)) {
        pokemon_state.decrement_status_with_stage_value(
            StatusWithStage::LightScreening
        );
    }
    // 1.2 Mist wears off: "your team's mist wore off"
    // 1.3 Safeguard fades: "your team is no longer protected by safeguard"
    // 1.4 Tailwind ends: "your team's tailwind petered out"
    // 1.5 Lucky Chant: your team's lucky chant wore off"
}

inline void apply_end_of_turn_2([[maybe_unused]] PokemonState& pokemon_state) {
    // 2.0 Wish: "pokemon's wish came true"
}

template <typename... Policies>
void apply_end_of_turn_3(
    const PolicyContainer<Policies...>& policy_container,
    const BattleState& battle_state,
    PokemonState& pokemon_state,
    const Who who
) {
    // 3.0 Hail, Rain, Sandstorm, or Sun message
    if (battle_state.has_weather(Weather::Hail) &&
        !pokemon_state.has_type(PokemonType::Ice)
    ) {
        try_apply_damage_to_pokemon_state(
            policy_container,
            pokemon_state,
            who,
            pokemon_state.get_original_stat(Stat::Health) / 16,
            DamageSource::Weather
        );
    }
}

inline void apply_end_of_turn_4([[maybe_unused]] PokemonState& pokemon_state) {
    // 4.0 Dry Skin, Hydration, Ice Body, Rain Dish
}

inline void apply_end_of_turn_5([[maybe_unused]] PokemonState& pokemon_state) {
    // 5.0 Gravity
}

template <typename... Policies>
void apply_end_of_turn_6(
    const PolicyContainer<Policies...>& policy_container,
    PokemonState& pokemon_state,
    const Who who
) {
    const Item item = pokemon_state.get_current_item_for_effect();
    const bool ko = pokemon_state.get_current_stat(Stat::Health) == 0;
    const uint16_t max_hp = pokemon_state.get_original_stat(Stat::Health);

    // 6.0 Ingrain
    // 6.1 Aqua Ring
    // 6.2 Speed Boost, Shed Skin
    // 6.3 Black Sludge, Leftovers: "pokémon restored a little HP using its leftovers"
    if (!ko && item == Item::Leftovers) {
        const uint16_t hp_gained =
            std::max(
                static_cast<uint16_t>(1),
                static_cast<uint16_t>(max_hp / 16)
            );
        pokemon_state.add_hp(hp_gained);
    }
    // 6.4 Leech Seed: "pokémon's health is sapped by leech seed"
    // 6.5 Burn, Nightmare, Poison Heal, Poison: "pokémon is hurt by poison"
    if (pokemon_state.has_status_condition(StatusCondition::Burn)) {
        try_apply_damage_to_pokemon_state(
            policy_container,
            pokemon_state,
            who,
            max_hp / 8,
            DamageSource::Burn
        );
    }
    if (pokemon_state.has_status_condition(StatusCondition::BadlyPoisoned)) {
        const uint8_t n =
            pokemon_state.get_status_stage(StatusWithStage::BadlyPoisoned);
        try_apply_damage_to_pokemon_state(
            policy_container,
            pokemon_state,
            who,
            static_cast<int16_t>(n * (max_hp / 16)),
            DamageSource::BadPoison
        );
        pokemon_state.set_status_with_stage(
            StatusWithStage::BadlyPoisoned,
            static_cast<uint8_t>(n + 1)
        );
    }
    // 6.6 Flame Orb activation, Toxic Orb activation
    // 6.7 Curse (from a Ghost)
    if (pokemon_state.has_status(Status::Cursed)) {
        try_apply_damage_to_pokemon_state(
            policy_container,
            pokemon_state,
            who,
            max_hp / 4,
            DamageSource::CurseStatus
        );
    }
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

inline void apply_end_of_turn_7([[maybe_unused]] PokemonState& pokemon_state) {
    // 7.0 Doom Desire, Future Sight
}

inline void apply_end_of_turn_8([[maybe_unused]] PokemonState& pokemon_state) {
    // 8.0 Perish Song
}

inline void apply_end_of_turn_9([[maybe_unused]] PokemonState& pokemon_state) {
    // 9.0 Trick Room
}

inline void apply_end_of_turn_10([[maybe_unused]] PokemonState& pokemon_state) {
    // 10.0 Pokemon is switched in (if previous Pokemon fainted)
    // 10.1 Toxic Spikes
    // 10.2 Spikes
    // 10.3 Stealth Rock
}

template <typename... Policies>
void apply_end_of_turn(
    const PolicyContainer<Policies...>& policy_container,
    BattleState& battle_state
) {
    auto& player = battle_state.player;
    auto& opponent = battle_state.opponent;
    const bool player_faster =
        policy_container.is_player_faster(battle_state);
    auto& first_state = player_faster ? player : opponent;
    auto& second_state = player_faster ? opponent : player;
    const Who who_first_state_is = player_faster ? Who::Player : Who::Opponent;
    const Who who_second_state_is = player_faster ? Who::Opponent : Who::Player;

    apply_end_of_turn_1(first_state);
    apply_end_of_turn_1(second_state);

    apply_end_of_turn_2(first_state);
    apply_end_of_turn_2(second_state);

    apply_end_of_turn_3(
        policy_container,
        battle_state,
        first_state,
        who_first_state_is
    );
    apply_end_of_turn_3(
        policy_container,
        battle_state,
        second_state,
        who_second_state_is
    );

    apply_end_of_turn_4(first_state);
    apply_end_of_turn_4(second_state);

    apply_end_of_turn_5(first_state);
    apply_end_of_turn_5(second_state);

    apply_end_of_turn_6(policy_container, first_state, who_first_state_is);
    apply_end_of_turn_6(policy_container, second_state, who_second_state_is);

    apply_end_of_turn_7(first_state);
    apply_end_of_turn_7(second_state);

    apply_end_of_turn_8(first_state);
    apply_end_of_turn_8(second_state);

    apply_end_of_turn_9(first_state);
    apply_end_of_turn_9(second_state);

    apply_end_of_turn_10(first_state);
    apply_end_of_turn_10(second_state);

    first_state.apply_end_of_turn();
    second_state.apply_end_of_turn();
    battle_state.apply_end_of_turn();
}

#endif //GEN_IV_BATTLE_FRONTIER_ANALYZER_END_OF_TURN_EFFECTS_H
