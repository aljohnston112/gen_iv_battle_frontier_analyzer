#pragma once

#include <string>
#include <unordered_map>

#include "type.h"

enum Item {
    ApicotBerry,
    AspearBerry,
    BigRoot,
    BlackBelt,
    BlackGlasses,
    BlackSludge,
    BrightPowder,
    Charcoal,
    CheriBerry,
    ChestoBerry,
    ChoiceBand,
    ChoiceScarf,
    ChoiceSpecs,
    DampRock,
    DeepSeaScale,
    DeepSeaTooth,
    DragonFang,
    ExpertBelt,
    FlameOrb,
    FocusBand,
    FocusSash,
    GanlonBerry,
    GripClaw,
    HardStone,
    HeatRock,
    IcyRock,
    IronBall,
    KingsRock,
    LansatBerry,
    LaxIncense,
    Leftovers,
    LiechiBerry,
    LifeOrb,
    LightBall,
    LightClay,
    LuckyPunch,
    LumBerry,
    Magnet,
    MentalHerb,
    MetalCoat,
    Metronome,
    MiracleSeed,
    MuscleBand,
    MysticWater,
    NeverMeltIce,
    OddIncense,
    PechaBerry,
    PersimBerry,
    PetayaBerry,
    PoisonBarb,
    PowerHerb,
    QuickClaw,
    QuickPowder,
    RawstBerry,
    RazorClaw,
    RazorFang,
    RockIncense,
    RockyHelmet,
    RoseIncense,
    SalacBerry,
    SeaIncense,
    ScopeLens,
    SharpBeak,
    ShellBell,
    SilkScarf,
    SilverPowder,
    SitrusBerry,
    SmoothRock,
    SoftSand,
    SpellTag,
    Stick,
    StickyBarb,
    ThickClub,
    ToxicOrb,
    TwistedSpoon,
    WaveIncense,
    WhiteHerb,
    WideLens,
    WiseGlasses,
    ZoomLens,

    FistPlate,
    SkyPlate,
    ToxicPlate,
    EarthPlate,
    StonePlate,
    InsectPlate,
    SpookyPlate,
    IronPlate,
    FlamePlate,
    SplashPlate,
    MeadowPlate,
    ZapPlate,
    MindPlate,
    IciclePlate,
    DracoPlate,
    DreadPlate,

    BabiriBerry,
    ChartiBerry,
    ChilanBerry,
    ChopleBerry,
    CobaBerry,
    ColburBerry,
    HabanBerry,
    KasibBerry,
    KebiaBerry,
    OccaBerry,
    PasshoBerry,
    PayapaBerry,
    RindoBerry,
    ShucaBerry,
    TangaBerry,
    WacanBerry,
    YacheBerry,

    NoItem
};

