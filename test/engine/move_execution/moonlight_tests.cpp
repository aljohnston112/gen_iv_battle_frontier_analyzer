#include "battle_state.h"
#include "move_execution.h"
#include "../mocks.h"
#include "gtest/gtest.h"

void moonlight_heals_the_correct_amount(
    const Weather weather
) {
    BattleState battle_state{
        PokemonState{&CresseliaLeftovers},
        PokemonState{&CresseliaLeftovers}
    };

    const uint32_t max_hp = battle_state.player.get_original_stat(Stat::Health);
    battle_state.player.add_damage(static_cast<uint16_t>(max_hp - 1));
    EXPECT_EQ(battle_state.player.get_current_stat(Stat::Health), 1);

    uint16_t expected_hp_gained = 0;
    switch (weather) {
    case Weather::Clear:
        expected_hp_gained = static_cast<uint16_t>(max_hp / 2u);
        break;
    case Weather::Sun:
        expected_hp_gained = static_cast<uint16_t>(max_hp * 2u / 3u);
        break;
    case Weather::Rain:
    case Weather::Sandstorm:
    case Weather::Hail:
    case Weather::Fog:
        expected_hp_gained = static_cast<uint16_t>(max_hp / 4u);
        break;
    default:
        throw std::runtime_error{"Bad weather"};
    }

    execute_moonlight(
        battle_state.player,
        weather
    );
    EXPECT_EQ(
        battle_state.player.get_current_stat(Stat::Health),
        expected_hp_gained + 1
    );
}

TEST(MoveExecution, MoonlightHealsTheRightAmountInClearWeather) {
    moonlight_heals_the_correct_amount(Weather::Clear);
}

TEST(MoveExecution, MoonlightHealsTheRightAmountInSun) {
    moonlight_heals_the_correct_amount(Weather::Sun);
}

TEST(MoveExecution, MoonlightHealsTheRightAmountInRain) {
    moonlight_heals_the_correct_amount(Weather::Rain);
}

TEST(MoveExecution, MoonlightHealsTheRightAmountInSandstorm) {
    moonlight_heals_the_correct_amount(Weather::Sandstorm);
}

TEST(MoveExecution, MoonlightHealsTheRightAmountInHail) {
    moonlight_heals_the_correct_amount(Weather::Hail);
}

TEST(MoveExecution, MoonlightHealsTheRightAmountInFog) {
    moonlight_heals_the_correct_amount(Weather::Fog);
}

TEST(MoveExecution, MoonlightDoesNotOverheal) {
    BattleState battle_state{
        PokemonState{&CresseliaLeftovers},
        PokemonState{&CresseliaLeftovers}
    };

    const uint16_t max_hp = battle_state.player.get_original_stat(Stat::Health);
    battle_state.player.add_damage(1);
    EXPECT_EQ(battle_state.player.get_current_stat(Stat::Health), max_hp - 1);

    execute_moonlight(
        battle_state.player,
        Weather::Clear
    );
    EXPECT_EQ(
        battle_state.player.get_current_stat(Stat::Health),
        max_hp
    );
}

