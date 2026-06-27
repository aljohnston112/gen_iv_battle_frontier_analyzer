#pragma once

#include <array>
#include <format>
#include <string>

#include "category.h"
#include "config.h"
#include "type.h"

enum Move {
    Pound,
    KarateChop,
    DoubleSlap,
    CometPunch,
    MegaPunch,
    PayDay,
    FirePunch,
    IcePunch,
    ThunderPunch,
    Scratch,
    ViceGrip,
    Guillotine,
    RazorWind,
    SwordsDance,
    Cut,
    Gust,
    WingAttack,
    Whirlwind,
    Fly,
    Bind,
    Slam,
    VineWhip,
    Stomp,
    DoubleKick,
    MegaKick,
    JumpKick,
    RollingKick,
    SandAttack,
    Headbutt,
    HornAttack,
    FuryAttack,
    HornDrill,
    Tackle,
    BodySlam,
    Wrap,
    TakeDown,
    Thrash,
    DoubleEdge,
    TailWhip,
    PoisonSting,
    Twineedle,
    PinMissile,
    Leer,
    Bite,
    Growl,
    Roar,
    Sing,
    Supersonic,
    SonicBoom,
    Disable,
    Acid,
    Ember,
    Flamethrower,
    Mist,
    WaterGun,
    HydroPump,
    Surf,
    IceBeam,
    Blizzard,
    Psybeam,
    Bubblebeam,
    AuroraBeam,
    HyperBeam,
    Peck,
    DrillPeck,
    Submission,
    LowKick,
    Counter,
    SeismicToss,
    Strength,
    Absorb,
    MegaDrain,
    LeechSeed,
    Growth,
    RazorLeaf,
    SolarBeam,
    PoisonPowder,
    StunSpore,
    SleepPowder,
    PetalDance,
    StringShot,
    DragonRage,
    FireSpin,
    Thundershock,
    Thunderbolt,
    ThunderWave,
    Thunder,
    RockThrow,
    Earthquake,
    Fissure,
    Dig,
    Toxic,
    Confusion,
    PsychicMove,
    Hypnosis,
    Meditate,
    Agility,
    QuickAttack,
    Rage,
    Teleport,
    NightShade,
    Mimic,
    Screech,
    DoubleTeam,
    Recover,
    Harden,
    Minimize,
    Smokescreen,
    ConfuseRay,
    Withdraw,
    DefenseCurl,
    Barrier,
    LightScreen,
    Haze,
    Reflect,
    FocusEnergy,
    Bide,
    MetronomeMove,
    MirrorMove,
    Selfdestruct,
    EggBomb,
    Lick,
    Smog,
    Sludge,
    BoneClub,
    FireBlast,
    Waterfall,
    Clamp,
    Swift,
    SkullBash,
    SpikeCannon,
    Constrict,
    Amnesia,
    Kinesis,
    Softboiled,
    HighJumpKick,
    Glare,
    DreamEater,
    PoisonGas,
    Barrage,
    LeechLife,
    LovelyKiss,
    SkyAttack,
    Transform,
    Bubble,
    DizzyPunch,
    Spore,
    Flash,
    Psywave,
    Splash,
    AcidArmor,
    Crabhammer,
    Explosion,
    FurySwipes,
    Bonemerang,
    Rest,
    RockSlide,
    HyperFang,
    Sharpen,
    Conversion,
    TriAttack,
    SuperFang,
    Slash,
    Substitute,
    Struggle,
    Sketch,
    TripleKick,
    Thief,
    SpiderWeb,
    MindReader,
    Nightmare,
    FlameWheel,
    Snore,
    Curse,
    Flail,
    Conversion2,
    Aeroblast,
    CottonSpore,
    Reversal,
    Spite,
    PowderSnow,
    Protect,
    MachPunch,
    ScaryFace,
    FaintAttack,
    SweetKiss,
    BellyDrum,
    SludgeBomb,
    MudSlap,
    Octazooka,
    Spikes,
    ZapCannon,
    Foresight,
    DestinyBond,
    PerishSong,
    IcyWind,
    Detect,
    BoneRush,
    LockOn,
    Outrage,
    SandstormMove,
    GigaDrain,
    Endure,
    Charm,
    Rollout,
    FalseSwipe,
    Swagger,
    MilkDrink,
    Spark,
    FuryCutter,
    SteelWing,
    MeanLook,
    Attract,
    SleepTalk,
    HealBell,
    Return,
    Present,
    Frustration,
    Safeguard,
    PainSplit,
    SacredFire,
    Magnitude,
    Dynamicpunch,
    Megahorn,
    DragonBreath,
    BatonPass,
    Encore,
    Pursuit,
    RapidSpin,
    SweetScent,
    IronTail,
    MetalClaw,
    VitalThrow,
    MorningSun,
    Synthesis,
    Moonlight,
    HiddenPower,
    CrossChop,
    Twister,
    RainDance,
    SunnyDay,
    Crunch,
    MirrorCoat,
    PsychUp,
    ExtremeSpeed,
    Ancientpower,
    ShadowBall,
    FutureSight,
    RockSmash,
    Whirlpool,
    BeatUp,
    FakeOut,
    Uproar,
    Stockpile,
    SpitUp,
    Swallow,
    HeatWave,
    HailMove,
    Torment,
    Flatter,
    WillOWisp,
    Memento,
    Facade,
    FocusPunch,
    Smellingsalt,
    FollowMe,
    NaturePower,
    Charge,
    Taunt,
    HelpingHand,
    Trick,
    RolePlay,
    Wish,
    Assist,
    Ingrain,
    Superpower,
    MagicCoat,
    Recycle,
    Revenge,
    BrickBreak,
    Yawn,
    KnockOff,
    Endeavor,
    Eruption,
    SkillSwap,
    Imprison,
    Refresh,
    Grudge,
    Snatch,
    SecretPower,
    Dive,
    ArmThrust,
    Camouflage,
    TailGlow,
    LusterPurge,
    MistBall,
    Featherdance,
    TeeterDance,
    BlazeKick,
    MudSport,
    IceBall,
    NeedleArm,
    SlackOff,
    HyperVoice,
    PoisonFang,
    CrushClaw,
    BlastBurn,
    HydroCannon,
    MeteorMash,
    Astonish,
    WeatherBall,
    Aromatherapy,
    FakeTears,
    AirCutter,
    Overheat,
    OdorSleuth,
    RockTomb,
    SilverWind,
    MetalSound,
    Grasswhistle,
    Tickle,
    CosmicPower,
    WaterSpout,
    SignalBeam,
    ShadowPunch,
    Extrasensory,
    SkyUppercut,
    SandTomb,
    SheerCold,
    MuddyWater,
    BulletSeed,
    AerialAce,
    IcicleSpear,
    IronDefense,
    Block,
    Howl,
    DragonClaw,
    FrenzyPlant,
    BulkUp,
    Bounce,
    MudShot,
    PoisonTail,
    Covet,
    VoltTackle,
    MagicalLeaf,
    WaterSport,
    CalmMind,
    LeafBlade,
    DragonDance,
    RockBlast,
    ShockWave,
    WaterPulse,
    DoomDesire,
    PsychoBoost,
    Roost,
    Gravity,
    MiracleEye,
    WakeUpSlap,
    HammerArm,
    GyroBall,
    HealingWish,
    Brine,
    NaturalGift,
    Feint,
    Pluck,
    Tailwind,
    Acupressure,
    MetalBurst,
    UTurn,
    CloseCombat,
    Payback,
    Assurance,
    Embargo,
    Fling,
    PsychoShift,
    TrumpCard,
    HealBlock,
    WringOut,
    PowerTrick,
    GastroAcid,
    LuckyChant,
    MeFirst,
    Copycat,
    PowerSwap,
    GuardSwap,
    Punishment,
    LastResort,
    WorrySeed,
    SuckerPunch,
    ToxicSpikes,
    HeartSwap,
    AquaRing,
    MagnetRise,
    FlareBlitz,
    ForcePalm,
    AuraSphere,
    RockPolish,
    PoisonJab,
    DarkPulse,
    NightSlash,
    AquaTail,
    SeedBomb,
    AirSlash,
    XScissor,
    BugBuzz,
    DragonPulse,
    DragonRush,
    PowerGem,
    DrainPunch,
    VacuumWave,
    FocusBlast,
    EnergyBall,
    BraveBird,
    EarthPower,
    Switcheroo,
    GigaImpact,
    NastyPlot,
    BulletPunch,
    Avalanche,
    IceShard,
    ShadowClaw,
    ThunderFang,
    IceFang,
    FireFang,
    ShadowSneak,
    MudBomb,
    PsychoCut,
    ZenHeadbutt,
    MirrorShot,
    FlashCannon,
    RockClimb,
    Defog,
    TrickRoom,
    DracoMeteor,
    Discharge,
    LavaPlume,
    LeafStorm,
    PowerWhip,
    RockWrecker,
    CrossPoison,
    GunkShot,
    IronHead,
    MagnetBomb,
    StoneEdge,
    Captivate,
    StealthRock,
    GrassKnot,
    Chatter,
    Judgment,
    BugBite,
    ChargeBeam,
    WoodHammer,
    AquaJet,
    AttackOrder,
    DefendOrder,
    HealOrder,
    HeadSmash,
    DoubleHit,
    RoarOfTime,
    SpacialRend,
    LunarDance,
    CrushGrip,
    MagmaStorm,
    DarkVoid,
    SeedFlare,
    OminousWind,
    ShadowForce,
    MoveCount
};

struct MoveInfo {
    std::string name;
    Move move;
    PokemonType type;
    Category category;
    int16_t power;
    int accuracy;
    int power_points;
    int effect_percent;

    bool operator==(const MoveInfo& other) const {
        return move == other.move;
    }
};

