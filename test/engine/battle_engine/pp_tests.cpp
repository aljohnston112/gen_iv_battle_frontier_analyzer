#include "battle_engine.h"

#include "battle_state.h"
#include "../mocks.h"
#include "gtest/gtest.h"

TEST(Engine, PPLossTriggersStruggle) {
    BattleState battle_state{
        PokemonState{&Cresselia},
        PokemonState{&Cresselia}
    };

    const auto player_moves = battle_state.player.get_moves();
    for (const auto move : player_moves) {
        battle_state.player.clear_power_points(move);
    }

    EXPECT_EQ(
        Move::Struggle,
        choose_move_against_defender(
            OpponentOptimizedKnowledgePolicy{},
            FalseRNGPolicy{},
            battle_state,
            battle_state.player,
            battle_state.opponent,
            Who::Player
        )
    );
}

