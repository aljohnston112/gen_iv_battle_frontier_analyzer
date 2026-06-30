#pragma once
#include "util.h"

enum class PokemonType {
    Normal,
    Fighting,
    Flying,
    Poison,
    Ground,
    Rock,
    Bug,
    Ghost,
    Steel,
    Fire,
    Water,
    Grass,
    Electric,
    Psychic,
    Ice,
    Dragon,
    Dark,
    NoType,
    PokemonTypeCount
};

constexpr int pokemonTypeCount = to_int(PokemonType::PokemonTypeCount);

inline const std::unordered_map<std::string, PokemonType> STRING_TO_TYPE_MAP{
    {"normal", PokemonType::Normal},
    {"fighting", PokemonType::Fighting},
    {"flying", PokemonType::Flying},
    {"poison", PokemonType::Poison},
    {"ground", PokemonType::Ground},
    {"rock", PokemonType::Rock},
    {"bug", PokemonType::Bug},
    {"ghost", PokemonType::Ghost},
    {"steel", PokemonType::Steel},
    {"fire", PokemonType::Fire},
    {"water", PokemonType::Water},
    {"grass", PokemonType::Grass},
    {"electric", PokemonType::Electric},
    {"psychic", PokemonType::Psychic},
    {"ice", PokemonType::Ice},
    {"dragon", PokemonType::Dragon},
    {"dark", PokemonType::Dark}
};

constexpr double not_effective = 0.0;
constexpr double not_very_effective = 0.5;
constexpr double super_effective = 2.0;

constexpr std::array<
    std::array<double, pokemonTypeCount>,
    pokemonTypeCount
