#pragma once

enum PokemonType {
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

inline const std::unordered_map<std::string, PokemonType> STRING_TO_TYPE_MAP{
    {"normal", Normal},
    {"fighting", Fighting},
    {"flying", Flying},
    {"poison", Poison},
    {"ground", Ground},
    {"rock", Rock},
    {"bug", Bug},
    {"ghost", Ghost},
    {"steel", Steel},
    {"fire", Fire},
    {"water", Water},
    {"grass", Grass},
    {"electric", Electric},
    {"psychic", Psychic},
    {"ice", Ice},
    {"dragon", Dragon},
    {"dark", Dark}
};

constexpr double not_effective = 0.0;
constexpr double not_very_effective = 0.5;
constexpr double super_effective = 2.0;

constexpr std::array<
    std::array<double, PokemonTypeCount>,
    PokemonTypeCount
> EFFECTIVENESS_TABLE = [] {
    std::array<std::array<double, PokemonTypeCount>, PokemonTypeCount> table{};
    for (auto& row : table) {
        row.fill(1.0);
    }

    table[Normal][Fighting] = super_effective;
    table[Normal][Ghost] = not_effective;

    table[Fire][Fire] = not_very_effective;
    table[Fire][Water] = super_effective;
    table[Fire][Grass] = not_very_effective;
    table[Fire][Ice] = not_very_effective;
    table[Fire][Ground] = super_effective;
    table[Fire][Bug] = not_very_effective;
    table[Fire][Rock] = super_effective;
    table[Fire][Steel] = not_very_effective;

    table[Water][Fire] = not_very_effective;
    table[Water][Water] = not_very_effective;
    table[Water][Electric] = super_effective;
    table[Water][Grass] = super_effective;
    table[Water][Ice] = not_very_effective;
    table[Water][Steel] = not_very_effective;

    table[Electric][Electric] = not_very_effective;
    table[Electric][Ground] = super_effective;
    table[Electric][Flying] = not_very_effective;
    table[Electric][Steel] = not_very_effective;

    table[Grass][Fire] = super_effective;
    table[Grass][Water] = not_very_effective;
    table[Grass][Electric] = not_very_effective;
    table[Grass][Grass] = not_very_effective;
    table[Grass][Ice] = super_effective;
    table[Grass][Poison] = super_effective;
    table[Grass][Ground] = not_very_effective;
    table[Grass][Flying] = super_effective;
    table[Grass][Bug] = super_effective;

    table[Ice][Fire] = super_effective;
    table[Ice][Ice] = not_very_effective;
    table[Ice][Fighting] = super_effective;
    table[Ice][Rock] = super_effective;
    table[Ice][Steel] = super_effective;

    table[Fighting][Flying] = super_effective;
    table[Fighting][Psychic] = super_effective;
    table[Fighting][Bug] = not_very_effective;
    table[Fighting][Rock] = not_very_effective;
    table[Fighting][Dark] = not_very_effective;

    table[Poison][Grass] = not_very_effective;
    table[Poison][Fighting] = not_very_effective;
    table[Poison][Poison] = not_very_effective;
    table[Poison][Ground] = super_effective;
    table[Poison][Psychic] = super_effective;
    table[Poison][Bug] = not_very_effective;

    table[Ground][Water] = super_effective;
    table[Ground][Electric] = not_effective;
    table[Ground][Grass] = super_effective;
    table[Ground][Ice] = super_effective;
    table[Ground][Poison] = not_very_effective;
    table[Ground][Rock] = not_very_effective;

    table[Flying][Electric] = super_effective;
    table[Flying][Grass] = not_very_effective;
    table[Flying][Ice] = super_effective;
    table[Flying][Fighting] = not_very_effective;
    table[Flying][Ground] = not_effective;
    table[Flying][Bug] = not_very_effective;
    table[Flying][Rock] = super_effective;

    table[Psychic][Fighting] = not_very_effective;
    table[Psychic][Psychic] = not_very_effective;
    table[Psychic][Bug] = super_effective;
    table[Psychic][Ghost] = super_effective;
    table[Psychic][Dark] = super_effective;

    table[Bug][Fire] = super_effective;
    table[Bug][Grass] = not_very_effective;
    table[Bug][Fighting] = not_very_effective;
    table[Bug][Ground] = not_very_effective;
    table[Bug][Flying] = super_effective;
    table[Bug][Rock] = super_effective;

    table[Rock][Normal] = not_very_effective;
    table[Rock][Fire] = not_very_effective;
    table[Rock][Water] = super_effective;
    table[Rock][Grass] = super_effective;
    table[Rock][Fighting] = super_effective;
    table[Rock][Poison] = not_very_effective;
    table[Rock][Ground] = super_effective;
    table[Rock][Flying] = not_very_effective;
    table[Rock][Steel] = super_effective;

    table[Ghost][Normal] = not_effective;
    table[Ghost][Fighting] = not_effective;
    table[Ghost][Poison] = not_very_effective;
    table[Ghost][Bug] = not_very_effective;
    table[Ghost][Ghost] = super_effective;
    table[Ghost][Dark] = super_effective;

    table[Dragon][Fire] = not_very_effective;
    table[Dragon][Water] = not_very_effective;
    table[Dragon][Electric] = not_very_effective;
    table[Dragon][Grass] = not_very_effective;
    table[Dragon][Ice] = super_effective;
    table[Dragon][Dragon] = super_effective;

    table[Dark][Fighting] = super_effective;
    table[Dark][Psychic] = not_effective;
    table[Dark][Bug] = super_effective;
    table[Dark][Ghost] = not_very_effective;
    table[Dark][Dark] = not_very_effective;

    table[Steel][Normal] = not_very_effective;
    table[Steel][Fire] = super_effective;
    table[Steel][Grass] = not_very_effective;
    table[Steel][Ice] = not_very_effective;
    table[Steel][Fighting] = super_effective;
    table[Steel][Poison] = not_effective;
    table[Steel][Ground] = super_effective;
    table[Steel][Flying] = not_very_effective;
    table[Steel][Psychic] = not_very_effective;
    table[Steel][Bug] = not_very_effective;
    table[Steel][Rock] = not_very_effective;
    table[Steel][Ghost] = not_very_effective;
    table[Steel][Dragon] = not_very_effective;
    table[Steel][Dark] = not_very_effective;
    table[Steel][Steel] = not_very_effective;

    return table;
}();

constexpr size_t get_key(
    const std::array<PokemonType, 2>& defender_types,
    const PokemonType& move_type) {
    return move_type *
        PokemonTypeCount *
        PokemonTypeCount +
        defender_types[0] * PokemonTypeCount +
        defender_types[1];
}

constexpr auto EFFECTIVENESS_CACHE = [] {
    std::array<
        double,
        PokemonTypeCount *
        PokemonTypeCount *
        PokemonTypeCount
    > cache{};
    for (int move_type = 0; move_type < NoType; move_type++) {
        for (int type1 = 0; type1 < PokemonTypeCount; type1++) {
            for (int type2 = 0; type2 < PokemonTypeCount; type2++) {
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
