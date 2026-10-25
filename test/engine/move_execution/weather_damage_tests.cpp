#include "../mocks.h"
#include "../test_policies.h"

#include "damage_util.h"
#include "end_of_turn_effects.h"

#include "gtest/gtest.h"

TEST(MoveExecution, PhysicalWaterMoveHasHalfPowerInSun) {
    BattleState battle_state{
        PokemonState{&Suicune_7_2},
        PokemonState{&Suicune_7_2}
    };
    battle_state.set_weather(Weather::Sun, 5);
    random_does_correct_damage_for_attack<
        DamageTestCase<NeverCritRNGPolicy, LowDamageRandomFactorPolicy, 11>,
        DamageTestCase<NeverCritRNGPolicy, HighDamageRandomFactorPolicy, 13>
    >(battle_state, Move::Waterfall);
}

TEST(MoveExecution, SpecialWaterMoveHasHalfPowerInSun) {
    BattleState battle_state{
        PokemonState{&Latias_7_4},
        PokemonState{&Latias_7_4}
    };
    battle_state.set_weather(Weather::Sun, 5);
    random_does_correct_damage_for_attack<
        DamageTestCase<NeverCritRNGPolicy, LowDamageRandomFactorPolicy, 11>,
        DamageTestCase<NeverCritRNGPolicy, HighDamageRandomFactorPolicy, 13>
    >(battle_state, Move::Surf);
}

TEST(MoveExecution, PhysicalFireMoveHasHalfPowerInRain) {
    BattleState battle_state{
        PokemonState{&Entei_7_2},
        PokemonState{&Entei_7_2}
    };
    battle_state.set_weather(Weather::Rain, 5);
    random_does_correct_damage_for_attack<
        DamageTestCase<NeverCritRNGPolicy, LowDamageRandomFactorPolicy, 15>,
        DamageTestCase<NeverCritRNGPolicy, HighDamageRandomFactorPolicy, 18>
    >(battle_state, Move::FireFang);
}

TEST(MoveExecution, SpecialFireMoveHasHalfPowerInRain) {
    BattleState battle_state{
        PokemonState{&Heatran_7_3},
        PokemonState{&Latias_7_4}
    };
    battle_state.set_weather(Weather::Rain, 5);
    random_does_correct_damage_for_attack<
        DamageTestCase<NeverCritRNGPolicy, LowDamageRandomFactorPolicy, 18>,
        DamageTestCase<NeverCritRNGPolicy, HighDamageRandomFactorPolicy, 21>
    >(battle_state, Move::Flamethrower);
}

TEST(MoveExecution, PhysicalFireMoveHasDoublePowerInSun) {
    BattleState battle_state{
        PokemonState{&Entei_7_2},
        PokemonState{&Entei_7_2}
    };
    battle_state.set_weather(Weather::Sun, 5);
    random_does_correct_damage_for_attack<
        DamageTestCase<NeverCritRNGPolicy, LowDamageRandomFactorPolicy, 43>,
        DamageTestCase<NeverCritRNGPolicy, HighDamageRandomFactorPolicy, 51>
    >(battle_state, Move::FireFang);
}

TEST(MoveExecution, SpecialFireMoveHasDoublePowerInSun) {
    BattleState battle_state{
        PokemonState{&Heatran_7_3},
        PokemonState{&Latias_7_4}
    };
    battle_state.set_weather(Weather::Sun, 5);
    random_does_correct_damage_for_attack<
        DamageTestCase<NeverCritRNGPolicy, LowDamageRandomFactorPolicy, 53>,
        DamageTestCase<NeverCritRNGPolicy, HighDamageRandomFactorPolicy, 63>
    >(battle_state, Move::Flamethrower);
}

TEST(MoveExecution, PhysicalWaterMoveHasDoublePowerInRain) {
    BattleState battle_state{
        PokemonState{&Suicune_7_2},
        PokemonState{&Suicune_7_2}
    };
    battle_state.set_weather(Weather::Rain, 5);
    random_does_correct_damage_for_attack<
        DamageTestCase<NeverCritRNGPolicy, LowDamageRandomFactorPolicy, 31>,
        DamageTestCase<NeverCritRNGPolicy, HighDamageRandomFactorPolicy, 37>
    >(battle_state, Move::Waterfall);
}

TEST(MoveExecution, SpecialWaterMoveHasDoublePowerInRain) {
    BattleState battle_state{
        PokemonState{&Latias_7_4},
        PokemonState{&Latias_7_4}
    };
    battle_state.set_weather(Weather::Rain, 5);
    random_does_correct_damage_for_attack<
        DamageTestCase<NeverCritRNGPolicy, LowDamageRandomFactorPolicy, 31>,
        DamageTestCase<NeverCritRNGPolicy, HighDamageRandomFactorPolicy, 37>
    >(battle_state, Move::Surf);
}

