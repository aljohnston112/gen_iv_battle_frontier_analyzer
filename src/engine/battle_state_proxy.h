#ifndef GEN_IV_BATTLE_FRONTIER_ANALYZER_BATTLE_STATE_PROXY_H
#define GEN_IV_BATTLE_FRONTIER_ANALYZER_BATTLE_STATE_PROXY_H

#include "battle_state.h"
#include "policies.h"

template <typename... Policies>
void try_apply_damage_to_pokemon_state(
    const PolicyContainer<Policies...>& policy_container,
    PokemonState& pokemon_state,
    const Who who_the_state_is_for,
    uint16_t damage,
    const DamageSource damage_source
) {
    const uint16_t states_hp = pokemon_state.get_current_stat(Stat::Health);

    if (damage_source == DamageSource::OtherPokemonPowerMove) {
        if (pokemon_state.has_move_status_with_stage(
                MoveStatusWithStage::BehindSubstitute
            )
        ) [[unlikely]] {
            const uint8_t substitute_hp = pokemon_state.get_move_status_stage(
                MoveStatusWithStage::BehindSubstitute
            );
            if (damage >= substitute_hp) {
                pokemon_state.clear_move_status_with_stage(
                    MoveStatusWithStage::BehindSubstitute
                );
            } else {
                pokemon_state.set_move_status_with_stage(
                    MoveStatusWithStage::BehindSubstitute,
                    Move::Substitute,
                    static_cast<int8_t>(
                        static_cast<int16_t>(substitute_hp) - damage
                    )
                );
            }
            return;
        }
    }

    if (pokemon_state.get_current_item_for_effect() == Item::FocusBand &&
        (damage_source == DamageSource::HitInConfusion ||
            damage_source == DamageSource::OtherPokemonPowerMove) &&
        damage >= states_hp && states_hp > 0 &&
        policy_container.roll_for_survival(10, who_the_state_is_for)
    ) {
        damage = states_hp - 1;
    }

    pokemon_state.add_damage(damage, damage_source);
}

#endif //GEN_IV_BATTLE_FRONTIER_ANALYZER_BATTLE_STATE_PROXY_H
