#include "../mocks.h"
#include "../test_policies.h"

#include "move_execution.h"
#include "policies.h"

#include "gtest/gtest.h"

TEST(BattleEngine, FalseRollDoesNotCauseSleep) {
    auto defender = PokemonState{&Cresselia_7_4};

    constexpr PolicyContainer<
        HighRandomSleepEffectPolicy,
        NeverSleepRNGPolicy
    > policy_container{};

    roll_sleep(
        policy_container,
        defender,
        Who::Player,
        100
    );
    EXPECT_FALSE(defender.has_status_with_stage(StatusWithStage::Asleep));
}

TEST(BattleEngine, TrueRollDoesCauseSleep) {
    auto defender = PokemonState{&Cresselia_7_4};

    constexpr PolicyContainer<
        HighRandomSleepEffectPolicy,
        AlwaysSleepRNGPolicy
    > policy_container{};

    roll_sleep(
        policy_container,
        defender,
        Who::Player,
        0
    );
    EXPECT_TRUE(defender.has_status_with_stage(StatusWithStage::Asleep));
}

TEST(BattleEngine, BeingAsleepPreventsAttacking) {
    BattleState battle_state{
        PokemonState{&Cresselia_7_4},
        PokemonState{&Cresselia_7_4}
    };

    roll_sleep(
        ALWAYS_SLEEP_HIGH_RANDOM_SLEEP_POLICY_CONTAINER,
        battle_state.player,
        Who::Player,
        0
    );
    EXPECT_TRUE(
        battle_state.player.has_status_with_stage(StatusWithStage::Asleep)
    );

    EXPECT_EQ(
        0,
        execute_move(
            ALWAYS_SLEEP_HIGH_RANDOM_SLEEP_POLICY_CONTAINER,
            battle_state,
            Who::Player,
            Move::Psychic
        )
    );

    EXPECT_TRUE(
        battle_state.player.has_status_with_stage(StatusWithStage::Asleep)
    );
}

TEST(BattleEngine, SleepEndsOnCorrectTurn) {
    BattleState battle_state{
        PokemonState{&Cresselia_7_4},
        PokemonState{&Cresselia_7_4}
    };

    roll_sleep(
        ALWAYS_SLEEP_LOW_RANDOM_SLEEP_POLICY_CONTAINER,
        battle_state.player,
        Who::Player,
        0
    );
    EXPECT_TRUE(
        battle_state.player.has_status_with_stage(StatusWithStage::Asleep)
    );

    EXPECT_EQ(
        0,
        execute_move(
            ALWAYS_SLEEP_LOW_RANDOM_SLEEP_POLICY_CONTAINER,
            battle_state,
            Who::Player,
            Move::Psychic
        )
    );
    battle_state.player.apply_end_of_turn();

    EXPECT_TRUE(
        battle_state.player.has_status_with_stage(StatusWithStage::Asleep)
    );

    EXPECT_EQ(
        0,
        execute_move(
            ALWAYS_SLEEP_LOW_RANDOM_SLEEP_POLICY_CONTAINER,
            battle_state,
            Who::Player,
            Move::Psychic
        )
    );
    battle_state.player.apply_end_of_turn();

    EXPECT_FALSE(
        battle_state.player.has_status_with_stage(StatusWithStage::Asleep)
    );

    EXPECT_NE(
        0,
        execute_move(
            ALWAYS_SLEEP_LOW_RANDOM_SLEEP_POLICY_CONTAINER,
            battle_state,
            Who::Player,
            Move::Psychic
        )
    );
}


TEST(BattleEngine, ChestoBerryPreventsSleepAndIsConsumed) {
    auto defender = PokemonState{&Regirock_7_3};

    constexpr PolicyContainer<
        HighRandomSleepEffectPolicy,
        AlwaysSleepRNGPolicy
    > policy_container{};

    roll_sleep(
        policy_container,
        defender,
        Who::Player,
        0
    );
    EXPECT_FALSE(defender.has_status_with_stage(StatusWithStage::Asleep));
    EXPECT_EQ(Item::NoItem, defender.get_current_item_for_effect());
}