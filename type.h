#pragma once

enum class PokemonType {
    NORMAL,
    FIGHTING,
    FLYING,
    POISON,
    GROUND,
    ROCK,
    BUG,
    GHOST,
    STEEL,
    FIRE,
    WATER,
    GRASS,
    ELECTRIC,
    PSYCHIC,
    ICE,
    DRAGON,
    DARK,
    COUNT
};

inline const std::unordered_map<std::string, PokemonType> STRING_TO_TYPE_MAP{
    {"normal", PokemonType::NORMAL},
    {"fighting", PokemonType::FIGHTING},
    {"flying", PokemonType::FLYING},
    {"poison", PokemonType::POISON},
    {"ground", PokemonType::GROUND},
    {"rock", PokemonType::ROCK},
    {"bug", PokemonType::BUG},
    {"ghost", PokemonType::GHOST},
    {"steel", PokemonType::STEEL},
    {"fire", PokemonType::FIRE},
    {"water", PokemonType::WATER},
    {"grass", PokemonType::GRASS},
    {"electric", PokemonType::ELECTRIC},
    {"psychic", PokemonType::PSYCHIC},
    {"ice", PokemonType::ICE},
    {"dragon", PokemonType::DRAGON},
    {"dark", PokemonType::DARK}
};
