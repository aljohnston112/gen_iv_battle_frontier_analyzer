#include "../mocks.h"
#include "battle_state.h"
#include "move_execution.h"
#include "gtest/gtest.h"

TEST(MoveExecution, FalseRollDoesNotFreeze) {
    auto defender = PokemonState{&CresseliaLeftovers};

    constexpr PolicyContainer<
        NeverFreezeRNGPolicy
    > policy_container{};

    for (uint i = 0; i < to_int(Weather::Clear) + 1; i++) {
        roll_freeze(
            policy_container,
            static_cast<Weather>(i),
            defender,
            0
        );
        EXPECT_NE(
            StatusCondition::Freeze,
            defender.get_current_status_condition()
        );
    }
}

TEST(MoveExecution, TrueRollFreezes) {
    auto defender = PokemonState{&CresseliaLeftovers};

    constexpr PolicyContainer<
        AlwaysFreezeRNGPolicy
    > policy_container{};

    for (uint i = 0; i < to_int(Weather::Clear) + 1; i++) {
        if (static_cast<Weather>(i) != Weather::Sun) {
            roll_freeze(
                policy_container,
                static_cast<Weather>(i),
                defender,
                0
            );
            EXPECT_EQ(
                StatusCondition::Freeze,
                defender.get_current_status_condition()
            );
        }
    }
}

TEST(MoveExecution, TrueRollDoesNotFreezeInSun) {
    auto defender = PokemonState{&CresseliaLeftovers};

    constexpr PolicyContainer<
        AlwaysFreezeRNGPolicy
    > policy_container{};

    roll_freeze(
        policy_container,
        Weather::Sun,
        defender,
        0
    );
    EXPECT_NE(
        StatusCondition::Freeze,
        defender.get_current_status_condition()
    );
}

TEST(MoveExecution, ThawsOnTrueRoll) {
    const auto& all_move_infos =
        get_all_moves();

    BattleState battle_state{
        PokemonState{&CresseliaLeftovers},
        PokemonState{&CresseliaLeftovers}
    };

    constexpr PolicyContainer<
        AlwaysFreezeRNGPolicy
    > always_freeze_policy_container{};

    roll_freeze(
        always_freeze_policy_container,
        Weather::Clear,
        battle_state.player,
        0
    );
    EXPECT_EQ(
        StatusCondition::Freeze,
        battle_state.player.get_current_status_condition()
    );

    constexpr PolicyContainer<
        OpponentOptimizedConfusionStatusPolicy,
        NeverConfuseRNGPolicy,
        NeverCritRNGPolicy,
        OpponentOptimizedRandomFactorPolicy,
        NeverFreezeRNGPolicy,
        OpponentOptimizedStatChangePolicy,
        NeverParalyzeRNGPolicy
    > never_freeze_policy_container{};

    EXPECT_NE(
        0,
        execute_move(
            never_freeze_policy_container,
            battle_state,
            Who::Player,
            &all_move_infos[to_int(Move::Psychic)]
        )
    );

    EXPECT_NE(
        StatusCondition::Freeze,
        battle_state.player.get_current_status_condition()
    );
}

TEST(MoveExecution, DoesNotMoveWhenFrozen) {
    const auto& all_move_infos =
        get_all_moves();

    BattleState battle_state{
        PokemonState{&CresseliaLeftovers},
        PokemonState{&CresseliaLeftovers}
    };

    constexpr PolicyContainer<
        AlwaysFreezeRNGPolicy
    > always_freeze_policy_container{};

    roll_freeze(
        always_freeze_policy_container,
        Weather::Clear,
        battle_state.player,
        0
    );
    EXPECT_EQ(
        StatusCondition::Freeze,
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
    > never_freeze_policy_container{};

    EXPECT_EQ(
        0,
        execute_move(
            never_freeze_policy_container,
            battle_state,
            Who::Player,
            &all_move_infos[to_int(Move::Psychic)]
        )
    );

    EXPECT_EQ(
        StatusCondition::Freeze,
        battle_state.player.get_current_status_condition()
    );
}


TEST(MoveExecution, FireMoveFromOpponentThaws) {
    // TODO once a fire move is implemented
}

// TODO once these moves are implemented
TEST(MoveExecution, UsingFlameWheelThawsOneself) {}

TEST(MoveExecution, UsingFlareBlitzThawsOneself) {}

TEST(MoveExecution, UsingSacredThawsOneself) {}
