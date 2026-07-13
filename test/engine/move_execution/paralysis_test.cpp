#include "battle_state.h"
#include "move_execution.h"
#include "serebii_pokemon_data_source.h"
#include "../mocks.h"
#include "gtest/gtest.h"

TEST(MoveExecution, ThunderBoltParalyzesOnTrueRoll) {
    const auto& all_move_infos =
        get_all_moves();

    BattleState battle_state{
        PokemonState{&Latias},
        PokemonState{&Latias}
    };

    constexpr PolicyContainer<
        OpponentOptimizedConfusionStatusPolicy,
        NeverConfuseRNGPolicy,
        NeverCritRNGPolicy,
        OpponentOptimizedRandomFactorPolicy,
        NeverFreezeRNGPolicy,
        OpponentOptimizedStatChangePolicy,
        AlwaysParalyzeRNGPolicy
    > policy_container{};

    execute_move(
        policy_container,
        battle_state,
        Who::Player,
        &all_move_infos[to_int(Move::Thunderbolt)]
    );

    EXPECT_EQ(
        StatusCondition::Paralysis,
        battle_state.opponent.get_current_status_condition()
    );
}

TEST(MoveExecution, ThunderBoltDoesNotParalyzOnFalseRoll) {
    const auto& all_move_infos =
        get_all_moves();

    BattleState battle_state{
        PokemonState{&Latias},
        PokemonState{&Latias}
    };

    constexpr PolicyContainer<
        OpponentOptimizedConfusionStatusPolicy,
        NeverConfuseRNGPolicy,
        NeverCritRNGPolicy,
        OpponentOptimizedRandomFactorPolicy,
        NeverFreezeRNGPolicy,
        OpponentOptimizedStatChangePolicy,
        NeverParalyzeRNGPolicy
    > policy_container{};

    execute_move(
        policy_container,
        battle_state,
        Who::Player,
        &all_move_infos[to_int(Move::Thunderbolt)]
    );

    EXPECT_NE(
        StatusCondition::Paralysis,
        battle_state.opponent.get_current_status_condition()
    );
}

TEST(MoveExecution, ParalysisPreventsAttackOnTrueRoll) {
    const auto& all_move_infos =
        get_all_moves();

    BattleState battle_state{
        PokemonState{&CresseliaLeftovers},
        PokemonState{&CresseliaLeftovers}
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

    constexpr PolicyContainer<
        OpponentOptimizedConfusionStatusPolicy,
        NeverConfuseRNGPolicy,
        NeverCritRNGPolicy,
        OpponentOptimizedRandomFactorPolicy,
        NeverFreezeRNGPolicy,
        OpponentOptimizedStatChangePolicy,
        AlwaysParalyzeRNGPolicy
    > policy_container{};

    EXPECT_EQ(
        0,
        execute_move(
            policy_container,
            battle_state,
            Who::Player,
            &all_move_infos[to_int(Move::Psychic)]
        )
    );

    EXPECT_EQ(
        StatusCondition::Paralysis,
        battle_state.player.get_current_status_condition()
    );
}

TEST(MoveExecution, ParalysisDoesNotPreventMoveOnFalseRoll) {
    const auto& all_move_infos =
        get_all_moves();

    BattleState battle_state{
        PokemonState{&CresseliaLeftovers},
        PokemonState{&CresseliaLeftovers}
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

    constexpr PolicyContainer<
        OpponentOptimizedConfusionStatusPolicy,
        NeverConfuseRNGPolicy,
        NeverCritRNGPolicy,
        OpponentOptimizedRandomFactorPolicy,
        AlwaysFreezeRNGPolicy,
        OpponentOptimizedStatChangePolicy,
        NeverParalyzeRNGPolicy
    > never_paralyze_policy_container{};

    EXPECT_NE(
        0,
        execute_move(
            never_paralyze_policy_container,
            battle_state,
            Who::Player,
            &all_move_infos[to_int(Move::Psychic)]
        )
    );

    EXPECT_EQ(
        StatusCondition::Paralysis,
        battle_state.player.get_current_status_condition()
    );
}

TEST(MoveExecution, ParalysisDropsSpeed) {
    PokemonState state{&CresseliaLeftovers};

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

TEST(MoveExecution, MagicGuardPreventsParalysisOnTrueRoll) {
    // TODO once a pokemon with magic guard has its set implemented
}