> EFFECTIVENESS_TABLE = [] {
    std::array<
        std::array<double, pokemonTypeCount>,
        pokemonTypeCount
    > table{};
    for (auto& row : table) {
        row.fill(1.0);
    }

    table[to_int(PokemonType::Normal)][to_int(PokemonType::Fighting)] =
        super_effective;
    table[to_int(PokemonType::Normal)][to_int(PokemonType::Ghost)] =
        not_effective;

    table[to_int(PokemonType::Fire)][to_int(PokemonType::Fire)] =
        not_very_effective;
    table[to_int(PokemonType::Fire)][to_int(PokemonType::Water)] =
        super_effective;
    table[to_int(PokemonType::Fire)][to_int(PokemonType::Grass)] =
        not_very_effective;
    table[to_int(PokemonType::Fire)][to_int(PokemonType::Ice)] =
        not_very_effective;
    table[to_int(PokemonType::Fire)][to_int(PokemonType::Ground)] =
        super_effective;
    table[to_int(PokemonType::Fire)][to_int(PokemonType::Bug)] =
        not_very_effective;
    table[to_int(PokemonType::Fire)][to_int(PokemonType::Rock)] =
        super_effective;
    table[to_int(PokemonType::Fire)][to_int(PokemonType::Steel)] =
        not_very_effective;

    table[to_int(PokemonType::Water)][to_int(PokemonType::Fire)] =
        not_very_effective;
    table[to_int(PokemonType::Water)][to_int(PokemonType::Water)] =
        not_very_effective;
    table[to_int(PokemonType::Water)][to_int(PokemonType::Electric)] =
        super_effective;
    table[to_int(PokemonType::Water)][to_int(PokemonType::Grass)] =
        super_effective;
    table[to_int(PokemonType::Water)][to_int(PokemonType::Ice)] =
        not_very_effective;
    table[to_int(PokemonType::Water)][to_int(PokemonType::Steel)] =
        not_very_effective;

    table[to_int(PokemonType::Electric)][to_int(PokemonType::Electric)] =
        not_very_effective;
    table[to_int(PokemonType::Electric)][to_int(PokemonType::Ground)] =
        super_effective;
    table[to_int(PokemonType::Electric)][to_int(PokemonType::Flying)] =
        not_very_effective;
    table[to_int(PokemonType::Electric)][to_int(PokemonType::Steel)] =
        not_very_effective;

    table[to_int(PokemonType::Grass)][to_int(PokemonType::Fire)] =
        super_effective;
    table[to_int(PokemonType::Grass)][to_int(PokemonType::Water)] =
        not_very_effective;
    table[to_int(PokemonType::Grass)][to_int(PokemonType::Electric)] =
        not_very_effective;
    table[to_int(PokemonType::Grass)][to_int(PokemonType::Grass)] =
        not_very_effective;
    table[to_int(PokemonType::Grass)][to_int(PokemonType::Ice)] =
        super_effective;
    table[to_int(PokemonType::Grass)][to_int(PokemonType::Poison)] =
        super_effective;
    table[to_int(PokemonType::Grass)][to_int(PokemonType::Ground)] =
        not_very_effective;
    table[to_int(PokemonType::Grass)][to_int(PokemonType::Flying)] =
        super_effective;
    table[to_int(PokemonType::Grass)][to_int(PokemonType::Bug)] =
        super_effective;

    table[to_int(PokemonType::Ice)][to_int(PokemonType::Fire)] =
        super_effective;
    table[to_int(PokemonType::Ice)][to_int(PokemonType::Ice)] =
        not_very_effective;
    table[to_int(PokemonType::Ice)][to_int(PokemonType::Fighting)] =
        super_effective;
    table[to_int(PokemonType::Ice)][to_int(PokemonType::Rock)] =
        super_effective;
    table[to_int(PokemonType::Ice)][to_int(PokemonType::Steel)] =
        super_effective;

    table[to_int(PokemonType::Fighting)][to_int(PokemonType::Flying)] =
        super_effective;
    table[to_int(PokemonType::Fighting)][to_int(PokemonType::Psychic)] =
        super_effective;
    table[to_int(PokemonType::Fighting)][to_int(PokemonType::Bug)] =
        not_very_effective;
    table[to_int(PokemonType::Fighting)][to_int(PokemonType::Rock)] =
        not_very_effective;
    table[to_int(PokemonType::Fighting)][to_int(PokemonType::Dark)] =
        not_very_effective;

    table[to_int(PokemonType::Poison)][to_int(PokemonType::Grass)] =
        not_very_effective;
    table[to_int(PokemonType::Poison)][to_int(PokemonType::Fighting)] =
        not_very_effective;
    table[to_int(PokemonType::Poison)][to_int(PokemonType::Poison)] =
        not_very_effective;
    table[to_int(PokemonType::Poison)][to_int(PokemonType::Ground)] =
        super_effective;
    table[to_int(PokemonType::Poison)][to_int(PokemonType::Psychic)] =
        super_effective;
    table[to_int(PokemonType::Poison)][to_int(PokemonType::Bug)] =
        not_very_effective;

    table[to_int(PokemonType::Ground)][to_int(PokemonType::Water)] =
        super_effective;
    table[to_int(PokemonType::Ground)][to_int(PokemonType::Electric)] =
        not_effective;
    table[to_int(PokemonType::Ground)][to_int(PokemonType::Grass)] =
        super_effective;
    table[to_int(PokemonType::Ground)][to_int(PokemonType::Ice)] =
        super_effective;
    table[to_int(PokemonType::Ground)][to_int(PokemonType::Poison)] =
        not_very_effective;
    table[to_int(PokemonType::Ground)][to_int(PokemonType::Rock)] =
        not_very_effective;

    table[to_int(PokemonType::Flying)][to_int(PokemonType::Electric)] =
        super_effective;
    table[to_int(PokemonType::Flying)][to_int(PokemonType::Grass)] =
        not_very_effective;
    table[to_int(PokemonType::Flying)][to_int(PokemonType::Ice)] =
        super_effective;
    table[to_int(PokemonType::Flying)][to_int(PokemonType::Fighting)] =
        not_very_effective;
    table[to_int(PokemonType::Flying)][to_int(PokemonType::Ground)] =
        not_effective;
    table[to_int(PokemonType::Flying)][to_int(PokemonType::Bug)] =
        not_very_effective;
    table[to_int(PokemonType::Flying)][to_int(PokemonType::Rock)] =
        super_effective;

    table[to_int(PokemonType::Psychic)][to_int(PokemonType::Fighting)] =
        not_very_effective;
    table[to_int(PokemonType::Psychic)][to_int(PokemonType::Psychic)] =
        not_very_effective;
    table[to_int(PokemonType::Psychic)][to_int(PokemonType::Bug)] =
        super_effective;
    table[to_int(PokemonType::Psychic)][to_int(PokemonType::Ghost)] =
        super_effective;
    table[to_int(PokemonType::Psychic)][to_int(PokemonType::Dark)] =
        super_effective;

    table[to_int(PokemonType::Bug)][to_int(PokemonType::Fire)] =
        super_effective;
    table[to_int(PokemonType::Bug)][to_int(PokemonType::Grass)] =
        not_very_effective;
    table[to_int(PokemonType::Bug)][to_int(PokemonType::Fighting)] =
        not_very_effective;
    table[to_int(PokemonType::Bug)][to_int(PokemonType::Ground)] =
        not_very_effective;
    table[to_int(PokemonType::Bug)][to_int(PokemonType::Flying)] =
        super_effective;
    table[to_int(PokemonType::Bug)][to_int(PokemonType::Rock)] =
        super_effective;

    table[to_int(PokemonType::Rock)][to_int(PokemonType::Normal)] =
        not_very_effective;
    table[to_int(PokemonType::Rock)][to_int(PokemonType::Fire)] =
        not_very_effective;
    table[to_int(PokemonType::Rock)][to_int(PokemonType::Water)] =
        super_effective;
    table[to_int(PokemonType::Rock)][to_int(PokemonType::Grass)] =
        super_effective;
    table[to_int(PokemonType::Rock)][to_int(PokemonType::Fighting)] =
        super_effective;
    table[to_int(PokemonType::Rock)][to_int(PokemonType::Poison)] =
        not_very_effective;
    table[to_int(PokemonType::Rock)][to_int(PokemonType::Ground)] =
        super_effective;
    table[to_int(PokemonType::Rock)][to_int(PokemonType::Flying)] =
        not_very_effective;
    table[to_int(PokemonType::Rock)][to_int(PokemonType::Steel)] =
        super_effective;

    table[to_int(PokemonType::Ghost)][to_int(PokemonType::Normal)] =
        not_effective;
    table[to_int(PokemonType::Ghost)][to_int(PokemonType::Fighting)] =
        not_effective;
    table[to_int(PokemonType::Ghost)][to_int(PokemonType::Poison)] =
        not_very_effective;
    table[to_int(PokemonType::Ghost)][to_int(PokemonType::Bug)] =
        not_very_effective;
    table[to_int(PokemonType::Ghost)][to_int(PokemonType::Ghost)] =
        super_effective;
    table[to_int(PokemonType::Ghost)][to_int(PokemonType::Dark)] =
        super_effective;

    table[to_int(PokemonType::Dragon)][to_int(PokemonType::Fire)] =
        not_very_effective;
    table[to_int(PokemonType::Dragon)][to_int(PokemonType::Water)] =
        not_very_effective;
    table[to_int(PokemonType::Dragon)][to_int(PokemonType::Electric)] =
        not_very_effective;
    table[to_int(PokemonType::Dragon)][to_int(PokemonType::Grass)] =
        not_very_effective;
    table[to_int(PokemonType::Dragon)][to_int(PokemonType::Ice)] =
        super_effective;
    table[to_int(PokemonType::Dragon)][to_int(PokemonType::Dragon)] =
        super_effective;

    table[to_int(PokemonType::Dark)][to_int(PokemonType::Fighting)] =
        super_effective;
    table[to_int(PokemonType::Dark)][to_int(PokemonType::Psychic)] =
        not_effective;
    table[to_int(PokemonType::Dark)][to_int(PokemonType::Bug)] =
        super_effective;
    table[to_int(PokemonType::Dark)][to_int(PokemonType::Ghost)] =
        not_very_effective;
    table[to_int(PokemonType::Dark)][to_int(PokemonType::Dark)] =
        not_very_effective;

    table[to_int(PokemonType::Steel)][to_int(PokemonType::Normal)] =
        not_very_effective;
    table[to_int(PokemonType::Steel)][to_int(PokemonType::Fire)] =
        super_effective;
    table[to_int(PokemonType::Steel)][to_int(PokemonType::Grass)] =
        not_very_effective;
    table[to_int(PokemonType::Steel)][to_int(PokemonType::Ice)] =
        not_very_effective;
    table[to_int(PokemonType::Steel)][to_int(PokemonType::Fighting)] =
        super_effective;
    table[to_int(PokemonType::Steel)][to_int(PokemonType::Poison)] =
        not_effective;
    table[to_int(PokemonType::Steel)][to_int(PokemonType::Ground)] =
        super_effective;
    table[to_int(PokemonType::Steel)][to_int(PokemonType::Flying)] =
        not_very_effective;
    table[to_int(PokemonType::Steel)][to_int(PokemonType::Psychic)] =
        not_very_effective;
    table[to_int(PokemonType::Steel)][to_int(PokemonType::Bug)] =
        not_very_effective;
    table[to_int(PokemonType::Steel)][to_int(PokemonType::Rock)] =
        not_very_effective;
    table[to_int(PokemonType::Steel)][to_int(PokemonType::Ghost)] =
        not_very_effective;
    table[to_int(PokemonType::Steel)][to_int(PokemonType::Dragon)] =
        not_very_effective;
    table[to_int(PokemonType::Steel)][to_int(PokemonType::Dark)] =
        not_very_effective;
    table[to_int(PokemonType::Steel)][to_int(PokemonType::Steel)] =
        not_very_effective;

    return table;
}();

