#include "move_execution.h"
#include "move_heuristic.h"
#include "../mocks.h"
#include "../test_policies.h"

#include "gtest/gtest.h"

TEST(MoveExecution, RestCauseSleepForTwoTurns) {
    BattleState battle_state{
        PokemonState{&Regirock_7_3_NoItem},
        PokemonState{&Cresselia_7_4}
    };
    battle_state.player.add_damage(1);
    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state,
        Who::Player,
        Move::Rest
    );

    EXPECT_TRUE(
        battle_state.player.has_status_with_stage(StatusWithStage::Asleep)
    );

    EXPECT_EQ(
        0,
        execute_move(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state,
            Who::Player,
            Move::HammerArm
        )
    );
    battle_state.player.apply_end_of_turn();

    EXPECT_TRUE(
        battle_state.player.has_status_with_stage(StatusWithStage::Asleep)
    );

    EXPECT_EQ(
        0,
        execute_move(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state,
            Who::Player,
            Move::HammerArm
        )
    );
    battle_state.player.apply_end_of_turn();

    EXPECT_FALSE(
        battle_state.player.has_status_with_stage(StatusWithStage::Asleep)
    );

    EXPECT_NE(
        0,
        execute_move(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state,
            Who::Player,
            Move::HammerArm
        )
    );
}

TEST(MoveExecution, RestMakesHPOfUserFull) {
    BattleState battle_state{
        PokemonState{&Regirock_7_3_NoItem},
        PokemonState{&Cresselia_7_4}
    };
    battle_state.player.add_damage(1);

    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state,
        Who::Player,
        Move::Rest
    );

    EXPECT_TRUE(
        battle_state.player.has_status_with_stage(StatusWithStage::Asleep)
    );

    EXPECT_EQ(
        battle_state.player.get_original_stat(Stat::Health),
        battle_state.player.get_current_stat(Stat::Health)
    );
}

TEST(BattleEngine, RestMakesUserFallAsleepAfterChestoBerryIsConsumed) {
    BattleState battle_state{
        PokemonState{&Regirock_7_3},
        PokemonState{&Cresselia_7_4}
    };

    constexpr PolicyContainer<
        HighRandomSleepEffectPolicy,
        AlwaysSleepRNGPolicy
    > policy_container{};
    roll_sleep(
        policy_container,
        battle_state.player,
        Who::Player,
        0
    );

    EXPECT_FALSE(
        battle_state.player.has_status_with_stage(StatusWithStage::Asleep));
    EXPECT_EQ(Item::NoItem, battle_state.player.get_current_item_for_effect());

    battle_state.player.add_damage(1);

    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state,
        Who::Player,
        Move::Rest
    );

    EXPECT_TRUE(
        battle_state.player.has_status_with_stage(StatusWithStage::Asleep));
}


TEST(MoveExecution, RestClearsPoison) {
    BattleState battle_state{
        PokemonState{&Regirock_7_3_NoItem},
        PokemonState{&Cresselia_7_4}
    };
    battle_state.player.add_damage(1);
    battle_state.player.try_set_status_condition(StatusCondition::PoisonStatus);

    EXPECT_EQ(
        StatusCondition::PoisonStatus,
        battle_state.player.get_current_status_condition()
    );

    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state,
        Who::Player,
        Move::Rest
    );

    EXPECT_TRUE(
        battle_state.player.has_status_with_stage(StatusWithStage::Asleep)
    );

    EXPECT_EQ(
        StatusCondition::NoCondition,
        battle_state.player.get_current_status_condition()
    );
}

TEST(MoveExecution, RestClearsBadPoison) {
    BattleState battle_state{
        PokemonState{&Regirock_7_3_NoItem},
        PokemonState{&Cresselia_7_4}
    };
    battle_state.player.add_damage(1);
    battle_state.player.
                 try_set_status_condition(StatusCondition::BadlyPoisoned);

    EXPECT_EQ(
        StatusCondition::BadlyPoisoned,
        battle_state.player.get_current_status_condition()
    );

    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state,
        Who::Player,
        Move::Rest
    );

    EXPECT_TRUE(
        battle_state.player.has_status_with_stage(StatusWithStage::Asleep)
    );

    EXPECT_EQ(
        StatusCondition::NoCondition,
        battle_state.player.get_current_status_condition()
    );
}

