#include "../mocks.h"
#include "../test_policies.h"

#include "battle_state.h"
#include "move_execution.h"

#include "gtest/gtest.h"

TEST(MoveExecution, FalseRollDoesNotFreeze) {
    auto defender = PokemonState{&Cresselia_7_4};

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
    auto defender = PokemonState{&Cresselia_7_4};

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
            defender.clear_status_condition();
        }
    }
}

namespace {
    template <Move M>
    void move_does_not_freeze_on_false_roll(const CustomPokemon* pokemon) {
        BattleState battle_state{
            PokemonState{pokemon},
            PokemonState{&Cresselia_7_4}
        };

        for (uint i = 0; i < to_int(Weather::Clear) + 1; i++) {
            execute_move(
                NEVER_FREEZE_POLICY_CONTAINER,
                battle_state,
                Who::Player,
                M
            );
            battle_state.player.increment_power_point(M, 1);

            EXPECT_NE(
                StatusCondition::Freeze,
                battle_state.opponent.get_current_status_condition()
            );
            battle_state.opponent.clear_status_condition();
        }
    }

    template <Move M>
    void move_freezes_on_true_roll(const CustomPokemon* pokemon) {
        BattleState battle_state{
            PokemonState{pokemon},
            PokemonState{&Cresselia_7_4}
        };

        for (uint i = 0; i < to_int(Weather::Clear) + 1; i++) {
            if (static_cast<Weather>(i) != Weather::Sun) {
                execute_move(
                    ALWAYS_FREEZE_POLICY_CONTAINER,
                    battle_state,
                    Who::Player,
                    M
                );
                battle_state.player.increment_power_point(M, 1);

                EXPECT_EQ(
                    StatusCondition::Freeze,
                    battle_state.opponent.get_current_status_condition()
                );
            }
        }
    }
}

TEST(MoveExecution, FalseRollDoesNotFreezeWhenIceBeamIsUsed) {
    move_does_not_freeze_on_false_roll<Move::IceBeam>(&Cresselia_7_4);
}

TEST(MoveExecution, TrueRollFreezesWhenIceBeamIsUsed) {
    move_freezes_on_true_roll<Move::IceBeam>(&Cresselia_7_4);
}

TEST(MoveExecution, FalseRollDoesNotFreezeWhenBlizzardIsUsed) {
    move_does_not_freeze_on_false_roll<Move::Blizzard>(&Suicune_7_3);
}

TEST(MoveExecution, TrueRollFreezesWhenBlizzardIsUsed) {
    move_freezes_on_true_roll<Move::Blizzard>(&Suicune_7_3);
}


TEST(MoveExecution, TrueRollDoesNotFreezeInSun) {
    auto defender = PokemonState{&Cresselia_7_4};

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
    BattleState battle_state{
        PokemonState{&Cresselia_7_4},
        PokemonState{&Cresselia_7_4}
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

    EXPECT_NE(
        0,
        execute_move(
            NEVER_FREEZE_POLICY_CONTAINER,
            battle_state,
            Who::Player,
            Move::Psychic
        )
    );

    EXPECT_NE(
        StatusCondition::Freeze,
        battle_state.player.get_current_status_condition()
    );
}

TEST(MoveExecution, DoesNotMoveWhenFrozen) {
    BattleState battle_state{
        PokemonState{&Cresselia_7_4},
        PokemonState{&Cresselia_7_4}
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

    EXPECT_EQ(
        0,
        execute_move(
            ALWAYS_FREEZE_POLICY_CONTAINER,
            battle_state,
            Who::Player,
            Move::Psychic
        )
    );

    EXPECT_EQ(
        StatusCondition::Freeze,
        battle_state.player.get_current_status_condition()
    );
}

TEST(MoveExecution, FireMoveFromOpponentThaws) {
    BattleState battle_state{
        PokemonState{&Heatran_7_3},
        PokemonState{&Cresselia_7_3}
    };
    battle_state.opponent.try_set_status_condition(StatusCondition::Freeze);
    EXPECT_TRUE(
        battle_state.opponent.has_status_condition(StatusCondition::Freeze)
    );

    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state,
        Who::Player,
        Move::Flamethrower
    );

    EXPECT_TRUE(
        battle_state.opponent.has_status_condition(StatusCondition::NoCondition)
    );
}

// TODO once these moves are implemented
TEST(MoveExecution, UsingFlameWheelThawsOneself) {}

TEST(MoveExecution, UsingFlareBlitzThawsOneself) {}

TEST(MoveExecution, UsingSacredThawsOneself) {}
