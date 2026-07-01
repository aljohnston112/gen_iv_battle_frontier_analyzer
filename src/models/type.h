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

enum class Effectiveness {
    Zero = 0,
    Quarter = 1,
    Half = 2,
    One = 4,
    Double = 8,
    Quadruple = 16
};

constexpr std::array<
    std::array<Effectiveness, pokemonTypeCount>,
    pokemonTypeCount
> EFFECTIVENESS_TABLE = [] {
    std::array<
        std::array<Effectiveness, pokemonTypeCount>,
        pokemonTypeCount
    > table{};
    for (auto& row : table) {
        row.fill(Effectiveness::One);
    }

    table[to_int(PokemonType::Normal)][to_int(PokemonType::Fighting)] =
        Effectiveness::Double;
    table[to_int(PokemonType::Normal)][to_int(PokemonType::Ghost)] =
        Effectiveness::Zero;

    table[to_int(PokemonType::Fire)][to_int(PokemonType::Fire)] =
        Effectiveness::Half;
    table[to_int(PokemonType::Fire)][to_int(PokemonType::Water)] =
        Effectiveness::Double;
    table[to_int(PokemonType::Fire)][to_int(PokemonType::Grass)] =
        Effectiveness::Half;
    table[to_int(PokemonType::Fire)][to_int(PokemonType::Ice)] =
        Effectiveness::Half;
    table[to_int(PokemonType::Fire)][to_int(PokemonType::Ground)] =
        Effectiveness::Double;
    table[to_int(PokemonType::Fire)][to_int(PokemonType::Bug)] =
        Effectiveness::Half;
    table[to_int(PokemonType::Fire)][to_int(PokemonType::Rock)] =
        Effectiveness::Double;
    table[to_int(PokemonType::Fire)][to_int(PokemonType::Steel)] =
        Effectiveness::Half;

    table[to_int(PokemonType::Water)][to_int(PokemonType::Fire)] =
        Effectiveness::Half;
    table[to_int(PokemonType::Water)][to_int(PokemonType::Water)] =
        Effectiveness::Half;
    table[to_int(PokemonType::Water)][to_int(PokemonType::Electric)] =
        Effectiveness::Double;
    table[to_int(PokemonType::Water)][to_int(PokemonType::Grass)] =
        Effectiveness::Double;
    table[to_int(PokemonType::Water)][to_int(PokemonType::Ice)] =
        Effectiveness::Half;
    table[to_int(PokemonType::Water)][to_int(PokemonType::Steel)] =
        Effectiveness::Half;

    table[to_int(PokemonType::Electric)][to_int(PokemonType::Electric)] =
        Effectiveness::Half;
    table[to_int(PokemonType::Electric)][to_int(PokemonType::Ground)] =
        Effectiveness::Double;
    table[to_int(PokemonType::Electric)][to_int(PokemonType::Flying)] =
        Effectiveness::Half;
    table[to_int(PokemonType::Electric)][to_int(PokemonType::Steel)] =
        Effectiveness::Half;

    table[to_int(PokemonType::Grass)][to_int(PokemonType::Fire)] =
        Effectiveness::Double;
    table[to_int(PokemonType::Grass)][to_int(PokemonType::Water)] =
        Effectiveness::Half;
    table[to_int(PokemonType::Grass)][to_int(PokemonType::Electric)] =
        Effectiveness::Half;
    table[to_int(PokemonType::Grass)][to_int(PokemonType::Grass)] =
        Effectiveness::Half;
    table[to_int(PokemonType::Grass)][to_int(PokemonType::Ice)] =
        Effectiveness::Double;
    table[to_int(PokemonType::Grass)][to_int(PokemonType::Poison)] =
        Effectiveness::Double;
    table[to_int(PokemonType::Grass)][to_int(PokemonType::Ground)] =
        Effectiveness::Half;
    table[to_int(PokemonType::Grass)][to_int(PokemonType::Flying)] =
        Effectiveness::Double;
    table[to_int(PokemonType::Grass)][to_int(PokemonType::Bug)] =
        Effectiveness::Double;

    table[to_int(PokemonType::Ice)][to_int(PokemonType::Fire)] =
        Effectiveness::Double;
    table[to_int(PokemonType::Ice)][to_int(PokemonType::Ice)] =
        Effectiveness::Half;
    table[to_int(PokemonType::Ice)][to_int(PokemonType::Fighting)] =
        Effectiveness::Double;
    table[to_int(PokemonType::Ice)][to_int(PokemonType::Rock)] =
        Effectiveness::Double;
    table[to_int(PokemonType::Ice)][to_int(PokemonType::Steel)] =
        Effectiveness::Double;

    table[to_int(PokemonType::Fighting)][to_int(PokemonType::Flying)] =
        Effectiveness::Double;
    table[to_int(PokemonType::Fighting)][to_int(PokemonType::Psychic)] =
        Effectiveness::Double;
    table[to_int(PokemonType::Fighting)][to_int(PokemonType::Bug)] =
        Effectiveness::Half;
    table[to_int(PokemonType::Fighting)][to_int(PokemonType::Rock)] =
        Effectiveness::Half;
    table[to_int(PokemonType::Fighting)][to_int(PokemonType::Dark)] =
        Effectiveness::Half;

    table[to_int(PokemonType::Poison)][to_int(PokemonType::Grass)] =
        Effectiveness::Half;
    table[to_int(PokemonType::Poison)][to_int(PokemonType::Fighting)] =
        Effectiveness::Half;
    table[to_int(PokemonType::Poison)][to_int(PokemonType::Poison)] =
        Effectiveness::Half;
    table[to_int(PokemonType::Poison)][to_int(PokemonType::Ground)] =
        Effectiveness::Double;
    table[to_int(PokemonType::Poison)][to_int(PokemonType::Psychic)] =
        Effectiveness::Double;
    table[to_int(PokemonType::Poison)][to_int(PokemonType::Bug)] =
        Effectiveness::Half;

    table[to_int(PokemonType::Ground)][to_int(PokemonType::Water)] =
        Effectiveness::Double;
    table[to_int(PokemonType::Ground)][to_int(PokemonType::Electric)] =
        Effectiveness::Zero;
    table[to_int(PokemonType::Ground)][to_int(PokemonType::Grass)] =
        Effectiveness::Double;
    table[to_int(PokemonType::Ground)][to_int(PokemonType::Ice)] =
        Effectiveness::Double;
    table[to_int(PokemonType::Ground)][to_int(PokemonType::Poison)] =
        Effectiveness::Half;
    table[to_int(PokemonType::Ground)][to_int(PokemonType::Rock)] =
        Effectiveness::Half;

    table[to_int(PokemonType::Flying)][to_int(PokemonType::Electric)] =
        Effectiveness::Double;
    table[to_int(PokemonType::Flying)][to_int(PokemonType::Grass)] =
        Effectiveness::Half;
    table[to_int(PokemonType::Flying)][to_int(PokemonType::Ice)] =
        Effectiveness::Double;
    table[to_int(PokemonType::Flying)][to_int(PokemonType::Fighting)] =
        Effectiveness::Half;
    table[to_int(PokemonType::Flying)][to_int(PokemonType::Ground)] =
        Effectiveness::Zero;
    table[to_int(PokemonType::Flying)][to_int(PokemonType::Bug)] =
        Effectiveness::Half;
    table[to_int(PokemonType::Flying)][to_int(PokemonType::Rock)] =
        Effectiveness::Double;

    table[to_int(PokemonType::Psychic)][to_int(PokemonType::Fighting)] =
        Effectiveness::Half;
    table[to_int(PokemonType::Psychic)][to_int(PokemonType::Psychic)] =
        Effectiveness::Half;
    table[to_int(PokemonType::Psychic)][to_int(PokemonType::Bug)] =
        Effectiveness::Double;
    table[to_int(PokemonType::Psychic)][to_int(PokemonType::Ghost)] =
        Effectiveness::Double;
    table[to_int(PokemonType::Psychic)][to_int(PokemonType::Dark)] =
        Effectiveness::Double;

    table[to_int(PokemonType::Bug)][to_int(PokemonType::Fire)] =
        Effectiveness::Double;
    table[to_int(PokemonType::Bug)][to_int(PokemonType::Grass)] =
        Effectiveness::Half;
    table[to_int(PokemonType::Bug)][to_int(PokemonType::Fighting)] =
        Effectiveness::Half;
    table[to_int(PokemonType::Bug)][to_int(PokemonType::Ground)] =
        Effectiveness::Half;
    table[to_int(PokemonType::Bug)][to_int(PokemonType::Flying)] =
        Effectiveness::Double;
    table[to_int(PokemonType::Bug)][to_int(PokemonType::Rock)] =
        Effectiveness::Double;

    table[to_int(PokemonType::Rock)][to_int(PokemonType::Normal)] =
        Effectiveness::Half;
    table[to_int(PokemonType::Rock)][to_int(PokemonType::Fire)] =
        Effectiveness::Half;
    table[to_int(PokemonType::Rock)][to_int(PokemonType::Water)] =
        Effectiveness::Double;
    table[to_int(PokemonType::Rock)][to_int(PokemonType::Grass)] =
        Effectiveness::Double;
    table[to_int(PokemonType::Rock)][to_int(PokemonType::Fighting)] =
        Effectiveness::Double;
    table[to_int(PokemonType::Rock)][to_int(PokemonType::Poison)] =
        Effectiveness::Half;
    table[to_int(PokemonType::Rock)][to_int(PokemonType::Ground)] =
        Effectiveness::Double;
    table[to_int(PokemonType::Rock)][to_int(PokemonType::Flying)] =
        Effectiveness::Half;
    table[to_int(PokemonType::Rock)][to_int(PokemonType::Steel)] =
        Effectiveness::Double;

    table[to_int(PokemonType::Ghost)][to_int(PokemonType::Normal)] =
        Effectiveness::Zero;
    table[to_int(PokemonType::Ghost)][to_int(PokemonType::Fighting)] =
        Effectiveness::Zero;
    table[to_int(PokemonType::Ghost)][to_int(PokemonType::Poison)] =
        Effectiveness::Half;
    table[to_int(PokemonType::Ghost)][to_int(PokemonType::Bug)] =
        Effectiveness::Half;
    table[to_int(PokemonType::Ghost)][to_int(PokemonType::Ghost)] =
        Effectiveness::Double;
    table[to_int(PokemonType::Ghost)][to_int(PokemonType::Dark)] =
        Effectiveness::Double;

    table[to_int(PokemonType::Dragon)][to_int(PokemonType::Fire)] =
        Effectiveness::Half;
    table[to_int(PokemonType::Dragon)][to_int(PokemonType::Water)] =
        Effectiveness::Half;
    table[to_int(PokemonType::Dragon)][to_int(PokemonType::Electric)] =
        Effectiveness::Half;
    table[to_int(PokemonType::Dragon)][to_int(PokemonType::Grass)] =
        Effectiveness::Half;
    table[to_int(PokemonType::Dragon)][to_int(PokemonType::Ice)] =
        Effectiveness::Double;
    table[to_int(PokemonType::Dragon)][to_int(PokemonType::Dragon)] =
        Effectiveness::Double;

    table[to_int(PokemonType::Dark)][to_int(PokemonType::Fighting)] =
        Effectiveness::Double;
    table[to_int(PokemonType::Dark)][to_int(PokemonType::Psychic)] =
        Effectiveness::Zero;
    table[to_int(PokemonType::Dark)][to_int(PokemonType::Bug)] =
        Effectiveness::Double;
    table[to_int(PokemonType::Dark)][to_int(PokemonType::Ghost)] =
        Effectiveness::Half;
    table[to_int(PokemonType::Dark)][to_int(PokemonType::Dark)] =
        Effectiveness::Half;

    table[to_int(PokemonType::Steel)][to_int(PokemonType::Normal)] =
        Effectiveness::Half;
    table[to_int(PokemonType::Steel)][to_int(PokemonType::Fire)] =
        Effectiveness::Double;
    table[to_int(PokemonType::Steel)][to_int(PokemonType::Grass)] =
        Effectiveness::Half;
    table[to_int(PokemonType::Steel)][to_int(PokemonType::Ice)] =
        Effectiveness::Half;
    table[to_int(PokemonType::Steel)][to_int(PokemonType::Fighting)] =
        Effectiveness::Double;
    table[to_int(PokemonType::Steel)][to_int(PokemonType::Poison)] =
        Effectiveness::Zero;
    table[to_int(PokemonType::Steel)][to_int(PokemonType::Ground)] =
        Effectiveness::Double;
    table[to_int(PokemonType::Steel)][to_int(PokemonType::Flying)] =
        Effectiveness::Half;
    table[to_int(PokemonType::Steel)][to_int(PokemonType::Psychic)] =
        Effectiveness::Half;
    table[to_int(PokemonType::Steel)][to_int(PokemonType::Bug)] =
        Effectiveness::Half;
    table[to_int(PokemonType::Steel)][to_int(PokemonType::Rock)] =
        Effectiveness::Half;
    table[to_int(PokemonType::Steel)][to_int(PokemonType::Ghost)] =
        Effectiveness::Half;
    table[to_int(PokemonType::Steel)][to_int(PokemonType::Dragon)] =
        Effectiveness::Half;
    table[to_int(PokemonType::Steel)][to_int(PokemonType::Dark)] =
        Effectiveness::Half;
    table[to_int(PokemonType::Steel)][to_int(PokemonType::Steel)] =
        Effectiveness::Half;

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
        uint16_t,
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

                auto effectiveness1 = EFFECTIVENESS_TABLE[type1][move_type];
                auto effectiveness2 = EFFECTIVENESS_TABLE[type2][move_type];

                cache[key] =
                    static_cast<uint16_t>(effectiveness1) *
                    static_cast<uint16_t>(effectiveness2);
            }
        }
    }
    return cache;
}();

constexpr uint16_t get_effectiveness(
    const std::array<PokemonType, 2>& defender_types,
    const PokemonType& move_type
) {
    return EFFECTIVENESS_CACHE[get_key(defender_types, move_type)];
}
