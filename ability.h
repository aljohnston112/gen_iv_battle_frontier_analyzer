#pragma once

#include <format>
#include <unordered_map>

#include "config.h"

enum class Ability {
    Adaptability, // STAB is 2 instead of 1.5
    Aftermath, // Attacker loses 1/4 of thier max HP when making this pokemon faint
               // except if a pokemon with damp is on the field or knock out is the result of direct damage
    AirLock, // Negate weather effects
    AngerPoint, // Attack stat is raised to +6 if hit by a critical hit
                // Includes critical hits on a substitute
    Anticipation, // Pokemon "shudders" if an opponent has a super effective or one-hit knockout move, self-destruct, or explosion
    ArenaTrap, // Grounded pokemon can not switch out
               // Does not affect flying types, levitate or magent rise
               // u-turn and baton pass still work
    BadDreams, // All sleeping opponents lose 1/8 of their max hp from their hp
    BattleArmor, // Prevents all critical hits on this pokemon
    Blaze, // Fire moves used by this pokemon have 50% more power if its HP is <= 1/3 of its HP
    Chlorophyll, // Speed is double if the sun is harsh
    ClearBody, // Prevents stat reduction on this pokemon that are caused by stat lowering moves and abilities
               // Self-inflicted stat changes still happen
               // Iron ball, status, heart swap, guard swap, power swap, baton pass, guard split, and power split still apply stat changes
    CloudNine, // Weather effects are negated
    ColorChange, // Getting hit by a damage dealing move makes this pokemon the type of that move
                 // Activates on the first hit of a multi hit move
                 // Status effects happen before color change
                 // Not activate by struggle, pain split, future sight, or doom desire
    Compoundeyes, // Increases the accuray of moves by 1.3 times their base accuracy
    CuteCharm, // Contact moves from the opposite gender cause infatuation with a 30% chance
               // Each hit of a multi turn move trigger this ability
    Damp,
    Download,
    Drizzle,
    Drought,
    DrySkin,
    EarlyBird,
    EffectSpore,
    Filter,
    FlameBody,
    FlashFire,
    FlowerGift,
    Forecast,
    Forewarn,
    Frisk,
    Gluttony,
    Guts,
    Heatproof,
    HoneyGather,
    HugePower,
    Hustle,
    Hydration,
    HyperCutter,
    IceBody,
    Illuminate,
    Immunity,
    InnerFocus,
    Insomnia,
    Intimidate,
    IronFist,
    KeenEye,
    Klutz,
    LeafGuard,
    Levitate,
    LightningRod,
    Limber,
    LiquidOoze,
    MagicGuard,
    MagmaArmor,
    MagnetPull,
    MarvelScale,
    Minus,
    MoldBreaker,
    MotorDrive,
    Multitype,
    NaturalCure,
    NoGuard,
    Normalize,
    Oblivious,
    Overgrow,
    OwnTempo,
    Pickup,
    Plus,
    PoisonHeal,
    PoisonPoint,
    Pressure,
    PurePower,
    QuickFeet,
    RainDish,
    Reckless,
    Rivalry,
    RockHead,
    RoughSkin,
    RunAway,
    SandStream,
    SandVeil,
    Scrappy,
    SereneGrace,
    ShadowTag,
    ShedSkin,
    ShellArmor,
    ShieldDust,
    Simple,
    SkillLink,
    SlowStart,
    Sniper,
    SnowCloak,
    SnowWarning,
    SolarPower,
    SolidRock,
    Soundproof,
    SpeedBoost,
    Stall,
    Static,
    Steadfast,
    Stench,
    StickyHold,
    StormDrain,
    Sturdy,
    SuctionCups,
    SuperLuck,
    Swarm,
    SwiftSwim,
    Synchronize,
    TangledFeet,
    Technician,
    ThickFat,
    TintedLens,
    Torrent,
    Trace,
    Truant,
    Unaware,
    Unburden,
    VitalSpirit,
    VoltAbsorb,
    WaterAbsorb,
    WaterVeil,
    WhiteSmoke,
    WonderGuard,
    Disabled
};

