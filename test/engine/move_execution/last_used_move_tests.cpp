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

TEST(MoveExecution, LastUsedMoveIsInvalidatedWhenAttackerFlinches) {
    BattleState battle_state{
        PokemonState{&Regirock_7_3},
        PokemonState{&Regirock_7_3}
    };
    constexpr auto policy_container =
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING;
    execute_move(
        policy_container,
        battle_state,
        Who::Player,
        Move::Curse
    );

    EXPECT_EQ(Move::Curse, battle_state.get_last_used_move());
    EXPECT_EQ(Move::Curse, battle_state.player.get_last_used_move());

    battle_state.player.set_status(Status::Flinched);

    EXPECT_EQ(
        0,
        execute_move(
            policy_container,
            battle_state,
            Who::Player,
            Move::Rest
        )
    );
    EXPECT_EQ(Move::MoveCount, battle_state.get_last_used_move());
    EXPECT_EQ(Move::MoveCount, battle_state.player.get_last_used_move());
}

TEST(MoveExecution, LastUsedMoveIsInvalidatedWhenAttackerIsParalyzed) {
    BattleState battle_state{
        PokemonState{&Regirock_7_3},
        PokemonState{&Regirock_7_3}
    };
    constexpr auto policy_container = ALWAYS_PARALYZE_POLICY_CONTAINER;
    execute_move(
        policy_container,
        battle_state,
        Who::Player,
        Move::Curse
    );

    EXPECT_EQ(Move::Curse, battle_state.get_last_used_move());
    EXPECT_EQ(Move::Curse, battle_state.player.get_last_used_move());

    battle_state.player.try_set_status_condition(StatusCondition::Paralysis);

    EXPECT_TRUE(
        battle_state.player.has_status_condition(StatusCondition::Paralysis)
    );
    EXPECT_EQ(
        0,
        execute_move(
            policy_container,
            battle_state,
            Who::Player,
            Move::Rest
        )
    );
    EXPECT_EQ(Move::MoveCount, battle_state.get_last_used_move());
    EXPECT_EQ(Move::MoveCount, battle_state.player.get_last_used_move());
}

TEST(MoveExecution, LastUsedMoveIsInvalidatedWhenAttackerIsAsleep) {
    BattleState battle_state{
        PokemonState{&Regirock_7_3},
        PokemonState{&Regirock_7_3}
    };
    constexpr auto policy_container =
        ALWAYS_SLEEP_HIGH_RANDOM_SLEEP_POLICY_CONTAINER;
    execute_move(
        policy_container,
        battle_state,
        Who::Player,
        Move::Curse
    );

    EXPECT_EQ(Move::Curse, battle_state.get_last_used_move());
    EXPECT_EQ(Move::Curse, battle_state.player.get_last_used_move());

    // Clear Lum Berry
    battle_state.player.set_status_with_stage(StatusWithStage::Asleep, 5);
    battle_state.player.set_status_with_stage(StatusWithStage::Asleep, 5);

    EXPECT_TRUE(
        battle_state.player.has_status_with_stage(StatusWithStage::Asleep)
    );
    EXPECT_EQ(
        0,
        execute_move(
            policy_container,
            battle_state,
            Who::Player,
            Move::Rest
        )
    );
    EXPECT_EQ(Move::MoveCount, battle_state.get_last_used_move());
    EXPECT_EQ(Move::MoveCount, battle_state.player.get_last_used_move());
}