inline const std::unordered_map<std::string, Move> STRING_TO_MOVE_MAP = {
    {"Pound", Pound},
    {"Karate Chop", KarateChop},
    {"Doubleslap", DoubleSlap},
    {"Comet Punch", CometPunch},
    {"Mega Punch", MegaPunch},
    {"Pay Day", PayDay},
    {"Fire Punch", FirePunch},
    {"Ice Punch", IcePunch},
    {"Thunderpunch", ThunderPunch},
    {"Thunder Punch", ThunderPunch},
    {"Scratch", Scratch},
    {"Vicegrip", ViceGrip},
    {"Guillotine", Guillotine},
    {"Razor Wind", RazorWind},
    {"Swords Dance", SwordsDance},
    {"Cut", Cut},
    {"Gust", Gust},
    {"Wing Attack", WingAttack},
    {"Whirlwind", Whirlwind},
    {"Fly", Fly},
    {"Bind", Bind},
    {"Slam", Slam},
    {"Vine Whip", VineWhip},
    {"Stomp", Stomp},
    {"Double Kick", DoubleKick},
    {"Mega Kick", MegaKick},
    {"Jump Kick", JumpKick},
    {"Rolling Kick", RollingKick},
    {"Sand-attack", SandAttack},
    {"Sand Attack", SandAttack},
    {"Headbutt", Headbutt},
    {"Horn Attack", HornAttack},
    {"Fury Attack", FuryAttack},
    {"Horn Drill", HornDrill},
    {"Tackle", Tackle},
    {"Body Slam", BodySlam},
    {"Wrap", Wrap},
    {"Take Down", TakeDown},
    {"Thrash", Thrash},
    {"Double-edge", DoubleEdge},
    {"Double-Edge", DoubleEdge},
    {"Tail Whip", TailWhip},
    {"Poison Sting", PoisonSting},
    {"Twineedle", Twineedle},
    {"Pin Missile", PinMissile},
    {"Leer", Leer},
    {"Bite", Bite},
    {"Growl", Growl},
    {"Roar", Roar},
    {"Sing", Sing},
    {"Supersonic", Supersonic},
    {"Sonicboom", SonicBoom},
    {"Disable", Disable},
    {"Acid", Acid},
    {"Ember", Ember},
    {"Flamethrower", Flamethrower},
    {"Mist", Mist},
    {"Water Gun", WaterGun},
    {"Hydro Pump", HydroPump},
    {"Surf", Surf},
    {"Ice Beam", IceBeam},
    {"Blizzard", Blizzard},
    {"Psybeam", Psybeam},
    {"Bubblebeam", Bubblebeam},
    {"Bubble Beam", Bubblebeam},
    {"Aurora Beam", AuroraBeam},
    {"Hyper Beam", HyperBeam},
    {"Peck", Peck},
    {"Drill Peck", DrillPeck},
    {"Submission", Submission},
    {"Low Kick", LowKick},
    {"Counter", Counter},
    {"Seismic Toss", SeismicToss},
    {"Strength", Strength},
    {"Absorb", Absorb},
    {"Mega Drain", MegaDrain},
    {"Leech Seed", LeechSeed},
    {"Growth", Growth},
    {"Razor Leaf", RazorLeaf},
    {"Solarbeam", SolarBeam},
    {"Solar Beam", SolarBeam},
    {"Poisonpowder", PoisonPowder},
    {"Poison Powder", PoisonPowder},
    {"Stun Spore", StunSpore},
    {"Sleep Powder", SleepPowder},
    {"Petal Dance", PetalDance},
    {"String Shot", StringShot},
    {"Dragon Rage", DragonRage},
    {"Fire Spin", FireSpin},
    {"Thundershock", Thundershock},
    {"Thunderbolt", Thunderbolt},
    {"Thunder Wave", ThunderWave},
    {"Thunder", Thunder},
    {"Rock Throw", RockThrow},
    {"Earthquake", Earthquake},
    {"Fissure", Fissure},
    {"Dig", Dig},
    {"Toxic", Toxic},
    {"Confusion", Confusion},
    {"Psychic", PsychicMove},
    {"Hypnosis", Hypnosis},
    {"Meditate", Meditate},
    {"Agility", Agility},
    {"Quick Attack", QuickAttack},
    {"Rage", Rage},
    {"Teleport", Teleport},
    {"Night Shade", NightShade},
    {"Mimic", Mimic},
    {"Screech", Screech},
    {"Double Team", DoubleTeam},
    {"Recover", Recover},
    {"Harden", Harden},
    {"Minimize", Minimize},
    {"Smokescreen", Smokescreen},
    {"SmokeScreen", Smokescreen},
    {"Confuse Ray", ConfuseRay},
    {"Withdraw", Withdraw},
    {"Defense Curl", DefenseCurl},
    {"Barrier", Barrier},
    {"Light Screen", LightScreen},
    {"Haze", Haze},
    {"Reflect", Reflect},
    {"Focus Energy", FocusEnergy},
    {"Bide", Bide},
    {"Metronome", MetronomeMove},
    {"Mirror Move", MirrorMove},
    {"Selfdestruct", Selfdestruct},
    {"Egg Bomb", EggBomb},
    {"Lick", Lick},
    {"Smog", Smog},
    {"Sludge", Sludge},
    {"Bone Club", BoneClub},
    {"Fire Blast", FireBlast},
    {"Waterfall", Waterfall},
    {"Clamp", Clamp},
    {"Swift", Swift},
    {"Skull Bash", SkullBash},
    {"Spike Cannon", SpikeCannon},
    {"Constrict", Constrict},
    {"Amnesia", Amnesia},
    {"Kinesis", Kinesis},
    {"Softboiled", Softboiled},
    {"Soft-Boiled", Softboiled},
    {"Hi Jump Kick", HighJumpKick},
    {"High Jump Kick", HighJumpKick},
    {"Glare", Glare},
    {"Dream Eater", DreamEater},
    {"Poison Gas", PoisonGas},
    {"Barrage", Barrage},
    {"Leech Life", LeechLife},
    {"Lovely Kiss", LovelyKiss},
    {"Sky Attack", SkyAttack},
    {"Transform", Transform},
    {"Bubble", Bubble},
    {"Dizzy Punch", DizzyPunch},
    {"Spore", Spore},
    {"Flash", Flash},
    {"Psywave", Psywave},
    {"Splash", Splash},
    {"Acid Armor", AcidArmor},
    {"Crabhammer", Crabhammer},
    {"Explosion", Explosion},
    {"Fury Swipes", FurySwipes},
    {"Bonemerang", Bonemerang},
    {"Rest", Rest},
    {"Rock Slide", RockSlide},
    {"Hyper Fang", HyperFang},
    {"Sharpen", Sharpen},
    {"Conversion", Conversion},
    {"Tri Attack", TriAttack},
    {"Super Fang", SuperFang},
    {"Slash", Slash},
    {"Substitute", Substitute},
    {"Struggle", Struggle},
    {"Sketch", Sketch},
    {"Triple Kick", TripleKick},
    {"Thief", Thief},
    {"Spider Web", SpiderWeb},
    {"Mind Reader", MindReader},
    {"Nightmare", Nightmare},
    {"Flame Wheel", FlameWheel},
    {"Snore", Snore},
    {"Curse", Curse},
    {"Flail", Flail},
    {"Conversion 2", Conversion2},
    {"Aeroblast", Aeroblast},
    {"Cotton Spore", CottonSpore},
    {"Reversal", Reversal},
    {"Spite", Spite},
    {"Powder Snow", PowderSnow},
    {"Protect", Protect},
    {"Mach Punch", MachPunch},
    {"Scary Face", ScaryFace},
    {"Faint Attack", FaintAttack},
    {"Feint Attack", FaintAttack},
    {"Sweet Kiss", SweetKiss},
    {"Belly Drum", BellyDrum},
    {"Sludge Bomb", SludgeBomb},
    {"Mud-slap", MudSlap},
    {"Mud-Slap", MudSlap},
    {"Octazooka", Octazooka},
    {"Spikes", Spikes},
    {"Zap Cannon", ZapCannon},
    {"Foresight", Foresight},
    {"Destiny Bond", DestinyBond},
    {"Perish Song", PerishSong},
    {"Icy Wind", IcyWind},
    {"Detect", Detect},
    {"Bone Rush", BoneRush},
    {"Lock-on", LockOn},
    {"Outrage", Outrage},
    {"Sandstorm", SandstormMove},
    {"Giga Drain", GigaDrain},
    {"Endure", Endure},
    {"Charm", Charm},
    {"Rollout", Rollout},
    {"False Swipe", FalseSwipe},
    {"Swagger", Swagger},
    {"Milk Drink", MilkDrink},
    {"Spark", Spark},
    {"Fury Cutter", FuryCutter},
    {"Steel Wing", SteelWing},
    {"Mean Look", MeanLook},
    {"Attract", Attract},
    {"Sleep Talk", SleepTalk},
    {"Heal Bell", HealBell},
    {"Return", Return},
    {"Present", Present},
    {"Frustration", Frustration},
    {"Safeguard", Safeguard},
    {"Pain Split", PainSplit},
    {"Sacred Fire", SacredFire},
    {"Magnitude", Magnitude},
    {"Dynamicpunch", Dynamicpunch},
    {"Dynamic Punch", Dynamicpunch},
    {"Megahorn", Megahorn},
    {"Dragonbreath", DragonBreath},
    {"Baton Pass", BatonPass},
    {"Encore", Encore},
    {"Pursuit", Pursuit},
    {"Rapid Spin", RapidSpin},
    {"Sweet Scent", SweetScent},
    {"Iron Tail", IronTail},
    {"Metal Claw", MetalClaw},
    {"Vital Throw", VitalThrow},
    {"Morning Sun", MorningSun},
    {"Synthesis", Synthesis},
    {"Moonlight", Moonlight},
    {"Hidden Power", HiddenPower},
    {"Cross Chop", CrossChop},
    {"Twister", Twister},
    {"Rain Dance", RainDance},
    {"Sunny Day", SunnyDay},
    {"Crunch", Crunch},
    {"Mirror Coat", MirrorCoat},
    {"Psych Up", PsychUp},
    {"Extremespeed", ExtremeSpeed},
    {"Extreme Speed", ExtremeSpeed},
    {"Ancientpower", Ancientpower},
    {"Ancient Power", Ancientpower},
    {"Shadow Ball", ShadowBall},
    {"Future Sight", FutureSight},
    {"Rock Smash", RockSmash},
    {"Whirlpool", Whirlpool},
    {"Beat Up", BeatUp},
    {"Fake Out", FakeOut},
    {"Uproar", Uproar},
    {"Stockpile", Stockpile},
    {"Spit Up", SpitUp},
    {"Swallow", Swallow},
    {"Heat Wave", HeatWave},
    {"Hail", HailMove},
    {"Torment", Torment},
    {"Flatter", Flatter},
    {"Will-o-wisp", WillOWisp},
    {"Will-O-Wisp", WillOWisp},
    {"Memento", Memento},
    {"Facade", Facade},
    {"Focus Punch", FocusPunch},
    {"Smellingsalt", Smellingsalt},
    {"Follow Me", FollowMe},
    {"Nature Power", NaturePower},
    {"Charge", Charge},
    {"Taunt", Taunt},
    {"Helping Hand", HelpingHand},
    {"Trick", Trick},
    {"Role Play", RolePlay},
    {"Wish", Wish},
    {"Assist", Assist},
    {"Ingrain", Ingrain},
    {"Superpower", Superpower},
    {"Magic Coat", MagicCoat},
    {"Recycle", Recycle},
    {"Revenge", Revenge},
    {"Brick Break", BrickBreak},
    {"Yawn", Yawn},
    {"Knock Off", KnockOff},
    {"Endeavor", Endeavor},
    {"Eruption", Eruption},
    {"Skill Swap", SkillSwap},
    {"Imprison", Imprison},
    {"Refresh", Refresh},
    {"Grudge", Grudge},
    {"Snatch", Snatch},
    {"Secret Power", SecretPower},
    {"Dive", Dive},
    {"Arm Thrust", ArmThrust},
    {"Camouflage", Camouflage},
    {"Tail Glow", TailGlow},
    {"Luster Purge", LusterPurge},
    {"Mist Ball", MistBall},
    {"Featherdance", Featherdance},
    {"Feather Dance", Featherdance},
    {"Teeter Dance", TeeterDance},
    {"Blaze Kick", BlazeKick},
    {"Mud Sport", MudSport},
    {"Ice Ball", IceBall},
    {"Needle Arm", NeedleArm},
    {"Slack Off", SlackOff},
    {"Hyper Voice", HyperVoice},
    {"Poison Fang", PoisonFang},
    {"Crush Claw", CrushClaw},
    {"Blast Burn", BlastBurn},
    {"Hydro Cannon", HydroCannon},
    {"Meteor Mash", MeteorMash},
    {"Astonish", Astonish},
    {"Weather Ball", WeatherBall},
    {"Aromatherapy", Aromatherapy},
    {"Fake Tears", FakeTears},
    {"Air Cutter", AirCutter},
    {"Overheat", Overheat},
    {"Odor Sleuth", OdorSleuth},
    {"Rock Tomb", RockTomb},
    {"Silver Wind", SilverWind},
    {"Metal Sound", MetalSound},
    {"Grasswhistle", Grasswhistle},
    {"Tickle", Tickle},
    {"Cosmic Power", CosmicPower},
    {"Water Spout", WaterSpout},
    {"Signal Beam", SignalBeam},
    {"Shadow Punch", ShadowPunch},
    {"Extrasensory", Extrasensory},
    {"Sky Uppercut", SkyUppercut},
    {"Sand Tomb", SandTomb},
    {"Sheer Cold", SheerCold},
    {"Muddy Water", MuddyWater},
    {"Bullet Seed", BulletSeed},
    {"Aerial Ace", AerialAce},
    {"Icicle Spear", IcicleSpear},
    {"Iron Defense", IronDefense},
    {"Block", Block},
    {"Howl", Howl},
    {"Dragon Claw", DragonClaw},
    {"Frenzy Plant", FrenzyPlant},
    {"Bulk Up", BulkUp},
    {"Bounce", Bounce},
    {"Mud Shot", MudShot},
    {"Poison Tail", PoisonTail},
    {"Covet", Covet},
    {"Volt Tackle", VoltTackle},
    {"Magical Leaf", MagicalLeaf},
    {"Water Sport", WaterSport},
    {"Calm Mind", CalmMind},
    {"Leaf Blade", LeafBlade},
    {"Dragon Dance", DragonDance},
    {"Rock Blast", RockBlast},
    {"Shock Wave", ShockWave},
    {"Water Pulse", WaterPulse},
    {"Doom Desire", DoomDesire},
    {"Psycho Boost", PsychoBoost},
    {"Roost", Roost},
    {"Gravity", Gravity},
    {"Miracle Eye", MiracleEye},
    {"Wake-up Slap", WakeUpSlap},
    {"Hammer Arm", HammerArm},
    {"Gyro Ball", GyroBall},
    {"Healing Wish", HealingWish},
    {"Brine", Brine},
    {"Natural Gift", NaturalGift},
    {"Feint", Feint},
    {"Pluck", Pluck},
    {"Tailwind", Tailwind},
    {"Acupressure", Acupressure},
    {"Metal Burst", MetalBurst},
    {"U-turn", UTurn},
    {"Close Combat", CloseCombat},
    {"Payback", Payback},
    {"Assurance", Assurance},
    {"Embargo", Embargo},
    {"Fling", Fling},
    {"Psycho Shift", PsychoShift},
    {"Trump Card", TrumpCard},
    {"Heal Block", HealBlock},
    {"Wring Out", WringOut},
    {"Power Trick", PowerTrick},
    {"Gastro Acid", GastroAcid},
    {"Lucky Chant", LuckyChant},
    {"Me First", MeFirst},
    {"Copycat", Copycat},
    {"Power Swap", PowerSwap},
    {"Guard Swap", GuardSwap},
    {"Punishment", Punishment},
    {"Last Resort", LastResort},
    {"Worry Seed", WorrySeed},
    {"Sucker Punch", SuckerPunch},
    {"Toxic Spikes", ToxicSpikes},
    {"Heart Swap", HeartSwap},
    {"Aqua Ring", AquaRing},
    {"Magnet Rise", MagnetRise},
    {"Flare Blitz", FlareBlitz},
    {"Force Palm", ForcePalm},
    {"Aura Sphere", AuraSphere},
    {"Rock Polish", RockPolish},
    {"Poison Jab", PoisonJab},
    {"Dark Pulse", DarkPulse},
    {"Night Slash", NightSlash},
    {"Aqua Tail", AquaTail},
    {"Seed Bomb", SeedBomb},
    {"Air Slash", AirSlash},
    {"X-scissor", XScissor},
    {"X-Scissor", XScissor},
    {"Bug Buzz", BugBuzz},
    {"Dragon Pulse", DragonPulse},
    {"Dragon Rush", DragonRush},
    {"Power Gem", PowerGem},
    {"Drain Punch", DrainPunch},
    {"Vacuum Wave", VacuumWave},
    {"Focus Blast", FocusBlast},
    {"Energy Ball", EnergyBall},
    {"Brave Bird", BraveBird},
    {"Earth Power", EarthPower},
    {"Switcheroo", Switcheroo},
    {"Giga Impact", GigaImpact},
    {"Nasty Plot", NastyPlot},
    {"Bullet Punch", BulletPunch},
    {"Avalanche", Avalanche},
    {"Ice Shard", IceShard},
    {"Shadow Claw", ShadowClaw},
    {"Thunder Fang", ThunderFang},
    {"Ice Fang", IceFang},
    {"Fire Fang", FireFang},
    {"Shadow Sneak", ShadowSneak},
    {"Mud Bomb", MudBomb},
    {"Psycho Cut", PsychoCut},
    {"Zen Headbutt", ZenHeadbutt},
    {"Mirror Shot", MirrorShot},
    {"Flash Cannon", FlashCannon},
    {"Rock Climb", RockClimb},
    {"Defog", Defog},
    {"Trick Room", TrickRoom},
    {"Draco Meteor", DracoMeteor},
    {"Discharge", Discharge},
    {"Lava Plume", LavaPlume},
    {"Leaf Storm", LeafStorm},
    {"Power Whip", PowerWhip},
    {"Rock Wrecker", RockWrecker},
    {"Cross Poison", CrossPoison},
    {"Gunk Shot", GunkShot},
    {"Iron Head", IronHead},
    {"Magnet Bomb", MagnetBomb},
    {"Stone Edge", StoneEdge},
    {"Captivate", Captivate},
    {"Stealth Rock", StealthRock},
    {"Grass Knot", GrassKnot},
    {"Chatter", Chatter},
    {"Judgment", Judgment},
    {"Bug Bite", BugBite},
    {"Charge Beam", ChargeBeam},
    {"Wood Hammer", WoodHammer},
    {"Aqua Jet", AquaJet},
    {"Attack Order", AttackOrder},
    {"Defend Order", DefendOrder},
    {"Heal Order", HealOrder},
    {"Head Smash", HeadSmash},
    {"Double Hit", DoubleHit},
    {"Roar Of Time", RoarOfTime},
    {"Spacial Rend", SpacialRend},
    {"Lunar Dance", LunarDance},
    {"Crush Grip", CrushGrip},
    {"Magma Storm", MagmaStorm},
    {"Dark Void", DarkVoid},
    {"Seed Flare", SeedFlare},
    {"Ominous Wind", OminousWind},
    {"Shadow Force", ShadowForce}
};

