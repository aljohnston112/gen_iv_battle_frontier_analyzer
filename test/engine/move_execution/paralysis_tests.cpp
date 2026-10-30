#include "../mocks.h"
#include "../test_policies.h"

#include "battle_state.h"
#include "move_execution.h"
#include "serebii_pokemon_data_source.h"

#include "gtest/gtest.h"

namespace {
    template <Move M>
    void move_paralyzes_on_true_roll(const CustomPokemon& custom_pokemon) {
        BattleState battle_state{
            PokemonState{&custom_pokemon},
            PokemonState{&Latias_7_4_No_Item}
        };

        execute_move(
            ALWAYS_PARALYZE_POLICY_CONTAINER,
            battle_state,
            Who::Player,
            M
        );

        EXPECT_EQ(
            StatusCondition::Paralysis,
            battle_state.opponent.get_current_status_condition()
        );
    }

    template <Move M>
    void move_does_not_paralyze_on_false_roll(
        const CustomPokemon& custom_pokemon
    ) {
        BattleState battle_state{
            PokemonState{&custom_pokemon},
            PokemonState{&Latias_7_4_No_Item}
        };

        execute_move(
            NEVER_PARALYZE_POLICY_CONTAINER,
            battle_state,
            Who::Player,
            M
        );

        EXPECT_EQ(
            StatusCondition::NoCondition,
            battle_state.opponent.get_current_status_condition()
        );
    }

    template <Move M>
    void move_paralyzes_on_false_roll(
        const CustomPokemon& custom_pokemon
    ) {
        BattleState battle_state{
            PokemonState{&custom_pokemon},
            PokemonState{&Latias_7_4_No_Item}
        };

        execute_move(
            NEVER_PARALYZE_POLICY_CONTAINER,
            battle_state,
            Who::Player,
            M
        );

        EXPECT_EQ(
            StatusCondition::Paralysis,
            battle_state.opponent.get_current_status_condition()
        );
    }
}

TEST(MoveExecution, ThunderBoltParalyzesOnTrueRoll) {
    move_paralyzes_on_true_roll<Move::Thunderbolt>(
        Latias_7_4_No_Item
    );
}

TEST(MoveExecution, ThunderBoltDoesNotParalyzeOnFalseRoll) {
    move_does_not_paralyze_on_false_roll<Move::Thunderbolt>(
        Latias_7_4_No_Item
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
        Who::Player,
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
        Who::Player,
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
        Who::Player,
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
        Who::Player,
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

TEST(MoveExecution, ThunderParalyzesOnTrueRoll) {
    move_paralyzes_on_true_roll<Move::Thunder>(Raikou_7_3);
}

TEST(MoveExecution, ThunderDoesNotParalyzeOnFalseRoll) {
    move_does_not_paralyze_on_false_roll<Move::Thunder>(
        Raikou_7_3
    );
}

TEST(MoveExecution, ThunderParalyzesElectricTypeOnTrueRoll) {
    BattleState battle_state{
        PokemonState{&Raikou_7_3},
        PokemonState{&Raikou_7_3}
    };

    execute_move(
        ALWAYS_PARALYZE_POLICY_CONTAINER,
        battle_state,
        Who::Player,
        Move::Thunder
    );

    EXPECT_EQ(
        StatusCondition::Paralysis,
        battle_state.opponent.get_current_status_condition()
    );
}

TEST(MoveExecution, ThunderFangParalyzesOnTrueRoll) {
    move_paralyzes_on_true_roll<Move::ThunderFang>(
        Raikou_7_2
    );
}

TEST(MoveExecution, ThunderFangDoesNotParalyzeOnFalseRoll) {
    move_does_not_paralyze_on_false_roll<Move::ThunderFang>(
        Raikou_7_2
    );
}


TEST(MoveExecution, ThunderWaveParalyzesOnTrueRoll) {
    move_paralyzes_on_true_roll<Move::ThunderWave>(
        Regigigas_7_1
    );
}

TEST(MoveExecution, ThunderWaveParalyzesOnFalseRoll) {
    move_paralyzes_on_false_roll<Move::ThunderWave>(
        Regigigas_7_1
    );
}
