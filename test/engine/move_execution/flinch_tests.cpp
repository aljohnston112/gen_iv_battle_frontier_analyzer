#include "../mocks.h"
#include "../test_policies.h"

#include "move_execution.h"

#include "gtest/gtest.h"

TEST(MoveExecution, FlinchedStatusOnAttackerPreventsItsMove) {
    BattleState battle_state{
        PokemonState{&Heatran_7_3},
        PokemonState{&Heatran_7_3}
    };

    battle_state.player.set_status(Status::Flinched);

    ASSERT_TRUE(battle_state.player.has_status(Status::Flinched));
    ASSERT_EQ(
        0,
        execute_move(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state,
            Who::Player,
            Move::Flamethrower
        )
    );
}

TEST(MoveExecution, FlinchedStatusIsClearedAfterMoveFails) {
    BattleState battle_state{
        PokemonState{&Heatran_7_3},
        PokemonState{&Heatran_7_3}
    };

    battle_state.player.set_status(Status::Flinched);

    ASSERT_TRUE(battle_state.player.has_status(Status::Flinched));

    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state,
        Who::Player,
        Move::Flamethrower
    );

    ASSERT_FALSE(battle_state.player.has_status(Status::Flinched));
}

TEST(MoveExecution, DarkPulseCausesFlinchOnTrueRoll) {
    BattleState battle_state{
        PokemonState{&Heatran_7_3},
        PokemonState{&Heatran_7_3}
    };

    ASSERT_FALSE(battle_state.player.has_status(Status::Flinched));

    execute_move(
        ALWAYS_FLINCH_POLICY_CONTAINER,
        battle_state,
        Who::Opponent,
        Move::DarkPulse
    );

    ASSERT_TRUE(battle_state.player.has_status(Status::Flinched));
}

TEST(MoveExecution, DarkPulseDoesNotCauseFlinchOnFalseRoll) {
    BattleState battle_state{
        PokemonState{&Heatran_7_3},
        PokemonState{&Heatran_7_3}
    };

    ASSERT_FALSE(battle_state.player.has_status(Status::Flinched));

    execute_move(
        NEVER_FLINCH_POLICY_CONTAINER,
        battle_state,
        Who::Opponent,
        Move::DarkPulse
    );

    ASSERT_FALSE(battle_state.player.has_status(Status::Flinched));
}
