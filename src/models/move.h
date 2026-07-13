#pragma once

#include <array>
#include <format>
#include <string>
#include <vector>

#include "category.h"
#include "config.h"
#include "type.h"
#include "util.h"

enum class Move {
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
    Psychic,
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
    Metronome,
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
    Sandstorm,
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
    Hail,
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

inline const std::unordered_map<std::string, Move> STRING_TO_MOVE_MAP{
    {"Pound", Move::Pound},
    {"Karate Chop", Move::KarateChop},
    {"Doubleslap", Move::DoubleSlap},
    {"Comet Punch", Move::CometPunch},
    {"Mega Punch", Move::MegaPunch},
    {"Pay Day", Move::PayDay},
    {"Fire Punch", Move::FirePunch},
    {"Ice Punch", Move::IcePunch},
    {"Thunderpunch", Move::ThunderPunch},
    {"Thunder Punch", Move::ThunderPunch},
    {"Scratch", Move::Scratch},
    {"Vicegrip", Move::ViceGrip},
    {"Guillotine", Move::Guillotine},
    {"Razor Wind", Move::RazorWind},
    {"Swords Dance", Move::SwordsDance},
    {"Cut", Move::Cut},
    {"Gust", Move::Gust},
    {"Wing Attack", Move::WingAttack},
    {"Whirlwind", Move::Whirlwind},
    {"Fly", Move::Fly},
    {"Bind", Move::Bind},
    {"Slam", Move::Slam},
    {"Vine Whip", Move::VineWhip},
    {"Stomp", Move::Stomp},
    {"Double Kick", Move::DoubleKick},
    {"Mega Kick", Move::MegaKick},
    {"Jump Kick", Move::JumpKick},
    {"Rolling Kick", Move::RollingKick},
    {"Sand-attack", Move::SandAttack},
    {"Sand Attack", Move::SandAttack},
    {"Headbutt", Move::Headbutt},
    {"Horn Attack", Move::HornAttack},
    {"Fury Attack", Move::FuryAttack},
    {"Horn Drill", Move::HornDrill},
    {"Tackle", Move::Tackle},
    {"Body Slam", Move::BodySlam},
    {"Wrap", Move::Wrap},
    {"Take Down", Move::TakeDown},
    {"Thrash", Move::Thrash},
    {"Double-edge", Move::DoubleEdge},
    {"Double-Edge", Move::DoubleEdge},
    {"Tail Whip", Move::TailWhip},
    {"Poison Sting", Move::PoisonSting},
    {"Twineedle", Move::Twineedle},
    {"Pin Missile", Move::PinMissile},
    {"Leer", Move::Leer},
    {"Bite", Move::Bite},
    {"Growl", Move::Growl},
    {"Roar", Move::Roar},
    {"Sing", Move::Sing},
    {"Supersonic", Move::Supersonic},
    {"Sonicboom", Move::SonicBoom},
    {"Disable", Move::Disable},
    {"Acid", Move::Acid},
    {"Ember", Move::Ember},
    {"Flamethrower", Move::Flamethrower},
    {"Mist", Move::Mist},
    {"Water Gun", Move::WaterGun},
    {"Hydro Pump", Move::HydroPump},
    {"Surf", Move::Surf},
    {"Ice Beam", Move::IceBeam},
    {"Blizzard", Move::Blizzard},
    {"Psybeam", Move::Psybeam},
    {"Bubblebeam", Move::Bubblebeam},
    {"Bubble Beam", Move::Bubblebeam},
    {"Aurora Beam", Move::AuroraBeam},
    {"Hyper Beam", Move::HyperBeam},
    {"Peck", Move::Peck},
    {"Drill Peck", Move::DrillPeck},
    {"Submission", Move::Submission},
    {"Low Kick", Move::LowKick},
    {"Counter", Move::Counter},
    {"Seismic Toss", Move::SeismicToss},
    {"Strength", Move::Strength},
    {"Absorb", Move::Absorb},
    {"Mega Drain", Move::MegaDrain},
    {"Leech Seed", Move::LeechSeed},
    {"Growth", Move::Growth},
    {"Razor Leaf", Move::RazorLeaf},
    {"Solarbeam", Move::SolarBeam},
    {"Solar Beam", Move::SolarBeam},
    {"Poisonpowder", Move::PoisonPowder},
    {"Poison Powder", Move::PoisonPowder},
    {"Stun Spore", Move::StunSpore},
    {"Sleep Powder", Move::SleepPowder},
    {"Petal Dance", Move::PetalDance},
    {"String Shot", Move::StringShot},
    {"Dragon Rage", Move::DragonRage},
    {"Fire Spin", Move::FireSpin},
    {"Thundershock", Move::Thundershock},
    {"Thunderbolt", Move::Thunderbolt},
    {"Thunder Wave", Move::ThunderWave},
    {"Thunder", Move::Thunder},
    {"Rock Throw", Move::RockThrow},
    {"Earthquake", Move::Earthquake},
    {"Fissure", Move::Fissure},
    {"Dig", Move::Dig},
    {"Toxic", Move::Toxic},
    {"Confusion", Move::Confusion},
    {"Psychic", Move::Psychic},
    {"Hypnosis", Move::Hypnosis},
    {"Meditate", Move::Meditate},
    {"Agility", Move::Agility},
    {"Quick Attack", Move::QuickAttack},
    {"Rage", Move::Rage},
    {"Teleport", Move::Teleport},
    {"Night Shade", Move::NightShade},
    {"Mimic", Move::Mimic},
    {"Screech", Move::Screech},
    {"Double Team", Move::DoubleTeam},
    {"Recover", Move::Recover},
    {"Harden", Move::Harden},
    {"Minimize", Move::Minimize},
    {"Smokescreen", Move::Smokescreen},
    {"SmokeScreen", Move::Smokescreen},
    {"Confuse Ray", Move::ConfuseRay},
    {"Withdraw", Move::Withdraw},
    {"Defense Curl", Move::DefenseCurl},
    {"Barrier", Move::Barrier},
    {"Light Screen", Move::LightScreen},
    {"Haze", Move::Haze},
    {"Reflect", Move::Reflect},
    {"Focus Energy", Move::FocusEnergy},
    {"Bide", Move::Bide},
    {"Metronome", Move::Metronome},
    {"Mirror Move", Move::MirrorMove},
    {"Selfdestruct", Move::Selfdestruct},
    {"Egg Bomb", Move::EggBomb},
    {"Lick", Move::Lick},
    {"Smog", Move::Smog},
    {"Sludge", Move::Sludge},
    {"Bone Club", Move::BoneClub},
    {"Fire Blast", Move::FireBlast},
    {"Waterfall", Move::Waterfall},
    {"Clamp", Move::Clamp},
    {"Swift", Move::Swift},
    {"Skull Bash", Move::SkullBash},
    {"Spike Cannon", Move::SpikeCannon},
    {"Constrict", Move::Constrict},
    {"Amnesia", Move::Amnesia},
    {"Kinesis", Move::Kinesis},
    {"Softboiled", Move::Softboiled},
    {"Soft-Boiled", Move::Softboiled},
    {"Hi Jump Kick", Move::HighJumpKick},
    {"High Jump Kick", Move::HighJumpKick},
    {"Glare", Move::Glare},
    {"Dream Eater", Move::DreamEater},
    {"Poison Gas", Move::PoisonGas},
    {"Barrage", Move::Barrage},
    {"Leech Life", Move::LeechLife},
    {"Lovely Kiss", Move::LovelyKiss},
    {"Sky Attack", Move::SkyAttack},
    {"Transform", Move::Transform},
    {"Bubble", Move::Bubble},
    {"Dizzy Punch", Move::DizzyPunch},
    {"Spore", Move::Spore},
    {"Flash", Move::Flash},
    {"Psywave", Move::Psywave},
    {"Splash", Move::Splash},
    {"Acid Armor", Move::AcidArmor},
    {"Crabhammer", Move::Crabhammer},
    {"Explosion", Move::Explosion},
    {"Fury Swipes", Move::FurySwipes},
    {"Bonemerang", Move::Bonemerang},
    {"Rest", Move::Rest},
    {"Rock Slide", Move::RockSlide},
    {"Hyper Fang", Move::HyperFang},
    {"Sharpen", Move::Sharpen},
    {"Conversion", Move::Conversion},
    {"Tri Attack", Move::TriAttack},
    {"Super Fang", Move::SuperFang},
    {"Slash", Move::Slash},
    {"Substitute", Move::Substitute},
    {"Struggle", Move::Struggle},
    {"Sketch", Move::Sketch},
    {"Triple Kick", Move::TripleKick},
    {"Thief", Move::Thief},
    {"Spider Web", Move::SpiderWeb},
    {"Mind Reader", Move::MindReader},
    {"Nightmare", Move::Nightmare},
    {"Flame Wheel", Move::FlameWheel},
    {"Snore", Move::Snore},
    {"Curse", Move::Curse},
    {"Flail", Move::Flail},
    {"Conversion 2", Move::Conversion2},
    {"Aeroblast", Move::Aeroblast},
    {"Cotton Spore", Move::CottonSpore},
    {"Reversal", Move::Reversal},
    {"Spite", Move::Spite},
    {"Powder Snow", Move::PowderSnow},
    {"Protect", Move::Protect},
    {"Mach Punch", Move::MachPunch},
    {"Scary Face", Move::ScaryFace},
    {"Faint Attack", Move::FaintAttack},
    {"Feint Attack", Move::FaintAttack},
    {"Sweet Kiss", Move::SweetKiss},
    {"Belly Drum", Move::BellyDrum},
    {"Sludge Bomb", Move::SludgeBomb},
    {"Mud-slap", Move::MudSlap},
    {"Mud-Slap", Move::MudSlap},
    {"Octazooka", Move::Octazooka},
    {"Spikes", Move::Spikes},
    {"Zap Cannon", Move::ZapCannon},
    {"Foresight", Move::Foresight},
    {"Destiny Bond", Move::DestinyBond},
    {"Perish Song", Move::PerishSong},
    {"Icy Wind", Move::IcyWind},
    {"Detect", Move::Detect},
    {"Bone Rush", Move::BoneRush},
    {"Lock-on", Move::LockOn},
    {"Outrage", Move::Outrage},
    {"Sandstorm", Move::Sandstorm},
    {"Giga Drain", Move::GigaDrain},
    {"Endure", Move::Endure},
    {"Charm", Move::Charm},
    {"Rollout", Move::Rollout},
    {"False Swipe", Move::FalseSwipe},
    {"Swagger", Move::Swagger},
    {"Milk Drink", Move::MilkDrink},
    {"Spark", Move::Spark},
    {"Fury Cutter", Move::FuryCutter},
    {"Steel Wing", Move::SteelWing},
    {"Mean Look", Move::MeanLook},
    {"Attract", Move::Attract},
    {"Sleep Talk", Move::SleepTalk},
    {"Heal Bell", Move::HealBell},
    {"Return", Move::Return},
    {"Present", Move::Present},
    {"Frustration", Move::Frustration},
    {"Safeguard", Move::Safeguard},
    {"Pain Split", Move::PainSplit},
    {"Sacred Fire", Move::SacredFire},
    {"Magnitude", Move::Magnitude},
    {"Dynamicpunch", Move::Dynamicpunch},
    {"Dynamic Punch", Move::Dynamicpunch},
    {"Megahorn", Move::Megahorn},
    {"Dragonbreath", Move::DragonBreath},
    {"Baton Pass", Move::BatonPass},
    {"Encore", Move::Encore},
    {"Pursuit", Move::Pursuit},
    {"Rapid Spin", Move::RapidSpin},
    {"Sweet Scent", Move::SweetScent},
    {"Iron Tail", Move::IronTail},
    {"Metal Claw", Move::MetalClaw},
    {"Vital Throw", Move::VitalThrow},
    {"Morning Sun", Move::MorningSun},
    {"Synthesis", Move::Synthesis},
    {"Moonlight", Move::Moonlight},
    {"Hidden Power", Move::HiddenPower},
    {"Cross Chop", Move::CrossChop},
    {"Twister", Move::Twister},
    {"Rain Dance", Move::RainDance},
    {"Sunny Day", Move::SunnyDay},
    {"Crunch", Move::Crunch},
    {"Mirror Coat", Move::MirrorCoat},
    {"Psych Up", Move::PsychUp},
    {"Extremespeed", Move::ExtremeSpeed},
    {"Extreme Speed", Move::ExtremeSpeed},
    {"Ancientpower", Move::Ancientpower},
    {"Ancient Power", Move::Ancientpower},
    {"Shadow Ball", Move::ShadowBall},
    {"Future Sight", Move::FutureSight},
    {"Rock Smash", Move::RockSmash},
    {"Whirlpool", Move::Whirlpool},
    {"Beat Up", Move::BeatUp},
    {"Fake Out", Move::FakeOut},
    {"Uproar", Move::Uproar},
    {"Stockpile", Move::Stockpile},
    {"Spit Up", Move::SpitUp},
    {"Swallow", Move::Swallow},
    {"Heat Wave", Move::HeatWave},
    {"Hail", Move::Hail},
    {"Torment", Move::Torment},
    {"Flatter", Move::Flatter},
    {"Will-o-wisp", Move::WillOWisp},
    {"Will-O-Wisp", Move::WillOWisp},
    {"Memento", Move::Memento},
    {"Facade", Move::Facade},
    {"Focus Punch", Move::FocusPunch},
    {"Smellingsalt", Move::Smellingsalt},
    {"Follow Me", Move::FollowMe},
    {"Nature Power", Move::NaturePower},
    {"Charge", Move::Charge},
    {"Taunt", Move::Taunt},
    {"Helping Hand", Move::HelpingHand},
    {"Trick", Move::Trick},
    {"Role Play", Move::RolePlay},
    {"Wish", Move::Wish},
    {"Assist", Move::Assist},
    {"Ingrain", Move::Ingrain},
    {"Superpower", Move::Superpower},
    {"Magic Coat", Move::MagicCoat},
    {"Recycle", Move::Recycle},
    {"Revenge", Move::Revenge},
    {"Brick Break", Move::BrickBreak},
    {"Yawn", Move::Yawn},
    {"Knock Off", Move::KnockOff},
    {"Endeavor", Move::Endeavor},
    {"Eruption", Move::Eruption},
    {"Skill Swap", Move::SkillSwap},
    {"Imprison", Move::Imprison},
    {"Refresh", Move::Refresh},
    {"Grudge", Move::Grudge},
    {"Snatch", Move::Snatch},
    {"Secret Power", Move::SecretPower},
    {"Dive", Move::Dive},
    {"Arm Thrust", Move::ArmThrust},
    {"Camouflage", Move::Camouflage},
    {"Tail Glow", Move::TailGlow},
    {"Luster Purge", Move::LusterPurge},
    {"Mist Ball", Move::MistBall},
    {"Featherdance", Move::Featherdance},
    {"Feather Dance", Move::Featherdance},
    {"Teeter Dance", Move::TeeterDance},
    {"Blaze Kick", Move::BlazeKick},
    {"Mud Sport", Move::MudSport},
    {"Ice Ball", Move::IceBall},
    {"Needle Arm", Move::NeedleArm},
    {"Slack Off", Move::SlackOff},
    {"Hyper Voice", Move::HyperVoice},
    {"Poison Fang", Move::PoisonFang},
    {"Crush Claw", Move::CrushClaw},
    {"Blast Burn", Move::BlastBurn},
    {"Hydro Cannon", Move::HydroCannon},
    {"Meteor Mash", Move::MeteorMash},
    {"Astonish", Move::Astonish},
    {"Weather Ball", Move::WeatherBall},
    {"Aromatherapy", Move::Aromatherapy},
    {"Fake Tears", Move::FakeTears},
    {"Air Cutter", Move::AirCutter},
    {"Overheat", Move::Overheat},
    {"Odor Sleuth", Move::OdorSleuth},
    {"Rock Tomb", Move::RockTomb},
    {"Silver Wind", Move::SilverWind},
    {"Metal Sound", Move::MetalSound},
    {"Grasswhistle", Move::Grasswhistle},
    {"Tickle", Move::Tickle},
    {"Cosmic Power", Move::CosmicPower},
    {"Water Spout", Move::WaterSpout},
    {"Signal Beam", Move::SignalBeam},
    {"Shadow Punch", Move::ShadowPunch},
    {"Extrasensory", Move::Extrasensory},
    {"Sky Uppercut", Move::SkyUppercut},
    {"Sand Tomb", Move::SandTomb},
    {"Sheer Cold", Move::SheerCold},
    {"Muddy Water", Move::MuddyWater},
    {"Bullet Seed", Move::BulletSeed},
    {"Aerial Ace", Move::AerialAce},
    {"Icicle Spear", Move::IcicleSpear},
    {"Iron Defense", Move::IronDefense},
    {"Block", Move::Block},
    {"Howl", Move::Howl},
    {"Dragon Claw", Move::DragonClaw},
    {"Frenzy Plant", Move::FrenzyPlant},
    {"Bulk Up", Move::BulkUp},
    {"Bounce", Move::Bounce},
    {"Mud Shot", Move::MudShot},
    {"Poison Tail", Move::PoisonTail},
    {"Covet", Move::Covet},
    {"Volt Tackle", Move::VoltTackle},
    {"Magical Leaf", Move::MagicalLeaf},
    {"Water Sport", Move::WaterSport},
    {"Calm Mind", Move::CalmMind},
    {"Leaf Blade", Move::LeafBlade},
    {"Dragon Dance", Move::DragonDance},
    {"Rock Blast", Move::RockBlast},
    {"Shock Wave", Move::ShockWave},
    {"Water Pulse", Move::WaterPulse},
    {"Doom Desire", Move::DoomDesire},
    {"Psycho Boost", Move::PsychoBoost},
    {"Roost", Move::Roost},
    {"Gravity", Move::Gravity},
    {"Miracle Eye", Move::MiracleEye},
    {"Wake-up Slap", Move::WakeUpSlap},
    {"Hammer Arm", Move::HammerArm},
    {"Gyro Ball", Move::GyroBall},
    {"Healing Wish", Move::HealingWish},
    {"Brine", Move::Brine},
    {"Natural Gift", Move::NaturalGift},
    {"Feint", Move::Feint},
    {"Pluck", Move::Pluck},
    {"Tailwind", Move::Tailwind},
    {"Acupressure", Move::Acupressure},
    {"Metal Burst", Move::MetalBurst},
    {"U-turn", Move::UTurn},
    {"Close Combat", Move::CloseCombat},
    {"Payback", Move::Payback},
    {"Assurance", Move::Assurance},
    {"Embargo", Move::Embargo},
    {"Fling", Move::Fling},
    {"Psycho Shift", Move::PsychoShift},
    {"Trump Card", Move::TrumpCard},
    {"Heal Block", Move::HealBlock},
    {"Wring Out", Move::WringOut},
    {"Power Trick", Move::PowerTrick},
    {"Gastro Acid", Move::GastroAcid},
    {"Lucky Chant", Move::LuckyChant},
    {"Me First", Move::MeFirst},
    {"Copycat", Move::Copycat},
    {"Power Swap", Move::PowerSwap},
    {"Guard Swap", Move::GuardSwap},
    {"Punishment", Move::Punishment},
    {"Last Resort", Move::LastResort},
    {"Worry Seed", Move::WorrySeed},
    {"Sucker Punch", Move::SuckerPunch},
    {"Toxic Spikes", Move::ToxicSpikes},
    {"Heart Swap", Move::HeartSwap},
    {"Aqua Ring", Move::AquaRing},
    {"Magnet Rise", Move::MagnetRise},
    {"Flare Blitz", Move::FlareBlitz},
    {"Force Palm", Move::ForcePalm},
    {"Aura Sphere", Move::AuraSphere},
    {"Rock Polish", Move::RockPolish},
    {"Poison Jab", Move::PoisonJab},
    {"Dark Pulse", Move::DarkPulse},
    {"Night Slash", Move::NightSlash},
    {"Aqua Tail", Move::AquaTail},
    {"Seed Bomb", Move::SeedBomb},
    {"Air Slash", Move::AirSlash},
    {"X-scissor", Move::XScissor},
    {"X-Scissor", Move::XScissor},
    {"Bug Buzz", Move::BugBuzz},
    {"Dragon Pulse", Move::DragonPulse},
    {"Dragon Rush", Move::DragonRush},
    {"Power Gem", Move::PowerGem},
    {"Drain Punch", Move::DrainPunch},
    {"Vacuum Wave", Move::VacuumWave},
    {"Focus Blast", Move::FocusBlast},
    {"Energy Ball", Move::EnergyBall},
    {"Brave Bird", Move::BraveBird},
    {"Earth Power", Move::EarthPower},
    {"Switcheroo", Move::Switcheroo},
    {"Giga Impact", Move::GigaImpact},
    {"Nasty Plot", Move::NastyPlot},
    {"Bullet Punch", Move::BulletPunch},
    {"Avalanche", Move::Avalanche},
    {"Ice Shard", Move::IceShard},
    {"Shadow Claw", Move::ShadowClaw},
    {"Thunder Fang", Move::ThunderFang},
    {"Ice Fang", Move::IceFang},
    {"Fire Fang", Move::FireFang},
    {"Shadow Sneak", Move::ShadowSneak},
    {"Mud Bomb", Move::MudBomb},
    {"Psycho Cut", Move::PsychoCut},
    {"Zen Headbutt", Move::ZenHeadbutt},
    {"Mirror Shot", Move::MirrorShot},
    {"Flash Cannon", Move::FlashCannon},
    {"Rock Climb", Move::RockClimb},
    {"Defog", Move::Defog},
    {"Trick Room", Move::TrickRoom},
    {"Draco Meteor", Move::DracoMeteor},
    {"Discharge", Move::Discharge},
    {"Lava Plume", Move::LavaPlume},
    {"Leaf Storm", Move::LeafStorm},
    {"Power Whip", Move::PowerWhip},
    {"Rock Wrecker", Move::RockWrecker},
    {"Cross Poison", Move::CrossPoison},
    {"Gunk Shot", Move::GunkShot},
    {"Iron Head", Move::IronHead},
    {"Magnet Bomb", Move::MagnetBomb},
    {"Stone Edge", Move::StoneEdge},
    {"Captivate", Move::Captivate},
    {"Stealth Rock", Move::StealthRock},
    {"Grass Knot", Move::GrassKnot},
    {"Chatter", Move::Chatter},
    {"Judgment", Move::Judgment},
    {"Bug Bite", Move::BugBite},
    {"Charge Beam", Move::ChargeBeam},
    {"Wood Hammer", Move::WoodHammer},
    {"Aqua Jet", Move::AquaJet},
    {"Attack Order", Move::AttackOrder},
    {"Defend Order", Move::DefendOrder},
    {"Heal Order", Move::HealOrder},
    {"Head Smash", Move::HeadSmash},
    {"Double Hit", Move::DoubleHit},
    {"Roar Of Time", Move::RoarOfTime},
    {"Spacial Rend", Move::SpacialRend},
    {"Lunar Dance", Move::LunarDance},
    {"Crush Grip", Move::CrushGrip},
    {"Magma Storm", Move::MagmaStorm},
    {"Dark Void", Move::DarkVoid},
    {"Seed Flare", Move::SeedFlare},
    {"Ominous Wind", Move::OminousWind},
    {"Shadow Force", Move::ShadowForce}
};

inline std::unordered_map<Move, std::string> create_reverse_move_map() {
    std::unordered_map<Move, std::string> reverse_map;
    for (const auto& [str, move] : STRING_TO_MOVE_MAP) {
        reverse_map[move] = str;
    }
    return reverse_map;
}

inline const auto MOVE_TO_STRING_MAP =
    create_reverse_move_map();

enum class MoveFlag {
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
    CONFUSES_DEFENDER, // TODO replace
    CONTINUES,
    DEALS_DOUBLE_AFTER_MINIMIZE,
    FLINCHES_DEFENDER,
    FORCES_USER_OUT,
    FREEZES_DEFENDER, // TODO replace
    FREEZES_DEFENDER_10,
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
    LOWERS_DEFENDER_SPECIAL_ATTACK, // TODO replace
    LOWERS_DEFENDER_SPECIAL_ATTACK_ONE_STAGE_50,
    LOWERS_DEFENDER_SPECIAL_DEFENSE, // TODO replace
    LOWERS_DEFENDER_SPECIAL_DEFENSE_ONE_STAGE_10,
    LOWERS_DEFENDER_SPEED,
    MAKES_ATTACKER_FAINT,
    MAKES_CONTACT,
    MAKES_DEFENDER_SLEEP,
    BYPASSES_ACCURACY,
    OMNI_BOOSTS_ATTACKER,
    PARALYZES_DEFENDER, // TODO remove
    PARALYZES_DEFENDER_10,
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

using MoveFlagSet = std::array<bool, to_int(MoveFlag::COUNT)>;
inline constexpr std::array<
    MoveFlagSet,
    to_int(Move::MoveCount)
> MOVE_FLAGS = [] {
    std::array<MoveFlagSet, to_int(Move::MoveCount)> flags{};
    for (auto& flag : flags) {
        flag.fill(false);
    }

    flags[to_int(Move::BulletPunch)][to_int(MoveFlag::POWERS_IRON_FIST)] = true;
    flags[to_int(Move::CometPunch)][to_int(MoveFlag::POWERS_IRON_FIST)] = true;
    flags[to_int(Move::DizzyPunch)][to_int(MoveFlag::POWERS_IRON_FIST)] = true;
    flags[to_int(Move::DrainPunch)][to_int(MoveFlag::POWERS_IRON_FIST)] = true;
    flags[to_int(Move::Dynamicpunch)][to_int(MoveFlag::POWERS_IRON_FIST)] =
        true;
    flags[to_int(Move::FirePunch)][to_int(MoveFlag::POWERS_IRON_FIST)] = true;
    flags[to_int(Move::FocusPunch)][to_int(MoveFlag::POWERS_IRON_FIST)] = true;
    flags[to_int(Move::HammerArm)][to_int(MoveFlag::POWERS_IRON_FIST)] = true;
    flags[to_int(Move::IcePunch)][to_int(MoveFlag::POWERS_IRON_FIST)] = true;
    flags[to_int(Move::MachPunch)][to_int(MoveFlag::POWERS_IRON_FIST)] = true;
    flags[to_int(Move::ShadowPunch)][to_int(MoveFlag::POWERS_IRON_FIST)] = true;
    flags[to_int(Move::SkyUppercut)][to_int(MoveFlag::POWERS_IRON_FIST)] = true;
    flags[to_int(Move::ThunderPunch)][to_int(MoveFlag::POWERS_IRON_FIST)] =
        true;

    flags[to_int(Move::Pound)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::DoubleSlap)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::CometPunch)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::MegaPunch)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::PayDay)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::FirePunch)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::IcePunch)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::ThunderPunch)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::Scratch)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::ViceGrip)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::RazorWind)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::Cut)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::Gust)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::WingAttack)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::Fly)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::Bind)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::Slam)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::VineWhip)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::Stomp)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::DoubleKick)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::MegaKick)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::JumpKick)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::RollingKick)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::Headbutt)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::HornAttack)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::FuryAttack)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::Tackle)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::BodySlam)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::Wrap)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::TakeDown)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::Thrash)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::DoubleEdge)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::PoisonSting)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::Twineedle)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::PinMissile)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::Bite)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::Acid)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::Ember)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::Flamethrower)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::WaterGun)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::HydroPump)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::Surf)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::IceBeam)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::Blizzard)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::Psybeam)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::Bubblebeam)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::AuroraBeam)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::HyperBeam)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::Peck)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::DrillPeck)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::Submission)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::Strength)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::Absorb)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::MegaDrain)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::RazorLeaf)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::SolarBeam)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::PetalDance)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::FireSpin)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::Thundershock)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::Thunderbolt)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::RockThrow)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::Earthquake)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::Dig)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::Confusion)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::Psychic)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::QuickAttack)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::Selfdestruct)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::EggBomb)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::Lick)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::Smog)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::Sludge)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::BoneClub)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::FireBlast)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::Waterfall)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::Clamp)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::Swift)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::SkullBash)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::SpikeCannon)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::Constrict)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::HighJumpKick)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::Barrage)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::LeechLife)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::SkyAttack)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::Bubble)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::DizzyPunch)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::Crabhammer)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::Explosion)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::FuryAttack)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::Bonemerang)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::RockSlide)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::HyperFang)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::TriAttack)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::Slash)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::FlameWheel)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::Aeroblast)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::PowderSnow)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::MachPunch)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::FaintAttack)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::SludgeBomb)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::MudSlap)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::Octazooka)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::ZapCannon)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::IcyWind)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::BoneRush)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::Outrage)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::GigaDrain)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::Spark)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::SteelWing)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::Return)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::Frustration)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::SacredFire)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::Dynamicpunch)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::Megahorn)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::DragonBreath)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::IronTail)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::MetalClaw)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::VitalThrow)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::CrossChop)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::Twister)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::Crunch)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::ExtremeSpeed)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::Ancientpower)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::ShadowBall)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::RockSmash)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::Whirlpool)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::HeatWave)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::Superpower)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::Dive)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::ArmThrust)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::LusterPurge)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::MistBall)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::BlazeKick)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::NeedleArm)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::HyperVoice)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::PoisonFang)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::CrushClaw)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::BlastBurn)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::HydroCannon)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::MeteorMash)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::Astonish)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::AirCutter)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::Overheat)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::RockTomb)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::SilverWind)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::SignalBeam)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::ShadowPunch)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::Extrasensory)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::SkyUppercut)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::SandTomb)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::MuddyWater)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::BulletSeed)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::AerialAce)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::IcicleSpear)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::DragonClaw)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::FrenzyPlant)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::Bounce)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::MudShot)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::PoisonTail)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::VoltTackle)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::MagicalLeaf)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::LeafBlade)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::RockBlast)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::ShockWave)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::WaterPulse)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::PsychoBoost)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::HammerArm)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::CloseCombat)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::FlareBlitz)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::ForcePalm)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::AuraSphere)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::PoisonJab)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::DarkPulse)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::NightSlash)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::AquaTail)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::SeedBomb)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::AirSlash)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::XScissor)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::BugBuzz)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::DragonPulse)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::DragonRush)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::PowerGem)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::DrainPunch)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::VacuumWave)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::FocusBlast)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::EnergyBall)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::BraveBird)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::EarthPower)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::GigaImpact)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::BulletPunch)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::IceShard)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::ShadowClaw)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::ThunderFang)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::IceFang)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::FireFang)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::ShadowSneak)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::MudBomb)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::PsychoCut)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::ZenHeadbutt)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::MirrorShot)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::FlashCannon)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::RockClimb)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::DracoMeteor)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::Discharge)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::LavaPlume)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::LeafStorm)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::PowerWhip)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::RockWrecker)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::CrossPoison)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::GunkShot)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::IronHead)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::MagnetBomb)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::StoneEdge)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::ChargeBeam)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::WoodHammer)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::AquaJet)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::AttackOrder)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::HeadSmash)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::DoubleHit)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::RoarOfTime)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::SpacialRend)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::SeedFlare)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::OminousWind)][to_int(MoveFlag::HAS_POWER)] = true;
    flags[to_int(Move::ShadowForce)][to_int(MoveFlag::HAS_POWER)] = true;

    flags[to_int(Move::Absorb)][to_int(MoveFlag::HEALS_ATTACKER)] = true;
    flags[to_int(Move::MegaDrain)][to_int(MoveFlag::HEALS_ATTACKER)] = true;
    flags[to_int(Move::Recover)][to_int(MoveFlag::HEALS_ATTACKER)] = true;
    flags[to_int(Move::Softboiled)][to_int(MoveFlag::HEALS_ATTACKER)] = true;
    flags[to_int(Move::LeechLife)][to_int(MoveFlag::HEALS_ATTACKER)] = true;
    flags[to_int(Move::GigaDrain)][to_int(MoveFlag::HEALS_ATTACKER)] = true;
    flags[to_int(Move::MilkDrink)][to_int(MoveFlag::HEALS_ATTACKER)] = true;
    flags[to_int(Move::MorningSun)][to_int(MoveFlag::HEALS_ATTACKER)] = true;
    flags[to_int(Move::Synthesis)][to_int(MoveFlag::HEALS_ATTACKER)] = true;
    flags[to_int(Move::Moonlight)][to_int(MoveFlag::HEALS_ATTACKER)] = true;
    flags[to_int(Move::SlackOff)][to_int(MoveFlag::HEALS_ATTACKER)] = true;
    flags[to_int(Move::DrainPunch)][to_int(MoveFlag::HEALS_ATTACKER)] = true;
    flags[to_int(Move::HealOrder)][to_int(MoveFlag::HEALS_ATTACKER)] = true;

    flags[to_int(Move::SwordsDance)][to_int(MoveFlag::BOOSTS_ATTACKER_STAT)] =
        true;
    flags[to_int(Move::Growth)][to_int(MoveFlag::BOOSTS_ATTACKER_STAT)] = true;
    flags[to_int(Move::Meditate)][to_int(MoveFlag::BOOSTS_ATTACKER_STAT)] =
        true;
    flags[to_int(Move::Agility)][to_int(MoveFlag::BOOSTS_ATTACKER_STAT)] = true;
    flags[to_int(Move::DoubleTeam)][to_int(MoveFlag::BOOSTS_ATTACKER_STAT)] =
        true;
    flags[to_int(Move::Harden)][to_int(MoveFlag::BOOSTS_ATTACKER_STAT)] = true;
    flags[to_int(Move::Minimize)][to_int(MoveFlag::BOOSTS_ATTACKER_STAT)] =
        true;
    flags[to_int(Move::Withdraw)][to_int(MoveFlag::BOOSTS_ATTACKER_STAT)] =
        true;
    flags[to_int(Move::Amnesia)][to_int(MoveFlag::BOOSTS_ATTACKER_STAT)] = true;
    flags[to_int(Move::AcidArmor)][to_int(MoveFlag::BOOSTS_ATTACKER_STAT)] =
        true;
    flags[to_int(Move::Sharpen)][to_int(MoveFlag::BOOSTS_ATTACKER_STAT)] = true;
    flags[to_int(Move::TailGlow)][to_int(MoveFlag::BOOSTS_ATTACKER_STAT)] =
        true;
    flags[to_int(Move::CosmicPower)][to_int(MoveFlag::BOOSTS_ATTACKER_STAT)] =
        true;
    flags[to_int(Move::IronDefense)][to_int(MoveFlag::BOOSTS_ATTACKER_STAT)] =
        true;
    flags[to_int(Move::Howl)][to_int(MoveFlag::BOOSTS_ATTACKER_STAT)] = true;
    flags[to_int(Move::BulkUp)][to_int(MoveFlag::BOOSTS_ATTACKER_STAT)] = true;
    flags[to_int(Move::CalmMind)][to_int(MoveFlag::BOOSTS_ATTACKER_STAT)] =
        true;
    flags[to_int(Move::DragonDance)][to_int(MoveFlag::BOOSTS_ATTACKER_STAT)] =
        true;
    flags[to_int(Move::RockPolish)][to_int(MoveFlag::BOOSTS_ATTACKER_STAT)] =
        true;
    flags[to_int(Move::NastyPlot)][to_int(MoveFlag::BOOSTS_ATTACKER_STAT)] =
        true;
    flags[to_int(Move::DefendOrder)][to_int(MoveFlag::BOOSTS_ATTACKER_STAT)] =
        true;

    flags[to_int(Move::SwordsDance)][to_int(MoveFlag::BOOSTS_ATTACKERS_ATTACK)]
        = true;
    flags[to_int(Move::Meditate)][to_int(MoveFlag::BOOSTS_ATTACKERS_ATTACK)] =
        true;
    flags[to_int(Move::Sharpen)][to_int(MoveFlag::BOOSTS_ATTACKERS_ATTACK)] =
        true;
    flags[to_int(Move::BellyDrum)][to_int(MoveFlag::BOOSTS_ATTACKERS_ATTACK)] =
        true;
    flags[to_int(Move::MetalClaw)][to_int(MoveFlag::BOOSTS_ATTACKERS_ATTACK)] =
        true;
    flags[to_int(Move::MeteorMash)][to_int(MoveFlag::BOOSTS_ATTACKERS_ATTACK)] =
        true;
    flags[to_int(Move::Howl)][to_int(MoveFlag::BOOSTS_ATTACKERS_ATTACK)] = true;
    flags[to_int(Move::BulkUp)][to_int(MoveFlag::BOOSTS_ATTACKERS_ATTACK)] =
        true;
    flags[to_int(Move::DragonDance)][to_int(MoveFlag::BOOSTS_ATTACKERS_ATTACK)]
        = true;

    flags[to_int(Move::Superpower)][to_int(MoveFlag::LOWERS_ATTACKERS_ATTACK)] =
        true;

    flags[to_int(Move::Harden)][to_int(MoveFlag::BOOSTS_ATTACKERS_DEFENSE)] =
        true;
    flags[to_int(Move::Withdraw)][to_int(MoveFlag::BOOSTS_ATTACKERS_DEFENSE)] =
        true;
    flags[to_int(Move::SkullBash)][to_int(MoveFlag::BOOSTS_ATTACKERS_DEFENSE)] =
        true;
    flags[to_int(Move::AcidArmor)][to_int(MoveFlag::BOOSTS_ATTACKERS_DEFENSE)] =
        true;
    flags[to_int(Move::SteelWing)][to_int(MoveFlag::BOOSTS_ATTACKERS_DEFENSE)] =
        true;
    flags[to_int(Move::CosmicPower)][to_int(MoveFlag::BOOSTS_ATTACKERS_DEFENSE)]
        = true;
    flags[to_int(Move::IronDefense)][to_int(MoveFlag::BOOSTS_ATTACKERS_DEFENSE)]
        = true;
    flags[to_int(Move::BulkUp)][to_int(MoveFlag::BOOSTS_ATTACKERS_DEFENSE)] =
        true;
    flags[to_int(Move::DefendOrder)][to_int(MoveFlag::BOOSTS_ATTACKERS_DEFENSE)]
        = true;

    flags[to_int(Move::Superpower)][to_int(MoveFlag::LOWERS_ATTACKERS_DEFENSE)]
        = true;
    flags[to_int(Move::CloseCombat)][to_int(MoveFlag::LOWERS_ATTACKERS_DEFENSE)]
        = true;

    flags[to_int(Move::Overheat)][to_int(
        MoveFlag::LOWERS_ATTACKERS_SPECIAL_ATTACK)] = true;
    flags[to_int(Move::PsychoBoost)][to_int(
        MoveFlag::LOWERS_ATTACKERS_SPECIAL_ATTACK)] = true;
    flags[to_int(Move::DracoMeteor)][to_int(
        MoveFlag::LOWERS_ATTACKERS_SPECIAL_ATTACK)] = true;
    flags[to_int(Move::LeafStorm)][to_int(
        MoveFlag::LOWERS_ATTACKERS_SPECIAL_ATTACK)] = true;

    flags[to_int(Move::Growth)][to_int(
        MoveFlag::BOOSTS_ATTACKERS_SPECIAL_ATTACK)] = true;
    flags[to_int(Move::TailGlow)][to_int(
        MoveFlag::BOOSTS_ATTACKERS_SPECIAL_ATTACK)] = true;
    flags[to_int(Move::CalmMind)][to_int(
        MoveFlag::BOOSTS_ATTACKERS_SPECIAL_ATTACK)] = true;
    flags[to_int(Move::NastyPlot)][to_int(
        MoveFlag::BOOSTS_ATTACKERS_SPECIAL_ATTACK)] = true;
    flags[to_int(Move::ChargeBeam)][to_int(
        MoveFlag::BOOSTS_ATTACKERS_SPECIAL_ATTACK)] = true;

    flags[to_int(Move::Amnesia)][to_int(
        MoveFlag::BOOSTS_ATTACKERS_SPECIAL_DEFENSE)] = true;
    flags[to_int(Move::CosmicPower)][to_int(
        MoveFlag::BOOSTS_ATTACKERS_SPECIAL_DEFENSE)] = true;
    flags[to_int(Move::CalmMind)][to_int(
        MoveFlag::BOOSTS_ATTACKERS_SPECIAL_DEFENSE)] = true;
    flags[to_int(Move::DefendOrder)][to_int(
        MoveFlag::BOOSTS_ATTACKERS_SPECIAL_DEFENSE)] = true;

    flags[to_int(Move::CloseCombat)][to_int(
        MoveFlag::LOWERS_ATTACKERS_SPECIAL_DEFENSE)] = true;

    flags[to_int(Move::Agility)][to_int(MoveFlag::BOOSTS_ATTACKERS_SPEED)] =
        true;
    flags[to_int(Move::DragonDance)][to_int(MoveFlag::BOOSTS_ATTACKERS_SPEED)] =
        true;
    flags[to_int(Move::RockPolish)][to_int(MoveFlag::BOOSTS_ATTACKERS_SPEED)] =
        true;

    flags[to_int(Move::HammerArm)][to_int(MoveFlag::LOWERS_ATTACKERS_SPEED)] =
        true;

    flags[to_int(Move::DoubleTeam)][to_int(MoveFlag::BOOSTS_ATTACKERS_EVASION)]
        = true;
    flags[to_int(Move::Minimize)][to_int(MoveFlag::BOOSTS_ATTACKERS_EVASION)] =
        true;

    flags[to_int(Move::FocusEnergy)][to_int(
        MoveFlag::BOOSTS_ATTACKERS_CRIT_RATE)] = true;

    flags[to_int(Move::Ancientpower)][to_int(MoveFlag::OMNI_BOOSTS_ATTACKER)] =
        true;
    flags[to_int(Move::SilverWind)][to_int(MoveFlag::OMNI_BOOSTS_ATTACKER)] =
        true;
    flags[to_int(Move::OminousWind)][to_int(MoveFlag::OMNI_BOOSTS_ATTACKER)] =
        true;

    flags[to_int(Move::Swagger)][to_int(MoveFlag::RAISES_DEFENDER_ATTACK)] =
        true;

    flags[to_int(Move::Growl)][to_int(MoveFlag::LOWERS_DEFENDER_ATTACK)] = true;
    flags[to_int(Move::AuroraBeam)][to_int(MoveFlag::LOWERS_DEFENDER_ATTACK)] =
        true;
    flags[to_int(Move::Charm)][to_int(MoveFlag::LOWERS_DEFENDER_ATTACK)] = true;
    flags[to_int(Move::Memento)][to_int(MoveFlag::LOWERS_DEFENDER_ATTACK)] =
        true;
    flags[to_int(Move::Featherdance)][to_int(MoveFlag::LOWERS_DEFENDER_ATTACK)]
        = true;
    flags[to_int(Move::Tickle)][to_int(MoveFlag::LOWERS_DEFENDER_ATTACK)] =
        true;

    flags[to_int(Move::Flatter)][to_int(
        MoveFlag::RAISES_DEFENDER_SPECIAL_ATTACK)] = true;

    flags[to_int(Move::Memento)][to_int(
        MoveFlag::LOWERS_DEFENDER_SPECIAL_ATTACK)] = true;
    flags[to_int(Move::MistBall)][to_int(
        MoveFlag::LOWERS_DEFENDER_SPECIAL_ATTACK_ONE_STAGE_50)] = true;

    flags[to_int(Move::TailWhip)][to_int(MoveFlag::LOWERS_DEFENDER_DEFENSE)] =
        true;
    flags[to_int(Move::Leer)][to_int(MoveFlag::LOWERS_DEFENDER_DEFENSE)] = true;
    flags[to_int(Move::Screech)][to_int(MoveFlag::LOWERS_DEFENDER_DEFENSE)] =
        true;
    flags[to_int(Move::IronTail)][to_int(MoveFlag::LOWERS_DEFENDER_DEFENSE)] =
        true;
    flags[to_int(Move::Crunch)][to_int(MoveFlag::LOWERS_DEFENDER_DEFENSE)] =
        true;
    flags[to_int(Move::RockSmash)][to_int(MoveFlag::LOWERS_DEFENDER_DEFENSE)] =
        true;
    flags[to_int(Move::CrushClaw)][to_int(MoveFlag::LOWERS_DEFENDER_DEFENSE)] =
        true;
    flags[to_int(Move::Tickle)][to_int(MoveFlag::LOWERS_DEFENDER_DEFENSE)] =
        true;

    flags[to_int(Move::Acid)][to_int(MoveFlag::LOWERS_DEFENDER_SPECIAL_DEFENSE)]
        = true;
    flags[to_int(Move::Psychic)][to_int(
        MoveFlag::LOWERS_DEFENDER_SPECIAL_DEFENSE_ONE_STAGE_10)] = true;
    flags[to_int(Move::ShadowBall)][to_int(
        MoveFlag::LOWERS_DEFENDER_SPECIAL_DEFENSE)] = true;
    flags[to_int(Move::LusterPurge)][to_int(
        MoveFlag::LOWERS_DEFENDER_SPECIAL_DEFENSE)] = true;
    flags[to_int(Move::FakeTears)][to_int(
        MoveFlag::LOWERS_DEFENDER_SPECIAL_DEFENSE)] = true;
    flags[to_int(Move::MetalSound)][to_int(
        MoveFlag::LOWERS_DEFENDER_SPECIAL_DEFENSE)] = true;
    flags[to_int(Move::BugBuzz)][to_int(
        MoveFlag::LOWERS_DEFENDER_SPECIAL_DEFENSE)] = true;
    flags[to_int(Move::FocusBlast)][to_int(
        MoveFlag::LOWERS_DEFENDER_SPECIAL_DEFENSE)] = true;
    flags[to_int(Move::EnergyBall)][to_int(
        MoveFlag::LOWERS_DEFENDER_SPECIAL_DEFENSE)] = true;
    flags[to_int(Move::EarthPower)][to_int(
        MoveFlag::LOWERS_DEFENDER_SPECIAL_DEFENSE)] = true;
    flags[to_int(Move::FlashCannon)][to_int(
        MoveFlag::LOWERS_DEFENDER_SPECIAL_DEFENSE)] = true;
    flags[to_int(Move::SeedFlare)][to_int(
        MoveFlag::LOWERS_DEFENDER_SPECIAL_DEFENSE)] = true;

    flags[to_int(Move::Bubblebeam)][to_int(MoveFlag::LOWERS_DEFENDER_SPEED)] =
        true;
    flags[to_int(Move::StringShot)][to_int(MoveFlag::LOWERS_DEFENDER_SPEED)] =
        true;
    flags[to_int(Move::Constrict)][to_int(MoveFlag::LOWERS_DEFENDER_SPEED)] =
        true;
    flags[to_int(Move::Bubble)][to_int(MoveFlag::LOWERS_DEFENDER_SPEED)] = true;
    flags[to_int(Move::CottonSpore)][to_int(MoveFlag::LOWERS_DEFENDER_SPEED)] =
        true;
    flags[to_int(Move::ScaryFace)][to_int(MoveFlag::LOWERS_DEFENDER_SPEED)] =
        true;
    flags[to_int(Move::IcyWind)][to_int(MoveFlag::LOWERS_DEFENDER_SPEED)] =
        true;
    flags[to_int(Move::RockTomb)][to_int(MoveFlag::LOWERS_DEFENDER_SPEED)] =
        true;
    flags[to_int(Move::MudShot)][to_int(MoveFlag::LOWERS_DEFENDER_SPEED)] =
        true;

    flags[to_int(Move::SandAttack)][to_int(MoveFlag::LOWERS_DEFENDER_ACCURACY)]
        = true;
    flags[to_int(Move::Smokescreen)][to_int(MoveFlag::LOWERS_DEFENDER_ACCURACY)]
        = true;
    flags[to_int(Move::Kinesis)][to_int(MoveFlag::LOWERS_DEFENDER_ACCURACY)] =
        true;
    flags[to_int(Move::Flash)][to_int(MoveFlag::LOWERS_DEFENDER_ACCURACY)] =
        true;
    flags[to_int(Move::MudSlap)][to_int(MoveFlag::LOWERS_DEFENDER_ACCURACY)] =
        true;
    flags[to_int(Move::Octazooka)][to_int(MoveFlag::LOWERS_DEFENDER_ACCURACY)] =
        true;
    flags[to_int(Move::MuddyWater)][to_int(MoveFlag::LOWERS_DEFENDER_ACCURACY)]
        = true;
    flags[to_int(Move::MudBomb)][to_int(MoveFlag::LOWERS_DEFENDER_ACCURACY)] =
        true;
    flags[to_int(Move::MirrorShot)][to_int(MoveFlag::LOWERS_DEFENDER_ACCURACY)]
        = true;

    flags[to_int(Move::SweetScent)][to_int(MoveFlag::LOWERS_DEFENDER_EVASION)] =
        true;

    flags[to_int(Move::Blizzard)][to_int(MoveFlag::BYPASSES_ACCURACY)] = true;
    flags[to_int(Move::Thunder)][to_int(MoveFlag::BYPASSES_ACCURACY)] = true;
    flags[to_int(Move::Swift)][to_int(MoveFlag::BYPASSES_ACCURACY)] = true;
    flags[to_int(Move::FaintAttack)][to_int(MoveFlag::BYPASSES_ACCURACY)] =
        true;
    flags[to_int(Move::VitalThrow)][to_int(MoveFlag::BYPASSES_ACCURACY)] = true;
    flags[to_int(Move::ShadowPunch)][to_int(MoveFlag::BYPASSES_ACCURACY)] =
        true;
    flags[to_int(Move::AerialAce)][to_int(MoveFlag::BYPASSES_ACCURACY)] = true;
    flags[to_int(Move::MagicalLeaf)][to_int(MoveFlag::BYPASSES_ACCURACY)] =
        true;
    flags[to_int(Move::ShockWave)][to_int(MoveFlag::BYPASSES_ACCURACY)] = true;
    flags[to_int(Move::AuraSphere)][to_int(MoveFlag::BYPASSES_ACCURACY)] = true;
    flags[to_int(Move::MagnetBomb)][to_int(MoveFlag::BYPASSES_ACCURACY)] = true;

    flags[to_int(Move::Bounce)][to_int(MoveFlag::CANT_BE_USED_DURING_GRAVITY)] =
        true;
    flags[to_int(Move::Fly)][to_int(MoveFlag::CANT_BE_USED_DURING_GRAVITY)] =
        true;
    flags[to_int(Move::HighJumpKick)][to_int(
        MoveFlag::CANT_BE_USED_DURING_GRAVITY)] = true;
    flags[to_int(Move::JumpKick)][to_int(MoveFlag::CANT_BE_USED_DURING_GRAVITY)]
        = true;
    flags[to_int(Move::MagnetRise)][to_int(
        MoveFlag::CANT_BE_USED_DURING_GRAVITY)] = true;
    flags[to_int(Move::Splash)][to_int(MoveFlag::CANT_BE_USED_DURING_GRAVITY)] =
        true;

    flags[to_int(Move::Detect)][to_int(MoveFlag::PROTECTS_USER)] = true;
    flags[to_int(Move::Protect)][to_int(MoveFlag::PROTECTS_USER)] = true;

    flags[to_int(Move::Disable)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Mist)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::LowKick)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Counter)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::LeechSeed)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Rage)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Teleport)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Mimic)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::DefenseCurl)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Barrier)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::LightScreen)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Haze)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Reflect)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Bide)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Metronome)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::MirrorMove)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::DreamEater)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Transform)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Psywave)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Splash)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Rest)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Conversion)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::TriAttack)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::SuperFang)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Substitute)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Struggle)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Sketch)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::TripleKick)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Thief)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::SpiderWeb)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::MindReader)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Nightmare)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Snore)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Curse)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Flail)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Conversion2)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Reversal)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Spite)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Spikes)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Foresight)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::DestinyBond)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::PerishSong)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::LockOn)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Rollout)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::FalseSwipe)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::FuryCutter)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::MeanLook)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Attract)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::SleepTalk)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::HealBell)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Present)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Safeguard)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::PainSplit)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Magnitude)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::BatonPass)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Encore)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Pursuit)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::RapidSpin)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::HiddenPower)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::MirrorCoat)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::PsychUp)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::FutureSight)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::BeatUp)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::FakeOut)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Uproar)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Stockpile)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::SpitUp)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Swallow)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Torment)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Facade)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::FocusPunch)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Smellingsalt)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::FollowMe)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::NaturePower)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Charge)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Taunt)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::HelpingHand)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Trick)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::RolePlay)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Wish)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Assist)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Ingrain)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::MagicCoat)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Recycle)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Revenge)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::BrickBreak)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Yawn)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::KnockOff)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Endeavor)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Eruption)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::SkillSwap)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Imprison)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Refresh)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Grudge)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Snatch)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::SecretPower)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Camouflage)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::MudSport)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::IceBall)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::WeatherBall)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Aromatherapy)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::OdorSleuth)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::WaterSpout)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Block)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Covet)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::WaterSport)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::DoomDesire)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Roost)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Gravity)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::MiracleEye)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::WakeUpSlap)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::GyroBall)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::HealingWish)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Brine)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::NaturalGift)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Feint)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Pluck)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Tailwind)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Acupressure)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::MetalBurst)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::UTurn)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Payback)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Assurance)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Embargo)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Fling)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::PsychoShift)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::TrumpCard)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::HealBlock)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::WringOut)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::PowerTrick)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::GastroAcid)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::LuckyChant)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::MeFirst)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Copycat)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::PowerSwap)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::GuardSwap)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Punishment)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::LastResort)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::WorrySeed)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::SuckerPunch)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::ToxicSpikes)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::HeartSwap)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::AquaRing)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::MagnetRise)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Switcheroo)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Avalanche)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Defog)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::TrickRoom)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Captivate)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::StealthRock)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::GrassKnot)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Chatter)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::Judgment)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::BugBite)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::LunarDance)][to_int(MoveFlag::IS_OTHER)] = true;
    flags[to_int(Move::CrushGrip)][to_int(MoveFlag::IS_OTHER)] = true;

    flags[to_int(Move::Sandstorm)][to_int(MoveFlag::CHANGES_WEATHER)] = true;
    flags[to_int(Move::RainDance)][to_int(MoveFlag::CHANGES_WEATHER)] = true;
    flags[to_int(Move::SunnyDay)][to_int(MoveFlag::CHANGES_WEATHER)] = true;
    flags[to_int(Move::Hail)][to_int(MoveFlag::CHANGES_WEATHER)] = true;

    flags[to_int(Move::Whirlwind)][to_int(MoveFlag::FORCES_USER_OUT)] = true;
    flags[to_int(Move::Roar)][to_int(MoveFlag::FORCES_USER_OUT)] = true;

    flags[to_int(Move::Guillotine)][to_int(MoveFlag::KOS_IN_ONE_HIT)] = true;
    flags[to_int(Move::HornDrill)][to_int(MoveFlag::KOS_IN_ONE_HIT)] = true;
    flags[to_int(Move::Fissure)][to_int(MoveFlag::KOS_IN_ONE_HIT)] = true;
    flags[to_int(Move::SheerCold)][to_int(MoveFlag::KOS_IN_ONE_HIT)] = true;

    flags[to_int(Move::Selfdestruct)][to_int(MoveFlag::MAKES_ATTACKER_FAINT)] =
        true;
    flags[to_int(Move::Explosion)][to_int(MoveFlag::MAKES_ATTACKER_FAINT)] =
        true;
    flags[to_int(Move::Memento)][to_int(MoveFlag::MAKES_ATTACKER_FAINT)] = true;

    flags[to_int(Move::KarateChop)][to_int(MoveFlag::HAS_INCREASED_CRIT_CHANCE)]
        = true;
    flags[to_int(Move::RazorWind)][to_int(MoveFlag::HAS_INCREASED_CRIT_CHANCE)]
        = true;
    flags[to_int(Move::RazorLeaf)][to_int(MoveFlag::HAS_INCREASED_CRIT_CHANCE)]
        = true;
    flags[to_int(Move::SkyAttack)][to_int(MoveFlag::HAS_INCREASED_CRIT_CHANCE)]
        = true;
    flags[to_int(Move::Crabhammer)][to_int(MoveFlag::HAS_INCREASED_CRIT_CHANCE)]
        = true;
    flags[to_int(Move::Slash)][to_int(MoveFlag::HAS_INCREASED_CRIT_CHANCE)] =
        true;
    flags[to_int(Move::Aeroblast)][to_int(MoveFlag::HAS_INCREASED_CRIT_CHANCE)]
        = true;
    flags[to_int(Move::CrossChop)][to_int(MoveFlag::HAS_INCREASED_CRIT_CHANCE)]
        = true;
    flags[to_int(Move::BlazeKick)][to_int(MoveFlag::HAS_INCREASED_CRIT_CHANCE)]
        = true;
    flags[to_int(Move::AirCutter)][to_int(MoveFlag::HAS_INCREASED_CRIT_CHANCE)]
        = true;
    flags[to_int(Move::PoisonTail)][to_int(MoveFlag::HAS_INCREASED_CRIT_CHANCE)]
        = true;
    flags[to_int(Move::LeafBlade)][to_int(MoveFlag::HAS_INCREASED_CRIT_CHANCE)]
        = true;
    flags[to_int(Move::NightSlash)][to_int(MoveFlag::HAS_INCREASED_CRIT_CHANCE)]
        = true;
    flags[to_int(Move::ShadowClaw)][to_int(MoveFlag::HAS_INCREASED_CRIT_CHANCE)]
        = true;
    flags[to_int(Move::PsychoCut)][to_int(MoveFlag::HAS_INCREASED_CRIT_CHANCE)]
        = true;
    flags[to_int(Move::CrossPoison)][
        to_int(MoveFlag::HAS_INCREASED_CRIT_CHANCE)] = true;
    flags[to_int(Move::StoneEdge)][to_int(MoveFlag::HAS_INCREASED_CRIT_CHANCE)]
        = true;
    flags[to_int(Move::AttackOrder)][
        to_int(MoveFlag::HAS_INCREASED_CRIT_CHANCE)] = true;
    flags[to_int(Move::SpacialRend)][
        to_int(MoveFlag::HAS_INCREASED_CRIT_CHANCE)] = true;

    flags[to_int(Move::RazorWind)][to_int(MoveFlag::REQUIRES_CHARGING_TURN)] =
        true;
    flags[to_int(Move::SolarBeam)][to_int(MoveFlag::REQUIRES_CHARGING_TURN)] =
        true;
    flags[to_int(Move::SkullBash)][to_int(MoveFlag::REQUIRES_CHARGING_TURN)] =
        true;
    flags[to_int(Move::SkyAttack)][to_int(MoveFlag::REQUIRES_CHARGING_TURN)] =
        true;

    flags[to_int(Move::HyperBeam)][to_int(MoveFlag::REQUIRES_RECHARGE_TURN)] =
        true;
    flags[to_int(Move::BlastBurn)][to_int(MoveFlag::REQUIRES_RECHARGE_TURN)] =
        true;
    flags[to_int(Move::HydroCannon)][to_int(MoveFlag::REQUIRES_RECHARGE_TURN)] =
        true;
    flags[to_int(Move::FrenzyPlant)][to_int(MoveFlag::REQUIRES_RECHARGE_TURN)] =
        true;
    flags[to_int(Move::GigaImpact)][to_int(MoveFlag::REQUIRES_RECHARGE_TURN)] =
        true;
    flags[to_int(Move::RockWrecker)][to_int(MoveFlag::REQUIRES_RECHARGE_TURN)] =
        true;
    flags[to_int(Move::RoarOfTime)][to_int(MoveFlag::REQUIRES_RECHARGE_TURN)] =
        true;

    flags[to_int(Move::Stomp)][to_int(MoveFlag::DEALS_DOUBLE_AFTER_MINIMIZE)] =
        true;

    flags[to_int(Move::Bind)][to_int(MoveFlag::CONTINUES)] = true;
    flags[to_int(Move::Wrap)][to_int(MoveFlag::CONTINUES)] = true;
    flags[to_int(Move::FireSpin)][to_int(MoveFlag::CONTINUES)] = true;
    flags[to_int(Move::Clamp)][to_int(MoveFlag::CONTINUES)] = true;
    flags[to_int(Move::Whirlpool)][to_int(MoveFlag::CONTINUES)] = true;
    flags[to_int(Move::SandTomb)][to_int(MoveFlag::CONTINUES)] = true;
    flags[to_int(Move::MagmaStorm)][to_int(MoveFlag::CONTINUES)] = true;

    flags[to_int(Move::FirePunch)][to_int(MoveFlag::BURNS_DEFENDER)] = true;
    flags[to_int(Move::Ember)][to_int(MoveFlag::BURNS_DEFENDER)] = true;
    flags[to_int(Move::Flamethrower)][to_int(MoveFlag::BURNS_DEFENDER)] = true;
    flags[to_int(Move::FireBlast)][to_int(MoveFlag::BURNS_DEFENDER)] = true;
    flags[to_int(Move::FlameWheel)][to_int(MoveFlag::BURNS_DEFENDER)] = true;
    flags[to_int(Move::SacredFire)][to_int(MoveFlag::BURNS_DEFENDER)] = true;
    flags[to_int(Move::HeatWave)][to_int(MoveFlag::BURNS_DEFENDER)] = true;
    flags[to_int(Move::WillOWisp)][to_int(MoveFlag::BURNS_DEFENDER)] = true;
    flags[to_int(Move::BlazeKick)][to_int(MoveFlag::BURNS_DEFENDER)] = true;
    flags[to_int(Move::FlareBlitz)][to_int(MoveFlag::BURNS_DEFENDER)] = true;
    flags[to_int(Move::FireFang)][to_int(MoveFlag::BURNS_DEFENDER)] = true;
    flags[to_int(Move::LavaPlume)][to_int(MoveFlag::BURNS_DEFENDER)] = true;

    flags[to_int(Move::IcePunch)][to_int(MoveFlag::FREEZES_DEFENDER)] = true;
    flags[to_int(Move::IceBeam)][to_int(MoveFlag::FREEZES_DEFENDER_10)] = true;
    flags[to_int(Move::Blizzard)][to_int(MoveFlag::FREEZES_DEFENDER)] = true;
    flags[to_int(Move::PowderSnow)][to_int(MoveFlag::FREEZES_DEFENDER)] = true;
    flags[to_int(Move::IceFang)][to_int(MoveFlag::FREEZES_DEFENDER)] = true;

    flags[to_int(Move::ThunderPunch)][to_int(MoveFlag::PARALYZES_DEFENDER)] =
        true;
    flags[to_int(Move::BodySlam)][to_int(MoveFlag::PARALYZES_DEFENDER)] = true;
    flags[to_int(Move::StunSpore)][to_int(MoveFlag::PARALYZES_DEFENDER)] = true;
    flags[to_int(Move::Thundershock)][to_int(MoveFlag::PARALYZES_DEFENDER)] =
        true;
    flags[to_int(Move::Thunderbolt)][to_int(MoveFlag::PARALYZES_DEFENDER_10)] =
        true;
    flags[to_int(Move::ThunderWave)][to_int(MoveFlag::PARALYZES_DEFENDER)] =
        true;
    flags[to_int(Move::Thunder)][to_int(MoveFlag::PARALYZES_DEFENDER)] = true;
    flags[to_int(Move::Lick)][to_int(MoveFlag::PARALYZES_DEFENDER)] = true;
    flags[to_int(Move::Glare)][to_int(MoveFlag::PARALYZES_DEFENDER)] = true;
    flags[to_int(Move::ZapCannon)][to_int(MoveFlag::PARALYZES_DEFENDER)] = true;
    flags[to_int(Move::Spark)][to_int(MoveFlag::PARALYZES_DEFENDER)] = true;
    flags[to_int(Move::DragonBreath)][to_int(MoveFlag::PARALYZES_DEFENDER)] =
        true;
    flags[to_int(Move::Bounce)][to_int(MoveFlag::PARALYZES_DEFENDER)] = true;
    flags[to_int(Move::VoltTackle)][to_int(MoveFlag::PARALYZES_DEFENDER)] =
        true;
    flags[to_int(Move::ForcePalm)][to_int(MoveFlag::PARALYZES_DEFENDER)] = true;
    flags[to_int(Move::ThunderFang)][to_int(MoveFlag::PARALYZES_DEFENDER)] =
        true;
    flags[to_int(Move::Discharge)][to_int(MoveFlag::PARALYZES_DEFENDER)] = true;

    flags[to_int(Move::PoisonSting)][to_int(MoveFlag::POISONS_DEFENDER)] = true;
    flags[to_int(Move::Twineedle)][to_int(MoveFlag::POISONS_DEFENDER)] = true;
    flags[to_int(Move::PoisonPowder)][to_int(MoveFlag::POISONS_DEFENDER)] =
        true;
    flags[to_int(Move::Smog)][to_int(MoveFlag::POISONS_DEFENDER)] = true;
    flags[to_int(Move::Sludge)][to_int(MoveFlag::POISONS_DEFENDER)] = true;
    flags[to_int(Move::PoisonGas)][to_int(MoveFlag::POISONS_DEFENDER)] = true;
    flags[to_int(Move::SludgeBomb)][to_int(MoveFlag::POISONS_DEFENDER)] = true;
    flags[to_int(Move::PoisonTail)][to_int(MoveFlag::POISONS_DEFENDER)] = true;
    flags[to_int(Move::PoisonJab)][to_int(MoveFlag::POISONS_DEFENDER)] = true;
    flags[to_int(Move::CrossPoison)][to_int(MoveFlag::POISONS_DEFENDER)] = true;
    flags[to_int(Move::GunkShot)][to_int(MoveFlag::POISONS_DEFENDER)] = true;

    flags[to_int(Move::Toxic)][to_int(MoveFlag::BADLY_POISONS)] = true;
    flags[to_int(Move::PoisonFang)][to_int(MoveFlag::BADLY_POISONS)] = true;

    flags[to_int(Move::Sing)][to_int(MoveFlag::MAKES_DEFENDER_SLEEP)] = true;
    flags[to_int(Move::SleepPowder)][to_int(MoveFlag::MAKES_DEFENDER_SLEEP)] =
        true;
    flags[to_int(Move::Hypnosis)][to_int(MoveFlag::MAKES_DEFENDER_SLEEP)] =
        true;
    flags[to_int(Move::LovelyKiss)][to_int(MoveFlag::MAKES_DEFENDER_SLEEP)] =
        true;
    flags[to_int(Move::Spore)][to_int(MoveFlag::MAKES_DEFENDER_SLEEP)] = true;
    flags[to_int(Move::Grasswhistle)][to_int(MoveFlag::MAKES_DEFENDER_SLEEP)] =
        true;
    flags[to_int(Move::DarkVoid)][to_int(MoveFlag::MAKES_DEFENDER_SLEEP)] =
        true;

    flags[to_int(Move::Supersonic)][to_int(MoveFlag::CONFUSES_DEFENDER)] = true;
    flags[to_int(Move::Psybeam)][to_int(MoveFlag::CONFUSES_DEFENDER)] = true;
    flags[to_int(Move::Confusion)][to_int(MoveFlag::CONFUSES_DEFENDER)] = true;
    flags[to_int(Move::ConfuseRay)][to_int(MoveFlag::CONFUSES_DEFENDER)] = true;
    flags[to_int(Move::DizzyPunch)][to_int(MoveFlag::CONFUSES_DEFENDER)] = true;
    flags[to_int(Move::SweetKiss)][to_int(MoveFlag::CONFUSES_DEFENDER)] = true;
    flags[to_int(Move::Swagger)][to_int(MoveFlag::CONFUSES_DEFENDER)] = true;
    flags[to_int(Move::Dynamicpunch)][to_int(MoveFlag::CONFUSES_DEFENDER)] =
        true;
    flags[to_int(Move::Flatter)][to_int(MoveFlag::CONFUSES_DEFENDER)] = true;
    flags[to_int(Move::TeeterDance)][to_int(MoveFlag::CONFUSES_DEFENDER)] =
        true;
    flags[to_int(Move::SignalBeam)][to_int(MoveFlag::CONFUSES_DEFENDER_10)] =
        true;
    flags[to_int(Move::WaterPulse)][to_int(MoveFlag::CONFUSES_DEFENDER)] = true;
    flags[to_int(Move::RockClimb)][to_int(MoveFlag::CONFUSES_DEFENDER)] = true;

    flags[to_int(Move::Stomp)][to_int(MoveFlag::FLINCHES_DEFENDER)] = true;
    flags[to_int(Move::RollingKick)][to_int(MoveFlag::FLINCHES_DEFENDER)] =
        true;
    flags[to_int(Move::Headbutt)][to_int(MoveFlag::FLINCHES_DEFENDER)] = true;
    flags[to_int(Move::Bite)][to_int(MoveFlag::FLINCHES_DEFENDER)] = true;
    flags[to_int(Move::BoneClub)][to_int(MoveFlag::FLINCHES_DEFENDER)] = true;
    flags[to_int(Move::Waterfall)][to_int(MoveFlag::FLINCHES_DEFENDER)] = true;
    flags[to_int(Move::SkyAttack)][to_int(MoveFlag::FLINCHES_DEFENDER)] = true;
    flags[to_int(Move::HyperFang)][to_int(MoveFlag::FLINCHES_DEFENDER)] = true;
    flags[to_int(Move::Twister)][to_int(MoveFlag::FLINCHES_DEFENDER)] = true;
    flags[to_int(Move::NeedleArm)][to_int(MoveFlag::FLINCHES_DEFENDER)] = true;
    flags[to_int(Move::Astonish)][to_int(MoveFlag::FLINCHES_DEFENDER)] = true;
    flags[to_int(Move::Extrasensory)][to_int(MoveFlag::FLINCHES_DEFENDER)] =
        true;
    flags[to_int(Move::DarkPulse)][to_int(MoveFlag::FLINCHES_DEFENDER)] = true;
    flags[to_int(Move::AirSlash)][to_int(MoveFlag::FLINCHES_DEFENDER)] = true;
    flags[to_int(Move::DragonRush)][to_int(MoveFlag::FLINCHES_DEFENDER)] = true;
    flags[to_int(Move::ThunderFang)][to_int(MoveFlag::FLINCHES_DEFENDER)] =
        true;
    flags[to_int(Move::IceFang)][to_int(MoveFlag::FLINCHES_DEFENDER)] = true;
    flags[to_int(Move::FireFang)][to_int(MoveFlag::FLINCHES_DEFENDER)] = true;
    flags[to_int(Move::ZenHeadbutt)][to_int(MoveFlag::FLINCHES_DEFENDER)] =
        true;
    flags[to_int(Move::IronHead)][to_int(MoveFlag::FLINCHES_DEFENDER)] = true;

    flags[to_int(Move::JumpKick)][to_int(MoveFlag::HAS_RECOIL)] = true;
    flags[to_int(Move::TakeDown)][to_int(MoveFlag::HAS_RECOIL)] = true;
    flags[to_int(Move::DoubleEdge)][to_int(MoveFlag::HAS_RECOIL)] = true;
    flags[to_int(Move::Submission)][to_int(MoveFlag::HAS_RECOIL)] = true;
    flags[to_int(Move::HighJumpKick)][to_int(MoveFlag::HAS_RECOIL)] = true;
    flags[to_int(Move::BellyDrum)][to_int(MoveFlag::HAS_RECOIL)] = true;
    flags[to_int(Move::VoltTackle)][to_int(MoveFlag::HAS_RECOIL)] = true;
    flags[to_int(Move::FlareBlitz)][to_int(MoveFlag::HAS_RECOIL)] = true;
    flags[to_int(Move::BraveBird)][to_int(MoveFlag::HAS_RECOIL)] = true;
    flags[to_int(Move::WoodHammer)][to_int(MoveFlag::HAS_RECOIL)] = true;
    flags[to_int(Move::HeadSmash)][to_int(MoveFlag::HAS_RECOIL)] = true;

    flags[to_int(Move::DoubleSlap)][to_int(MoveFlag::HITS_MULTIPLE_TIMES)] =
        true;
    flags[to_int(Move::CometPunch)][to_int(MoveFlag::HITS_MULTIPLE_TIMES)] =
        true;
    flags[to_int(Move::DoubleKick)][to_int(MoveFlag::HITS_MULTIPLE_TIMES)] =
        true;
    flags[to_int(Move::FuryAttack)][to_int(MoveFlag::HITS_MULTIPLE_TIMES)] =
        true;
    flags[to_int(Move::Twineedle)][to_int(MoveFlag::HITS_MULTIPLE_TIMES)] =
        true;
    flags[to_int(Move::PinMissile)][to_int(MoveFlag::HITS_MULTIPLE_TIMES)] =
        true;
    flags[to_int(Move::SpikeCannon)][to_int(MoveFlag::HITS_MULTIPLE_TIMES)] =
        true;
    flags[to_int(Move::Barrage)][to_int(MoveFlag::HITS_MULTIPLE_TIMES)] = true;
    flags[to_int(Move::FuryAttack)][to_int(MoveFlag::HITS_MULTIPLE_TIMES)] =
        true;
    flags[to_int(Move::Bonemerang)][to_int(MoveFlag::HITS_MULTIPLE_TIMES)] =
        true;
    flags[to_int(Move::BoneRush)][to_int(MoveFlag::HITS_MULTIPLE_TIMES)] = true;
    flags[to_int(Move::ArmThrust)][to_int(MoveFlag::HITS_MULTIPLE_TIMES)] =
        true;
    flags[to_int(Move::BulletSeed)][to_int(MoveFlag::HITS_MULTIPLE_TIMES)] =
        true;
    flags[to_int(Move::IcicleSpear)][to_int(MoveFlag::HITS_MULTIPLE_TIMES)] =
        true;
    flags[to_int(Move::RockBlast)][to_int(MoveFlag::HITS_MULTIPLE_TIMES)] =
        true;
    flags[to_int(Move::DoubleHit)][to_int(MoveFlag::HITS_MULTIPLE_TIMES)] =
        true;

    flags[to_int(Move::Thrash)][to_int(MoveFlag::LASTS_MULTIPLE_TURNS)] = true;
    flags[to_int(Move::PetalDance)][to_int(MoveFlag::LASTS_MULTIPLE_TURNS)] =
        true;
    flags[to_int(Move::Outrage)][to_int(MoveFlag::LASTS_MULTIPLE_TURNS)] = true;

    flags[to_int(Move::SonicBoom)][to_int(MoveFlag::HAS_FIXED_DAMAGE)] = true;
    flags[to_int(Move::SeismicToss)][to_int(MoveFlag::HAS_FIXED_DAMAGE)] = true;
    flags[to_int(Move::DragonRage)][to_int(MoveFlag::HAS_FIXED_DAMAGE)] = true;
    flags[to_int(Move::NightShade)][to_int(MoveFlag::HAS_FIXED_DAMAGE)] = true;

    flags[to_int(Move::Bounce)][to_int(MoveFlag::GOES_INTO_AIR)] = true;
    flags[to_int(Move::Fly)][to_int(MoveFlag::GOES_INTO_AIR)] = true;

    flags[to_int(Move::Gust)][to_int(MoveFlag::HITS_DEFENDER_IN_AIR)] = true;
    flags[to_int(Move::SkyUppercut)][to_int(MoveFlag::HITS_DEFENDER_IN_AIR)] =
        true;
    flags[to_int(Move::Thunder)][to_int(MoveFlag::HITS_DEFENDER_IN_AIR)] = true;
    flags[to_int(Move::Twister)][to_int(MoveFlag::HITS_DEFENDER_IN_AIR)] = true;

    flags[to_int(Move::Dig)][to_int(MoveFlag::GOES_UNDER_GROUND)] = true;

    flags[to_int(Move::Earthquake)][
        to_int(MoveFlag::HITS_DEFENDER_UNDER_GROUND)] = true;
    flags[to_int(Move::Magnitude)][to_int(MoveFlag::HITS_DEFENDER_UNDER_GROUND)]
        = true;
    flags[to_int(Move::Fissure)][to_int(MoveFlag::HITS_DEFENDER_UNDER_GROUND)] =
        true;

    flags[to_int(Move::Dive)][to_int(MoveFlag::GOES_UNDER_WATER)] = true;

    flags[to_int(Move::Surf)][to_int(MoveFlag::HITS_DEFENDER_UNDER_WATER)] =
        true;
    flags[to_int(Move::Whirlpool)][to_int(MoveFlag::HITS_DEFENDER_UNDER_WATER)]
        = true;

    flags[to_int(Move::ShadowForce)][to_int(MoveFlag::GOES_INTO_VOID)] = true;

    flags[to_int(Move::Pound)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::KarateChop)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::DoubleSlap)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::CometPunch)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::MegaPunch)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::FirePunch)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::IcePunch)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::ThunderPunch)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::Scratch)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::ViceGrip)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::Guillotine)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::Cut)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::WingAttack)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::Fly)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::Bind)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::Slam)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::VineWhip)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::Stomp)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::DoubleKick)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::MegaKick)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::JumpKick)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::RollingKick)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::Headbutt)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::HornAttack)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::FuryAttack)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::HornDrill)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::Tackle)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::BodySlam)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::Wrap)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::TakeDown)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::Thrash)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::DoubleEdge)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::Bite)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::Peck)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::DrillPeck)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::Submission)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::LowKick)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::Counter)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::SeismicToss)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::Strength)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::PetalDance)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::Dig)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::QuickAttack)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::Rage)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::Bide)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::Lick)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::Waterfall)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::Clamp)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::SkullBash)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::Constrict)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::HighJumpKick)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::LeechLife)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::DizzyPunch)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::Crabhammer)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::FurySwipes)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::HyperFang)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::SuperFang)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::Slash)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::Struggle)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::TripleKick)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::Thief)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::FlameWheel)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::Flail)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::Reversal)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::MachPunch)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::FaintAttack)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::Outrage)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::Rollout)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::FalseSwipe)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::Spark)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::FuryCutter)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::SteelWing)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::Return)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::Frustration)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::Dynamicpunch)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::Megahorn)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::Pursuit)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::RapidSpin)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::IronTail)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::MetalClaw)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::VitalThrow)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::CrossChop)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::Crunch)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::ExtremeSpeed)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::RockSmash)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::FakeOut)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::Facade)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::FocusPunch)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::Smellingsalt)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::Superpower)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::Revenge)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::BrickBreak)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::KnockOff)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::Endeavor)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::Dive)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::ArmThrust)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::BlazeKick)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::IceBall)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::NeedleArm)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::PoisonFang)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::CrushClaw)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::MeteorMash)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::Astonish)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::ShadowPunch)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::SkyUppercut)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::AerialAce)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::DragonClaw)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::Bounce)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::PoisonTail)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::Covet)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::VoltTackle)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::LeafBlade)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::WakeUpSlap)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::HammerArm)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::GyroBall)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::Pluck)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::UTurn)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::CloseCombat)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::Payback)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::Assurance)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::Punishment)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::LastResort)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::SuckerPunch)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::FlareBlitz)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::ForcePalm)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::PoisonJab)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::NightSlash)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::AquaTail)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::XScissor)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::DragonRush)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::DrainPunch)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::BraveBird)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::GigaImpact)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::BulletPunch)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::Avalanche)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::ShadowClaw)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::ThunderFang)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::IceFang)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::FireFang)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::ShadowSneak)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::ZenHeadbutt)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::RockClimb)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::PowerWhip)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::CrossPoison)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::IronHead)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::BugBite)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::WoodHammer)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::AquaJet)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::HeadSmash)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::DoubleHit)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::CrushGrip)][to_int(MoveFlag::MAKES_CONTACT)] = true;
    flags[to_int(Move::ShadowForce)][to_int(MoveFlag::MAKES_CONTACT)] = true;

    flags[to_int(Move::Acupressure)][to_int(MoveFlag::BYPASSES_PROTECT)] = true;
    flags[to_int(Move::Curse)][to_int(MoveFlag::BYPASSES_PROTECT)] = true;
    flags[to_int(Move::DoomDesire)][to_int(MoveFlag::BYPASSES_PROTECT)] = true;
    flags[to_int(Move::Feint)][to_int(MoveFlag::BYPASSES_PROTECT)] = true;
    flags[to_int(Move::FutureSight)][to_int(MoveFlag::BYPASSES_PROTECT)] = true;
    flags[to_int(Move::PerishSong)][to_int(MoveFlag::BYPASSES_PROTECT)] = true;
    flags[to_int(Move::PsychUp)][to_int(MoveFlag::BYPASSES_PROTECT)] = true;
    flags[to_int(Move::RolePlay)][to_int(MoveFlag::BYPASSES_PROTECT)] = true;
    flags[to_int(Move::ShadowForce)][to_int(MoveFlag::BYPASSES_PROTECT)] = true;
    flags[to_int(Move::Sketch)][to_int(MoveFlag::BYPASSES_PROTECT)] = true;
    flags[to_int(Move::Transform)][to_int(MoveFlag::BYPASSES_PROTECT)] = true;

    flags[to_int(Move::Feint)][to_int(MoveFlag::BREAKS_PROTECT)] = true;
    flags[to_int(Move::ShadowForce)][to_int(MoveFlag::BREAKS_PROTECT)] = true;

    flags[to_int(Move::Attract)][to_int(
        MoveFlag::CAN_BE_REFLECTED_BY_MIRROR_MOVE)] = true;
    flags[to_int(Move::Block)][
        to_int(MoveFlag::CAN_BE_REFLECTED_BY_MIRROR_MOVE)] = true;
    flags[to_int(Move::Captivate)][to_int(
        MoveFlag::CAN_BE_REFLECTED_BY_MIRROR_MOVE)] = true;
    flags[to_int(Move::Charm)][
        to_int(MoveFlag::CAN_BE_REFLECTED_BY_MIRROR_MOVE)] = true;
    flags[to_int(Move::ConfuseRay)][to_int(
        MoveFlag::CAN_BE_REFLECTED_BY_MIRROR_MOVE)] = true;
    flags[to_int(Move::CottonSpore)][to_int(
        MoveFlag::CAN_BE_REFLECTED_BY_MIRROR_MOVE)] = true;
    flags[to_int(Move::DarkVoid)][to_int(
        MoveFlag::CAN_BE_REFLECTED_BY_MIRROR_MOVE)] = true;
    flags[to_int(Move::FakeTears)][to_int(
        MoveFlag::CAN_BE_REFLECTED_BY_MIRROR_MOVE)] = true;
    flags[to_int(Move::Featherdance)][to_int(
        MoveFlag::CAN_BE_REFLECTED_BY_MIRROR_MOVE)] = true;
    flags[to_int(Move::Flash)][
        to_int(MoveFlag::CAN_BE_REFLECTED_BY_MIRROR_MOVE)] = true;
    flags[to_int(Move::Flatter)][to_int(
        MoveFlag::CAN_BE_REFLECTED_BY_MIRROR_MOVE)] = true;
    flags[to_int(Move::GastroAcid)][to_int(
        MoveFlag::CAN_BE_REFLECTED_BY_MIRROR_MOVE)] = true;
    flags[to_int(Move::Glare)][
        to_int(MoveFlag::CAN_BE_REFLECTED_BY_MIRROR_MOVE)] = true;
    flags[to_int(Move::Grasswhistle)][to_int(
        MoveFlag::CAN_BE_REFLECTED_BY_MIRROR_MOVE)] = true;
    flags[to_int(Move::Growl)][
        to_int(MoveFlag::CAN_BE_REFLECTED_BY_MIRROR_MOVE)] = true;
    flags[to_int(Move::Hypnosis)][to_int(
        MoveFlag::CAN_BE_REFLECTED_BY_MIRROR_MOVE)] = true;
    flags[to_int(Move::Kinesis)][to_int(
        MoveFlag::CAN_BE_REFLECTED_BY_MIRROR_MOVE)] = true;
    flags[to_int(Move::LeechSeed)][to_int(
        MoveFlag::CAN_BE_REFLECTED_BY_MIRROR_MOVE)] = true;
    flags[to_int(Move::Leer)][to_int(MoveFlag::CAN_BE_REFLECTED_BY_MIRROR_MOVE)]
        = true;
    flags[to_int(Move::LovelyKiss)][to_int(
        MoveFlag::CAN_BE_REFLECTED_BY_MIRROR_MOVE)] = true;
    flags[to_int(Move::MeanLook)][to_int(
        MoveFlag::CAN_BE_REFLECTED_BY_MIRROR_MOVE)] = true;
    flags[to_int(Move::MetalSound)][to_int(
        MoveFlag::CAN_BE_REFLECTED_BY_MIRROR_MOVE)] = true;
    flags[to_int(Move::PoisonGas)][to_int(
        MoveFlag::CAN_BE_REFLECTED_BY_MIRROR_MOVE)] = true;
    flags[to_int(Move::PoisonPowder)][to_int(
        MoveFlag::CAN_BE_REFLECTED_BY_MIRROR_MOVE)] = true;
    flags[to_int(Move::SandAttack)][to_int(
        MoveFlag::CAN_BE_REFLECTED_BY_MIRROR_MOVE)] = true;
    flags[to_int(Move::ScaryFace)][to_int(
        MoveFlag::CAN_BE_REFLECTED_BY_MIRROR_MOVE)] = true;
    flags[to_int(Move::Screech)][to_int(
        MoveFlag::CAN_BE_REFLECTED_BY_MIRROR_MOVE)] = true;
    flags[to_int(Move::Sing)][to_int(MoveFlag::CAN_BE_REFLECTED_BY_MIRROR_MOVE)]
        = true;
    flags[to_int(Move::SleepPowder)][to_int(
        MoveFlag::CAN_BE_REFLECTED_BY_MIRROR_MOVE)] = true;
    flags[to_int(Move::Smokescreen)][to_int(
        MoveFlag::CAN_BE_REFLECTED_BY_MIRROR_MOVE)] = true;
    flags[to_int(Move::SpiderWeb)][to_int(
        MoveFlag::CAN_BE_REFLECTED_BY_MIRROR_MOVE)] = true;
    flags[to_int(Move::Spore)][
        to_int(MoveFlag::CAN_BE_REFLECTED_BY_MIRROR_MOVE)] = true;
    flags[to_int(Move::StringShot)][to_int(
        MoveFlag::CAN_BE_REFLECTED_BY_MIRROR_MOVE)] = true;
    flags[to_int(Move::StunSpore)][to_int(
        MoveFlag::CAN_BE_REFLECTED_BY_MIRROR_MOVE)] = true;
    flags[to_int(Move::Supersonic)][to_int(
        MoveFlag::CAN_BE_REFLECTED_BY_MIRROR_MOVE)] = true;
    flags[to_int(Move::Swagger)][to_int(
        MoveFlag::CAN_BE_REFLECTED_BY_MIRROR_MOVE)] = true;
    flags[to_int(Move::SweetKiss)][to_int(
        MoveFlag::CAN_BE_REFLECTED_BY_MIRROR_MOVE)] = true;
    flags[to_int(Move::SweetScent)][to_int(
        MoveFlag::CAN_BE_REFLECTED_BY_MIRROR_MOVE)] = true;
    flags[to_int(Move::TailWhip)][to_int(
        MoveFlag::CAN_BE_REFLECTED_BY_MIRROR_MOVE)] = true;
    flags[to_int(Move::ThunderWave)][to_int(
        MoveFlag::CAN_BE_REFLECTED_BY_MIRROR_MOVE)] = true;
    flags[to_int(Move::Tickle)][to_int(
        MoveFlag::CAN_BE_REFLECTED_BY_MIRROR_MOVE)] = true;
    flags[to_int(Move::Toxic)][
        to_int(MoveFlag::CAN_BE_REFLECTED_BY_MIRROR_MOVE)] = true;
    flags[to_int(Move::WillOWisp)][to_int(
        MoveFlag::CAN_BE_REFLECTED_BY_MIRROR_MOVE)] = true;
    flags[to_int(Move::WorrySeed)][to_int(
        MoveFlag::CAN_BE_REFLECTED_BY_MIRROR_MOVE)] = true;
    flags[to_int(Move::Yawn)][to_int(MoveFlag::CAN_BE_REFLECTED_BY_MIRROR_MOVE)]
        = true;

    flags[to_int(Move::AcidArmor)][to_int(MoveFlag::CAN_BE_SNATCHED)] = true;
    flags[to_int(Move::Acupressure)][to_int(MoveFlag::CAN_BE_SNATCHED)] = true;
    flags[to_int(Move::Agility)][to_int(MoveFlag::CAN_BE_SNATCHED)] = true;
    flags[to_int(Move::Amnesia)][to_int(MoveFlag::CAN_BE_SNATCHED)] = true;
    flags[to_int(Move::Aromatherapy)][to_int(MoveFlag::CAN_BE_SNATCHED)] = true;
    flags[to_int(Move::Barrier)][to_int(MoveFlag::CAN_BE_SNATCHED)] = true;
    flags[to_int(Move::BellyDrum)][to_int(MoveFlag::CAN_BE_SNATCHED)] = true;
    flags[to_int(Move::BulkUp)][to_int(MoveFlag::CAN_BE_SNATCHED)] = true;
    flags[to_int(Move::CalmMind)][to_int(MoveFlag::CAN_BE_SNATCHED)] = true;
    flags[to_int(Move::Camouflage)][to_int(MoveFlag::CAN_BE_SNATCHED)] = true;
    flags[to_int(Move::Charge)][to_int(MoveFlag::CAN_BE_SNATCHED)] = true;
    flags[to_int(Move::CosmicPower)][to_int(MoveFlag::CAN_BE_SNATCHED)] = true;
    flags[to_int(Move::DefendOrder)][to_int(MoveFlag::CAN_BE_SNATCHED)] = true;
    flags[to_int(Move::DefenseCurl)][to_int(MoveFlag::CAN_BE_SNATCHED)] = true;
    flags[to_int(Move::DoubleTeam)][to_int(MoveFlag::CAN_BE_SNATCHED)] = true;
    flags[to_int(Move::DragonDance)][to_int(MoveFlag::CAN_BE_SNATCHED)] = true;
    flags[to_int(Move::FocusEnergy)][to_int(MoveFlag::CAN_BE_SNATCHED)] = true;
    flags[to_int(Move::Growth)][to_int(MoveFlag::CAN_BE_SNATCHED)] = true;
    flags[to_int(Move::Harden)][to_int(MoveFlag::CAN_BE_SNATCHED)] = true;
    flags[to_int(Move::HealBell)][to_int(MoveFlag::CAN_BE_SNATCHED)] = true;
    flags[to_int(Move::HealOrder)][to_int(MoveFlag::CAN_BE_SNATCHED)] = true;
    flags[to_int(Move::Howl)][to_int(MoveFlag::CAN_BE_SNATCHED)] = true;
    flags[to_int(Move::Ingrain)][to_int(MoveFlag::CAN_BE_SNATCHED)] = true;
    flags[to_int(Move::IronDefense)][to_int(MoveFlag::CAN_BE_SNATCHED)] = true;
    flags[to_int(Move::LightScreen)][to_int(MoveFlag::CAN_BE_SNATCHED)] = true;
    flags[to_int(Move::Meditate)][to_int(MoveFlag::CAN_BE_SNATCHED)] = true;
    flags[to_int(Move::MilkDrink)][to_int(MoveFlag::CAN_BE_SNATCHED)] = true;
    flags[to_int(Move::Minimize)][to_int(MoveFlag::CAN_BE_SNATCHED)] = true;
    flags[to_int(Move::Mist)][to_int(MoveFlag::CAN_BE_SNATCHED)] = true;
    flags[to_int(Move::Moonlight)][to_int(MoveFlag::CAN_BE_SNATCHED)] = true;
    flags[to_int(Move::MorningSun)][to_int(MoveFlag::CAN_BE_SNATCHED)] = true;
    flags[to_int(Move::NastyPlot)][to_int(MoveFlag::CAN_BE_SNATCHED)] = true;
    flags[to_int(Move::PsychUp)][to_int(MoveFlag::CAN_BE_SNATCHED)] = true;
    flags[to_int(Move::Recover)][to_int(MoveFlag::CAN_BE_SNATCHED)] = true;
    flags[to_int(Move::Reflect)][to_int(MoveFlag::CAN_BE_SNATCHED)] = true;
    flags[to_int(Move::Refresh)][to_int(MoveFlag::CAN_BE_SNATCHED)] = true;
    flags[to_int(Move::Rest)][to_int(MoveFlag::CAN_BE_SNATCHED)] = true;
    flags[to_int(Move::RockPolish)][to_int(MoveFlag::CAN_BE_SNATCHED)] = true;
    flags[to_int(Move::Roost)][to_int(MoveFlag::CAN_BE_SNATCHED)] = true;
    flags[to_int(Move::Safeguard)][to_int(MoveFlag::CAN_BE_SNATCHED)] = true;
    flags[to_int(Move::Sharpen)][to_int(MoveFlag::CAN_BE_SNATCHED)] = true;
    flags[to_int(Move::SlackOff)][to_int(MoveFlag::CAN_BE_SNATCHED)] = true;
    flags[to_int(Move::Softboiled)][to_int(MoveFlag::CAN_BE_SNATCHED)] = true;
    flags[to_int(Move::Stockpile)][to_int(MoveFlag::CAN_BE_SNATCHED)] = true;
    flags[to_int(Move::Substitute)][to_int(MoveFlag::CAN_BE_SNATCHED)] = true;
    flags[to_int(Move::Swallow)][to_int(MoveFlag::CAN_BE_SNATCHED)] = true;
    flags[to_int(Move::SwordsDance)][to_int(MoveFlag::CAN_BE_SNATCHED)] = true;
    flags[to_int(Move::Synthesis)][to_int(MoveFlag::CAN_BE_SNATCHED)] = true;
    flags[to_int(Move::TailGlow)][to_int(MoveFlag::CAN_BE_SNATCHED)] = true;
    flags[to_int(Move::Tailwind)][to_int(MoveFlag::CAN_BE_SNATCHED)] = true;
    flags[to_int(Move::Withdraw)][to_int(MoveFlag::CAN_BE_SNATCHED)] = true;

    flags[to_int(Move::AerialAce)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::Aeroblast)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::AirCutter)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::AirSlash)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::AquaJet)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::AquaTail)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::ArmThrust)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::Assurance)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::AttackOrder)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::AuraSphere)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::Avalanche)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::Barrage)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::BeatUp)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::Bide)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] = true;
    flags[to_int(Move::Bind)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] = true;
    flags[to_int(Move::BlastBurn)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::BoneRush)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::Bonemerang)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::Bounce)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::BraveBird)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::BrickBreak)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::Brine)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] = true;
    flags[to_int(Move::BugBite)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::BulletPunch)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::BulletSeed)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::ChargeBeam)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::Clamp)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] = true;
    flags[to_int(Move::CloseCombat)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::CometPunch)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::Crabhammer)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::CrossChop)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::CrossPoison)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::CrushGrip)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::Cut)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] = true;
    flags[to_int(Move::DarkPulse)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::Dig)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] = true;
    flags[to_int(Move::Discharge)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::Dive)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] = true;
    flags[to_int(Move::DoubleHit)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::DoubleKick)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::DoubleSlap)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::DoubleEdge)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::DracoMeteor)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::DragonBreath)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)]
        = true;
    flags[to_int(Move::DragonClaw)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::DragonPulse)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::DragonRush)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::DrainPunch)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::DrillPeck)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::EarthPower)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::Earthquake)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::EggBomb)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::Endeavor)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::Eruption)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::Explosion)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::ExtremeSpeed)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)]
        = true;
    flags[to_int(Move::FalseSwipe)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::FaintAttack)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::FireFang)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::FireSpin)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::Flail)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] = true;
    flags[to_int(Move::FlashCannon)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::Fly)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] = true;
    flags[to_int(Move::ForcePalm)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::FrenzyPlant)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::Frustration)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::FuryAttack)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::FuryCutter)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::FurySwipes)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::GigaImpact)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::GrassKnot)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::GunkShot)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::GyroBall)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::HammerArm)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::HeadSmash)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::HiddenPower)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::HighJumpKick)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)]
        = true;
    flags[to_int(Move::HornAttack)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::HydroCannon)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::HydroPump)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::HyperBeam)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::IceBall)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::IceFang)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::IceShard)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::IcicleSpear)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::IronHead)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::Judgment)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::JumpKick)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::KarateChop)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::LastResort)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::LavaPlume)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::LeafBlade)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::LeafStorm)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::LowKick)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::MachPunch)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::MagicalLeaf)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::MagmaStorm)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::MagnetBomb)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::Magnitude)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::MegaKick)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::MegaPunch)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::Megahorn)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::MeteorMash)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::MirrorCoat)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::MirrorShot)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::MudBomb)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::MudShot)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::MuddyWater)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::NightShade)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::NightSlash)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::OminousWind)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::Outrage)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::Overheat)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::PayDay)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::Payback)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::Peck)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] = true;
    flags[to_int(Move::PetalDance)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::PinMissile)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::Pluck)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] = true;
    flags[to_int(Move::PoisonJab)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::PoisonTail)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::PowerGem)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::PowerWhip)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::PsychoBoost)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::PsychoCut)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::Psywave)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::Punishment)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::QuickAttack)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::Rage)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] = true;
    flags[to_int(Move::RapidSpin)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::RazorLeaf)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::RazorWind)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::Return)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::Revenge)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::Reversal)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::RoarOfTime)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::RockBlast)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::RockClimb)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::RockThrow)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::RockWrecker)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::RollingKick)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::Rollout)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::SandTomb)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::Scratch)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::SeedBomb)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::SeedFlare)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::SeismicToss)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::ShadowClaw)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::ShadowForce)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::ShadowPunch)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::ShadowSneak)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::ShockWave)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::SignalBeam)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::SilverWind)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::SkullBash)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::SkyAttack)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::SkyUppercut)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::Slam)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] = true;
    flags[to_int(Move::Slash)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] = true;
    flags[to_int(Move::Snore)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] = true;
    flags[to_int(Move::SolarBeam)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::SonicBoom)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::SpacialRend)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::SpikeCannon)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::SpitUp)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::SteelWing)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::StoneEdge)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::Strength)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::Struggle)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::Submission)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::SuckerPunch)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::Surf)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] = true;
    flags[to_int(Move::Swift)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] = true;
    flags[to_int(Move::Tackle)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::TakeDown)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::Thrash)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::ThunderFang)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::TripleKick)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::TrumpCard)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::Twister)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::UTurn)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] = true;
    flags[to_int(Move::Uproar)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::VacuumWave)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::ViceGrip)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::VineWhip)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::VitalThrow)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::VoltTackle)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::WakeUpSlap)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::WaterGun)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::WaterPulse)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::Waterfall)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::WeatherBall)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::Whirlpool)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::WingAttack)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::WoodHammer)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::Wrap)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] = true;
    flags[to_int(Move::WringOut)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;
    flags[to_int(Move::XScissor)][to_int(MoveFlag::AFFECTED_BY_KINGS_ROCK)] =
        true;

    flags[to_int(Move::Growl)][to_int(MoveFlag::IS_SOUND_BASED)] = true;
    flags[to_int(Move::Roar)][to_int(MoveFlag::IS_SOUND_BASED)] = true;
    flags[to_int(Move::Sing)][to_int(MoveFlag::IS_SOUND_BASED)] = true;
    flags[to_int(Move::Supersonic)][to_int(MoveFlag::IS_SOUND_BASED)] = true;
    flags[to_int(Move::Screech)][to_int(MoveFlag::IS_SOUND_BASED)] = true;
    flags[to_int(Move::Snore)][to_int(MoveFlag::IS_SOUND_BASED)] = true;
    flags[to_int(Move::PerishSong)][to_int(MoveFlag::IS_SOUND_BASED)] = true;
    flags[to_int(Move::HealBell)][to_int(MoveFlag::IS_SOUND_BASED)] = true;
    flags[to_int(Move::Uproar)][to_int(MoveFlag::IS_SOUND_BASED)] = true;
    flags[to_int(Move::HyperVoice)][to_int(MoveFlag::IS_SOUND_BASED)] = true;
    flags[to_int(Move::MetalSound)][to_int(MoveFlag::IS_SOUND_BASED)] = true;
    flags[to_int(Move::Grasswhistle)][to_int(MoveFlag::IS_SOUND_BASED)] = true;
    flags[to_int(Move::Howl)][to_int(MoveFlag::IS_SOUND_BASED)] = true;
    flags[to_int(Move::BugBuzz)][to_int(MoveFlag::IS_SOUND_BASED)] = true;
    flags[to_int(Move::Chatter)][to_int(MoveFlag::IS_SOUND_BASED)] = true;
    return flags;
}();

inline bool move_has_flag(const Move move, const MoveFlag move_flag) {
    return move != Move::MoveCount && MOVE_FLAGS[to_int(move)][to_int(move_flag)];
}

constexpr auto IMPLEMENTED_MOVES = [] {
    std::array<bool, to_int(Move::MoveCount)> implemented_moves{};
    implemented_moves[to_int(Move::Moonlight)] = true;
    implemented_moves[to_int(Move::SignalBeam)] = true;
    implemented_moves[to_int(Move::Psychic)] = true;
    implemented_moves[to_int(Move::IceBeam)] = true;
    implemented_moves[to_int(Move::MistBall)] = true;
    implemented_moves[to_int(Move::Thunderbolt)] = true;
    implemented_moves[to_int(Move::Surf)] = true;
    return implemented_moves;
}();

inline void verify_move_implemented(const Move move) {
    if (!IMPLEMENTED_MOVES[to_int(move)]) {
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
    for (const auto& move : moves) {
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

