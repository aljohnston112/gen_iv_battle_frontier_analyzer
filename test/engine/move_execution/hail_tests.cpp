#include "end_of_turn_effects.h"
#include "move_execution.h"
#include "../mocks.h"
#include "../test_policies.h"

#include "gtest/gtest.h"

TEST(MoveExecution, HailLastFiveTurns) {
    BattleState battle_state{
        PokemonState{&Suicune_7_3},
        PokemonState{&Suicune_7_3}
    };

    ASSERT_EQ(Weather::Clear, battle_state.get_weather());

    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state,
        Who::Player,
        Move::Hail
    );

    ASSERT_EQ(Weather::Hail, battle_state.get_weather());
    for (uint8_t i = 0; i < 4; ++i) {
        apply_end_of_turn(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state
        );
        ASSERT_EQ(Weather::Hail, battle_state.get_weather());
    }

    apply_end_of_turn(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state
    );
    ASSERT_EQ(Weather::Clear, battle_state.get_weather());
}

TEST(MoveExecution, HailDamagesNonIceTypesForASixteenthOfTheirMaxHealth) {
    BattleState battle_state{
        PokemonState{&Suicune_7_3},
        PokemonState{&Suicune_7_3}
    };

    for (uint8_t i = 0; i < to_int(PokemonType::PokemonTypeCount); ++i) {
        if (i == to_int(PokemonType::Ice)) {
            continue;
        }

        battle_state.opponent.set_type(static_cast<PokemonType>(i));

        const uint16_t hp_before =
            battle_state.opponent.get_current_stat(Stat::Health);

        execute_move(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state,
            Who::Player,
            Move::Hail
        );
        battle_state.player.increment_power_point(Move::Hail, 1);

        ASSERT_EQ(Weather::Hail, battle_state.get_weather());

        apply_end_of_turn(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state
        );

        ASSERT_EQ(
            hp_before -
            (battle_state.opponent.get_original_stat(Stat::Health) / 16),
            battle_state.opponent.get_current_stat(Stat::Health)
        );

        battle_state.opponent.add_hp(
            battle_state.opponent.get_original_stat(Stat::Health)
        );
    }
}

TEST(MoveExecution, HailDoesNotDamageIceTypes) {
    BattleState battle_state{
        PokemonState{&Suicune_7_3},
        PokemonState{&Suicune_7_3}
    };


    battle_state.opponent.set_type(PokemonType::Ice);

    const uint16_t hp_before =
        battle_state.opponent.get_current_stat(Stat::Health);

    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state,
        Who::Player,
        Move::Hail
    );

    ASSERT_EQ(Weather::Hail, battle_state.get_weather());

    apply_end_of_turn(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state
    );

    ASSERT_EQ(
        hp_before,
        battle_state.opponent.get_current_stat(Stat::Health)
    );
}

TEST(MoveExecution, HailLastEightTurnsWhenUserIsHoldingIcyRock) {
    BattleState battle_state{
        PokemonState{&Suicune_7_3},
        PokemonState{&Suicune_7_3}
    };
    battle_state.player.set_item(Item::IcyRock);

    ASSERT_EQ(Weather::Clear, battle_state.get_weather());

    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state,
        Who::Player,
        Move::Hail
    );

    ASSERT_EQ(Weather::Hail, battle_state.get_weather());
    for (uint8_t i = 0; i < 7; ++i) {
        apply_end_of_turn(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state
        );
        ASSERT_EQ(Weather::Hail, battle_state.get_weather());
    }

    apply_end_of_turn(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state
    );
    ASSERT_EQ(Weather::Clear, battle_state.get_weather());
}
