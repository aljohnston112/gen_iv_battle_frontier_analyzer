#pragma once
#include "pokemon.h"

class PokemonState {
public:
    const CustomPokemon* pokemon;
    explicit PokemonState(const CustomPokemon* pokemon)
        : pokemon(pokemon) {}

};

class BattleState {
public:
    BattleState(const PokemonState& player, const PokemonState& opponent)
        : player(player),
          opponent(opponent) {}

private:
    PokemonState player;
    PokemonState opponent;
};


