#include "battle_state.h"
#include "move_execution.h"
#include "../mocks.h"
#include "gtest/gtest.h"

void moonlight_heals_the_correct_amount(
    const Weather weather
) {
    BattleState battle_state{
        PokemonState{&Cresselia},
        PokemonState{&Cresselia}
    };

    const uint16_t max_hp = battle_state.player.get_original_stat(Stat::Health);
    battle_state.player.add_damage(max_hp - 1);
    EXPECT_EQ(battle_state.player.get_current_stat(Stat::Health), 1);

    uint16_t expected_hp_gained = 0;
    switch (weather) {
    case Weather::Clear:
        expected_hp_gained = max_hp / 2;
        break;
    case Weather::Sun:
        expected_hp_gained = 2 * max_hp / 3;
        break;
    case Weather::Rain:
    case Weather::Sandstorm:
    case Weather::Hail:
    case Weather::Fog:
        expected_hp_gained = max_hp / 4;
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

TEST(Engine, MoonlightHealsTheRightAmountInClearWeather) {
    moonlight_heals_the_correct_amount(Weather::Clear);
}

TEST(Engine, MoonlightHealsTheRightAmountInSun) {
    moonlight_heals_the_correct_amount(Weather::Sun);
}

TEST(Engine, MoonlightHealsTheRightAmountInRain) {
    moonlight_heals_the_correct_amount(Weather::Rain);
}

TEST(Engine, MoonlightHealsTheRightAmountInSandstorm) {
    moonlight_heals_the_correct_amount(Weather::Sandstorm);
}

TEST(Engine, MoonlightHealsTheRightAmountInHail) {
    moonlight_heals_the_correct_amount(Weather::Hail);
}

TEST(Engine, MoonlightHealsTheRightAmountInFog) {
    moonlight_heals_the_correct_amount(Weather::Fog);
}

TEST(Engine, MoonlightDoesNotOverheal) {
    BattleState battle_state{
        PokemonState{&Cresselia},
        PokemonState{&Cresselia}
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

