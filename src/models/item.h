#pragma once

#include <string>
#include <unordered_map>

#include "type.h"

enum class Item {
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
    {"Apicot Berry", Item::ApicotBerry},
    {"Aspear Berry", Item::AspearBerry},
    {"Big Root", Item::BigRoot},
    {"Black Belt", Item::BlackBelt},
    {"BlackGlasses", Item::BlackGlasses},
    {"Black Sludge", Item::BlackSludge},
    {"Brightpowder", Item::BrightPowder},
    {"BrightPowder", Item::BrightPowder},
    {"Charcoal", Item::Charcoal},
    {"Cheri Berry", Item::CheriBerry},
    {"Chesto Berry", Item::ChestoBerry},
    {"Choice Band", Item::ChoiceBand},
    {"Choice Scarf", Item::ChoiceScarf},
    {"Choice Specs", Item::ChoiceSpecs},
    {"Damp Rock", Item::DampRock},
    {"DeepSeaScale", Item::DeepSeaScale},
    {"DeepSeaTooth", Item::DeepSeaTooth},
    {"Dragon Fang", Item::DragonFang},
    {"Expert Belt", Item::ExpertBelt},
    {"Flame Orb", Item::FlameOrb},
    {"Focus Band", Item::FocusBand},
    {"Focus Sash", Item::FocusSash},
    {"Ganlon Berry", Item::GanlonBerry},
    {"Grip Claw", Item::GripClaw},
    {"Hard Stone", Item::HardStone},
    {"Heat Rock", Item::HeatRock},
    {"Icy Rock", Item::IcyRock},
    {"Iron Ball", Item::IronBall},
    {"King's Rock", Item::KingsRock},
    {"Lansat Berry", Item::LansatBerry},
    {"Lax Incense", Item::LaxIncense},
    {"Light Ball", Item::LightBall},
    {"Leftovers", Item::Leftovers},
    {"Liechi Berry", Item::LiechiBerry},
    {"Life Orb", Item::LifeOrb},
    {"Light Clay", Item::LightClay},
    {"Lucky Punch", Item::LuckyPunch},
    {"Lum Berry", Item::LumBerry},
    {"Magnet", Item::Magnet},
    {"Metal Coat", Item::MetalCoat},
    {"Metronome", Item::Metronome},
    {"Mental Herb", Item::MentalHerb},
    {"Miracle Seed", Item::MiracleSeed},
    {"Muscle Band", Item::MuscleBand},
    {"Mystic Water", Item::MysticWater},
    {"NeverMeltIce", Item::NeverMeltIce},
    {"Odd Incense", Item::OddIncense},
    {"Pecha Berry", Item::PechaBerry},
    {"Persim Berry", Item::PersimBerry},
    {"Petaya Berry", Item::PetayaBerry},
    {"Poison Barb", Item::PoisonBarb},
    {"Power Herb", Item::PowerHerb},
    {"Quick Claw", Item::QuickClaw},
    {"Quick Powder", Item::QuickPowder},
    {"Rawst Berry", Item::RawstBerry},
    {"Razor Claw", Item::RazorClaw},
    {"Razor Fang", Item::RazorFang},
    {"Rock Incense", Item::RockIncense},
    {"Rocky Helmet", Item::RockyHelmet},
    {"Rose Incense", Item::RoseIncense},
    {"Salac Berry", Item::SalacBerry},
    {"Sea Incense", Item::SeaIncense},
    {"Scope Lens", Item::ScopeLens},
    {"Sharp Beak", Item::SharpBeak},
    {"Shell Bell", Item::ShellBell},
    {"Silk Scarf", Item::SilkScarf},
    {"SilverPowder", Item::SilverPowder},
    {"Sitrus Berry", Item::SitrusBerry},
    {"Smooth Rock", Item::SmoothRock},
    {"Soft Sand", Item::SoftSand},
    {"Spell Tag", Item::SpellTag},
    {"Stick", Item::Stick},
    {"Sticky Barb", Item::StickyBarb},
    {"Thick Club", Item::ThickClub},
    {"Toxic Orb", Item::ToxicOrb},
    {"Twisted Spoon", Item::TwistedSpoon},
    {"TwistedSpoon", Item::TwistedSpoon},
    {"Wave Incense", Item::WaveIncense},
    {"White Herb", Item::WhiteHerb},
    {"Wide Lens", Item::WideLens},
    {"Wise Glasses", Item::WiseGlasses},
    {"Zoom Lens", Item::ZoomLens},

    {"Babiri Berry", Item::BabiriBerry},
    {"Charti Berry", Item::ChartiBerry},
    {"Chilan Berry", Item::ChilanBerry},
    {"Chople Berry", Item::ChopleBerry},
    {"Coba Berry", Item::CobaBerry},
    {"Colbur Berry", Item::ColburBerry},
    {"Haban Berry", Item::HabanBerry},
    {"Kasib Berry", Item::KasibBerry},
    {"Kebia Berry", Item::KebiaBerry},
    {"Occa Berry", Item::OccaBerry},
    {"Passho Berry", Item::PasshoBerry},
    {"Payapa Berry", Item::PayapaBerry},
    {"Rindo Berry", Item::RindoBerry},
    {"Shuca Berry", Item::ShucaBerry},
    {"Tanga Berry", Item::TangaBerry},
    {"Wacan Berry", Item::WacanBerry},
    {"Yache Berry", Item::YacheBerry},

    {"", Item::NoItem}
};

inline const std::unordered_map<Item, PokemonType> DAMAGE_REDUCING_BERRIES = {
    {Item::BabiriBerry, PokemonType::Steel},
    {Item::ChartiBerry, PokemonType::Rock},
    {Item::ChilanBerry, PokemonType::Normal},
    {Item::ChopleBerry, PokemonType::Fighting},
    {Item::CobaBerry, PokemonType::Flying},
    {Item::ColburBerry, PokemonType::Dark},
    {Item::HabanBerry, PokemonType::Dragon},
    {Item::KasibBerry, PokemonType::Ghost},
    {Item::KebiaBerry, PokemonType::Poison},
    {Item::OccaBerry, PokemonType::Fire},
    {Item::PasshoBerry, PokemonType::Water},
    {Item::PayapaBerry, PokemonType::Psychic},
    {Item::RindoBerry, PokemonType::Grass},
    {Item::ShucaBerry, PokemonType::Ground},
    {Item::TangaBerry, PokemonType::Bug},
    {Item::WacanBerry, PokemonType::Electric},
    {Item::YacheBerry, PokemonType::Ice}
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

inline std::unordered_map<Item, std::string> ITEM_TO_STRING_MAP =
    initialize_item_to_string_map();

constexpr auto IMPLEMENTED_ITEMS = [] {
    std::array<bool, to_int(Item::NoItem)> implemented_items{};
    implemented_items[to_int(Item::Leftovers)] = true;
    implemented_items[to_int(Item::WhiteHerb)] = true;
    // Any damage modifiers may also need to be applied to hit_from_confusion
    // Items removed or switched may necessitate modifying state
    return implemented_items;
}();

inline void verify_item_implemented(const Item item) {
    if (!IMPLEMENTED_ITEMS[to_int(item)]) {
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