TEST(MoveExecution, RestClearsParalysis) {
    BattleState battle_state{
        PokemonState{&Regirock_7_3_NoItem},
        PokemonState{&Cresselia_7_4}
    };
    battle_state.player.add_damage(1);
    battle_state.player.try_set_status_condition(StatusCondition::Paralysis);

    EXPECT_EQ(
        StatusCondition::Paralysis,
        battle_state.player.get_current_status_condition()
    );

    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state,
        Who::Player,
        Move::Rest
    );

    EXPECT_TRUE(
        battle_state.player.has_status_with_stage(StatusWithStage::Asleep)
    );

    EXPECT_EQ(
        StatusCondition::NoCondition,
        battle_state.player.get_current_status_condition()
    );
}

TEST(MoveExecution, RestClearsBurn) {
    BattleState battle_state{
        PokemonState{&Regirock_7_3_NoItem},
        PokemonState{&Cresselia_7_4}
    };
    battle_state.player.add_damage(1);
    battle_state.player.try_set_status_condition(StatusCondition::Burn);

    EXPECT_EQ(
        StatusCondition::Burn,
        battle_state.player.get_current_status_condition()
    );

    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state,
        Who::Player,
        Move::Rest
    );

    EXPECT_TRUE(
        battle_state.player.has_status_with_stage(StatusWithStage::Asleep)
    );

    EXPECT_EQ(
        StatusCondition::NoCondition,
        battle_state.player.get_current_status_condition()
    );
}

TEST(MoveExecution, RestFailsAtFullHP) {
    BattleState battle_state{
        PokemonState{&Regirock_7_3_NoItem},
        PokemonState{&Cresselia_7_4}
    };

    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state,
        Who::Player,
        Move::Rest
    );

    EXPECT_FALSE(
        battle_state.player.has_status_with_stage(StatusWithStage::Asleep)
    );
}

TEST(MoveExecution, RestFailsIfUproarIsInEffect) {
    BattleState battle_state{
        PokemonState{&Regirock_7_3_NoItem},
        PokemonState{&Cresselia_7_4}
    };
    battle_state.player.add_damage(1);
    battle_state.set_field_status(FieldStatus::UproarActive);

    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state,
        Who::Player,
        Move::Rest
    );

    EXPECT_FALSE(
        battle_state.player.has_status_with_stage(StatusWithStage::Asleep)
    );
}

TEST(MoveExecution, RestFailsIfUserIsHealBlocked) {
    BattleState battle_state{
        PokemonState{&Regirock_7_3_NoItem},
        PokemonState{&Cresselia_7_4}
    };
    battle_state.player.add_damage(1);
    battle_state.player.set_status_with_stage(
        StatusWithStage::HealBlocked,
        5
    );

    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state,
        Who::Player,
        Move::Rest
    );

    EXPECT_FALSE(
        battle_state.player.has_status_with_stage(StatusWithStage::Asleep)
    );
}

TEST(
    MoveExecution,
    StruggleIsUsedWhenRestIsUsedAndUserIsHealBlockedAndOtherMovesDoNotHavePP
) {
    BattleState battle_state{
        PokemonState{&Regirock_7_3_NoItem},
        PokemonState{&Cresselia_7_4}
    };
    battle_state.player.add_damage(1);
    battle_state.player.set_status_with_stage(
        StatusWithStage::HealBlocked,
        5
    );
    const auto moves = battle_state.player.get_moves();
    for (const auto move : moves) {
        if (move != Move::Rest) {
            battle_state.player.clear_power_points(move);
        }
    }

    EXPECT_NE(
        0,
        execute_move(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state,
            Who::Player,
            Move::Rest
        )
    );

    EXPECT_FALSE(
        battle_state.player.has_status_with_stage(StatusWithStage::Asleep)
    );
}

TEST(MoveExecution, RestWorksWithSafeguardInEffect) {
    BattleState battle_state{
        PokemonState{&Regirock_7_3_NoItem},
        PokemonState{&Cresselia_7_4}
    };
    battle_state.player.add_damage(1);
    battle_state.player.set_status_with_stage(
        StatusWithStage::Safeguarding,
        5
    );

    EXPECT_TRUE(
        battle_state.player.has_status_with_stage(StatusWithStage::Safeguarding)
    );

    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state,
        Who::Player,
        Move::Rest
    );

    EXPECT_TRUE(
        battle_state.player.has_status_with_stage(StatusWithStage::Asleep)
    );
}
