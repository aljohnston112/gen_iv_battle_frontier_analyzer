#include "battle_state.h"
#include "move_execution.h"

#include "../mocks.h"
#include "../test_policies.h"

#include "gtest/gtest.h"

TEST(MoveExecution, HyperBeamRequiresRechargeTurn) {
    BattleState battle_state{
        PokemonState{&Entei_7_3},
        PokemonState{&Suicune_7_3}
    };
    const int8_t initial_power_points =
        battle_state.player.get_power_points(Move::HyperBeam);
    const uint16_t initial_hp =
        battle_state.opponent.get_current_stat(Stat::Health);
    const uint16_t damage =
        execute_move(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state,
            Who::Player,
            Move::HyperBeam
        );

    EXPECT_LT(0, damage);
    EXPECT_TRUE(
        battle_state.player.has_status_with_stage(
            StatusWithStage::Recharging
        )
    );
    EXPECT_EQ(
        initial_hp - damage,
        battle_state.opponent.get_current_stat(Stat::Health)
    );
    EXPECT_EQ(
        initial_power_points - 2,
        battle_state.player.get_power_points(Move::HyperBeam)
    );
    EXPECT_EQ(
        0,
        execute_move(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state,
            Who::Player,
            Move::HyperBeam
        )
    );
    EXPECT_FALSE(
        battle_state.player.has_status_with_stage(
            StatusWithStage::Recharging
        )
    );
    EXPECT_EQ(
        initial_hp - damage,
        battle_state.opponent.get_current_stat(Stat::Health)
    );
    EXPECT_EQ(
        initial_power_points - 2,
        battle_state.player.get_power_points(Move::HyperBeam)
    );
}

TEST(MoveExecution, HyperBeamWillNotRequireARechargeTurnOnMiss) {
    BattleState battle_state{
        PokemonState{&Entei_7_3},
        PokemonState{&Suicune_7_3}
    };
    const int8_t initial_power_points =
        battle_state.player.get_power_points(Move::HyperBeam);
    const uint16_t initial_hp =
        battle_state.opponent.get_current_stat(Stat::Health);
    const uint16_t damage =
        execute_move(
            ALWAYS_MISS_POLICY_CONTAINER,
            battle_state,
            Who::Player,
            Move::HyperBeam
        );

    EXPECT_EQ(0, damage);
    EXPECT_FALSE(
        battle_state.player.has_status_with_stage(
            StatusWithStage::Recharging
        )
    );
    EXPECT_EQ(
        initial_hp,
        battle_state.opponent.get_current_stat(Stat::Health)
    );
    EXPECT_EQ(
        initial_power_points - 2,
        battle_state.player.get_power_points(Move::HyperBeam)
    );
}

TEST(
    MoveExecution,
    HyperBeamRequiresRechargeTurnAfterRechargeTurnIsInterruptedByFreeze
) {
    BattleState battle_state{
        PokemonState{&Entei_7_3},
        PokemonState{&Suicune_7_3}
    };
    const int8_t initial_power_points =
        battle_state.player.get_power_points(Move::HyperBeam);
    const uint16_t initial_hp =
        battle_state.opponent.get_current_stat(Stat::Health);
    const uint16_t damage =
        execute_move(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state,
            Who::Player,
            Move::HyperBeam
        );

    EXPECT_LT(0, damage);
    EXPECT_TRUE(
        battle_state.player.has_status_with_stage(
            StatusWithStage::Recharging
        )
    );
    EXPECT_EQ(
        initial_hp - damage,
        battle_state.opponent.get_current_stat(Stat::Health)
    );
    EXPECT_EQ(
        initial_power_points - 2,
        battle_state.player.get_power_points(Move::HyperBeam)
    );

    battle_state.player.try_set_status_condition(StatusCondition::Freeze);

    EXPECT_EQ(
        0,
        execute_move(
            ALWAYS_FREEZE_POLICY_CONTAINER,
            battle_state,
            Who::Player,
            Move::HyperBeam
        )
    );
    EXPECT_TRUE(
        battle_state.player.has_status_with_stage(
            StatusWithStage::Recharging
        )
    );
    EXPECT_EQ(
        initial_hp - damage,
        battle_state.opponent.get_current_stat(Stat::Health)
    );
    EXPECT_EQ(
        initial_power_points - 2,
        battle_state.player.get_power_points(Move::HyperBeam)
    );

    EXPECT_EQ(
        0,
        execute_move(
            NEVER_FREEZE_POLICY_CONTAINER,
            battle_state,
            Who::Player,
            Move::FireBlast
        )
    );
    EXPECT_FALSE(
        battle_state.player.has_status_with_stage(
            StatusWithStage::Recharging
        )
    );
    EXPECT_EQ(
        initial_power_points - 2,
        battle_state.player.get_power_points(Move::HyperBeam)
    );
}

