#include "../mocks.h"
#include "../test_policies.h"

#include <gtest/gtest.h>

#include "move_execution.h"

TEST(MoveExecution, FocusBandPreventsKnockOutOnTrueRoll) {
    BattleState battle_state{
        PokemonState{&Zapdos_7_2},
        PokemonState{&Zapdos_7_2}
    };
    battle_state.player.add_damage(
        battle_state.player.get_current_stat(Stat::Health) - 1,
        DamageSource::DontCare
    );

    EXPECT_EQ(
        1,
        battle_state.player.get_current_stat(Stat::Health)
    );

    execute_move(
        ALWAYS_SURVIVE_FOCUS_BAND_POLICY_CONTAINER,
        battle_state,
        Who::Opponent,
        Move::OminousWind
    );

    EXPECT_EQ(
        1,
        battle_state.player.get_current_stat(Stat::Health)
    );
}

TEST(MoveExecution, FocusBandDoesNotPreventKnockOutOnFalseRoll) {
    BattleState battle_state{
        PokemonState{&Zapdos_7_2},
        PokemonState{&Zapdos_7_2}
    };
    battle_state.player.add_damage(
        battle_state.player.get_current_stat(Stat::Health) - 1,
        DamageSource::DontCare
    );

    EXPECT_EQ(
        1,
        battle_state.player.get_current_stat(Stat::Health)
    );

    execute_move(
        NEVER_SURVIVE_FOCUS_BAND_POLICY_CONTAINER,
        battle_state,
        Who::Opponent,
        Move::OminousWind
    );

    EXPECT_EQ(
        0,
        battle_state.player.get_current_stat(Stat::Health)
    );
}

TEST(MoveExecution, FocusBandPreventsKnockOutFromSelfHitOnTrueRoll) {
    BattleState battle_state{
        PokemonState{&Zapdos_7_2},
        PokemonState{&Zapdos_7_2}
    };
    battle_state.player.add_damage(
        battle_state.player.get_current_stat(Stat::Health) - 1,
        DamageSource::DontCare
    );
    battle_state.player.set_status_with_stage(
        StatusWithStage::Confused,
        5
        );

    EXPECT_EQ(
        1,
        battle_state.player.get_current_stat(Stat::Health)
    );
    EXPECT_TRUE(
        battle_state.player.has_status_with_stage(StatusWithStage::Confused)
        );

    hit_from_confusion(
        ALWAYS_SURVIVE_FOCUS_BAND_POLICY_CONTAINER,
        battle_state.player,
        Who::Player
    );

    EXPECT_EQ(
        1,
        battle_state.player.get_current_stat(Stat::Health)
    );
}

TEST(MoveExecution, FocusBandDoesNotPreventKnockOutFromSelfHitOnFalseRoll) {
    BattleState battle_state{
        PokemonState{&Zapdos_7_2},
        PokemonState{&Zapdos_7_2}
    };
    battle_state.player.add_damage(
        battle_state.player.get_current_stat(Stat::Health) - 1,
        DamageSource::DontCare
    );
    battle_state.player.set_status_with_stage(
        StatusWithStage::Confused,
        5
        );

    EXPECT_EQ(
        1,
        battle_state.player.get_current_stat(Stat::Health)
    );
    EXPECT_TRUE(
        battle_state.player.has_status_with_stage(StatusWithStage::Confused)
        );

    hit_from_confusion(
        NEVER_SURVIVE_FOCUS_BAND_POLICY_CONTAINER,
        battle_state.player,
        Who::Player
    );

    EXPECT_EQ(
        0,
        battle_state.player.get_current_stat(Stat::Health)
    );
}