inline std::unordered_map<Move, std::string> create_reverse_move_map() {
    std::unordered_map<Move, std::string> reverse_map;
    for (const auto& [str, move] : STRING_TO_MOVE_MAP) {
        reverse_map[move] = str;
    }
    return reverse_map;
}

static const auto MOVE_TO_STRING_MAP =
    create_reverse_move_map();

enum MoveFlag {
    BOOSTS_ATTACKER_STAT,
    AFFECTED_BY_KINGS_ROCK,
    BADLY_POISONS,
    BOOSTS_ATTACKERS_ATTACK,
    BOOSTS_ATTACKERS_CRIT_RATE,
    BOOSTS_ATTACKERS_DEFENSE,
    BOOSTS_ATTACKERS_EVASION,
    BOOSTS_ATTACKERS_SPECIAL_ATTACK,
    BOOSTS_ATTACKERS_SPECIAL_DEFENSE,
    BOOSTS_ATTACKERS_SPEED,
    BREAKS_PROTECT,
    BURNS_DEFENDER,
    BYPASSES_PROTECT,
    CAN_BE_REFLECTED_BY_MIRROR_MOVE,
    CAN_BE_SNATCHED,
    CHANGES_WEATHER,
    CONFUSES_DEFENDER_10,
    CONFUSES_DEFENDER, // TODO remove
    CONTINUES,
    DEALS_DOUBLE_AFTER_MINIMIZE,
    FLINCHES_DEFENDER,
    FORCES_USER_OUT,
    FREEZES_DEFENDER,
    GOES_INTO_AIR,
    GOES_UNDER_GROUND,
    GOES_UNDER_WATER,
    HAS_FIXED_DAMAGE,
    HEALS_ATTACKER,
    HITS_DEFENDER_IN_AIR,
    HITS_DEFENDER_UNDER_GROUND,
    HITS_DEFENDER_UNDER_WATER,
    LOWERS_ATTACKERS_ATTACK,
    LOWERS_ATTACKERS_DEFENSE,
    LOWERS_ATTACKERS_SPECIAL_ATTACK,
    LOWERS_ATTACKERS_SPECIAL_DEFENSE,
    LOWERS_ATTACKERS_SPEED,
    LOWERS_DEFENDER_ACCURACY,
    LOWERS_DEFENDER_ATTACK,
    LOWERS_DEFENDER_DEFENSE,
    LOWERS_DEFENDER_EVASION,
    LOWERS_DEFENDER_SPECIAL_ATTACK,
    LOWERS_DEFENDER_SPECIAL_DEFENSE,
    LOWERS_DEFENDER_SPEED,
    MAKES_ATTACKER_FAINT,
    MAKES_CONTACT,
    MAKES_DEFENDER_SLEEP,
    BYPASSES_ACCURACY,
    OMNI_BOOSTS_ATTACKER,
    PARALYZES_DEFENDER,
    POISONS_DEFENDER,
    RAISES_DEFENDER_ATTACK,
    RAISES_DEFENDER_SPECIAL_ATTACK,
    REQUIRES_CHARGING_TURN,
    REQUIRES_RECHARGE_TURN,
    GOES_INTO_VOID,
    HAS_INCREASED_CRIT_CHANCE,
    HAS_RECOIL,
    HITS_MULTIPLE_TIMES,
    LASTS_MULTIPLE_TURNS,
    KOS_IN_ONE_HIT,
    IS_OTHER,
    HAS_POWER,
    PROTECTS_USER,
    IS_SOUND_BASED,
    CANT_BE_USED_DURING_GRAVITY,
    POWERS_IRON_FIST,
    COUNT
};

using MoveFlagSet = std::array<bool, COUNT>;
static constexpr std::array<
    MoveFlagSet,
    MoveCount
