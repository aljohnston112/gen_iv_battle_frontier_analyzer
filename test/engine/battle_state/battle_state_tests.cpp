#include "../mocks.h"
#include "battle_state.h"
#include "move_heuristic.h"
#include "policies.h"

#include "gtest/gtest.h"

TEST(BattleEngine, PPLossTriggersStruggle) {
    BattleState battle_state{
        PokemonState{&Cresselia_7_4},
        PokemonState{&Cresselia_7_4}
    };

    const auto player_moves = battle_state.player.get_moves();
    for (const auto move : player_moves) {
        battle_state.player.clear_power_points(move);
    }

    const auto moves = battle_state.player.get_moves();
    EXPECT_EQ(
        1,
        moves.size()
    );
    EXPECT_EQ(
        Move::Struggle,
        moves[0]
    );
}

TEST(BattleState, WhiteHerbClearsNegativeStatus) {
    auto state = PokemonState{&Latias_7_4};
    state.decrease_stat_stage(Stat::Attack, 1);
    EXPECT_EQ(
        0,
        state.get_stat_stage(Stat::Attack)
    );
    EXPECT_EQ(
        Item::NoItem,
        state.get_current_item_for_effect()
    );
}
