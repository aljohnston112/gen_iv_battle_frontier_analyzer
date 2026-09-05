#include "battle_state.h"
#include "end_of_turn_effects.h"
#include "../mocks.h"
#include "pokemon.h"

#include "gtest/gtest.h"

TEST(BattleState, SlowStartHalvesAttackAndSpeed) {
    const BattleState battle_state{
        PokemonState{&Regigias_7_3},
        PokemonState{&Regigias_7_3}
    };
    EXPECT_EQ(
        (Regigias_7_3.get_stat(Stat::Attack) / 2),
        battle_state.player.get_current_stat(Stat::Attack)
    );
    EXPECT_EQ(
        (Regigias_7_3.get_stat(Stat::Speed) / 2),
        battle_state.player.get_current_stat(Stat::Speed)
    );
}

TEST(BattleState, AttackAndSpeedAreRestoredAfter5TurnsOfSlowStart) {
    BattleState battle_state{
        PokemonState{&Regigias_7_3},
        PokemonState{&Regigias_7_3}
    };
    EXPECT_EQ(
        (Regigias_7_3.get_stat(Stat::Attack) / 2),
        battle_state.player.get_current_stat(Stat::Attack)
    );
    EXPECT_EQ(
        (Regigias_7_3.get_stat(Stat::Speed) / 2),
        battle_state.player.get_current_stat(Stat::Speed)
    );

    for (size_t i = 0; i < 5; i++) {
        apply_end_of_turn(DEFAULT_POLICY, battle_state);
    }

    EXPECT_EQ(
        Regigias_7_3.get_stat(Stat::Attack),
        battle_state.player.get_current_stat(Stat::Attack)
    );
    EXPECT_EQ(
        Regigias_7_3.get_stat(Stat::Speed),
        battle_state.player.get_current_stat(Stat::Speed)
    );
}

TEST(BattleState,
     AttackAndSpeedAreRestoredWithModifiersAfter5TurnsOfSlowStart) {
    BattleState battle_state{
        PokemonState{&Regigias_7_3},
        PokemonState{&Regigias_7_3}
    };
    EXPECT_EQ(
        (Regigias_7_3.get_stat(Stat::Attack) / 2),
        battle_state.player.get_current_stat(Stat::Attack)
    );
    EXPECT_EQ(
        (Regigias_7_3.get_stat(Stat::Speed) / 2),
        battle_state.player.get_current_stat(Stat::Speed)
    );
    battle_state.player.decrease_stat_stage(Stat::Attack, 1);
    battle_state.player.decrease_stat_stage(Stat::Speed, 2);

    for (size_t i = 0; i < 5; i++) {
        apply_end_of_turn(DEFAULT_POLICY, battle_state);
    }

    EXPECT_EQ(
        calculate_stat_based_on_stage(
            Regigias_7_3.get_stat(Stat::Attack),
            -1,
            StatusCondition::NoCondition
        ),
        battle_state.player.get_current_stat(Stat::Attack)
    );
    EXPECT_EQ(
        calculate_stat_based_on_stage(
            Regigias_7_3.get_stat(Stat::Speed),
            -2,
            StatusCondition::NoCondition
        ),
        battle_state.player.get_current_stat(Stat::Speed)
    );
}