inline const std::unordered_map<Ability, std::string> ABILITY_TO_STRING_MAP = {
    {Ability::Adaptability, "Adaptability"},
    {Ability::Aftermath, "Aftermath"},
    {Ability::AirLock, "Air Lock"},
    {Ability::AngerPoint, "Anger Point"},
    {Ability::Anticipation, "Anticipation"},
    {Ability::ArenaTrap, "Arena Trap"},
    {Ability::BadDreams, "Bad Dreams"},
    {Ability::BattleArmor, "Battle Armor"},
    {Ability::Blaze, "Blaze"},
    {Ability::Chlorophyll, "Chlorophyll"},
    {Ability::ClearBody, "Clear Body"},
    {Ability::CloudNine, "Cloud Nine"},
    {Ability::ColorChange, "Color Change"},
    {Ability::Compoundeyes, "Compound Eyes"},
    {Ability::CuteCharm, "Cute Charm"},
    {Ability::Damp, "Damp"},
    {Ability::Download, "Download"},
    {Ability::Drizzle, "Drizzle"},
    {Ability::Drought, "Drought"},
    {Ability::DrySkin, "Dry Skin"},
    {Ability::EarlyBird, "Early Bird"},
    {Ability::EffectSpore, "Effect Spore"},
    {Ability::Filter, "Filter"},
    {Ability::FlameBody, "Flame Body"},
    {Ability::FlashFire, "Flash Fire"},
    {Ability::FlowerGift, "Flower Gift"},
    {Ability::Forecast, "Forecast"},
    {Ability::Forewarn, "Forewarn"},
    {Ability::Frisk, "Frisk"},
    {Ability::Gluttony, "Gluttony"},
    {Ability::Guts, "Guts"},
    {Ability::Heatproof, "Heatproof"},
    {Ability::HoneyGather, "Honey Gather"},
    {Ability::HugePower, "Huge Power"},
    {Ability::Hustle, "Hustle"},
    {Ability::Hydration, "Hydration"},
    {Ability::HyperCutter, "Hyper Cutter"},
    {Ability::IceBody, "Ice Body"},
    {Ability::Illuminate, "Illuminate"},
    {Ability::Immunity, "Immunity"},
    {Ability::InnerFocus, "Inner Focus"},
    {Ability::Insomnia, "Insomnia"},
    {Ability::Intimidate, "Intimidate"},
    {Ability::IronFist, "Iron Fist"},
    {Ability::KeenEye, "Keen Eye"},
    {Ability::Klutz, "Klutz"},
    {Ability::LeafGuard, "Leaf Guard"},
    {Ability::Levitate, "Levitate"},
    {Ability::LightningRod, "Lightning Rod"},
    {Ability::Limber, "Limber"},
    {Ability::LiquidOoze, "Liquid Ooze"},
    {Ability::MagicGuard, "Magic Guard"},
    {Ability::MagmaArmor, "Magma Armor"},
    {Ability::MagnetPull, "Magnet Pull"},
    {Ability::MarvelScale, "Marvel Scale"},
    {Ability::Minus, "Minus"},
    {Ability::MoldBreaker, "Mold Breaker"},
    {Ability::MotorDrive, "Motor Drive"},
    {Ability::Multitype, "Multitype"},
    {Ability::NaturalCure, "Natural Cure"},
    {Ability::NoGuard, "No Guard"},
    {Ability::Normalize, "Normalize"},
    {Ability::Oblivious, "Oblivious"},
    {Ability::Overgrow, "Overgrow"},
    {Ability::OwnTempo, "Own Tempo"},
    {Ability::Pickup, "Pickup"},
    {Ability::Plus, "Plus"},
    {Ability::PoisonHeal, "Poison Heal"},
    {Ability::PoisonPoint, "Poison Point"},
    {Ability::Pressure, "Pressure"},
    {Ability::PurePower, "Pure Power"},
    {Ability::QuickFeet, "Quick Feet"},
    {Ability::RainDish, "Rain Dish"},
    {Ability::Reckless, "Reckless"},
    {Ability::Rivalry, "Rivalry"},
    {Ability::RockHead, "Rock Head"},
    {Ability::RoughSkin, "Rough Skin"},
    {Ability::RunAway, "Run Away"},
    {Ability::SandStream, "Sand Stream"},
    {Ability::SandVeil, "Sand Veil"},
    {Ability::Scrappy, "Scrappy"},
    {Ability::SereneGrace, "Serene Grace"},
    {Ability::ShadowTag, "Shadow Tag"},
    {Ability::ShedSkin, "Shed Skin"},
    {Ability::ShellArmor, "Shell Armor"},
    {Ability::ShieldDust, "Shield Dust"},
    {Ability::Simple, "Simple"},
    {Ability::SkillLink, "Skill Link"},
    {Ability::SlowStart, "Slow Start"},
    {Ability::Sniper, "Sniper"},
    {Ability::SnowCloak, "Snow Cloak"},
    {Ability::SnowWarning, "Snow Warning"},
    {Ability::SolarPower, "Solar Power"},
    {Ability::SolidRock, "Solid Rock"},
    {Ability::Soundproof, "Soundproof"},
    {Ability::SpeedBoost, "Speed Boost"},
    {Ability::Stall, "Stall"},
    {Ability::Static, "Static"},
    {Ability::Steadfast, "Steadfast"},
    {Ability::Stench, "Stench"},
    {Ability::StickyHold, "Sticky Hold"},
    {Ability::StormDrain, "Storm Drain"},
    {Ability::Sturdy, "Sturdy"},
    {Ability::SuctionCups, "Suction Cups"},
    {Ability::SuperLuck, "Super Luck"},
    {Ability::Swarm, "Swarm"},
    {Ability::SwiftSwim, "Swift Swim"},
    {Ability::Synchronize, "Synchronize"},
    {Ability::TangledFeet, "Tangled Feet"},
    {Ability::Technician, "Technician"},
    {Ability::ThickFat, "Thick Fat"},
    {Ability::TintedLens, "Tinted Lens"},
    {Ability::Torrent, "Torrent"},
    {Ability::Trace, "Trace"},
    {Ability::Truant, "Truant"},
    {Ability::Unaware, "Unaware"},
    {Ability::Unburden, "Unburden"},
    {Ability::VitalSpirit, "Vital Spirit"},
    {Ability::VoltAbsorb, "Volt Absorb"},
    {Ability::WaterAbsorb, "Water Absorb"},
    {Ability::WaterVeil, "Water Veil"},
    {Ability::WhiteSmoke, "White Smoke"},
    {Ability::WonderGuard, "Wonder Guard"}
};

constexpr auto IMPLEMENTED_ABILITIES = [] {
    std::array<bool, static_cast<int>(Ability::Disabled)> implemented_abilities{};
    implemented_abilities[static_cast<int>(Ability::Levitate)] = true;
    return implemented_abilities;
}();

inline void verify_ability_implmented(const Ability& player_ability) {
    if (!IMPLEMENTED_ABILITIES[static_cast<int>(player_ability)]) {
        throw std::runtime_error(
            std::format(
                "Unimplemented ability: {}",
                ABILITY_TO_STRING_MAP.at(player_ability)
            )
        );
    }
}

inline void verify_abilities_implemented(
    const Ability& player_ability,
    const Ability& opponent_ability
) {
    if constexpr (CHECK_UNIMPLEMENTED) {
        verify_ability_implmented(player_ability);
        verify_ability_implmented(opponent_ability);
    }
}
