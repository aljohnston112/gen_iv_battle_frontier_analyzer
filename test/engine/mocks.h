#ifndef GEN_IV_BATTLE_FRONTIER_ANALYZER_MOCKS_H
#define GEN_IV_BATTLE_FRONTIER_ANALYZER_MOCKS_H
#include "pokemon.h"
#include "policies.h"

const CustomPokemon Articuno_7_3{
    .unique_id = "Articuno_7_3",
    .name = Pokemon::Articuno,
    .ability = Ability::Pressure,
    .level = 50,
    .item = Item::WiseGlasses,
    .types = {PokemonType::Flying, PokemonType::Ice},
    .moves = {
        Move::OminousWind, Move::WaterPulse, Move::SignalBeam, Move::IceBeam
    },
    .stats = {162, 91, 148, 157, 142, 102},
    .pounds = 122.1
};

const CustomPokemon Cresselia_7_2{
    .unique_id = "Cresselia_7_2",
    .name = Pokemon::Cresselia,
    .ability = Ability::Levitate,
    .level = 50,
    .item = Item::LumBerry,
    .types = {PokemonType::Psychic, PokemonType::NoType},
    .moves = {
        Move::Psychic, Move::Moonlight, Move::Toxic, Move::DoubleTeam
    },
    .stats = {213, 78, 173, 92, 168, 102},
    .pounds = 188.7
};

