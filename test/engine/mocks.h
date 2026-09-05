#ifndef GEN_IV_BATTLE_FRONTIER_ANALYZER_MOCKS_H
#define GEN_IV_BATTLE_FRONTIER_ANALYZER_MOCKS_H
#include "pokemon.h"
#include "policies.h"

const CustomPokemon Cresselia_7_3{
    .unique_id = "Cresselia_7_3",
    .name = Pokemon::Cresselia,
    .ability = Ability::Levitate,
    .level = 50,
    .item = Item::WiseGlasses,
    .types = {PokemonType::Psychic, PokemonType::NoType},
    .moves = {Move::Psychic, Move::ShadowBall, Move::EnergyBall, Move::ChargeBeam},
    .stats = {233, 78, 137, 135, 147, 102},
    .pounds = 188.7
};

const CustomPokemon Cresselia_7_4{
    .unique_id = "Cresselia_7_4",
    .name = Pokemon::Cresselia,
    .ability = Ability::Levitate,
    .level = 50,
    .item = Item::Leftovers,
    .types = {PokemonType::Psychic, PokemonType::NoType},
    .moves = {Move::Moonlight, Move::SignalBeam, Move::Psychic, Move::IceBeam},
    .stats = {213, 78, 158, 101, 168, 102},
    .pounds = 188.7
};

const CustomPokemon Cresselia_7_4_NoItem{
    .unique_id = "Cresselia_7_4_NO_ITEM",
    .name = Pokemon::Cresselia,
    .ability = Ability::Levitate,
    .level = 50,
    .item = Item::NoItem,
    .types = {PokemonType::Psychic, PokemonType::NoType},
    .moves = {Move::Psychic, Move::IceBeam, Move::SignalBeam, Move::Moonlight},
    .stats = {213, 78, 158, 101, 168, 102},
    .pounds = 188.7
};

const CustomPokemon Latias_7_4{
    .unique_id = "Latias_7_4",
    .name = Pokemon::Latias,
    .ability = Ability::Levitate,
    .level = 50,
    .item = Item::WhiteHerb,
    .types = {PokemonType::Psychic, PokemonType::Dragon},
    .moves = {
        Move::MistBall,
        Move::DracoMeteor,
        Move::Thunderbolt,
        Move::Surf
    },
    .stats = {152, 87, 107, 173, 147, 158},
    .pounds = 88.2
};

const CustomPokemon LatiasNoItem{
    .unique_id = "Latias_7_4_NO_ITEM",
    .name = Pokemon::Latias,
    .ability = Ability::Levitate,
    .level = 50,
    .item = Item::NoItem,
    .types = {PokemonType::Psychic, PokemonType::Dragon},
    .moves = {
        Move::MistBall,
        Move::DracoMeteor,
        Move::Thunderbolt,
        Move::Surf
    },
    .stats = {152, 87, 107, 173, 147, 158},
    .pounds = 88.2
};

const CustomPokemon Regigias_7_3{
    .unique_id = "Regigias_7_3",
    .name = Pokemon::Regigigas,
    .ability = Ability::SlowStart,
    .level = 50,
    .item = Item::WiseGlasses,
    .types = {PokemonType::Normal, PokemonType::NoType},
    .moves = {
        Move::EarthPower, Move::FocusBlast, Move::Thunderbolt,
        Move::Ancientpower
    },
    .stats = {213, 159, 127, 140, 127, 117},
    .pounds = 925.9
};


constexpr auto DEFAULT_POLICY =
    PolicyContainer<
        OpponentOptimizedConfusionStatusPolicy,
        NeverConfuseRNGPolicy,
        NeverCritRNGPolicy,
        OpponentOptimizedRandomFactorPolicy,
        NeverFreezeRNGPolicy,
        NeverParalyzeRNGPolicy,
        OpponentOptimizedKnowledgePolicy,
        OpponentOptimizedSpeedAdvantagePolicy,
        OpponentOptimizedStatChangePolicy,
        NoLogging
    >{};

constexpr auto DEFAULT_POLICY_WITH_LOGGING =
    PolicyContainer<
        OpponentOptimizedConfusionStatusPolicy,
        NeverConfuseRNGPolicy,
        NeverCritRNGPolicy,
        OpponentOptimizedRandomFactorPolicy,
        NeverFreezeRNGPolicy,
        NeverParalyzeRNGPolicy,
        OpponentOptimizedKnowledgePolicy,
        OpponentOptimizedSpeedAdvantagePolicy,
        OpponentOptimizedStatChangePolicy,
        DebugLogging
    >{};

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
    requires IsDamageRandomFactorPolicy<typename
        T::DamageRandomFactorPolicyType>;
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
