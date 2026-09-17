#include "../mocks.h"
#include "../test_policies.h"

#include "battle_state.h"
#include "move_execution.h"

#include "gtest/gtest.h"

TEST(MoveExecution, DefenderWithPressureMakesAttackerLoseOneMorePowerPoint) {
    BattleState battle_state{
        PokemonState{&Suicune_7_3},
        PokemonState{&Cresselia_7_4}
    };
    const uint16_t power_points_before =
        battle_state.opponent.get_power_points(Move::Psychic);
    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state,
        Who::Opponent,
        Move::Psychic
    );

    EXPECT_EQ(
        power_points_before - 2,
        battle_state.opponent.get_power_points(Move::Psychic)
    );
}

TEST(
    MoveExecution,
    DefenderWithPressureDoesNotMakeAttackerLoseOneMorePowerPointWhenAttackerUsesCurseAndDoesNotHaveAGhostTyping
) {
    BattleState battle_state{
        PokemonState{&Suicune_7_3},
        PokemonState{&Regirock_7_3}
    };
    const uint16_t power_points_before =
        battle_state.opponent.get_power_points(Move::Curse);
    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state,
        Who::Opponent,
        Move::Curse
    );

    EXPECT_EQ(
        power_points_before - 1,
        battle_state.opponent.get_power_points(Move::Curse)
    );
}

TEST(
    MoveExecution,
    DefenderWithPressureMakesAttackerLoseOneMorePowerPointWhenAttackerUsesCurseAndHasAGhostTyping
) {
    BattleState battle_state{
        PokemonState{&Suicune_7_3},
        PokemonState{&Regirock_7_3}
    };
    battle_state.opponent.set_type(PokemonType::Ghost);
    const uint16_t power_points_before =
        battle_state.opponent.get_power_points(Move::Curse);
    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state,
        Who::Opponent,
        Move::Curse
    );

    EXPECT_EQ(
        power_points_before - 2,
        battle_state.opponent.get_power_points(Move::Curse)
    );
}
