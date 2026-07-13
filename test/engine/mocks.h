#ifndef GEN_IV_BATTLE_FRONTIER_ANALYZER_MOCKS_H
#define GEN_IV_BATTLE_FRONTIER_ANALYZER_MOCKS_H
#include "pokemon.h"
#include "policies.h"

const CustomPokemon CresseliaLeftovers{
    .name = Pokemon::Cresselia,
    .ability = Ability::Levitate,
    .level = 50,
    .item = Item::Leftovers,
    .types = {PokemonType::Psychic, PokemonType::NoType},
    .moves = {Move::Psychic, Move::IceBeam, Move::SignalBeam, Move::Moonlight},
    .stats = {213, 78, 158, 101, 168, 102},
    .pounds = 188.7
};

const CustomPokemon CresseliaNoItem{
    .name = Pokemon::Cresselia,
    .ability = Ability::Levitate,
    .level = 50,
    .item = Item::NoItem,
    .types = {PokemonType::Psychic, PokemonType::NoType},
    .moves = {Move::Psychic, Move::IceBeam, Move::SignalBeam, Move::Moonlight},
    .stats = {213, 78, 158, 101, 168, 102},
    .pounds = 188.7
};

const CustomPokemon Latias{
    .name = Pokemon::Latias,
    .ability = Ability::Levitate,
    .level = 50,
    .item = Item::NoItem,
    .types = {PokemonType::Psychic, PokemonType::NoType},
    .moves = {
        Move::MistBall,
        Move::DracoMeteor,
        Move::Thunderbolt,
        Move::Surf
    },
    .stats = {152, 87, 107, 173, 147, 158},
    .pounds = 88.2
};

const CustomPokemon LatiasWhiteHerb{
    .name = Pokemon::Latias,
    .ability = Ability::Levitate,
    .level = 50,
    .item = Item::WhiteHerb,
    .types = {PokemonType::Psychic, PokemonType::NoType},
    .moves = {
        Move::MistBall,
        Move::DracoMeteor,
        Move::Thunderbolt,
        Move::Surf
    },
    .stats = {152, 87, 107, 173, 147, 158},
    .pounds = 88.2
};


struct LowDamageRandomFactorPolicy :
    DamageRandomFactorPolicy<LowDamageRandomFactorPolicy> {
    static uint8_t roll_random(const Who) {
        return 85;
    }
};

struct HighDamageRandomFactorPolicy :
    DamageRandomFactorPolicy<HighDamageRandomFactorPolicy> {
    static uint8_t roll_random(const Who) {
        return 100;
    }
};

template <typename T>
concept IsDamageTestCase = requires {
    requires IsCritRNGPolicy<typename T::CritRNGPolicyType>;
    requires IsDamageRandomFactorPolicy<typename T::DamageRandomFactorPolicyType>;
    { +T::ExpectedValue } -> std::same_as<int32_t>;
};

template <
    IsCritRNGPolicy CritRNGPolicy,
    IsDamageRandomFactorPolicy DamageRandomFactorPolicy,
    int32_t Value
>
struct DamageTestCase {
    using CritRNGPolicyType = CritRNGPolicy;
    using DamageRandomFactorPolicyType = DamageRandomFactorPolicy;
    static constexpr int32_t ExpectedValue = Value;
};

#endif //GEN_IV_BATTLE_FRONTIER_ANALYZER_MOCKS_H
