
#include "damage_util.h"
#include "end_of_turn_effects.h"
#include "move_execution.h"
#include "../mocks.h"
#include "../test_policies.h"

#include "gtest/gtest.h"

TEST(MoveExecution, RainDanceFailsInRain) {
    BattleState battle_state{
        PokemonState{&Raikou_7_3},
        PokemonState{&Suicune_7_3}
    };

    battle_state.set_weather(Weather::Rain, 1);
    EXPECT_EQ(Weather::Rain, battle_state.get_weather());

    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state,
        Who::Player,
        Move::RainDance
    );
    apply_end_of_turn(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state
    );

    EXPECT_EQ(Weather::Clear, battle_state.get_weather());
}

TEST(MoveExecution, RainDanceReplacesSetWeather) {
    BattleState battle_state{
        PokemonState{&Raikou_7_3},
        PokemonState{&Suicune_7_3}
    };

    battle_state.set_weather(Weather::Hail, 5);
    EXPECT_EQ(Weather::Hail, battle_state.get_weather());

    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state,
        Who::Player,
        Move::RainDance
    );

    EXPECT_EQ(Weather::Rain, battle_state.get_weather());
    for (uint8_t i = 0; i < 4; ++i) {
        apply_end_of_turn(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state
        );
        EXPECT_EQ(Weather::Rain, battle_state.get_weather());
    }

    apply_end_of_turn(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state
    );
    EXPECT_EQ(Weather::Clear, battle_state.get_weather());
}

TEST(MoveExecution, RainDanceLastFiveTurns) {
    BattleState battle_state{
        PokemonState{&Raikou_7_3},
        PokemonState{&Suicune_7_3}
    };

    EXPECT_EQ(Weather::Clear, battle_state.get_weather());

    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state,
        Who::Player,
        Move::RainDance
    );

    EXPECT_EQ(Weather::Rain, battle_state.get_weather());
    for (uint8_t i = 0; i < 4; ++i) {
        apply_end_of_turn(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state
        );
        EXPECT_EQ(Weather::Rain, battle_state.get_weather());
    }

    apply_end_of_turn(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state
    );
    EXPECT_EQ(Weather::Clear, battle_state.get_weather());
}

TEST(MoveExecution, RainDanceLastEightTurnsWhenUserIsHoldingDampRock) {
    BattleState battle_state{
        PokemonState{&Raikou_7_3},
        PokemonState{&Suicune_7_3}
    };
    battle_state.player.set_item(Item::DampRock);

    EXPECT_EQ(Weather::Clear, battle_state.get_weather());

    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state,
        Who::Player,
        Move::RainDance
    );

    EXPECT_EQ(Weather::Rain, battle_state.get_weather());
    for (uint8_t i = 0; i < 7; ++i) {
        apply_end_of_turn(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state
        );
        EXPECT_EQ(Weather::Rain, battle_state.get_weather());
    }

    apply_end_of_turn(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state
    );
    EXPECT_EQ(Weather::Clear, battle_state.get_weather());
}

TEST(
    MoveExecution,
    RainMakesWaterMoveDoFiftyPercentMoreDamage
) {
    BattleState battle_state{
        PokemonState{&Latias_7_4},
        PokemonState{&Cresselia_7_3}
    };
    battle_state.set_weather(Weather::Rain, 5);
    random_does_correct_damage_for_attack<
        DamageTestCase<NeverCritRNGPolicy, LowDamageRandomFactorPolicy, 63>,
        DamageTestCase<NeverCritRNGPolicy, HighDamageRandomFactorPolicy, 75>
    >(battle_state, Move::Surf);
}