TEST(
    MoveExecution,
    ConfusionEndsOnCorrectTurnWhenRechargeInterruptsCountdown
) {
    BattleState battle_state{
        PokemonState{&Entei_7_3},
        PokemonState{&Cresselia_7_4}
    };
    const uint16_t health_before =
        battle_state.player.get_current_stat(Stat::Health);
    battle_state.player.set_status_with_stage(
        StatusWithStage::Confused,
        2
    );

    EXPECT_TRUE(
        battle_state.player.has_status_with_stage(StatusWithStage::Confused)
    );
    EXPECT_LT(
        0,
        execute_move(
            NEVER_CONFUSE_POLICY_CONTAINER,
            battle_state,
            Who::Player,
            Move::HyperBeam
        )
    );

    battle_state.player.apply_end_of_turn();

    EXPECT_TRUE(
        battle_state.player.has_status_with_stage(StatusWithStage::Confused)
    );
    EXPECT_EQ(
        0,
        execute_move(
            ALWAYS_CONFUSE_LOW_RANDOM_CONFUSION_POLICY_CONTAINER,
            battle_state,
            Who::Player,
            Move::HyperBeam
        )
    );
    EXPECT_EQ(
        health_before,
        battle_state.player.get_current_stat(Stat::Health)
    );

    battle_state.player.apply_end_of_turn();

    EXPECT_TRUE(
        battle_state.player.has_status_with_stage(StatusWithStage::Confused)
    );
    EXPECT_EQ(
        0,
        execute_move(
            ALWAYS_CONFUSE_LOW_RANDOM_CONFUSION_POLICY_CONTAINER,
            battle_state,
            Who::Player,
            Move::FireBlast
        )
    );
    EXPECT_GT(
        health_before,
        battle_state.player.get_current_stat(Stat::Health)
    );

    battle_state.player.apply_end_of_turn();

    EXPECT_FALSE(
        battle_state.player.has_status_with_stage(StatusWithStage::Confused)
    );
}

TEST(MoveExecution, HyperBeamRechargeTurnInvalidatesLastUsedMove) {
    BattleState battle_state{
        PokemonState{&Entei_7_3},
        PokemonState{&Suicune_7_3}
    };
    const int8_t initial_power_points =
        battle_state.player.get_power_points(Move::HyperBeam);
    const uint16_t initial_hp =
        battle_state.opponent.get_current_stat(Stat::Health);
    const uint16_t damage =
        execute_move(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state,
            Who::Player,
            Move::HyperBeam
        );

    EXPECT_LT(0, damage);
    EXPECT_TRUE(
        battle_state.player.has_status_with_stage(
            StatusWithStage::Recharging
        )
    );
    EXPECT_EQ(
        initial_hp - damage,
        battle_state.opponent.get_current_stat(Stat::Health)
    );
    EXPECT_EQ(
        initial_power_points - 2,
        battle_state.player.get_power_points(Move::HyperBeam)
    );
    EXPECT_EQ(
        Move::HyperBeam,
        battle_state.player.get_last_used_move()
    );
    EXPECT_EQ(
        Move::HyperBeam,
        battle_state.get_last_used_move()
    );
    EXPECT_EQ(
        0,
        execute_move(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state,
            Who::Player,
            Move::HyperBeam
        )
    );
    EXPECT_FALSE(
        battle_state.player.has_status_with_stage(
            StatusWithStage::Recharging
        )
    );
    EXPECT_EQ(
        initial_hp - damage,
        battle_state.opponent.get_current_stat(Stat::Health)
    );
    EXPECT_EQ(
        initial_power_points - 2,
        battle_state.player.get_power_points(Move::HyperBeam)
    );
    EXPECT_EQ(
        Move::MoveCount,
        battle_state.player.get_last_used_move()
    );
    EXPECT_EQ(
        Move::MoveCount,
        battle_state.get_last_used_move()
    );
}