constexpr size_t get_key(
    const std::array<PokemonType, 2>& defender_types,
    const PokemonType& move_type) {
    return to_int(move_type) *
        pokemonTypeCount *
        pokemonTypeCount +
        to_int(defender_types[0]) * pokemonTypeCount +
        to_int(defender_types[1]);
}

constexpr auto EFFECTIVENESS_CACHE = [] {
    std::array<
        double,
        pokemonTypeCount *
        pokemonTypeCount *
        pokemonTypeCount
    > cache{};
    for (int move_type = 0; 
        move_type < to_int(PokemonType::NoType); 
        move_type++
        ) {
        for (int type1 = 0; 
            type1 < pokemonTypeCount; 
            type1++
            ) {
            for (int type2 = 0; 
                type2 < pokemonTypeCount; 
                type2++
                ) {
                const size_t key =
                    get_key(
                        {
                            static_cast<PokemonType>(type1),
                            static_cast<PokemonType>(type2)
                        },
                        static_cast<PokemonType>(move_type)
                    );
                cache[key] =
                    EFFECTIVENESS_TABLE[type1][move_type] *
                    EFFECTIVENESS_TABLE[type2][move_type];
            }
        }
    }
    return cache;
}();

constexpr double get_effectiveness(
    const std::array<PokemonType, 2>& defender_types,
    const PokemonType& move_type
) {
    return EFFECTIVENESS_CACHE[get_key(defender_types, move_type)];
}
