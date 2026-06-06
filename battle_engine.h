#pragma once
#include <vector>

#include "move.h"

struct MoveResults {
    Move move;
    int damage;
};

struct BattleResultEntry {
    size_t player_index;
    size_t opponent_index;
    bool won;
    std::vector<MoveResults> player_moves;
    std::vector<MoveResults> opponent_moves;
};
