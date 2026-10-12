#include "../mocks.h"
#include "../test_policies.h"

#include "battle_state.h"
#include "move_execution.h"

#include "gtest/gtest.h"

TEST(MoveExecution, RainMakesThunderAlwaysHit) {
    BattleState battle_state{
        PokemonState{&Raikou_7_3},
        PokemonState{&Suicune_7_3}
    };

    ASSERT_EQ(Weather::Clear, battle_state.get_weather());
    ASSERT_EQ(
        0,
        execute_move(
            ALWAYS_MISS_POLICY_CONTAINER,
            battle_state,
            Who::Player,
            Move::Thunder
        )
    );

    battle_state.set_weather(Weather::Rain, 5);

    ASSERT_EQ(Weather::Rain, battle_state.get_weather());
    ASSERT_LT(
        0,
        execute_move(
            ALWAYS_MISS_POLICY_CONTAINER,
            battle_state,
            Who::Player,
            Move::Thunder
        )
    );
}

template <Move M>
static void
move_does_no_damage_when_defender_is_semi_invulnerable_and_it_is_raining(
    const CustomPokemon* pokemon,
    const MoveStatusWithStage move_status_with_stage
) {
    BattleState battle_state{
        PokemonState{pokemon},
        PokemonState{&Regirock_7_3}
    };
    battle_state.opponent.set_move_status_with_stage(
        move_status_with_stage,
        Move::MoveCount,
        2
    );
    battle_state.set_weather(Weather::Rain, 5);

    ASSERT_EQ(Weather::Rain, battle_state.get_weather());
    ASSERT_TRUE(
        battle_state.opponent.has_move_status_with_stage(
            move_status_with_stage
        )
    );
    ASSERT_TRUE(
        battle_state.opponent.is_semi_invulnerable()
    );

    ASSERT_EQ(
        0,
        execute_move(
            NEVER_MISS_POLICY_CONTAINER,
            battle_state,
            Who::Player,
            M
        )
    );
}

TEST(
    MoveExecution,
    ThunderDoesNotDamageDefenderWhenDefenderIsConcealedDuringRain
) {
    move_does_no_damage_when_defender_is_semi_invulnerable_and_it_is_raining<
        Move::Thunder
    >(
        &Raikou_7_3,
        MoveStatusWithStage::Concealed
    );
}

TEST(
    MoveExecution,
    ThunderDoesDamageToDefenderWhenDefenderIsSkyHigh
) {
    BattleState battle_state{
        PokemonState{&Raikou_7_3},
        PokemonState{&Regirock_7_3}
    };
    battle_state.opponent.set_move_status_with_stage(
        MoveStatusWithStage::SkyHigh,
        Move::MoveCount,
        2
    );

    ASSERT_TRUE(
        battle_state.opponent.has_move_status_with_stage(
            MoveStatusWithStage::SkyHigh
        )
    );
    ASSERT_TRUE(
        battle_state.opponent.is_semi_invulnerable()
    );

    ASSERT_LT(
        0,
        execute_move(
            NEVER_MISS_POLICY_CONTAINER,
            battle_state,
            Who::Player,
            Move::Thunder
        )
    );
}

TEST(
    MoveExecution,
    ThunderDoesNotDamageDefenderWhenDefenderIsSubmergedDuringRain
) {
    move_does_no_damage_when_defender_is_semi_invulnerable_and_it_is_raining<
        Move::Thunder
    >(
        &Raikou_7_3,
        MoveStatusWithStage::Submerged
    );
}

TEST(
    MoveExecution,
    ThunderDoesNotDamageDefenderWhenDefenderIsUndergroundDuringRain
) {
    move_does_no_damage_when_defender_is_semi_invulnerable_and_it_is_raining<
        Move::Thunder
    >(
        &Raikou_7_3,
        MoveStatusWithStage::Underground
    );
}

TEST(MoveExecution, ThunderHasFiftyPercentAccuracyInSun) {
    BattleState battle_state{
        PokemonState{&Regigigas_7_3},
        PokemonState{&Raikou_7_3}
    };
    battle_state.set_weather(Weather::Sun, 5);
    const MoveInfo* move_info = get_move_info(Move::Thunder);
    const uint16_t accuracy_evasion_value =
        calculate_accuracy_and_evasion_based_on_stage(
            move_info->accuracy,
            battle_state.player.get_status_stage(
                StatusWithStage::Accuracy
            ),
            battle_state.opponent.get_status_stage(
                StatusWithStage::Evasion
            )
        );
    EXPECT_EQ(
        accuracy_evasion_value / 2,
        RealAccuracyEvasionFactorPolicy::get_accuracy_evasion_value(
            battle_state,
            move_info,
            Who::Opponent
        )
    );
}

