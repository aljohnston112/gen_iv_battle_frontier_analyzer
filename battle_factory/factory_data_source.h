#pragma once

#include <unordered_map>

#include "../external/simdjson.h"

#include "../pokemon.h"
#include "../move.h"
#include "../nature.h"
#include "../type.h"

struct BattleFactoryPokemon {
    std::string name;
    std::string unique_id;
    Nature nature;
    std::array<PokemonType, 2> types;
    std::string item;
    std::vector<Move> moves;
    uint8_t set_number;
    std::array<uint16_t, static_cast<size_t>(Stat::NO_STAT)> effort_values;
};

inline std::unordered_map<std::string, BaseStats>
parse_base_stats_file(const char* path);

inline std::unordered_map<std::string, BattleFactoryPokemon>
parse_battle_factory_file(const char* path);

std::vector<CustomPokemon> get_all_custom_batle_factory_pokemon();
