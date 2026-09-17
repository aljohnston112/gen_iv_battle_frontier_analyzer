#include "../mocks.h"
#include "battle_state.h"


#include "gtest/gtest.h"

TEST(BattleState, PPLossTriggersStruggle) {
    BattleState battle_state{
        PokemonState{&Cresselia_7_4},
        PokemonState{&Cresselia_7_4}
    };

    const auto player_moves =
        battle_state.player.get_moves(true);
    for (const auto move : player_moves) {
        battle_state.player.clear_power_points(move);
    }

    const auto moves =
        battle_state.player.get_moves(true);
    EXPECT_EQ(
        1,
        moves.size()
    );
    EXPECT_EQ(
        Move::Struggle,
        moves[0]
    );
}
