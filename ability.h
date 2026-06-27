#pragma once

#include <format>
#include <unordered_map>

#include "config.h"

enum Ability {
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
    {Adaptability, "Adaptability"},
    {Aftermath, "Aftermath"},
    {AirLock, "Air Lock"},
    {AngerPoint, "Anger Point"},
    {Anticipation, "Anticipation"},
    {ArenaTrap, "Arena Trap"},
    {BadDreams, "Bad Dreams"},
    {BattleArmor, "Battle Armor"},
    {Blaze, "Blaze"},
    {Chlorophyll, "Chlorophyll"},
    {ClearBody, "Clear Body"},
    {CloudNine, "Cloud Nine"},
    {ColorChange, "Color Change"},
    {Compoundeyes, "Compound Eyes"},
    {CuteCharm, "Cute Charm"},
    {Damp, "Damp"},
    {Download, "Download"},
    {Drizzle, "Drizzle"},
    {Drought, "Drought"},
    {DrySkin, "Dry Skin"},
    {EarlyBird, "Early Bird"},
    {EffectSpore, "Effect Spore"},
    {Filter, "Filter"},
    {FlameBody, "Flame Body"},
    {FlashFire, "Flash Fire"},
    {FlowerGift, "Flower Gift"},
    {Forecast, "Forecast"},
    {Forewarn, "Forewarn"},
    {Frisk, "Frisk"},
    {Gluttony, "Gluttony"},
    {Guts, "Guts"},
    {Heatproof, "Heatproof"},
    {HoneyGather, "Honey Gather"},
    {HugePower, "Huge Power"},
    {Hustle, "Hustle"},
    {Hydration, "Hydration"},
    {HyperCutter, "Hyper Cutter"},
    {IceBody, "Ice Body"},
    {Illuminate, "Illuminate"},
    {Immunity, "Immunity"},
    {InnerFocus, "Inner Focus"},
    {Insomnia, "Insomnia"},
    {Intimidate, "Intimidate"},
    {IronFist, "Iron Fist"},
    {KeenEye, "Keen Eye"},
    {Klutz, "Klutz"},
    {LeafGuard, "Leaf Guard"},
    {Levitate, "Levitate"},
    {LightningRod, "Lightning Rod"},
    {Limber, "Limber"},
    {LiquidOoze, "Liquid Ooze"},
    {MagicGuard, "Magic Guard"},
    {MagmaArmor, "Magma Armor"},
    {MagnetPull, "Magnet Pull"},
    {MarvelScale, "Marvel Scale"},
    {Minus, "Minus"},
    {MoldBreaker, "Mold Breaker"},
    {MotorDrive, "Motor Drive"},
    {Multitype, "Multitype"},
    {NaturalCure, "Natural Cure"},
    {NoGuard, "No Guard"},
    {Normalize, "Normalize"},
    {Oblivious, "Oblivious"},
    {Overgrow, "Overgrow"},
    {OwnTempo, "Own Tempo"},
    {Pickup, "Pickup"},
    {Plus, "Plus"},
    {PoisonHeal, "Poison Heal"},
    {PoisonPoint, "Poison Point"},
    {Pressure, "Pressure"},
    {PurePower, "Pure Power"},
    {QuickFeet, "Quick Feet"},
    {RainDish, "Rain Dish"},
    {Reckless, "Reckless"},
    {Rivalry, "Rivalry"},
    {RockHead, "Rock Head"},
    {RoughSkin, "Rough Skin"},
    {RunAway, "Run Away"},
    {SandStream, "Sand Stream"},
    {SandVeil, "Sand Veil"},
    {Scrappy, "Scrappy"},
    {SereneGrace, "Serene Grace"},
    {ShadowTag, "Shadow Tag"},
    {ShedSkin, "Shed Skin"},
    {ShellArmor, "Shell Armor"},
    {ShieldDust, "Shield Dust"},
    {Simple, "Simple"},
    {SkillLink, "Skill Link"},
    {SlowStart, "Slow Start"},
    {Sniper, "Sniper"},
    {SnowCloak, "Snow Cloak"},
    {SnowWarning, "Snow Warning"},
    {SolarPower, "Solar Power"},
    {SolidRock, "Solid Rock"},
    {Soundproof, "Soundproof"},
    {SpeedBoost, "Speed Boost"},
    {Stall, "Stall"},
    {Static, "Static"},
    {Steadfast, "Steadfast"},
    {Stench, "Stench"},
    {StickyHold, "Sticky Hold"},
    {StormDrain, "Storm Drain"},
    {Sturdy, "Sturdy"},
    {SuctionCups, "Suction Cups"},
    {SuperLuck, "Super Luck"},
    {Swarm, "Swarm"},
    {SwiftSwim, "Swift Swim"},
    {Synchronize, "Synchronize"},
    {TangledFeet, "Tangled Feet"},
    {Technician, "Technician"},
    {ThickFat, "Thick Fat"},
    {TintedLens, "Tinted Lens"},
    {Torrent, "Torrent"},
    {Trace, "Trace"},
    {Truant, "Truant"},
    {Unaware, "Unaware"},
    {Unburden, "Unburden"},
    {VitalSpirit, "Vital Spirit"},
    {VoltAbsorb, "Volt Absorb"},
    {WaterAbsorb, "Water Absorb"},
    {WaterVeil, "Water Veil"},
    {WhiteSmoke, "White Smoke"},
    {WonderGuard, "Wonder Guard"}
};

constexpr auto IMPLEMENTED_ABILITIES = [] {
    std::array<bool, Disabled> implemented_abilities{};
    implemented_abilities[Levitate] = true;
    return implemented_abilities;
}();

inline void verify_ability_implmented(const Ability& player_ability) {
    if (!IMPLEMENTED_ABILITIES[player_ability]) {
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
