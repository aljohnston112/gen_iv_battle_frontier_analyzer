#include "damage_util.h"
#include "end_of_turn_effects.h"
#include "move_execution.h"
#include "../mocks.h"
#include "../test_policies.h"

#include "gtest/gtest.h"

TEST(MoveExecution, SunnyDayFailsInSun) {
    BattleState battle_state{
        PokemonState{&Entei_7_3},
        PokemonState{&Suicune_7_3}
    };

    battle_state.set_weather(Weather::Sun, 1);
    ASSERT_EQ(Weather::Sun, battle_state.get_weather());

    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state,
        Who::Player,
        Move::SunnyDay
    );
    apply_end_of_turn(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state
    );

    ASSERT_EQ(Weather::Clear, battle_state.get_weather());
}

TEST(MoveExecution, SunnyDayReplacesSetWeather) {
    BattleState battle_state{
        PokemonState{&Entei_7_3},
        PokemonState{&Suicune_7_3}
    };

    battle_state.set_weather(Weather::Rain, 5);
    ASSERT_EQ(Weather::Rain, battle_state.get_weather());

    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state,
        Who::Player,
        Move::SunnyDay
    );

    ASSERT_EQ(Weather::Sun, battle_state.get_weather());
    for (uint8_t i = 0; i < 4; ++i) {
        apply_end_of_turn(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state
        );
        ASSERT_EQ(Weather::Sun, battle_state.get_weather());
    }

    apply_end_of_turn(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state
    );
    ASSERT_EQ(Weather::Clear, battle_state.get_weather());
}

TEST(MoveExecution, SunnyDayLastFiveTurns) {
    BattleState battle_state{
        PokemonState{&Entei_7_3},
        PokemonState{&Suicune_7_3}
    };

    ASSERT_EQ(Weather::Clear, battle_state.get_weather());

    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state,
        Who::Player,
        Move::SunnyDay
    );

    ASSERT_EQ(Weather::Sun, battle_state.get_weather());
    for (uint8_t i = 0; i < 4; ++i) {
        apply_end_of_turn(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state
        );
        ASSERT_EQ(Weather::Sun, battle_state.get_weather());
    }

    apply_end_of_turn(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state
    );
    ASSERT_EQ(Weather::Clear, battle_state.get_weather());
}

TEST(MoveExecution, SunnyDayLastEightTurnsWhenUserIsHoldingHeatRock) {
    BattleState battle_state{
        PokemonState{&Entei_7_3},
        PokemonState{&Suicune_7_3}
    };
    battle_state.player.set_item(Item::HeatRock);

    ASSERT_EQ(Weather::Clear, battle_state.get_weather());

    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state,
        Who::Player,
        Move::SunnyDay
    );

    ASSERT_EQ(Weather::Sun, battle_state.get_weather());
    for (uint8_t i = 0; i < 7; ++i) {
        apply_end_of_turn(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state
        );
        ASSERT_EQ(Weather::Sun, battle_state.get_weather());
    }

    apply_end_of_turn(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state
    );
    ASSERT_EQ(Weather::Clear, battle_state.get_weather());
}

TEST(
    MoveExecution,
    SunMakesFireMoveDoFiftyPercentMoreDamage
) {
    BattleState battle_state{
        PokemonState{&Entei_7_3},
        PokemonState{&Cresselia_7_3}
    };
    battle_state.set_weather(Weather::Sun, 5);
    random_does_correct_damage_for_attack<
        DamageTestCase<NeverCritRNGPolicy, LowDamageRandomFactorPolicy, 105>,
        DamageTestCase<NeverCritRNGPolicy, HighDamageRandomFactorPolicy, 124>
    >(battle_state, Move::FireBlast);
}
