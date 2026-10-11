#include "../test_policies.h"
#include "../mocks.h"

#include "battle_state.h"
#include "move_execution.h"

#include "gtest/gtest.h"

TEST(MoveExecution, ShucaBerryActivatesWhenGroundMoveIsSuperEffective) {
    BattleState battle_state{
        PokemonState{&Entei_7_3},
        PokemonState{&Heatran_7_3}
    };

    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state,
        Who::Opponent,
        Move::EarthPower
    );

    EXPECT_EQ(
        battle_state.player.get_original_stat(Stat::Health) - 85,
        battle_state.player.get_current_stat(Stat::Health)
    );

    EXPECT_EQ(
        Item::NoItem,
        battle_state.player.get_current_item_for_effect()
    );
}

TEST(MoveExecution, ShucaBerryDoesNotActivateWhenMoveIsNotSuperEffective) {
    BattleState battle_state{
        PokemonState{&Entei_7_3},
        PokemonState{&Heatran_7_3}
    };

    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state,
        Who::Opponent,
        Move::DarkPulse
    );

    EXPECT_EQ(
        battle_state.player.get_original_stat(Stat::Health) - 76,
        battle_state.player.get_current_stat(Stat::Health)
    );
    EXPECT_EQ(
        Item::ShucaBerry,
        battle_state.player.get_current_item_for_effect()
    );
}

TEST(
    MoveExecution,
    ShucaBerryDoesNotActivateWhenGroundMoveIsNotSuperEffective
    ) {
    BattleState battle_state{
        PokemonState{&Suicune_7_3},
        PokemonState{&Heatran_7_3}
    };
    battle_state.player.set_item(Item::ShucaBerry);

    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state,
        Who::Opponent,
        Move::EarthPower
    );

    EXPECT_EQ(
        battle_state.player.get_original_stat(Stat::Health) - 60,
        battle_state.player.get_current_stat(Stat::Health)
    );
    EXPECT_EQ(
        Item::ShucaBerry,
        battle_state.player.get_current_item_for_effect()
    );
}
