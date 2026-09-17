#include "../mocks.h"
#include "../test_policies.h"

#include "gtest/gtest.h"
#include "gmock/gmock-matchers.h"

TEST(BattleState, PlayerHasBlizzrdInMovesInHail) {
    BattleState battle_state{
        PokemonState{&Suicune_7_3},
        PokemonState{&Regigigas_7_3}
    };

    EXPECT_THAT(
        battle_state.player.get_moves(false),
        ::testing::Not(::testing::Contains(Move::Blizzard))
    );

    battle_state.set_weather(Weather::Hail, 5);

    EXPECT_THAT(
        battle_state.player.get_moves(false),
        ::testing::Contains(Move::Blizzard)
    );
}

TEST(BattleState, PlayerDoesNotHaveBlizzrdInMovesAfterHailExpires) {
    BattleState battle_state{
        PokemonState{&Suicune_7_3},
        PokemonState{&Regigigas_7_3}
    };
    battle_state.set_weather(Weather::Hail, 1);
    battle_state.apply_end_of_turn();

    EXPECT_THAT(
        battle_state.player.get_moves(false),
        ::testing::Not(::testing::Contains(Move::Blizzard))
    );
}