inline const std::unordered_map<std::string, Item> STRING_TO_ITEM_MAP = {
    {"Apicot Berry", ApicotBerry},
    {"Aspear Berry", AspearBerry},
    {"Big Root", BigRoot},
    {"Black Belt", BlackBelt},
    {"BlackGlasses", BlackGlasses},
    {"Black Sludge", BlackSludge},
    {"Brightpowder", BrightPowder},
    {"BrightPowder", BrightPowder},
    {"Charcoal", Charcoal},
    {"Cheri Berry", CheriBerry},
    {"Chesto Berry", ChestoBerry},
    {"Choice Band", ChoiceBand},
    {"Choice Scarf", ChoiceScarf},
    {"Choice Specs", ChoiceSpecs},
    {"Damp Rock", DampRock},
    {"DeepSeaScale", DeepSeaScale},
    {"DeepSeaTooth", DeepSeaTooth},
    {"Dragon Fang", DragonFang},
    {"Expert Belt", ExpertBelt},
    {"Flame Orb", FlameOrb},
    {"Focus Band", FocusBand},
    {"Focus Sash", FocusSash},
    {"Ganlon Berry", GanlonBerry},
    {"Grip Claw", GripClaw},
    {"Hard Stone", HardStone},
    {"Heat Rock", HeatRock},
    {"Icy Rock", IcyRock},
    {"Iron Ball", IronBall},
    {"King's Rock", KingsRock},
    {"Lansat Berry", LansatBerry},
    {"Lax Incense", LaxIncense},
    {"Light Ball", LightBall},
    {"Leftovers", Leftovers},
    {"Liechi Berry", LiechiBerry},
    {"Life Orb", LifeOrb},
    {"Light Clay", LightClay},
    {"Lucky Punch", LuckyPunch},
    {"Lum Berry", LumBerry},
    {"Magnet", Magnet},
    {"Metal Coat", MetalCoat},
    {"Metronome", Metronome},
    {"Mental Herb", MentalHerb},
    {"Miracle Seed", MiracleSeed},
    {"Muscle Band", MuscleBand},
    {"Mystic Water", MysticWater},
    {"NeverMeltIce", NeverMeltIce},
    {"Odd Incense", OddIncense},
    {"Pecha Berry", PechaBerry},
    {"Persim Berry", PersimBerry},
    {"Petaya Berry", PetayaBerry},
    {"Poison Barb", PoisonBarb},
    {"Power Herb", PowerHerb},
    {"Quick Claw", QuickClaw},
    {"Quick Powder", QuickPowder},
    {"Rawst Berry", RawstBerry},
    {"Razor Claw", RazorClaw},
    {"Razor Fang", RazorFang},
    {"Rock Incense", RockIncense},
    {"Rocky Helmet", RockyHelmet},
    {"Rose Incense", RoseIncense},
    {"Salac Berry", SalacBerry},
    {"Sea Incense", SeaIncense},
    {"Scope Lens", ScopeLens},
    {"Sharp Beak", SharpBeak},
    {"Shell Bell", ShellBell},
    {"Silk Scarf", SilkScarf},
    {"SilverPowder", SilverPowder},
    {"Sitrus Berry", SitrusBerry},
    {"Smooth Rock", SmoothRock},
    {"Soft Sand", SoftSand},
    {"Spell Tag", SpellTag},
    {"Stick", Stick},
    {"Sticky Barb", StickyBarb},
    {"Thick Club", ThickClub},
    {"Toxic Orb", ToxicOrb},
    {"Twisted Spoon", TwistedSpoon},
    {"TwistedSpoon", TwistedSpoon},
    {"Wave Incense", WaveIncense},
    {"White Herb", WhiteHerb},
    {"Wide Lens", WideLens},
    {"Wise Glasses", WiseGlasses},
    {"Zoom Lens", ZoomLens},

    {"Babiri Berry", BabiriBerry},
    {"Charti Berry", ChartiBerry},
    {"Chilan Berry", ChilanBerry},
    {"Chople Berry", ChopleBerry},
    {"Coba Berry", CobaBerry},
    {"Colbur Berry", ColburBerry},
    {"Haban Berry", HabanBerry},
    {"Kasib Berry", KasibBerry},
    {"Kebia Berry", KebiaBerry},
    {"Occa Berry", OccaBerry},
    {"Passho Berry", PasshoBerry},
    {"Payapa Berry", PayapaBerry},
    {"Rindo Berry", RindoBerry},
    {"Shuca Berry", ShucaBerry},
    {"Tanga Berry", TangaBerry},
    {"Wacan Berry", WacanBerry},
    {"Yache Berry", YacheBerry},

    {"", NoItem}
};

inline const std::unordered_map<Item, PokemonType> DAMAGE_REDUCING_BERRIES = {
    {BabiriBerry, Steel},
    {ChartiBerry, Rock},
    {ChilanBerry, Normal},
    {ChopleBerry, Fighting},
    {CobaBerry, Flying},
    {ColburBerry, Dark},
    {HabanBerry, Dragon},
    {KasibBerry, Ghost},
    {KebiaBerry, Poison},
    {OccaBerry, Fire},
    {PasshoBerry, Water},
    {PayapaBerry, Psychic},
    {RindoBerry, Grass},
    {ShucaBerry, Ground},
    {TangaBerry, Bug},
    {WacanBerry, Electric},
    {YacheBerry, Ice}
};

inline std::unordered_map<Item, std::string> initialize_item_to_string_map() {
    std::unordered_map<Item, std::string> map{};
    for (const auto& [
             item_name,
             item
         ] : STRING_TO_ITEM_MAP
    ) {
        map[item] = item_name;
    }
    return map;
}

static std::unordered_map<Item, std::string> ITEM_TO_STRING_MAP =
    initialize_item_to_string_map();

constexpr auto IMPLEMENTED_ITEMS = [] {
    std::array<bool, NoItem> implemented_items{};
    implemented_items[Leftovers] = true;
    return implemented_items;
}();

inline void verify_item_implemented(const Item item) {
    if (!IMPLEMENTED_ITEMS[item]) {
        throw std::runtime_error(
            std::format(
                "Unimplemented item: {}",
                ITEM_TO_STRING_MAP[item]
            )
        );
    }
}

inline void verify_items_implemented(
    const Item player_item,
    const Item opponent_item
) {
    if constexpr (CHECK_UNIMPLEMENTED) {
        verify_item_implemented(player_item);
        verify_item_implemented(opponent_item);
    }
}
