#include "../mocks.h"
#include "../test_policies.h"

#include "gtest/gtest.h"

namespace {
    template <StatusCondition T>
    void lum_berry_clears_status_condition() {
        PokemonState state{&Suicune_7_3};

        ASSERT_EQ(Item::LumBerry, state.get_current_item_for_effect());

        state.try_set_status_condition(T);

        ASSERT_FALSE(state.has_status_condition(T));
        ASSERT_EQ(
            StatusCondition::NoCondition,
            state.get_current_status_condition()
        );
        ASSERT_EQ(Item::NoItem, state.get_current_item_for_effect());
    }
}

TEST(BattleState, LumBerryClearsBurn) {
    lum_berry_clears_status_condition<StatusCondition::Burn>();
}

TEST(BattleState, LumBerryClearsFreeze) {
    lum_berry_clears_status_condition<StatusCondition::Freeze>();
}

TEST(BattleState, LumBerryClearsParalysis) {
    lum_berry_clears_status_condition<StatusCondition::Paralysis>();
}

TEST(BattleState, LumBerryClearsPoison) {
    lum_berry_clears_status_condition<StatusCondition::PoisonStatus>();
}

TEST(BattleState, LumBerryClearsBadPoison) {
    lum_berry_clears_status_condition<StatusCondition::BadlyPoisoned>();
}

namespace {
    template <StatusWithStage T>
    void lum_berry_clears_status_with_stage() {
        PokemonState state{&Suicune_7_3};

        ASSERT_EQ(Item::LumBerry, state.get_current_item_for_effect());

        state.set_status_with_stage(T, 5);

        ASSERT_FALSE(state.has_status_with_stage(T));
        ASSERT_EQ(Item::NoItem, state.get_current_item_for_effect());
    }
}

TEST(BattleState, LumBerryClearsSleep) {
    lum_berry_clears_status_with_stage<StatusWithStage::Asleep>();
}

TEST(BattleState, LumBerryClearsConfusion) {
    lum_berry_clears_status_with_stage<StatusWithStage::Confused>();
}