const CustomPokemon Cresselia_7_3{
    .unique_id = "Cresselia_7_3",
    .name = Pokemon::Cresselia,
    .ability = Ability::Levitate,
    .level = 50,
    .item = Item::WiseGlasses,
    .types = {PokemonType::Psychic, PokemonType::NoType},
    .moves = {
        Move::Psychic, Move::ShadowBall, Move::EnergyBall, Move::ChargeBeam
    },
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

const CustomPokemon Entei_7_2{
    .unique_id = "Entei_7_2",
    .name = Pokemon::Entei,
    .ability = Ability::Pressure,
    .level = 50,
    .item = Item::KingsRock,
    .types = {PokemonType::Fire, PokemonType::NoType},
    .moves = {
        Move::Bite, Move::FireFang, Move::IronHead, Move::StoneEdge
    },
    .stats = {187, 163, 102, 96, 92, 162},
    .pounds = 436.5
};

const CustomPokemon Entei_7_2_No_Item{
    .unique_id = "Entei_7_2_No_Item",
    .name = Pokemon::Entei,
    .ability = Ability::Pressure,
    .level = 50,
    .item = Item::NoItem,
    .types = {PokemonType::Fire, PokemonType::NoType},
    .moves = {
        Move::Bite, Move::FireFang, Move::IronHead, Move::StoneEdge
    },
    .stats = {187, 163, 102, 96, 92, 162},
    .pounds = 436.5
};

const CustomPokemon Entei_7_3{
    .unique_id = "Entei_7_3",
    .name = Pokemon::Entei,
    .ability = Ability::Pressure,
    .level = 50,
    .item = Item::ShucaBerry,
    .types = {PokemonType::Fire, PokemonType::NoType},
    .moves = {
        Move::SunnyDay, Move::FireBlast, Move::SolarBeam, Move::HyperBeam
    },
    .stats = {187, 118, 102, 151, 92, 148},
    .pounds = 436.5
};

const CustomPokemon Heatran_7_1{
    .unique_id = "Heatran_7_1",
    .name = Pokemon::Heatran,
    .ability = Ability::FlashFire,
    .level = 50,
    .item = Item::ShucaBerry,
    .types = {PokemonType::Fire, PokemonType::Steel},
    .moves = {
        Move::ScaryFace, Move::Ancientpower, Move::FlashCannon, Move::HeatWave
    },
    .stats = {163, 96, 123, 195, 154, 94},
    .pounds = 948
};

const CustomPokemon Heatran_7_3{
    .unique_id = "Heatran_7_3",
    .name = Pokemon::Heatran,
    .ability = Ability::FlashFire,
    .level = 50,
    .item = Item::BrightPowder,
    .types = {PokemonType::Fire, PokemonType::Steel},
    .moves = {
        Move::DarkPulse, Move::EarthPower, Move::DragonPulse, Move::Flamethrower
    },
    .stats = {194, 96, 123, 195, 123, 94},
    .pounds = 948
};

const CustomPokemon Latias_7_2{
    .unique_id = "Latias_7_2",
    .name = Pokemon::Latias,
    .ability = Ability::Levitate,
    .level = 50,
    .item = Item::ExpertBelt,
    .types = {PokemonType::Psychic, PokemonType::Dragon},
    .moves = {
        Move::AerialAce,
        Move::DragonClaw,
        Move::ZenHeadbutt,
        Move::Earthquake
    },
    .stats = {152, 140, 107, 114, 147, 158},
    .pounds = 88.2
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

const CustomPokemon Latias_7_4_No_Item{
    .unique_id = "Latias_7_4_No_Item",
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

const CustomPokemon Raikou_7_2{
    .unique_id = "Raikou_7_2",
    .name = Pokemon::Raikou,
    .ability = Ability::Pressure,
    .level = 50,
    .item = Item::KingsRock,
    .types = {PokemonType::Electric, PokemonType::NoType},
    .moves = {
        Move::ThunderFang, Move::Crunch, Move::Return,
        Move::IronHead
    },
    .stats = {162, 133, 92, 118, 117, 179},
    .pounds = 392.4
};

const CustomPokemon Raikou_7_2_No_Item{
    .unique_id = "Raikou_7_2_No_Item",
    .name = Pokemon::Raikou,
    .ability = Ability::Pressure,
    .level = 50,
    .item = Item::NoItem,
    .types = {PokemonType::Electric, PokemonType::NoType},
    .moves = {
        Move::ThunderFang, Move::Crunch, Move::Return,
        Move::IronHead
    },
    .stats = {162, 133, 92, 118, 117, 179},
    .pounds = 392.4
};

const CustomPokemon Raikou_7_3{
    .unique_id = "Raikou_7_3",
    .name = Pokemon::Raikou,
    .ability = Ability::Pressure,
    .level = 50,
    .item = Item::WiseGlasses,
    .types = {PokemonType::Electric, PokemonType::NoType},
    .moves = {
        Move::Thunder, Move::RainDance, Move::Extrasensory,
        Move::SignalBeam
    },
    .stats = {162, 91, 92, 179, 117, 163},
    .pounds = 392.4
};

const CustomPokemon Regice_7_2{
    .unique_id = "Regice_7_2",
    .name = Pokemon::Regice,
    .ability = Ability::ClearBody,
    .level = 50,
    .item = Item::Leftovers,
    .types = {PokemonType::Ice, PokemonType::NoType},
    .moves = {
        Move::DoubleTeam, Move::HammerArm, Move::Avalanche, Move::Curse
    },
    .stats = {183, 67, 162, 105, 217, 67},
    .pounds = 385.8
};

const CustomPokemon Regirock_7_3{
    .unique_id = "Regirock_7_3",
    .name = Pokemon::Regirock,
    .ability = Ability::ClearBody,
    .level = 50,
    .item = Item::ChestoBerry,
    .types = {PokemonType::Rock, PokemonType::NoType},
    .moves = {
        Move::StoneEdge, Move::HammerArm, Move::Rest,
        Move::Curse
    },
    .stats = {183, 117, 217, 60, 162, 67},
    .pounds = 507.1
};

const CustomPokemon Regirock_7_3_NoItem{
    .unique_id = "Regirock_7_3",
    .name = Pokemon::Regirock,
    .ability = Ability::ClearBody,
    .level = 50,
    .item = Item::NoItem,
    .types = {PokemonType::Rock, PokemonType::NoType},
    .moves = {
        Move::StoneEdge, Move::HammerArm, Move::Rest,
        Move::Curse
    },
    .stats = {183, 117, 217, 60, 162, 67},
    .pounds = 507.1
};

const CustomPokemon Regigigas_7_1{
    .unique_id = "Regigias_7_1",
    .name = Pokemon::Regigigas,
    .ability = Ability::SlowStart,
    .level = 50,
    .item = Item::LaxIncense,
    .types = {PokemonType::Normal, PokemonType::NoType},
    .moves = {
        Move::ConfuseRay,
        Move::ThunderWave,
        Move::AerialAce,
        Move::Return
    },
    .stats = {203, 177, 162, 87, 148, 117},
    .pounds = 925.9
};

const CustomPokemon Regigigas_7_2{
    .unique_id = "Regigias_7_2",
    .name = Pokemon::Regigigas,
    .ability = Ability::SlowStart,
    .level = 50,
    .item = Item::Leftovers,
    .types = {PokemonType::Normal, PokemonType::NoType},
    .moves = {
        Move::DoubleTeam,
        Move::Substitute,
        Move::Facade,
        Move::ZenHeadbutt
    },
    .stats = {203, 177, 148, 87, 162, 117},
    .pounds = 925.9
};

const CustomPokemon Regigigas_7_3{
    .unique_id = "Regigias_7_3",
    .name = Pokemon::Regigigas,
    .ability = Ability::SlowStart,
    .level = 50,
    .item = Item::WiseGlasses,
    .types = {PokemonType::Normal, PokemonType::NoType},
    .moves = {
        Move::Ancientpower, Move::EarthPower, Move::FocusBlast,
        Move::Thunderbolt
    },
    .stats = {213, 159, 127, 140, 127, 117},
    .pounds = 925.9
};

const CustomPokemon Suicune_7_2{
    .unique_id = "Suicune_7_2",
    .name = Pokemon::Suicune,
    .ability = Ability::Pressure,
    .level = 50,
    .item = Item::KingsRock,
    .types = {PokemonType::Water, PokemonType::NoType},
    .moves = {
        Move::Waterfall, Move::IceFang, Move::Bite, Move::IronHead
    },
    .stats = {172, 123, 132, 96, 132, 146},
    .pounds = 412.3
};

const CustomPokemon Suicune_7_2_No_Item{
    .unique_id = "Suicune_7_2_No_Item",
    .name = Pokemon::Suicune,
    .ability = Ability::Pressure,
    .level = 50,
    .item = Item::NoItem,
    .types = {PokemonType::Water, PokemonType::NoType},
    .moves = {
        Move::Waterfall, Move::IceFang, Move::Bite, Move::IronHead
    },
    .stats = {172, 123, 132, 96, 132, 146},
    .pounds = 412.3
};

const CustomPokemon Suicune_7_3{
    .unique_id = "Suicune_7_3",
    .name = Pokemon::Suicune,
    .ability = Ability::Pressure,
    .level = 50,
    .item = Item::LumBerry,
    .types = {PokemonType::Water, PokemonType::NoType},
    .moves = {
        Move::Hail, Move::ShadowBall, Move::HydroPump, Move::Blizzard
    },
    .stats = {172, 82, 179, 138, 132, 102},
    .pounds = 412.3
};

const CustomPokemon Zapdos_7_2{
    .unique_id = "Zapdos_7_2",
    .name = Pokemon::Zapdos,
    .ability = Ability::Pressure,
    .level = 50,
    .item = Item::FocusBand,
    .types = {PokemonType::Electric, PokemonType::Flying},
    .moves = {
        Move::OminousWind, Move::LightScreen,
        Move::Thunderbolt, Move::Ancientpower
    },
    .stats = {162, 96, 102, 173, 107, 162},
    .pounds = 116
};

const CustomPokemon Zapdos_7_3{
    .unique_id = "Zapdos_7_3",
    .name = Pokemon::Zapdos,
    .ability = Ability::Pressure,
    .level = 50,
    .item = Item::KingsRock,
    .types = {PokemonType::Electric, PokemonType::Flying},
    .moves = {
        Move::Twister, Move::SteelWing, Move::UTurn, Move::DrillPeck
    },
    .stats = {162, 138, 102, 127, 107, 162},
    .pounds = 116
};

const CustomPokemon Zapdos_7_3_NoItem{
    .unique_id = "Zapdos_7_3",
    .name = Pokemon::Zapdos,
    .ability = Ability::Pressure,
    .level = 50,
    .item = Item::NoItem,
    .types = {PokemonType::Electric, PokemonType::Flying},
    .moves = {
        Move::Twister, Move::SteelWing, Move::UTurn, Move::DrillPeck
    },
    .stats = {162, 138, 102, 127, 107, 162},
    .pounds = 116
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