> MOVE_FLAGS = [] {
    std::array<MoveFlagSet, MoveCount> flags{};
    for (auto& flag : flags) {
        flag.fill(false);
    }

    flags[BulletPunch][POWERS_IRON_FIST] = true;
    flags[CometPunch][POWERS_IRON_FIST] = true;
    flags[DizzyPunch][POWERS_IRON_FIST] = true;
    flags[DrainPunch][POWERS_IRON_FIST] = true;
    flags[Dynamicpunch][POWERS_IRON_FIST] = true;
    flags[FirePunch][POWERS_IRON_FIST] = true;
    flags[FocusPunch][POWERS_IRON_FIST] = true;
    flags[HammerArm][POWERS_IRON_FIST] = true;
    flags[IcePunch][POWERS_IRON_FIST] = true;
    flags[MachPunch][POWERS_IRON_FIST] = true;
    flags[ShadowPunch][POWERS_IRON_FIST] = true;
    flags[SkyUppercut][POWERS_IRON_FIST] = true;
    flags[ThunderPunch][POWERS_IRON_FIST] = true;

    flags[Pound][HAS_POWER] = true;
    flags[DoubleSlap][HAS_POWER] = true;
    flags[CometPunch][HAS_POWER] = true;
    flags[MegaPunch][HAS_POWER] = true;
    flags[PayDay][HAS_POWER] = true;
    flags[FirePunch][HAS_POWER] = true;
    flags[IcePunch][HAS_POWER] = true;
    flags[ThunderPunch][HAS_POWER] = true;
    flags[Scratch][HAS_POWER] = true;
    flags[ViceGrip][HAS_POWER] = true;
    flags[RazorWind][HAS_POWER] = true;
    flags[Cut][HAS_POWER] = true;
    flags[Gust][HAS_POWER] = true;
    flags[WingAttack][HAS_POWER] = true;
    flags[Fly][HAS_POWER] = true;
    flags[Bind][HAS_POWER] = true;
    flags[Slam][HAS_POWER] = true;
    flags[VineWhip][HAS_POWER] = true;
    flags[Stomp][HAS_POWER] = true;
    flags[DoubleKick][HAS_POWER] = true;
    flags[MegaKick][HAS_POWER] = true;
    flags[JumpKick][HAS_POWER] = true;
    flags[RollingKick][HAS_POWER] = true;
    flags[Headbutt][HAS_POWER] = true;
    flags[HornAttack][HAS_POWER] = true;
    flags[FuryAttack][HAS_POWER] = true;
    flags[Tackle][HAS_POWER] = true;
    flags[BodySlam][HAS_POWER] = true;
    flags[Wrap][HAS_POWER] = true;
    flags[TakeDown][HAS_POWER] = true;
    flags[Thrash][HAS_POWER] = true;
    flags[DoubleEdge][HAS_POWER] = true;
    flags[PoisonSting][HAS_POWER] = true;
    flags[Twineedle][HAS_POWER] = true;
    flags[PinMissile][HAS_POWER] = true;
    flags[Bite][HAS_POWER] = true;
    flags[Acid][HAS_POWER] = true;
    flags[Ember][HAS_POWER] = true;
    flags[Flamethrower][HAS_POWER] = true;
    flags[WaterGun][HAS_POWER] = true;
    flags[HydroPump][HAS_POWER] = true;
    flags[Surf][HAS_POWER] = true;
    flags[IceBeam][HAS_POWER] = true;
    flags[Blizzard][HAS_POWER] = true;
    flags[Psybeam][HAS_POWER] = true;
    flags[Bubblebeam][HAS_POWER] = true;
    flags[AuroraBeam][HAS_POWER] = true;
    flags[HyperBeam][HAS_POWER] = true;
    flags[Peck][HAS_POWER] = true;
    flags[DrillPeck][HAS_POWER] = true;
    flags[Submission][HAS_POWER] = true;
    flags[Strength][HAS_POWER] = true;
    flags[Absorb][HAS_POWER] = true;
    flags[MegaDrain][HAS_POWER] = true;
    flags[RazorLeaf][HAS_POWER] = true;
    flags[SolarBeam][HAS_POWER] = true;
    flags[PetalDance][HAS_POWER] = true;
    flags[FireSpin][HAS_POWER] = true;
    flags[Thundershock][HAS_POWER] = true;
    flags[Thunderbolt][HAS_POWER] = true;
    flags[RockThrow][HAS_POWER] = true;
    flags[Earthquake][HAS_POWER] = true;
    flags[Dig][HAS_POWER] = true;
    flags[Confusion][HAS_POWER] = true;
    flags[PsychicMove][HAS_POWER] = true;
    flags[QuickAttack][HAS_POWER] = true;
    flags[Selfdestruct][HAS_POWER] = true;
    flags[EggBomb][HAS_POWER] = true;
    flags[Lick][HAS_POWER] = true;
    flags[Smog][HAS_POWER] = true;
    flags[Sludge][HAS_POWER] = true;
    flags[BoneClub][HAS_POWER] = true;
    flags[FireBlast][HAS_POWER] = true;
    flags[Waterfall][HAS_POWER] = true;
    flags[Clamp][HAS_POWER] = true;
    flags[Swift][HAS_POWER] = true;
    flags[SkullBash][HAS_POWER] = true;
    flags[SpikeCannon][HAS_POWER] = true;
    flags[Constrict][HAS_POWER] = true;
    flags[HighJumpKick][HAS_POWER] = true;
    flags[Barrage][HAS_POWER] = true;
    flags[LeechLife][HAS_POWER] = true;
    flags[SkyAttack][HAS_POWER] = true;
    flags[Bubble][HAS_POWER] = true;
    flags[DizzyPunch][HAS_POWER] = true;
    flags[Crabhammer][HAS_POWER] = true;
    flags[Explosion][HAS_POWER] = true;
    flags[FuryAttack][HAS_POWER] = true;
    flags[Bonemerang][HAS_POWER] = true;
    flags[RockSlide][HAS_POWER] = true;
    flags[HyperFang][HAS_POWER] = true;
    flags[TriAttack][HAS_POWER] = true;
    flags[Slash][HAS_POWER] = true;
    flags[FlameWheel][HAS_POWER] = true;
    flags[Aeroblast][HAS_POWER] = true;
    flags[PowderSnow][HAS_POWER] = true;
    flags[MachPunch][HAS_POWER] = true;
    flags[FaintAttack][HAS_POWER] = true;
    flags[SludgeBomb][HAS_POWER] = true;
    flags[MudSlap][HAS_POWER] = true;
    flags[Octazooka][HAS_POWER] = true;
    flags[ZapCannon][HAS_POWER] = true;
    flags[IcyWind][HAS_POWER] = true;
    flags[BoneRush][HAS_POWER] = true;
    flags[Outrage][HAS_POWER] = true;
    flags[GigaDrain][HAS_POWER] = true;
    flags[Spark][HAS_POWER] = true;
    flags[SteelWing][HAS_POWER] = true;
    flags[Return][HAS_POWER] = true;
    flags[Frustration][HAS_POWER] = true;
    flags[SacredFire][HAS_POWER] = true;
    flags[Dynamicpunch][HAS_POWER] = true;
    flags[Megahorn][HAS_POWER] = true;
    flags[DragonBreath][HAS_POWER] = true;
    flags[IronTail][HAS_POWER] = true;
    flags[MetalClaw][HAS_POWER] = true;
    flags[VitalThrow][HAS_POWER] = true;
    flags[CrossChop][HAS_POWER] = true;
    flags[Twister][HAS_POWER] = true;
    flags[Crunch][HAS_POWER] = true;
    flags[ExtremeSpeed][HAS_POWER] = true;
    flags[Ancientpower][HAS_POWER] = true;
    flags[ShadowBall][HAS_POWER] = true;
    flags[RockSmash][HAS_POWER] = true;
    flags[Whirlpool][HAS_POWER] = true;
    flags[HeatWave][HAS_POWER] = true;
    flags[Superpower][HAS_POWER] = true;
    flags[Dive][HAS_POWER] = true;
    flags[ArmThrust][HAS_POWER] = true;
    flags[LusterPurge][HAS_POWER] = true;
    flags[MistBall][HAS_POWER] = true;
    flags[BlazeKick][HAS_POWER] = true;
    flags[NeedleArm][HAS_POWER] = true;
    flags[HyperVoice][HAS_POWER] = true;
    flags[PoisonFang][HAS_POWER] = true;
    flags[CrushClaw][HAS_POWER] = true;
    flags[BlastBurn][HAS_POWER] = true;
    flags[HydroCannon][HAS_POWER] = true;
    flags[MeteorMash][HAS_POWER] = true;
    flags[Astonish][HAS_POWER] = true;
    flags[AirCutter][HAS_POWER] = true;
    flags[Overheat][HAS_POWER] = true;
    flags[RockTomb][HAS_POWER] = true;
    flags[SilverWind][HAS_POWER] = true;
    flags[SignalBeam][HAS_POWER] = true;
    flags[ShadowPunch][HAS_POWER] = true;
    flags[Extrasensory][HAS_POWER] = true;
    flags[SkyUppercut][HAS_POWER] = true;
    flags[SandTomb][HAS_POWER] = true;
    flags[MuddyWater][HAS_POWER] = true;
    flags[BulletSeed][HAS_POWER] = true;
    flags[AerialAce][HAS_POWER] = true;
    flags[IcicleSpear][HAS_POWER] = true;
    flags[DragonClaw][HAS_POWER] = true;
    flags[FrenzyPlant][HAS_POWER] = true;
    flags[Bounce][HAS_POWER] = true;
    flags[MudShot][HAS_POWER] = true;
    flags[PoisonTail][HAS_POWER] = true;
    flags[VoltTackle][HAS_POWER] = true;
    flags[MagicalLeaf][HAS_POWER] = true;
    flags[LeafBlade][HAS_POWER] = true;
    flags[RockBlast][HAS_POWER] = true;
    flags[ShockWave][HAS_POWER] = true;
    flags[WaterPulse][HAS_POWER] = true;
    flags[PsychoBoost][HAS_POWER] = true;
    flags[HammerArm][HAS_POWER] = true;
    flags[CloseCombat][HAS_POWER] = true;
    flags[FlareBlitz][HAS_POWER] = true;
    flags[ForcePalm][HAS_POWER] = true;
    flags[AuraSphere][HAS_POWER] = true;
    flags[PoisonJab][HAS_POWER] = true;
    flags[DarkPulse][HAS_POWER] = true;
    flags[NightSlash][HAS_POWER] = true;
    flags[AquaTail][HAS_POWER] = true;
    flags[SeedBomb][HAS_POWER] = true;
    flags[AirSlash][HAS_POWER] = true;
    flags[XScissor][HAS_POWER] = true;
    flags[BugBuzz][HAS_POWER] = true;
    flags[DragonPulse][HAS_POWER] = true;
    flags[DragonRush][HAS_POWER] = true;
    flags[PowerGem][HAS_POWER] = true;
    flags[DrainPunch][HAS_POWER] = true;
    flags[VacuumWave][HAS_POWER] = true;
    flags[FocusBlast][HAS_POWER] = true;
    flags[EnergyBall][HAS_POWER] = true;
    flags[BraveBird][HAS_POWER] = true;
    flags[EarthPower][HAS_POWER] = true;
    flags[GigaImpact][HAS_POWER] = true;
    flags[BulletPunch][HAS_POWER] = true;
    flags[IceShard][HAS_POWER] = true;
    flags[ShadowClaw][HAS_POWER] = true;
    flags[ThunderFang][HAS_POWER] = true;
    flags[IceFang][HAS_POWER] = true;
    flags[FireFang][HAS_POWER] = true;
    flags[ShadowSneak][HAS_POWER] = true;
    flags[MudBomb][HAS_POWER] = true;
    flags[PsychoCut][HAS_POWER] = true;
    flags[ZenHeadbutt][HAS_POWER] = true;
    flags[MirrorShot][HAS_POWER] = true;
    flags[FlashCannon][HAS_POWER] = true;
    flags[RockClimb][HAS_POWER] = true;
    flags[DracoMeteor][HAS_POWER] = true;
    flags[Discharge][HAS_POWER] = true;
    flags[LavaPlume][HAS_POWER] = true;
    flags[LeafStorm][HAS_POWER] = true;
    flags[PowerWhip][HAS_POWER] = true;
    flags[RockWrecker][HAS_POWER] = true;
    flags[CrossPoison][HAS_POWER] = true;
    flags[GunkShot][HAS_POWER] = true;
    flags[IronHead][HAS_POWER] = true;
    flags[MagnetBomb][HAS_POWER] = true;
    flags[StoneEdge][HAS_POWER] = true;
    flags[ChargeBeam][HAS_POWER] = true;
    flags[WoodHammer][HAS_POWER] = true;
    flags[AquaJet][HAS_POWER] = true;
    flags[AttackOrder][HAS_POWER] = true;
    flags[HeadSmash][HAS_POWER] = true;
    flags[DoubleHit][HAS_POWER] = true;
    flags[RoarOfTime][HAS_POWER] = true;
    flags[SpacialRend][HAS_POWER] = true;
    flags[SeedFlare][HAS_POWER] = true;
    flags[OminousWind][HAS_POWER] = true;
    flags[ShadowForce][HAS_POWER] = true;

    flags[Absorb][HEALS_ATTACKER] = true;
    flags[MegaDrain][HEALS_ATTACKER] = true;
    flags[Recover][HEALS_ATTACKER] = true;
    flags[Softboiled][HEALS_ATTACKER] = true;
    flags[LeechLife][HEALS_ATTACKER] = true;
    flags[GigaDrain][HEALS_ATTACKER] = true;
    flags[MilkDrink][HEALS_ATTACKER] = true;
    flags[MorningSun][HEALS_ATTACKER] = true;
    flags[Synthesis][HEALS_ATTACKER] = true;
    flags[Moonlight][HEALS_ATTACKER] = true;
    flags[SlackOff][HEALS_ATTACKER] = true;
    flags[DrainPunch][HEALS_ATTACKER] = true;
    flags[HealOrder][HEALS_ATTACKER] = true;

    flags[SwordsDance][BOOSTS_ATTACKER_STAT] = true;
    flags[Growth][BOOSTS_ATTACKER_STAT] = true;
    flags[Meditate][BOOSTS_ATTACKER_STAT] = true;
    flags[Agility][BOOSTS_ATTACKER_STAT] = true;
    flags[DoubleTeam][BOOSTS_ATTACKER_STAT] = true;
    flags[Harden][BOOSTS_ATTACKER_STAT] = true;
    flags[Minimize][BOOSTS_ATTACKER_STAT] = true;
    flags[Withdraw][BOOSTS_ATTACKER_STAT] = true;
    flags[Amnesia][BOOSTS_ATTACKER_STAT] = true;
    flags[AcidArmor][BOOSTS_ATTACKER_STAT] = true;
    flags[Sharpen][BOOSTS_ATTACKER_STAT] = true;
    flags[TailGlow][BOOSTS_ATTACKER_STAT] = true;
    flags[CosmicPower][BOOSTS_ATTACKER_STAT] = true;
    flags[IronDefense][BOOSTS_ATTACKER_STAT] = true;
    flags[Howl][BOOSTS_ATTACKER_STAT] = true;
    flags[BulkUp][BOOSTS_ATTACKER_STAT] = true;
    flags[CalmMind][BOOSTS_ATTACKER_STAT] = true;
    flags[DragonDance][BOOSTS_ATTACKER_STAT] = true;
    flags[RockPolish][BOOSTS_ATTACKER_STAT] = true;
    flags[NastyPlot][BOOSTS_ATTACKER_STAT] = true;
    flags[DefendOrder][BOOSTS_ATTACKER_STAT] = true;

    flags[SwordsDance][BOOSTS_ATTACKERS_ATTACK] = true;
    flags[Meditate][BOOSTS_ATTACKERS_ATTACK] = true;
    flags[Sharpen][BOOSTS_ATTACKERS_ATTACK] = true;
    flags[BellyDrum][BOOSTS_ATTACKERS_ATTACK] = true;
    flags[MetalClaw][BOOSTS_ATTACKERS_ATTACK] = true;
    flags[MeteorMash][BOOSTS_ATTACKERS_ATTACK] = true;
    flags[Howl][BOOSTS_ATTACKERS_ATTACK] = true;
    flags[BulkUp][BOOSTS_ATTACKERS_ATTACK] = true;
    flags[DragonDance][BOOSTS_ATTACKERS_ATTACK] = true;

    flags[Superpower][LOWERS_ATTACKERS_ATTACK] = true;

    flags[Harden][BOOSTS_ATTACKERS_DEFENSE] = true;
    flags[Withdraw][BOOSTS_ATTACKERS_DEFENSE] = true;
    flags[SkullBash][BOOSTS_ATTACKERS_DEFENSE] = true;
    flags[AcidArmor][BOOSTS_ATTACKERS_DEFENSE] = true;
    flags[SteelWing][BOOSTS_ATTACKERS_DEFENSE] = true;
    flags[CosmicPower][BOOSTS_ATTACKERS_DEFENSE] = true;
    flags[IronDefense][BOOSTS_ATTACKERS_DEFENSE] = true;
    flags[BulkUp][BOOSTS_ATTACKERS_DEFENSE] = true;
    flags[DefendOrder][BOOSTS_ATTACKERS_DEFENSE] = true;

    flags[Superpower][LOWERS_ATTACKERS_DEFENSE] = true;
    flags[CloseCombat][LOWERS_ATTACKERS_DEFENSE] = true;

    flags[Overheat][LOWERS_ATTACKERS_SPECIAL_ATTACK] = true;
    flags[PsychoBoost][LOWERS_ATTACKERS_SPECIAL_ATTACK] = true;
    flags[DracoMeteor][LOWERS_ATTACKERS_SPECIAL_ATTACK] = true;
    flags[LeafStorm][LOWERS_ATTACKERS_SPECIAL_ATTACK] = true;

    flags[Growth][BOOSTS_ATTACKERS_SPECIAL_ATTACK] = true;
    flags[TailGlow][BOOSTS_ATTACKERS_SPECIAL_ATTACK] = true;
    flags[CalmMind][BOOSTS_ATTACKERS_SPECIAL_ATTACK] = true;
    flags[NastyPlot][BOOSTS_ATTACKERS_SPECIAL_ATTACK] = true;
    flags[ChargeBeam][BOOSTS_ATTACKERS_SPECIAL_ATTACK] = true;

    flags[Amnesia][BOOSTS_ATTACKERS_SPECIAL_DEFENSE] = true;
    flags[CosmicPower][BOOSTS_ATTACKERS_SPECIAL_DEFENSE] = true;
    flags[CalmMind][BOOSTS_ATTACKERS_SPECIAL_DEFENSE] = true;
    flags[DefendOrder][BOOSTS_ATTACKERS_SPECIAL_DEFENSE] = true;

    flags[CloseCombat][LOWERS_ATTACKERS_SPECIAL_DEFENSE] = true;

    flags[Agility][BOOSTS_ATTACKERS_SPEED] = true;
    flags[DragonDance][BOOSTS_ATTACKERS_SPEED] = true;
    flags[RockPolish][BOOSTS_ATTACKERS_SPEED] = true;

    flags[HammerArm][LOWERS_ATTACKERS_SPEED] = true;

    flags[DoubleTeam][BOOSTS_ATTACKERS_EVASION] = true;
    flags[Minimize][BOOSTS_ATTACKERS_EVASION] = true;

    flags[FocusEnergy][BOOSTS_ATTACKERS_CRIT_RATE] = true;

    flags[Ancientpower][OMNI_BOOSTS_ATTACKER] = true;
    flags[SilverWind][OMNI_BOOSTS_ATTACKER] = true;
    flags[OminousWind][OMNI_BOOSTS_ATTACKER] = true;

    flags[Swagger][RAISES_DEFENDER_ATTACK] = true;

    flags[Growl][LOWERS_DEFENDER_ATTACK] = true;
    flags[AuroraBeam][LOWERS_DEFENDER_ATTACK] = true;
    flags[Charm][LOWERS_DEFENDER_ATTACK] = true;
    flags[Memento][LOWERS_DEFENDER_ATTACK] = true;
    flags[Featherdance][LOWERS_DEFENDER_ATTACK] = true;
    flags[Tickle][LOWERS_DEFENDER_ATTACK] = true;

    flags[Flatter][RAISES_DEFENDER_SPECIAL_ATTACK] = true;

    flags[Memento][LOWERS_DEFENDER_SPECIAL_ATTACK] = true;
    flags[MistBall][LOWERS_DEFENDER_SPECIAL_ATTACK] = true;

    flags[TailWhip][LOWERS_DEFENDER_DEFENSE] = true;
    flags[Leer][LOWERS_DEFENDER_DEFENSE] = true;
    flags[Screech][LOWERS_DEFENDER_DEFENSE] = true;
    flags[IronTail][LOWERS_DEFENDER_DEFENSE] = true;
    flags[Crunch][LOWERS_DEFENDER_DEFENSE] = true;
    flags[RockSmash][LOWERS_DEFENDER_DEFENSE] = true;
    flags[CrushClaw][LOWERS_DEFENDER_DEFENSE] = true;
    flags[Tickle][LOWERS_DEFENDER_DEFENSE] = true;

    flags[Acid][LOWERS_DEFENDER_SPECIAL_DEFENSE] = true;
    flags[PsychicMove][LOWERS_DEFENDER_SPECIAL_DEFENSE] = true;
    flags[ShadowBall][LOWERS_DEFENDER_SPECIAL_DEFENSE] = true;
    flags[LusterPurge][LOWERS_DEFENDER_SPECIAL_DEFENSE] = true;
    flags[FakeTears][LOWERS_DEFENDER_SPECIAL_DEFENSE] = true;
    flags[MetalSound][LOWERS_DEFENDER_SPECIAL_DEFENSE] = true;
    flags[BugBuzz][LOWERS_DEFENDER_SPECIAL_DEFENSE] = true;
    flags[FocusBlast][LOWERS_DEFENDER_SPECIAL_DEFENSE] = true;
    flags[EnergyBall][LOWERS_DEFENDER_SPECIAL_DEFENSE] = true;
    flags[EarthPower][LOWERS_DEFENDER_SPECIAL_DEFENSE] = true;
    flags[FlashCannon][LOWERS_DEFENDER_SPECIAL_DEFENSE] = true;
    flags[SeedFlare][LOWERS_DEFENDER_SPECIAL_DEFENSE] = true;

    flags[Bubblebeam][LOWERS_DEFENDER_SPEED] = true;
    flags[StringShot][LOWERS_DEFENDER_SPEED] = true;
    flags[Constrict][LOWERS_DEFENDER_SPEED] = true;
    flags[Bubble][LOWERS_DEFENDER_SPEED] = true;
    flags[CottonSpore][LOWERS_DEFENDER_SPEED] = true;
    flags[ScaryFace][LOWERS_DEFENDER_SPEED] = true;
    flags[IcyWind][LOWERS_DEFENDER_SPEED] = true;
    flags[RockTomb][LOWERS_DEFENDER_SPEED] = true;
    flags[MudShot][LOWERS_DEFENDER_SPEED] = true;

    flags[SandAttack][LOWERS_DEFENDER_ACCURACY] = true;
    flags[Smokescreen][LOWERS_DEFENDER_ACCURACY] = true;
    flags[Kinesis][LOWERS_DEFENDER_ACCURACY] = true;
    flags[Flash][LOWERS_DEFENDER_ACCURACY] = true;
    flags[MudSlap][LOWERS_DEFENDER_ACCURACY] = true;
    flags[Octazooka][LOWERS_DEFENDER_ACCURACY] = true;
    flags[MuddyWater][LOWERS_DEFENDER_ACCURACY] = true;
    flags[MudBomb][LOWERS_DEFENDER_ACCURACY] = true;
    flags[MirrorShot][LOWERS_DEFENDER_ACCURACY] = true;

    flags[SweetScent][LOWERS_DEFENDER_EVASION] = true;

    flags[Blizzard][BYPASSES_ACCURACY] = true;
    flags[Thunder][BYPASSES_ACCURACY] = true;
    flags[Swift][BYPASSES_ACCURACY] = true;
    flags[FaintAttack][BYPASSES_ACCURACY] = true;
    flags[VitalThrow][BYPASSES_ACCURACY] = true;
    flags[ShadowPunch][BYPASSES_ACCURACY] = true;
    flags[AerialAce][BYPASSES_ACCURACY] = true;
    flags[MagicalLeaf][BYPASSES_ACCURACY] = true;
    flags[ShockWave][BYPASSES_ACCURACY] = true;
    flags[AuraSphere][BYPASSES_ACCURACY] = true;
    flags[MagnetBomb][BYPASSES_ACCURACY] = true;

    flags[Bounce][CANT_BE_USED_DURING_GRAVITY] = true;
    flags[Fly][CANT_BE_USED_DURING_GRAVITY] = true;
    flags[HighJumpKick][CANT_BE_USED_DURING_GRAVITY] = true;
    flags[JumpKick][CANT_BE_USED_DURING_GRAVITY] = true;
    flags[MagnetRise][CANT_BE_USED_DURING_GRAVITY] = true;
    flags[Splash][CANT_BE_USED_DURING_GRAVITY] = true;

    flags[Detect][PROTECTS_USER] = true;
    flags[Protect][PROTECTS_USER] = true;

    flags[Disable][IS_OTHER] = true;
    flags[Mist][IS_OTHER] = true;
    flags[LowKick][IS_OTHER] = true;
    flags[Counter][IS_OTHER] = true;
    flags[LeechSeed][IS_OTHER] = true;
    flags[Rage][IS_OTHER] = true;
    flags[Teleport][IS_OTHER] = true;
    flags[Mimic][IS_OTHER] = true;
    flags[DefenseCurl][IS_OTHER] = true;
    flags[Barrier][IS_OTHER] = true;
    flags[LightScreen][IS_OTHER] = true;
    flags[Haze][IS_OTHER] = true;
    flags[Reflect][IS_OTHER] = true;
    flags[Bide][IS_OTHER] = true;
    flags[MetronomeMove][IS_OTHER] = true;
    flags[MirrorMove][IS_OTHER] = true;
    flags[DreamEater][IS_OTHER] = true;
    flags[Transform][IS_OTHER] = true;
    flags[Psywave][IS_OTHER] = true;
    flags[Splash][IS_OTHER] = true;
    flags[Rest][IS_OTHER] = true;
    flags[Conversion][IS_OTHER] = true;
    flags[TriAttack][IS_OTHER] = true;
    flags[SuperFang][IS_OTHER] = true;
    flags[Substitute][IS_OTHER] = true;
    flags[Struggle][IS_OTHER] = true;
    flags[Sketch][IS_OTHER] = true;
    flags[TripleKick][IS_OTHER] = true;
    flags[Thief][IS_OTHER] = true;
    flags[SpiderWeb][IS_OTHER] = true;
    flags[MindReader][IS_OTHER] = true;
    flags[Nightmare][IS_OTHER] = true;
    flags[Snore][IS_OTHER] = true;
    flags[Curse][IS_OTHER] = true;
    flags[Flail][IS_OTHER] = true;
    flags[Conversion2][IS_OTHER] = true;
    flags[Reversal][IS_OTHER] = true;
    flags[Spite][IS_OTHER] = true;
    flags[Spikes][IS_OTHER] = true;
    flags[Foresight][IS_OTHER] = true;
    flags[DestinyBond][IS_OTHER] = true;
    flags[PerishSong][IS_OTHER] = true;
    flags[LockOn][IS_OTHER] = true;
    flags[Rollout][IS_OTHER] = true;
    flags[FalseSwipe][IS_OTHER] = true;
    flags[FuryCutter][IS_OTHER] = true;
    flags[MeanLook][IS_OTHER] = true;
    flags[Attract][IS_OTHER] = true;
    flags[SleepTalk][IS_OTHER] = true;
    flags[HealBell][IS_OTHER] = true;
    flags[Present][IS_OTHER] = true;
    flags[Safeguard][IS_OTHER] = true;
    flags[PainSplit][IS_OTHER] = true;
    flags[Magnitude][IS_OTHER] = true;
    flags[BatonPass][IS_OTHER] = true;
    flags[Encore][IS_OTHER] = true;
    flags[Pursuit][IS_OTHER] = true;
    flags[RapidSpin][IS_OTHER] = true;
    flags[HiddenPower][IS_OTHER] = true;
    flags[MirrorCoat][IS_OTHER] = true;
    flags[PsychUp][IS_OTHER] = true;
    flags[FutureSight][IS_OTHER] = true;
    flags[BeatUp][IS_OTHER] = true;
    flags[FakeOut][IS_OTHER] = true;
    flags[Uproar][IS_OTHER] = true;
    flags[Stockpile][IS_OTHER] = true;
    flags[SpitUp][IS_OTHER] = true;
    flags[Swallow][IS_OTHER] = true;
    flags[Torment][IS_OTHER] = true;
    flags[Facade][IS_OTHER] = true;
    flags[FocusPunch][IS_OTHER] = true;
    flags[Smellingsalt][IS_OTHER] = true;
    flags[FollowMe][IS_OTHER] = true;
    flags[NaturePower][IS_OTHER] = true;
    flags[Charge][IS_OTHER] = true;
    flags[Taunt][IS_OTHER] = true;
    flags[HelpingHand][IS_OTHER] = true;
    flags[Trick][IS_OTHER] = true;
    flags[RolePlay][IS_OTHER] = true;
    flags[Wish][IS_OTHER] = true;
    flags[Assist][IS_OTHER] = true;
    flags[Ingrain][IS_OTHER] = true;
    flags[MagicCoat][IS_OTHER] = true;
    flags[Recycle][IS_OTHER] = true;
    flags[Revenge][IS_OTHER] = true;
    flags[BrickBreak][IS_OTHER] = true;
    flags[Yawn][IS_OTHER] = true;
    flags[KnockOff][IS_OTHER] = true;
    flags[Endeavor][IS_OTHER] = true;
    flags[Eruption][IS_OTHER] = true;
    flags[SkillSwap][IS_OTHER] = true;
    flags[Imprison][IS_OTHER] = true;
    flags[Refresh][IS_OTHER] = true;
    flags[Grudge][IS_OTHER] = true;
    flags[Snatch][IS_OTHER] = true;
    flags[SecretPower][IS_OTHER] = true;
    flags[Camouflage][IS_OTHER] = true;
    flags[MudSport][IS_OTHER] = true;
    flags[IceBall][IS_OTHER] = true;
    flags[WeatherBall][IS_OTHER] = true;
    flags[Aromatherapy][IS_OTHER] = true;
    flags[OdorSleuth][IS_OTHER] = true;
    flags[WaterSpout][IS_OTHER] = true;
    flags[Block][IS_OTHER] = true;
    flags[Covet][IS_OTHER] = true;
    flags[WaterSport][IS_OTHER] = true;
    flags[DoomDesire][IS_OTHER] = true;
    flags[Roost][IS_OTHER] = true;
    flags[Gravity][IS_OTHER] = true;
    flags[MiracleEye][IS_OTHER] = true;
    flags[WakeUpSlap][IS_OTHER] = true;
    flags[GyroBall][IS_OTHER] = true;
    flags[HealingWish][IS_OTHER] = true;
    flags[Brine][IS_OTHER] = true;
    flags[NaturalGift][IS_OTHER] = true;
    flags[Feint][IS_OTHER] = true;
    flags[Pluck][IS_OTHER] = true;
    flags[Tailwind][IS_OTHER] = true;
    flags[Acupressure][IS_OTHER] = true;
    flags[MetalBurst][IS_OTHER] = true;
    flags[UTurn][IS_OTHER] = true;
    flags[Payback][IS_OTHER] = true;
    flags[Assurance][IS_OTHER] = true;
    flags[Embargo][IS_OTHER] = true;
    flags[Fling][IS_OTHER] = true;
    flags[PsychoShift][IS_OTHER] = true;
    flags[TrumpCard][IS_OTHER] = true;
    flags[HealBlock][IS_OTHER] = true;
    flags[WringOut][IS_OTHER] = true;
    flags[PowerTrick][IS_OTHER] = true;
    flags[GastroAcid][IS_OTHER] = true;
    flags[LuckyChant][IS_OTHER] = true;
    flags[MeFirst][IS_OTHER] = true;
    flags[Copycat][IS_OTHER] = true;
    flags[PowerSwap][IS_OTHER] = true;
    flags[GuardSwap][IS_OTHER] = true;
    flags[Punishment][IS_OTHER] = true;
    flags[LastResort][IS_OTHER] = true;
    flags[WorrySeed][IS_OTHER] = true;
    flags[SuckerPunch][IS_OTHER] = true;
    flags[ToxicSpikes][IS_OTHER] = true;
    flags[HeartSwap][IS_OTHER] = true;
    flags[AquaRing][IS_OTHER] = true;
    flags[MagnetRise][IS_OTHER] = true;
    flags[Switcheroo][IS_OTHER] = true;
    flags[Avalanche][IS_OTHER] = true;
    flags[Defog][IS_OTHER] = true;
    flags[TrickRoom][IS_OTHER] = true;
    flags[Captivate][IS_OTHER] = true;
    flags[StealthRock][IS_OTHER] = true;
    flags[GrassKnot][IS_OTHER] = true;
    flags[Chatter][IS_OTHER] = true;
    flags[Judgment][IS_OTHER] = true;
    flags[BugBite][IS_OTHER] = true;
    flags[LunarDance][IS_OTHER] = true;
    flags[CrushGrip][IS_OTHER] = true;

    flags[SandstormMove][CHANGES_WEATHER] = true;
    flags[RainDance][CHANGES_WEATHER] = true;
    flags[SunnyDay][CHANGES_WEATHER] = true;
    flags[HailMove][CHANGES_WEATHER] = true;

    flags[Whirlwind][FORCES_USER_OUT] = true;
    flags[Roar][FORCES_USER_OUT] = true;

    flags[Guillotine][KOS_IN_ONE_HIT] = true;
    flags[HornDrill][KOS_IN_ONE_HIT] = true;
    flags[Fissure][KOS_IN_ONE_HIT] = true;
    flags[SheerCold][KOS_IN_ONE_HIT] = true;

    flags[Selfdestruct][MAKES_ATTACKER_FAINT] = true;
    flags[Explosion][MAKES_ATTACKER_FAINT] = true;
    flags[Memento][MAKES_ATTACKER_FAINT] = true;

    flags[KarateChop][HAS_INCREASED_CRIT_CHANCE] = true;
    flags[RazorWind][HAS_INCREASED_CRIT_CHANCE] = true;
    flags[RazorLeaf][HAS_INCREASED_CRIT_CHANCE] = true;
    flags[SkyAttack][HAS_INCREASED_CRIT_CHANCE] = true;
    flags[Crabhammer][HAS_INCREASED_CRIT_CHANCE] = true;
    flags[Slash][HAS_INCREASED_CRIT_CHANCE] = true;
    flags[Aeroblast][HAS_INCREASED_CRIT_CHANCE] = true;
    flags[CrossChop][HAS_INCREASED_CRIT_CHANCE] = true;
    flags[BlazeKick][HAS_INCREASED_CRIT_CHANCE] = true;
    flags[AirCutter][HAS_INCREASED_CRIT_CHANCE] = true;
    flags[PoisonTail][HAS_INCREASED_CRIT_CHANCE] = true;
    flags[LeafBlade][HAS_INCREASED_CRIT_CHANCE] = true;
    flags[NightSlash][HAS_INCREASED_CRIT_CHANCE] = true;
    flags[ShadowClaw][HAS_INCREASED_CRIT_CHANCE] = true;
    flags[PsychoCut][HAS_INCREASED_CRIT_CHANCE] = true;
    flags[CrossPoison][HAS_INCREASED_CRIT_CHANCE] = true;
    flags[StoneEdge][HAS_INCREASED_CRIT_CHANCE] = true;
    flags[AttackOrder][HAS_INCREASED_CRIT_CHANCE] = true;
    flags[SpacialRend][HAS_INCREASED_CRIT_CHANCE] = true;

    flags[RazorWind][REQUIRES_CHARGING_TURN] = true;
    flags[SolarBeam][REQUIRES_CHARGING_TURN] = true;
    flags[SkullBash][REQUIRES_CHARGING_TURN] = true;
    flags[SkyAttack][REQUIRES_CHARGING_TURN] = true;

    flags[HyperBeam][REQUIRES_RECHARGE_TURN] = true;
    flags[BlastBurn][REQUIRES_RECHARGE_TURN] = true;
    flags[HydroCannon][REQUIRES_RECHARGE_TURN] = true;
    flags[FrenzyPlant][REQUIRES_RECHARGE_TURN] = true;
    flags[GigaImpact][REQUIRES_RECHARGE_TURN] = true;
    flags[RockWrecker][REQUIRES_RECHARGE_TURN] = true;
    flags[RoarOfTime][REQUIRES_RECHARGE_TURN] = true;

    flags[Stomp][DEALS_DOUBLE_AFTER_MINIMIZE] = true;

    flags[Bind][CONTINUES] = true;
    flags[Wrap][CONTINUES] = true;
    flags[FireSpin][CONTINUES] = true;
    flags[Clamp][CONTINUES] = true;
    flags[Whirlpool][CONTINUES] = true;
    flags[SandTomb][CONTINUES] = true;
    flags[MagmaStorm][CONTINUES] = true;

    flags[FirePunch][BURNS_DEFENDER] = true;
    flags[Ember][BURNS_DEFENDER] = true;
    flags[Flamethrower][BURNS_DEFENDER] = true;
    flags[FireBlast][BURNS_DEFENDER] = true;
    flags[FlameWheel][BURNS_DEFENDER] = true;
    flags[SacredFire][BURNS_DEFENDER] = true;
    flags[HeatWave][BURNS_DEFENDER] = true;
    flags[WillOWisp][BURNS_DEFENDER] = true;
    flags[BlazeKick][BURNS_DEFENDER] = true;
    flags[FlareBlitz][BURNS_DEFENDER] = true;
    flags[FireFang][BURNS_DEFENDER] = true;
    flags[LavaPlume][BURNS_DEFENDER] = true;

    flags[IcePunch][FREEZES_DEFENDER] = true;
    flags[IceBeam][FREEZES_DEFENDER] = true;
    flags[Blizzard][FREEZES_DEFENDER] = true;
    flags[PowderSnow][FREEZES_DEFENDER] = true;
    flags[IceFang][FREEZES_DEFENDER] = true;

    flags[ThunderPunch][PARALYZES_DEFENDER] = true;
    flags[BodySlam][PARALYZES_DEFENDER] = true;
    flags[StunSpore][PARALYZES_DEFENDER] = true;
    flags[Thundershock][PARALYZES_DEFENDER] = true;
    flags[Thunderbolt][PARALYZES_DEFENDER] = true;
    flags[ThunderWave][PARALYZES_DEFENDER] = true;
    flags[Thunder][PARALYZES_DEFENDER] = true;
    flags[Lick][PARALYZES_DEFENDER] = true;
    flags[Glare][PARALYZES_DEFENDER] = true;
    flags[ZapCannon][PARALYZES_DEFENDER] = true;
    flags[Spark][PARALYZES_DEFENDER] = true;
    flags[DragonBreath][PARALYZES_DEFENDER] = true;
    flags[Bounce][PARALYZES_DEFENDER] = true;
    flags[VoltTackle][PARALYZES_DEFENDER] = true;
    flags[ForcePalm][PARALYZES_DEFENDER] = true;
    flags[ThunderFang][PARALYZES_DEFENDER] = true;
    flags[Discharge][PARALYZES_DEFENDER] = true;

    flags[PoisonSting][POISONS_DEFENDER] = true;
    flags[Twineedle][POISONS_DEFENDER] = true;
    flags[PoisonPowder][POISONS_DEFENDER] = true;
    flags[Smog][POISONS_DEFENDER] = true;
    flags[Sludge][POISONS_DEFENDER] = true;
    flags[PoisonGas][POISONS_DEFENDER] = true;
    flags[SludgeBomb][POISONS_DEFENDER] = true;
    flags[PoisonTail][POISONS_DEFENDER] = true;
    flags[PoisonJab][POISONS_DEFENDER] = true;
    flags[CrossPoison][POISONS_DEFENDER] = true;
    flags[GunkShot][POISONS_DEFENDER] = true;

    flags[Toxic][BADLY_POISONS] = true;
    flags[PoisonFang][BADLY_POISONS] = true;

    flags[Sing][MAKES_DEFENDER_SLEEP] = true;
    flags[SleepPowder][MAKES_DEFENDER_SLEEP] = true;
    flags[Hypnosis][MAKES_DEFENDER_SLEEP] = true;
    flags[LovelyKiss][MAKES_DEFENDER_SLEEP] = true;
    flags[Spore][MAKES_DEFENDER_SLEEP] = true;
    flags[Grasswhistle][MAKES_DEFENDER_SLEEP] = true;
    flags[DarkVoid][MAKES_DEFENDER_SLEEP] = true;

    flags[Supersonic][CONFUSES_DEFENDER] = true;
    flags[Psybeam][CONFUSES_DEFENDER] = true;
    flags[Confusion][CONFUSES_DEFENDER] = true;
    flags[ConfuseRay][CONFUSES_DEFENDER] = true;
    flags[DizzyPunch][CONFUSES_DEFENDER] = true;
    flags[SweetKiss][CONFUSES_DEFENDER] = true;
    flags[Swagger][CONFUSES_DEFENDER] = true;
    flags[Dynamicpunch][CONFUSES_DEFENDER] = true;
    flags[Flatter][CONFUSES_DEFENDER] = true;
    flags[TeeterDance][CONFUSES_DEFENDER] = true;
    flags[SignalBeam][CONFUSES_DEFENDER_10] = true;
    flags[WaterPulse][CONFUSES_DEFENDER] = true;
    flags[RockClimb][CONFUSES_DEFENDER] = true;

    flags[Stomp][FLINCHES_DEFENDER] = true;
    flags[RollingKick][FLINCHES_DEFENDER] = true;
    flags[Headbutt][FLINCHES_DEFENDER] = true;
    flags[Bite][FLINCHES_DEFENDER] = true;
    flags[BoneClub][FLINCHES_DEFENDER] = true;
    flags[Waterfall][FLINCHES_DEFENDER] = true;
    flags[SkyAttack][FLINCHES_DEFENDER] = true;
    flags[HyperFang][FLINCHES_DEFENDER] = true;
    flags[Twister][FLINCHES_DEFENDER] = true;
    flags[NeedleArm][FLINCHES_DEFENDER] = true;
    flags[Astonish][FLINCHES_DEFENDER] = true;
    flags[Extrasensory][FLINCHES_DEFENDER] = true;
    flags[DarkPulse][FLINCHES_DEFENDER] = true;
    flags[AirSlash][FLINCHES_DEFENDER] = true;
    flags[DragonRush][FLINCHES_DEFENDER] = true;
    flags[ThunderFang][FLINCHES_DEFENDER] = true;
    flags[IceFang][FLINCHES_DEFENDER] = true;
    flags[FireFang][FLINCHES_DEFENDER] = true;
    flags[ZenHeadbutt][FLINCHES_DEFENDER] = true;
    flags[IronHead][FLINCHES_DEFENDER] = true;

    flags[JumpKick][HAS_RECOIL] = true;
    flags[TakeDown][HAS_RECOIL] = true;
    flags[DoubleEdge][HAS_RECOIL] = true;
    flags[Submission][HAS_RECOIL] = true;
    flags[HighJumpKick][HAS_RECOIL] = true;
    flags[BellyDrum][HAS_RECOIL] = true;
    flags[VoltTackle][HAS_RECOIL] = true;
    flags[FlareBlitz][HAS_RECOIL] = true;
    flags[BraveBird][HAS_RECOIL] = true;
    flags[WoodHammer][HAS_RECOIL] = true;
    flags[HeadSmash][HAS_RECOIL] = true;

    flags[DoubleSlap][HITS_MULTIPLE_TIMES] = true;
    flags[CometPunch][HITS_MULTIPLE_TIMES] = true;
    flags[DoubleKick][HITS_MULTIPLE_TIMES] = true;
    flags[FuryAttack][HITS_MULTIPLE_TIMES] = true;
    flags[Twineedle][HITS_MULTIPLE_TIMES] = true;
    flags[PinMissile][HITS_MULTIPLE_TIMES] = true;
    flags[SpikeCannon][HITS_MULTIPLE_TIMES] = true;
    flags[Barrage][HITS_MULTIPLE_TIMES] = true;
    flags[FuryAttack][HITS_MULTIPLE_TIMES] = true;
    flags[Bonemerang][HITS_MULTIPLE_TIMES] = true;
    flags[BoneRush][HITS_MULTIPLE_TIMES] = true;
    flags[ArmThrust][HITS_MULTIPLE_TIMES] = true;
    flags[BulletSeed][HITS_MULTIPLE_TIMES] = true;
    flags[IcicleSpear][HITS_MULTIPLE_TIMES] = true;
    flags[RockBlast][HITS_MULTIPLE_TIMES] = true;
    flags[DoubleHit][HITS_MULTIPLE_TIMES] = true;

    flags[Thrash][LASTS_MULTIPLE_TURNS] = true;
    flags[PetalDance][LASTS_MULTIPLE_TURNS] = true;
    flags[Outrage][LASTS_MULTIPLE_TURNS] = true;

    flags[SonicBoom][HAS_FIXED_DAMAGE] = true;
    flags[SeismicToss][HAS_FIXED_DAMAGE] = true;
    flags[DragonRage][HAS_FIXED_DAMAGE] = true;
    flags[NightShade][HAS_FIXED_DAMAGE] = true;

    flags[Bounce][GOES_INTO_AIR] = true;
    flags[Fly][GOES_INTO_AIR] = true;

    flags[Gust][HITS_DEFENDER_IN_AIR] = true;
    flags[SkyUppercut][HITS_DEFENDER_IN_AIR] = true;
    flags[Thunder][HITS_DEFENDER_IN_AIR] = true;
    flags[Twister][HITS_DEFENDER_IN_AIR] = true;

    flags[Dig][GOES_UNDER_GROUND] = true;

    flags[Earthquake][HITS_DEFENDER_UNDER_GROUND] = true;
    flags[Magnitude][HITS_DEFENDER_UNDER_GROUND] = true;
    flags[Fissure][HITS_DEFENDER_UNDER_GROUND] = true;

    flags[Dive][GOES_UNDER_WATER] = true;

    flags[Surf][HITS_DEFENDER_UNDER_WATER] = true;
    flags[Whirlpool][HITS_DEFENDER_UNDER_WATER] = true;

    flags[ShadowForce][GOES_INTO_VOID] = true;

    flags[Pound][MAKES_CONTACT] = true;
    flags[KarateChop][MAKES_CONTACT] = true;
    flags[DoubleSlap][MAKES_CONTACT] = true;
    flags[CometPunch][MAKES_CONTACT] = true;
    flags[MegaPunch][MAKES_CONTACT] = true;
    flags[FirePunch][MAKES_CONTACT] = true;
    flags[IcePunch][MAKES_CONTACT] = true;
    flags[ThunderPunch][MAKES_CONTACT] = true;
    flags[Scratch][MAKES_CONTACT] = true;
    flags[ViceGrip][MAKES_CONTACT] = true;
    flags[Guillotine][MAKES_CONTACT] = true;
    flags[Cut][MAKES_CONTACT] = true;
    flags[WingAttack][MAKES_CONTACT] = true;
    flags[Fly][MAKES_CONTACT] = true;
    flags[Bind][MAKES_CONTACT] = true;
    flags[Slam][MAKES_CONTACT] = true;
    flags[VineWhip][MAKES_CONTACT] = true;
    flags[Stomp][MAKES_CONTACT] = true;
    flags[DoubleKick][MAKES_CONTACT] = true;
    flags[MegaKick][MAKES_CONTACT] = true;
    flags[JumpKick][MAKES_CONTACT] = true;
    flags[RollingKick][MAKES_CONTACT] = true;
    flags[Headbutt][MAKES_CONTACT] = true;
    flags[HornAttack][MAKES_CONTACT] = true;
    flags[FuryAttack][MAKES_CONTACT] = true;
    flags[HornDrill][MAKES_CONTACT] = true;
    flags[Tackle][MAKES_CONTACT] = true;
    flags[BodySlam][MAKES_CONTACT] = true;
    flags[Wrap][MAKES_CONTACT] = true;
    flags[TakeDown][MAKES_CONTACT] = true;
    flags[Thrash][MAKES_CONTACT] = true;
    flags[DoubleEdge][MAKES_CONTACT] = true;
    flags[Bite][MAKES_CONTACT] = true;
    flags[Peck][MAKES_CONTACT] = true;
    flags[DrillPeck][MAKES_CONTACT] = true;
    flags[Submission][MAKES_CONTACT] = true;
    flags[LowKick][MAKES_CONTACT] = true;
    flags[Counter][MAKES_CONTACT] = true;
    flags[SeismicToss][MAKES_CONTACT] = true;
    flags[Strength][MAKES_CONTACT] = true;
    flags[PetalDance][MAKES_CONTACT] = true;
    flags[Dig][MAKES_CONTACT] = true;
    flags[QuickAttack][MAKES_CONTACT] = true;
    flags[Rage][MAKES_CONTACT] = true;
    flags[Bide][MAKES_CONTACT] = true;
    flags[Lick][MAKES_CONTACT] = true;
    flags[Waterfall][MAKES_CONTACT] = true;
    flags[Clamp][MAKES_CONTACT] = true;
    flags[SkullBash][MAKES_CONTACT] = true;
    flags[Constrict][MAKES_CONTACT] = true;
    flags[HighJumpKick][MAKES_CONTACT] = true;
    flags[LeechLife][MAKES_CONTACT] = true;
    flags[DizzyPunch][MAKES_CONTACT] = true;
    flags[Crabhammer][MAKES_CONTACT] = true;
    flags[FurySwipes][MAKES_CONTACT] = true;
    flags[HyperFang][MAKES_CONTACT] = true;
    flags[SuperFang][MAKES_CONTACT] = true;
    flags[Slash][MAKES_CONTACT] = true;
    flags[Struggle][MAKES_CONTACT] = true;
    flags[TripleKick][MAKES_CONTACT] = true;
    flags[Thief][MAKES_CONTACT] = true;
    flags[FlameWheel][MAKES_CONTACT] = true;
    flags[Flail][MAKES_CONTACT] = true;
    flags[Reversal][MAKES_CONTACT] = true;
    flags[MachPunch][MAKES_CONTACT] = true;
    flags[FaintAttack][MAKES_CONTACT] = true;
    flags[Outrage][MAKES_CONTACT] = true;
    flags[Rollout][MAKES_CONTACT] = true;
    flags[FalseSwipe][MAKES_CONTACT] = true;
    flags[Spark][MAKES_CONTACT] = true;
    flags[FuryCutter][MAKES_CONTACT] = true;
    flags[SteelWing][MAKES_CONTACT] = true;
    flags[Return][MAKES_CONTACT] = true;
    flags[Frustration][MAKES_CONTACT] = true;
    flags[Dynamicpunch][MAKES_CONTACT] = true;
    flags[Megahorn][MAKES_CONTACT] = true;
    flags[Pursuit][MAKES_CONTACT] = true;
    flags[RapidSpin][MAKES_CONTACT] = true;
    flags[IronTail][MAKES_CONTACT] = true;
    flags[MetalClaw][MAKES_CONTACT] = true;
    flags[VitalThrow][MAKES_CONTACT] = true;
    flags[CrossChop][MAKES_CONTACT] = true;
    flags[Crunch][MAKES_CONTACT] = true;
    flags[ExtremeSpeed][MAKES_CONTACT] = true;
    flags[RockSmash][MAKES_CONTACT] = true;
    flags[FakeOut][MAKES_CONTACT] = true;
    flags[Facade][MAKES_CONTACT] = true;
    flags[FocusPunch][MAKES_CONTACT] = true;
    flags[Smellingsalt][MAKES_CONTACT] = true;
    flags[Superpower][MAKES_CONTACT] = true;
    flags[Revenge][MAKES_CONTACT] = true;
    flags[BrickBreak][MAKES_CONTACT] = true;
    flags[KnockOff][MAKES_CONTACT] = true;
    flags[Endeavor][MAKES_CONTACT] = true;
    flags[Dive][MAKES_CONTACT] = true;
    flags[ArmThrust][MAKES_CONTACT] = true;
    flags[BlazeKick][MAKES_CONTACT] = true;
    flags[IceBall][MAKES_CONTACT] = true;
    flags[NeedleArm][MAKES_CONTACT] = true;
    flags[PoisonFang][MAKES_CONTACT] = true;
    flags[CrushClaw][MAKES_CONTACT] = true;
    flags[MeteorMash][MAKES_CONTACT] = true;
    flags[Astonish][MAKES_CONTACT] = true;
    flags[ShadowPunch][MAKES_CONTACT] = true;
    flags[SkyUppercut][MAKES_CONTACT] = true;
    flags[AerialAce][MAKES_CONTACT] = true;
    flags[DragonClaw][MAKES_CONTACT] = true;
    flags[Bounce][MAKES_CONTACT] = true;
    flags[PoisonTail][MAKES_CONTACT] = true;
    flags[Covet][MAKES_CONTACT] = true;
    flags[VoltTackle][MAKES_CONTACT] = true;
    flags[LeafBlade][MAKES_CONTACT] = true;
    flags[WakeUpSlap][MAKES_CONTACT] = true;
    flags[HammerArm][MAKES_CONTACT] = true;
    flags[GyroBall][MAKES_CONTACT] = true;
    flags[Pluck][MAKES_CONTACT] = true;
    flags[UTurn][MAKES_CONTACT] = true;
    flags[CloseCombat][MAKES_CONTACT] = true;
    flags[Payback][MAKES_CONTACT] = true;
    flags[Assurance][MAKES_CONTACT] = true;
    flags[Punishment][MAKES_CONTACT] = true;
    flags[LastResort][MAKES_CONTACT] = true;
    flags[SuckerPunch][MAKES_CONTACT] = true;
    flags[FlareBlitz][MAKES_CONTACT] = true;
    flags[ForcePalm][MAKES_CONTACT] = true;
    flags[PoisonJab][MAKES_CONTACT] = true;
    flags[NightSlash][MAKES_CONTACT] = true;
    flags[AquaTail][MAKES_CONTACT] = true;
    flags[XScissor][MAKES_CONTACT] = true;
    flags[DragonRush][MAKES_CONTACT] = true;
    flags[DrainPunch][MAKES_CONTACT] = true;
    flags[BraveBird][MAKES_CONTACT] = true;
    flags[GigaImpact][MAKES_CONTACT] = true;
    flags[BulletPunch][MAKES_CONTACT] = true;
    flags[Avalanche][MAKES_CONTACT] = true;
    flags[ShadowClaw][MAKES_CONTACT] = true;
    flags[ThunderFang][MAKES_CONTACT] = true;
    flags[IceFang][MAKES_CONTACT] = true;
    flags[FireFang][MAKES_CONTACT] = true;
    flags[ShadowSneak][MAKES_CONTACT] = true;
    flags[ZenHeadbutt][MAKES_CONTACT] = true;
    flags[RockClimb][MAKES_CONTACT] = true;
    flags[PowerWhip][MAKES_CONTACT] = true;
    flags[CrossPoison][MAKES_CONTACT] = true;
    flags[IronHead][MAKES_CONTACT] = true;
    flags[BugBite][MAKES_CONTACT] = true;
    flags[WoodHammer][MAKES_CONTACT] = true;
    flags[AquaJet][MAKES_CONTACT] = true;
    flags[HeadSmash][MAKES_CONTACT] = true;
    flags[DoubleHit][MAKES_CONTACT] = true;
    flags[CrushGrip][MAKES_CONTACT] = true;
    flags[ShadowForce][MAKES_CONTACT] = true;

    flags[Acupressure][BYPASSES_PROTECT] = true;
    flags[Curse][BYPASSES_PROTECT] = true;
    flags[DoomDesire][BYPASSES_PROTECT] = true;
    flags[Feint][BYPASSES_PROTECT] = true;
    flags[FutureSight][BYPASSES_PROTECT] = true;
    flags[PerishSong][BYPASSES_PROTECT] = true;
    flags[PsychUp][BYPASSES_PROTECT] = true;
    flags[RolePlay][BYPASSES_PROTECT] = true;
    flags[ShadowForce][BYPASSES_PROTECT] = true;
    flags[Sketch][BYPASSES_PROTECT] = true;
    flags[Transform][BYPASSES_PROTECT] = true;

    flags[Feint][BREAKS_PROTECT] = true;
    flags[ShadowForce][BREAKS_PROTECT] = true;

    flags[Attract][CAN_BE_REFLECTED_BY_MIRROR_MOVE] = true;
    flags[Block][CAN_BE_REFLECTED_BY_MIRROR_MOVE] = true;
    flags[Captivate][CAN_BE_REFLECTED_BY_MIRROR_MOVE] = true;
    flags[Charm][CAN_BE_REFLECTED_BY_MIRROR_MOVE] = true;
    flags[ConfuseRay][CAN_BE_REFLECTED_BY_MIRROR_MOVE] = true;
    flags[CottonSpore][CAN_BE_REFLECTED_BY_MIRROR_MOVE] = true;
    flags[DarkVoid][CAN_BE_REFLECTED_BY_MIRROR_MOVE] = true;
    flags[FakeTears][CAN_BE_REFLECTED_BY_MIRROR_MOVE] = true;
    flags[Featherdance][CAN_BE_REFLECTED_BY_MIRROR_MOVE] = true;
    flags[Flash][CAN_BE_REFLECTED_BY_MIRROR_MOVE] = true;
    flags[Flatter][CAN_BE_REFLECTED_BY_MIRROR_MOVE] = true;
    flags[GastroAcid][CAN_BE_REFLECTED_BY_MIRROR_MOVE] = true;
    flags[Glare][CAN_BE_REFLECTED_BY_MIRROR_MOVE] = true;
    flags[Grasswhistle][CAN_BE_REFLECTED_BY_MIRROR_MOVE] = true;
    flags[Growl][CAN_BE_REFLECTED_BY_MIRROR_MOVE] = true;
    flags[Hypnosis][CAN_BE_REFLECTED_BY_MIRROR_MOVE] = true;
    flags[Kinesis][CAN_BE_REFLECTED_BY_MIRROR_MOVE] = true;
    flags[LeechSeed][CAN_BE_REFLECTED_BY_MIRROR_MOVE] = true;
    flags[Leer][CAN_BE_REFLECTED_BY_MIRROR_MOVE] = true;
    flags[LovelyKiss][CAN_BE_REFLECTED_BY_MIRROR_MOVE] = true;
    flags[MeanLook][CAN_BE_REFLECTED_BY_MIRROR_MOVE] = true;
    flags[MetalSound][CAN_BE_REFLECTED_BY_MIRROR_MOVE] = true;
    flags[PoisonGas][CAN_BE_REFLECTED_BY_MIRROR_MOVE] = true;
    flags[PoisonPowder][CAN_BE_REFLECTED_BY_MIRROR_MOVE] = true;
    flags[SandAttack][CAN_BE_REFLECTED_BY_MIRROR_MOVE] = true;
    flags[ScaryFace][CAN_BE_REFLECTED_BY_MIRROR_MOVE] = true;
    flags[Screech][CAN_BE_REFLECTED_BY_MIRROR_MOVE] = true;
    flags[Sing][CAN_BE_REFLECTED_BY_MIRROR_MOVE] = true;
    flags[SleepPowder][CAN_BE_REFLECTED_BY_MIRROR_MOVE] = true;
    flags[Smokescreen][CAN_BE_REFLECTED_BY_MIRROR_MOVE] = true;
    flags[SpiderWeb][CAN_BE_REFLECTED_BY_MIRROR_MOVE] = true;
    flags[Spore][CAN_BE_REFLECTED_BY_MIRROR_MOVE] = true;
    flags[StringShot][CAN_BE_REFLECTED_BY_MIRROR_MOVE] = true;
    flags[StunSpore][CAN_BE_REFLECTED_BY_MIRROR_MOVE] = true;
    flags[Supersonic][CAN_BE_REFLECTED_BY_MIRROR_MOVE] = true;
    flags[Swagger][CAN_BE_REFLECTED_BY_MIRROR_MOVE] = true;
    flags[SweetKiss][CAN_BE_REFLECTED_BY_MIRROR_MOVE] = true;
    flags[SweetScent][CAN_BE_REFLECTED_BY_MIRROR_MOVE] = true;
    flags[TailWhip][CAN_BE_REFLECTED_BY_MIRROR_MOVE] = true;
    flags[ThunderWave][CAN_BE_REFLECTED_BY_MIRROR_MOVE] = true;
    flags[Tickle][CAN_BE_REFLECTED_BY_MIRROR_MOVE] = true;
    flags[Toxic][CAN_BE_REFLECTED_BY_MIRROR_MOVE] = true;
    flags[WillOWisp][CAN_BE_REFLECTED_BY_MIRROR_MOVE] = true;
    flags[WorrySeed][CAN_BE_REFLECTED_BY_MIRROR_MOVE] = true;
    flags[Yawn][CAN_BE_REFLECTED_BY_MIRROR_MOVE] = true;

    flags[AcidArmor][CAN_BE_SNATCHED] = true;
    flags[Acupressure][CAN_BE_SNATCHED] = true;
    flags[Agility][CAN_BE_SNATCHED] = true;
    flags[Amnesia][CAN_BE_SNATCHED] = true;
    flags[Aromatherapy][CAN_BE_SNATCHED] = true;
    flags[Barrier][CAN_BE_SNATCHED] = true;
    flags[BellyDrum][CAN_BE_SNATCHED] = true;
    flags[BulkUp][CAN_BE_SNATCHED] = true;
    flags[CalmMind][CAN_BE_SNATCHED] = true;
    flags[Camouflage][CAN_BE_SNATCHED] = true;
    flags[Charge][CAN_BE_SNATCHED] = true;
    flags[CosmicPower][CAN_BE_SNATCHED] = true;
    flags[DefendOrder][CAN_BE_SNATCHED] = true;
    flags[DefenseCurl][CAN_BE_SNATCHED] = true;
    flags[DoubleTeam][CAN_BE_SNATCHED] = true;
    flags[DragonDance][CAN_BE_SNATCHED] = true;
    flags[FocusEnergy][CAN_BE_SNATCHED] = true;
    flags[Growth][CAN_BE_SNATCHED] = true;
    flags[Harden][CAN_BE_SNATCHED] = true;
    flags[HealBell][CAN_BE_SNATCHED] = true;
    flags[HealOrder][CAN_BE_SNATCHED] = true;
    flags[Howl][CAN_BE_SNATCHED] = true;
    flags[Ingrain][CAN_BE_SNATCHED] = true;
    flags[IronDefense][CAN_BE_SNATCHED] = true;
    flags[LightScreen][CAN_BE_SNATCHED] = true;
    flags[Meditate][CAN_BE_SNATCHED] = true;
    flags[MilkDrink][CAN_BE_SNATCHED] = true;
    flags[Minimize][CAN_BE_SNATCHED] = true;
    flags[Mist][CAN_BE_SNATCHED] = true;
    flags[Moonlight][CAN_BE_SNATCHED] = true;
    flags[MorningSun][CAN_BE_SNATCHED] = true;
    flags[NastyPlot][CAN_BE_SNATCHED] = true;
    flags[PsychUp][CAN_BE_SNATCHED] = true;
    flags[Recover][CAN_BE_SNATCHED] = true;
    flags[Reflect][CAN_BE_SNATCHED] = true;
    flags[Refresh][CAN_BE_SNATCHED] = true;
    flags[Rest][CAN_BE_SNATCHED] = true;
    flags[RockPolish][CAN_BE_SNATCHED] = true;
    flags[Roost][CAN_BE_SNATCHED] = true;
    flags[Safeguard][CAN_BE_SNATCHED] = true;
    flags[Sharpen][CAN_BE_SNATCHED] = true;
    flags[SlackOff][CAN_BE_SNATCHED] = true;
    flags[Softboiled][CAN_BE_SNATCHED] = true;
    flags[Stockpile][CAN_BE_SNATCHED] = true;
    flags[Substitute][CAN_BE_SNATCHED] = true;
    flags[Swallow][CAN_BE_SNATCHED] = true;
    flags[SwordsDance][CAN_BE_SNATCHED] = true;
    flags[Synthesis][CAN_BE_SNATCHED] = true;
    flags[TailGlow][CAN_BE_SNATCHED] = true;
    flags[Tailwind][CAN_BE_SNATCHED] = true;
    flags[Withdraw][CAN_BE_SNATCHED] = true;

    flags[AerialAce][AFFECTED_BY_KINGS_ROCK] = true;
    flags[Aeroblast][AFFECTED_BY_KINGS_ROCK] = true;
    flags[AirCutter][AFFECTED_BY_KINGS_ROCK] = true;
    flags[AirSlash][AFFECTED_BY_KINGS_ROCK] = true;
    flags[AquaJet][AFFECTED_BY_KINGS_ROCK] = true;
    flags[AquaTail][AFFECTED_BY_KINGS_ROCK] = true;
    flags[ArmThrust][AFFECTED_BY_KINGS_ROCK] = true;
    flags[Assurance][AFFECTED_BY_KINGS_ROCK] = true;
    flags[AttackOrder][AFFECTED_BY_KINGS_ROCK] = true;
    flags[AuraSphere][AFFECTED_BY_KINGS_ROCK] = true;
    flags[Avalanche][AFFECTED_BY_KINGS_ROCK] = true;
    flags[Barrage][AFFECTED_BY_KINGS_ROCK] = true;
    flags[BeatUp][AFFECTED_BY_KINGS_ROCK] = true;
    flags[Bide][AFFECTED_BY_KINGS_ROCK] = true;
    flags[Bind][AFFECTED_BY_KINGS_ROCK] = true;
    flags[BlastBurn][AFFECTED_BY_KINGS_ROCK] = true;
    flags[BoneRush][AFFECTED_BY_KINGS_ROCK] = true;
    flags[Bonemerang][AFFECTED_BY_KINGS_ROCK] = true;
    flags[Bounce][AFFECTED_BY_KINGS_ROCK] = true;
    flags[BraveBird][AFFECTED_BY_KINGS_ROCK] = true;
    flags[BrickBreak][AFFECTED_BY_KINGS_ROCK] = true;
    flags[Brine][AFFECTED_BY_KINGS_ROCK] = true;
    flags[BugBite][AFFECTED_BY_KINGS_ROCK] = true;
    flags[BulletPunch][AFFECTED_BY_KINGS_ROCK] = true;
    flags[BulletSeed][AFFECTED_BY_KINGS_ROCK] = true;
    flags[ChargeBeam][AFFECTED_BY_KINGS_ROCK] = true;
    flags[Clamp][AFFECTED_BY_KINGS_ROCK] = true;
    flags[CloseCombat][AFFECTED_BY_KINGS_ROCK] = true;
    flags[CometPunch][AFFECTED_BY_KINGS_ROCK] = true;
    flags[Crabhammer][AFFECTED_BY_KINGS_ROCK] = true;
    flags[CrossChop][AFFECTED_BY_KINGS_ROCK] = true;
    flags[CrossPoison][AFFECTED_BY_KINGS_ROCK] = true;
    flags[CrushGrip][AFFECTED_BY_KINGS_ROCK] = true;
    flags[Cut][AFFECTED_BY_KINGS_ROCK] = true;
    flags[DarkPulse][AFFECTED_BY_KINGS_ROCK] = true;
    flags[Dig][AFFECTED_BY_KINGS_ROCK] = true;
    flags[Discharge][AFFECTED_BY_KINGS_ROCK] = true;
    flags[Dive][AFFECTED_BY_KINGS_ROCK] = true;
    flags[DoubleHit][AFFECTED_BY_KINGS_ROCK] = true;
    flags[DoubleKick][AFFECTED_BY_KINGS_ROCK] = true;
    flags[DoubleSlap][AFFECTED_BY_KINGS_ROCK] = true;
    flags[DoubleEdge][AFFECTED_BY_KINGS_ROCK] = true;
    flags[DracoMeteor][AFFECTED_BY_KINGS_ROCK] = true;
    flags[DragonBreath][AFFECTED_BY_KINGS_ROCK] = true;
    flags[DragonClaw][AFFECTED_BY_KINGS_ROCK] = true;
    flags[DragonPulse][AFFECTED_BY_KINGS_ROCK] = true;
    flags[DragonRush][AFFECTED_BY_KINGS_ROCK] = true;
    flags[DrainPunch][AFFECTED_BY_KINGS_ROCK] = true;
    flags[DrillPeck][AFFECTED_BY_KINGS_ROCK] = true;
    flags[EarthPower][AFFECTED_BY_KINGS_ROCK] = true;
    flags[Earthquake][AFFECTED_BY_KINGS_ROCK] = true;
    flags[EggBomb][AFFECTED_BY_KINGS_ROCK] = true;
    flags[Endeavor][AFFECTED_BY_KINGS_ROCK] = true;
    flags[Eruption][AFFECTED_BY_KINGS_ROCK] = true;
    flags[Explosion][AFFECTED_BY_KINGS_ROCK] = true;
    flags[ExtremeSpeed][AFFECTED_BY_KINGS_ROCK] = true;
    flags[FalseSwipe][AFFECTED_BY_KINGS_ROCK] = true;
    flags[FaintAttack][AFFECTED_BY_KINGS_ROCK] = true;
    flags[FireFang][AFFECTED_BY_KINGS_ROCK] = true;
    flags[FireSpin][AFFECTED_BY_KINGS_ROCK] = true;
    flags[Flail][AFFECTED_BY_KINGS_ROCK] = true;
    flags[FlashCannon][AFFECTED_BY_KINGS_ROCK] = true;
    flags[Fly][AFFECTED_BY_KINGS_ROCK] = true;
    flags[ForcePalm][AFFECTED_BY_KINGS_ROCK] = true;
    flags[FrenzyPlant][AFFECTED_BY_KINGS_ROCK] = true;
    flags[Frustration][AFFECTED_BY_KINGS_ROCK] = true;
    flags[FuryAttack][AFFECTED_BY_KINGS_ROCK] = true;
    flags[FuryCutter][AFFECTED_BY_KINGS_ROCK] = true;
    flags[FurySwipes][AFFECTED_BY_KINGS_ROCK] = true;
    flags[GigaImpact][AFFECTED_BY_KINGS_ROCK] = true;
    flags[GrassKnot][AFFECTED_BY_KINGS_ROCK] = true;
    flags[GunkShot][AFFECTED_BY_KINGS_ROCK] = true;
    flags[GyroBall][AFFECTED_BY_KINGS_ROCK] = true;
    flags[HammerArm][AFFECTED_BY_KINGS_ROCK] = true;
    flags[HeadSmash][AFFECTED_BY_KINGS_ROCK] = true;
    flags[HiddenPower][AFFECTED_BY_KINGS_ROCK] = true;
    flags[HighJumpKick][AFFECTED_BY_KINGS_ROCK] = true;
    flags[HornAttack][AFFECTED_BY_KINGS_ROCK] = true;
    flags[HydroCannon][AFFECTED_BY_KINGS_ROCK] = true;
    flags[HydroPump][AFFECTED_BY_KINGS_ROCK] = true;
    flags[HyperBeam][AFFECTED_BY_KINGS_ROCK] = true;
    flags[IceBall][AFFECTED_BY_KINGS_ROCK] = true;
    flags[IceFang][AFFECTED_BY_KINGS_ROCK] = true;
    flags[IceShard][AFFECTED_BY_KINGS_ROCK] = true;
    flags[IcicleSpear][AFFECTED_BY_KINGS_ROCK] = true;
    flags[IronHead][AFFECTED_BY_KINGS_ROCK] = true;
    flags[Judgment][AFFECTED_BY_KINGS_ROCK] = true;
    flags[JumpKick][AFFECTED_BY_KINGS_ROCK] = true;
    flags[KarateChop][AFFECTED_BY_KINGS_ROCK] = true;
    flags[LastResort][AFFECTED_BY_KINGS_ROCK] = true;
    flags[LavaPlume][AFFECTED_BY_KINGS_ROCK] = true;
    flags[LeafBlade][AFFECTED_BY_KINGS_ROCK] = true;
    flags[LeafStorm][AFFECTED_BY_KINGS_ROCK] = true;
    flags[LowKick][AFFECTED_BY_KINGS_ROCK] = true;
    flags[MachPunch][AFFECTED_BY_KINGS_ROCK] = true;
    flags[MagicalLeaf][AFFECTED_BY_KINGS_ROCK] = true;
    flags[MagmaStorm][AFFECTED_BY_KINGS_ROCK] = true;
    flags[MagnetBomb][AFFECTED_BY_KINGS_ROCK] = true;
    flags[Magnitude][AFFECTED_BY_KINGS_ROCK] = true;
    flags[MegaKick][AFFECTED_BY_KINGS_ROCK] = true;
    flags[MegaPunch][AFFECTED_BY_KINGS_ROCK] = true;
    flags[Megahorn][AFFECTED_BY_KINGS_ROCK] = true;
    flags[MeteorMash][AFFECTED_BY_KINGS_ROCK] = true;
    flags[MirrorCoat][AFFECTED_BY_KINGS_ROCK] = true;
    flags[MirrorShot][AFFECTED_BY_KINGS_ROCK] = true;
    flags[MudBomb][AFFECTED_BY_KINGS_ROCK] = true;
    flags[MudShot][AFFECTED_BY_KINGS_ROCK] = true;
    flags[MuddyWater][AFFECTED_BY_KINGS_ROCK] = true;
    flags[NightShade][AFFECTED_BY_KINGS_ROCK] = true;
    flags[NightSlash][AFFECTED_BY_KINGS_ROCK] = true;
    flags[OminousWind][AFFECTED_BY_KINGS_ROCK] = true;
    flags[Outrage][AFFECTED_BY_KINGS_ROCK] = true;
    flags[Overheat][AFFECTED_BY_KINGS_ROCK] = true;
    flags[PayDay][AFFECTED_BY_KINGS_ROCK] = true;
    flags[Payback][AFFECTED_BY_KINGS_ROCK] = true;
    flags[Peck][AFFECTED_BY_KINGS_ROCK] = true;
    flags[PetalDance][AFFECTED_BY_KINGS_ROCK] = true;
    flags[PinMissile][AFFECTED_BY_KINGS_ROCK] = true;
    flags[Pluck][AFFECTED_BY_KINGS_ROCK] = true;
    flags[PoisonJab][AFFECTED_BY_KINGS_ROCK] = true;
    flags[PoisonTail][AFFECTED_BY_KINGS_ROCK] = true;
    flags[PowerGem][AFFECTED_BY_KINGS_ROCK] = true;
    flags[PowerWhip][AFFECTED_BY_KINGS_ROCK] = true;
    flags[PsychoBoost][AFFECTED_BY_KINGS_ROCK] = true;
    flags[PsychoCut][AFFECTED_BY_KINGS_ROCK] = true;
    flags[Psywave][AFFECTED_BY_KINGS_ROCK] = true;
    flags[Punishment][AFFECTED_BY_KINGS_ROCK] = true;
    flags[QuickAttack][AFFECTED_BY_KINGS_ROCK] = true;
    flags[Rage][AFFECTED_BY_KINGS_ROCK] = true;
    flags[RapidSpin][AFFECTED_BY_KINGS_ROCK] = true;
    flags[RazorLeaf][AFFECTED_BY_KINGS_ROCK] = true;
    flags[RazorWind][AFFECTED_BY_KINGS_ROCK] = true;
    flags[Return][AFFECTED_BY_KINGS_ROCK] = true;
    flags[Revenge][AFFECTED_BY_KINGS_ROCK] = true;
    flags[Reversal][AFFECTED_BY_KINGS_ROCK] = true;
    flags[RoarOfTime][AFFECTED_BY_KINGS_ROCK] = true;
    flags[RockBlast][AFFECTED_BY_KINGS_ROCK] = true;
    flags[RockClimb][AFFECTED_BY_KINGS_ROCK] = true;
    flags[RockThrow][AFFECTED_BY_KINGS_ROCK] = true;
    flags[RockWrecker][AFFECTED_BY_KINGS_ROCK] = true;
    flags[RollingKick][AFFECTED_BY_KINGS_ROCK] = true;
    flags[Rollout][AFFECTED_BY_KINGS_ROCK] = true;
    flags[SandTomb][AFFECTED_BY_KINGS_ROCK] = true;
    flags[Scratch][AFFECTED_BY_KINGS_ROCK] = true;
    flags[SeedBomb][AFFECTED_BY_KINGS_ROCK] = true;
    flags[SeedFlare][AFFECTED_BY_KINGS_ROCK] = true;
    flags[SeismicToss][AFFECTED_BY_KINGS_ROCK] = true;
    flags[ShadowClaw][AFFECTED_BY_KINGS_ROCK] = true;
    flags[ShadowForce][AFFECTED_BY_KINGS_ROCK] = true;
    flags[ShadowPunch][AFFECTED_BY_KINGS_ROCK] = true;
    flags[ShadowSneak][AFFECTED_BY_KINGS_ROCK] = true;
    flags[ShockWave][AFFECTED_BY_KINGS_ROCK] = true;
    flags[SignalBeam][AFFECTED_BY_KINGS_ROCK] = true;
    flags[SilverWind][AFFECTED_BY_KINGS_ROCK] = true;
    flags[SkullBash][AFFECTED_BY_KINGS_ROCK] = true;
    flags[SkyAttack][AFFECTED_BY_KINGS_ROCK] = true;
    flags[SkyUppercut][AFFECTED_BY_KINGS_ROCK] = true;
    flags[Slam][AFFECTED_BY_KINGS_ROCK] = true;
    flags[Slash][AFFECTED_BY_KINGS_ROCK] = true;
    flags[Snore][AFFECTED_BY_KINGS_ROCK] = true;
    flags[SolarBeam][AFFECTED_BY_KINGS_ROCK] = true;
    flags[SonicBoom][AFFECTED_BY_KINGS_ROCK] = true;
    flags[SpacialRend][AFFECTED_BY_KINGS_ROCK] = true;
    flags[SpikeCannon][AFFECTED_BY_KINGS_ROCK] = true;
    flags[SpitUp][AFFECTED_BY_KINGS_ROCK] = true;
    flags[SteelWing][AFFECTED_BY_KINGS_ROCK] = true;
    flags[StoneEdge][AFFECTED_BY_KINGS_ROCK] = true;
    flags[Strength][AFFECTED_BY_KINGS_ROCK] = true;
    flags[Struggle][AFFECTED_BY_KINGS_ROCK] = true;
    flags[Submission][AFFECTED_BY_KINGS_ROCK] = true;
    flags[SuckerPunch][AFFECTED_BY_KINGS_ROCK] = true;
    flags[Surf][AFFECTED_BY_KINGS_ROCK] = true;
    flags[Swift][AFFECTED_BY_KINGS_ROCK] = true;
    flags[Tackle][AFFECTED_BY_KINGS_ROCK] = true;
    flags[TakeDown][AFFECTED_BY_KINGS_ROCK] = true;
    flags[Thrash][AFFECTED_BY_KINGS_ROCK] = true;
    flags[ThunderFang][AFFECTED_BY_KINGS_ROCK] = true;
    flags[TripleKick][AFFECTED_BY_KINGS_ROCK] = true;
    flags[TrumpCard][AFFECTED_BY_KINGS_ROCK] = true;
    flags[Twister][AFFECTED_BY_KINGS_ROCK] = true;
    flags[UTurn][AFFECTED_BY_KINGS_ROCK] = true;
    flags[Uproar][AFFECTED_BY_KINGS_ROCK] = true;
    flags[VacuumWave][AFFECTED_BY_KINGS_ROCK] = true;
    flags[ViceGrip][AFFECTED_BY_KINGS_ROCK] = true;
    flags[VineWhip][AFFECTED_BY_KINGS_ROCK] = true;
    flags[VitalThrow][AFFECTED_BY_KINGS_ROCK] = true;
    flags[VoltTackle][AFFECTED_BY_KINGS_ROCK] = true;
    flags[WakeUpSlap][AFFECTED_BY_KINGS_ROCK] = true;
    flags[WaterGun][AFFECTED_BY_KINGS_ROCK] = true;
    flags[WaterPulse][AFFECTED_BY_KINGS_ROCK] = true;
    flags[Waterfall][AFFECTED_BY_KINGS_ROCK] = true;
    flags[WeatherBall][AFFECTED_BY_KINGS_ROCK] = true;
    flags[Whirlpool][AFFECTED_BY_KINGS_ROCK] = true;
    flags[WingAttack][AFFECTED_BY_KINGS_ROCK] = true;
    flags[WoodHammer][AFFECTED_BY_KINGS_ROCK] = true;
    flags[Wrap][AFFECTED_BY_KINGS_ROCK] = true;
    flags[WringOut][AFFECTED_BY_KINGS_ROCK] = true;
    flags[XScissor][AFFECTED_BY_KINGS_ROCK] = true;

    flags[Growl][IS_SOUND_BASED] = true;
    flags[Roar][IS_SOUND_BASED] = true;
    flags[Sing][IS_SOUND_BASED] = true;
    flags[Supersonic][IS_SOUND_BASED] = true;
    flags[Screech][IS_SOUND_BASED] = true;
    flags[Snore][IS_SOUND_BASED] = true;
    flags[PerishSong][IS_SOUND_BASED] = true;
    flags[HealBell][IS_SOUND_BASED] = true;
    flags[Uproar][IS_SOUND_BASED] = true;
    flags[HyperVoice][IS_SOUND_BASED] = true;
    flags[MetalSound][IS_SOUND_BASED] = true;
    flags[Grasswhistle][IS_SOUND_BASED] = true;
    flags[Howl][IS_SOUND_BASED] = true;
    flags[BugBuzz][IS_SOUND_BASED] = true;
    flags[Chatter][IS_SOUND_BASED] = true;
    return flags;
}();

inline bool move_has_flag(const Move move, const MoveFlag move_flag) {
    return MOVE_FLAGS[move][move_flag];
}

constexpr auto IMPLEMENTED_MOVES = [] {
    std::array<bool, MoveCount> implemented_moves{};
    implemented_moves[Moonlight] = true;
    implemented_moves[SignalBeam] = true;
    return implemented_moves;
}();

inline void verify_move_implemented(const Move move) {
    if (!IMPLEMENTED_MOVES[move]) {
        throw std::runtime_error(
            std::format(
                "Unimplemented move: {}",
                MOVE_TO_STRING_MAP.at(move)
            )
        );
    }
}

inline void _verify_moves_implemented(
    const std::vector<Move>& moves
) {
    for (const auto& move: moves) {
        verify_move_implemented(move);
    }
}

inline void verify_moves_implemented(
    const std::vector<Move>& player_moves,
    const std::vector<Move>& opponent_moves
    ) {
    if (CHECK_UNIMPLEMENTED) {
        _verify_moves_implemented(player_moves);
        _verify_moves_implemented(opponent_moves);
    }
}

