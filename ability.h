#pragma once

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