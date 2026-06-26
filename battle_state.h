#pragma once

#include "pokemon.h"

class PokemonState {
public:
    const CustomPokemon* pokemon;
    uint16_t current_hp;
    uint16_t current_speed;
    Item current_item;

    explicit PokemonState(const CustomPokemon* pokemon_in)
        : pokemon(pokemon_in),
          current_hp(pokemon_in->get_stat(Stat::HEALTH)),
          current_speed(pokemon_in->get_stat(Stat::SPEED)),
          current_item(pokemon_in->item) {}

    void add_hp(const uint16_t hp_gained) {
        current_hp = std::min(
            pokemon->get_stat(Stat::HEALTH),
            static_cast<uint16_t>(current_hp + hp_gained)
        );
    };
};

enum Weather {
    Sun,
    Rain,
    Sandstorm,
    Hail,
    Fog,
    None
};

class BattleState {
public:
    PokemonState player;
    PokemonState opponent;
    Weather weather;

    BattleState(
        const PokemonState&& player_in,
        const PokemonState&& opponent_in
    ) : player(player_in),
        opponent(opponent_in),
        weather(None) {}
};
