#include "../mocks.h"
#include "../test_policies.h"

#include <gtest/gtest.h>

#include "move_execution.h"

TEST(MoveExecution, LastUsedMoveIsUpdatedInPokemonState) {
    BattleState battle_state{
        PokemonState{&Regigigas_7_3},
        PokemonState{&Heatran_7_3}
    };

    EXPECT_EQ(Move::MoveCount, battle_state.player.get_last_used_move());

    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state,
        Who::Player,
        Move::Thunderbolt
    );

    EXPECT_EQ(Move::Thunderbolt, battle_state.player.get_last_used_move());
}

TEST(MoveExecution, LastUsedMoveIsUpdatedInBattleState) {
    BattleState battle_state{
        PokemonState{&Regigigas_7_3},
        PokemonState{&Heatran_7_3}
    };

    EXPECT_EQ(Move::MoveCount, battle_state.get_last_used_move());

    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state,
        Who::Player,
        Move::Thunderbolt
    );

    EXPECT_EQ(Move::Thunderbolt, battle_state.get_last_used_move());

    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state,
        Who::Opponent,
        Move::Flamethrower
    );

    EXPECT_EQ(Move::Flamethrower, battle_state.get_last_used_move());
}

TEST(MoveExecution, LastUsedMoveIsUpdatedInPokemonStateWhenMoveMisses) {
    BattleState battle_state{
        PokemonState{&Regigigas_7_3},
        PokemonState{&Heatran_7_3}
    };

    EXPECT_EQ(Move::MoveCount, battle_state.player.get_last_used_move());

    execute_move(
        ALWAYS_MISS_POLICY_CONTAINER,
        battle_state,
        Who::Player,
        Move::Thunderbolt
    );

    EXPECT_EQ(Move::Thunderbolt, battle_state.player.get_last_used_move());
}

TEST(MoveExecution, LastUsedMoveIsUpdatedInBattleStateWhenMoveMisses) {
    BattleState battle_state{
        PokemonState{&Regigigas_7_3},
        PokemonState{&Heatran_7_3}
    };

    EXPECT_EQ(Move::MoveCount, battle_state.get_last_used_move());

    execute_move(
        ALWAYS_MISS_POLICY_CONTAINER,
        battle_state,
        Who::Player,
        Move::Thunderbolt
    );

    EXPECT_EQ(Move::Thunderbolt, battle_state.get_last_used_move());

    execute_move(
        ALWAYS_MISS_POLICY_CONTAINER,
        battle_state,
        Who::Opponent,
        Move::Flamethrower
    );

    EXPECT_EQ(Move::Flamethrower, battle_state.get_last_used_move());
}

TEST(MoveExecution, LastUsedMoveIsUpdatedInPokemonStateWhenMoveFails) {
    BattleState battle_state{
        PokemonState{&Regirock_7_3},
        PokemonState{&Regirock_7_3}
    };

    EXPECT_EQ(Move::MoveCount, battle_state.player.get_last_used_move());

    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state,
        Who::Player,
        Move::Rest
    );

    EXPECT_EQ(Move::Rest, battle_state.player.get_last_used_move());
}

TEST(MoveExecution, LastUsedMoveIsUpdatedInBattleStateWhenMoveFails) {
    BattleState battle_state{
        PokemonState{&Regirock_7_3},
        PokemonState{&Regirock_7_3}
    };

    EXPECT_EQ(Move::MoveCount, battle_state.get_last_used_move());

    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state,
        Who::Player,
        Move::Rest
    );

    EXPECT_EQ(Move::Rest, battle_state.get_last_used_move());

    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state,
        Who::Opponent,
        Move::Curse
    );

    EXPECT_EQ(Move::Curse, battle_state.get_last_used_move());

    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state,
        Who::Opponent,
        Move::Rest
    );

    EXPECT_EQ(Move::Rest, battle_state.get_last_used_move());
}

TEST(MoveExecution, LastUsedMoveIsInvalidatedInPokemonStateByChargeTurn) {
    BattleState battle_state{
        PokemonState{&Entei_7_3},
        PokemonState{&Heatran_7_3}
    };

    EXPECT_EQ(Move::MoveCount, battle_state.player.get_last_used_move());

    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state,
        Who::Player,
        Move::SolarBeam
    );

    EXPECT_EQ(Move::MoveCount, battle_state.player.get_last_used_move());
}

TEST(MoveExecution, LastUsedMoveIsInvalidatedInBattleStateByChargeTurn) {
    BattleState battle_state{
        PokemonState{&Entei_7_3},
        PokemonState{&Entei_7_3}
    };

    EXPECT_EQ(Move::MoveCount, battle_state.get_last_used_move());

    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state,
        Who::Player,
        Move::SolarBeam
    );

    EXPECT_EQ(Move::MoveCount, battle_state.get_last_used_move());

    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state,
        Who::Player,
        Move::SolarBeam
    );

    EXPECT_EQ(Move::SolarBeam, battle_state.get_last_used_move());

    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state,
        Who::Opponent,
        Move::SolarBeam
    );

    EXPECT_EQ(Move::MoveCount, battle_state.get_last_used_move());
}
