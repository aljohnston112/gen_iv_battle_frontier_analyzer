#include "../mocks.h"
#include "../test_policies.h"

#include "battle_state.h"
#include "move_execution.h"
#include "serebii_pokemon_data_source.h"

#include "gtest/gtest.h"

TEST(MoveExecution, ThunderBoltParalyzesOnTrueRoll) {
    BattleState battle_state{
        PokemonState{&LatiasNoItem},
        PokemonState{&LatiasNoItem}
    };

    execute_move(
        ALWAYS_PARALYZE_POLICY_CONTAINER,
        battle_state,
        Who::Player,
        Move::Thunderbolt
    );

    EXPECT_EQ(
        StatusCondition::Paralysis,
        battle_state.opponent.get_current_status_condition()
    );
}

TEST(MoveExecution, ThunderBoltDoesNotParalyzOnFalseRoll) {
    BattleState battle_state{
        PokemonState{&LatiasNoItem},
        PokemonState{&LatiasNoItem}
    };

    execute_move(
        NEVER_PARALYZE_POLICY_CONTAINER,
        battle_state,
        Who::Player,
        Move::Thunderbolt
    );

    EXPECT_NE(
        StatusCondition::Paralysis,
        battle_state.opponent.get_current_status_condition()
    );
}

TEST(MoveExecution, ParalysisPreventsAttackOnTrueRoll) {
    BattleState battle_state{
        PokemonState{&Cresselia_7_4},
        PokemonState{&Cresselia_7_4}
    };

    constexpr PolicyContainer<
        AlwaysParalyzeRNGPolicy
    > always_paralyze_policy_container{};

    roll_paralysis(
        always_paralyze_policy_container,
        battle_state.player,
        0
    );
    EXPECT_EQ(
        StatusCondition::Paralysis,
        battle_state.player.get_current_status_condition()
    );

    EXPECT_EQ(
        0,
        execute_move(
            ALWAYS_PARALYZE_POLICY_CONTAINER,
            battle_state,
            Who::Player,
            Move::Psychic
        )
    );

    EXPECT_EQ(
        StatusCondition::Paralysis,
        battle_state.player.get_current_status_condition()
    );
}

TEST(MoveExecution, ParalysisDoesNotPreventMoveOnFalseRoll) {
    BattleState battle_state{
        PokemonState{&Cresselia_7_4},
        PokemonState{&Cresselia_7_4}
    };

    constexpr PolicyContainer<
        AlwaysParalyzeRNGPolicy
    > always_paralyze_policy_container{};

    roll_paralysis(
        always_paralyze_policy_container,
        battle_state.player,
        0
    );
    EXPECT_EQ(
        StatusCondition::Paralysis,
        battle_state.player.get_current_status_condition()
    );

    EXPECT_NE(
        0,
        execute_move(
            NEVER_PARALYZE_POLICY_CONTAINER,
            battle_state,
            Who::Player,
            Move::Psychic
        )
    );

    EXPECT_EQ(
        StatusCondition::Paralysis,
        battle_state.player.get_current_status_condition()
    );
}

TEST(MoveExecution, ParalysisDropsSpeed) {
    PokemonState state{&Cresselia_7_4};

    const uint16_t initial_speed = state.get_current_stat(Stat::Speed);
    constexpr PolicyContainer<
        AlwaysParalyzeRNGPolicy
    > always_paralyze_policy_container{};

    roll_paralysis(
        always_paralyze_policy_container,
        state,
        0
    );
    EXPECT_EQ(
        StatusCondition::Paralysis,
        state.get_current_status_condition()
    );
    EXPECT_EQ(
        initial_speed / 4,
        state.get_current_stat(Stat::Speed)
    );
}

TEST(MoveExecution, SpeedReturnsToNormalAfterParalysisIsCured) {
    PokemonState state{&Cresselia_7_4};

    const uint16_t initial_speed = state.get_current_stat(Stat::Speed);
    constexpr PolicyContainer<
        AlwaysParalyzeRNGPolicy
    > always_paralyze_policy_container{};

    roll_paralysis(
        always_paralyze_policy_container,
        state,
        0
    );

    EXPECT_EQ(
        StatusCondition::Paralysis,
        state.get_current_status_condition()
    );
    EXPECT_EQ(
        initial_speed / 4,
        state.get_current_stat(Stat::Speed)
    );

    state.clear_status_condition();

    EXPECT_EQ(
        initial_speed,
        state.get_current_stat(Stat::Speed)
    );
}

TEST(MoveExecution, MagicGuardPreventsParalysisOnTrueRoll) {
    // TODO once a pokemon with magic guard has its set implemented
}
