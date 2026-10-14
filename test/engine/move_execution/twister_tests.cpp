#include "../mocks.h"
#include "../test_policies.h"

#include "battle_state.h"
#include "move_execution.h"

#include "gtest/gtest.h"

static void twister_does_no_damage_when_defender_is_semi_invulnerable(
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

    EXPECT_TRUE(
        battle_state.opponent.has_move_status_with_stage(
            move_status_with_stage
        )
    );
    EXPECT_TRUE(
        battle_state.opponent.is_semi_invulnerable()
    );

    EXPECT_EQ(
        0,
        execute_move(
            NEVER_MISS_POLICY_CONTAINER,
            battle_state,
            Who::Player,
            Move::Twister
        )
    );
}

TEST(
    MoveExecution,
    TwisterDoesNotDamageDefenderWhenDefenderIsConcealed
) {
    twister_does_no_damage_when_defender_is_semi_invulnerable(
        &Zapdos_7_3,
        MoveStatusWithStage::Concealed
    );
}

TEST(
    MoveExecution,
    TwisterDoesMoreDamageToDefenderWhenDefenderIsSkyHigh
) {
    BattleState battle_state{
        PokemonState{&Zapdos_7_3},
        PokemonState{&Regirock_7_3}
    };
    battle_state.opponent.set_move_status_with_stage(
        MoveStatusWithStage::SkyHigh,
        Move::MoveCount,
        2
    );

    EXPECT_TRUE(
        battle_state.opponent.has_move_status_with_stage(
            MoveStatusWithStage::SkyHigh
        )
    );
    EXPECT_TRUE(
        battle_state.opponent.is_semi_invulnerable()
    );

    EXPECT_EQ(
        24,
        execute_move(
            NEVER_MISS_POLICY_CONTAINER,
            battle_state,
            Who::Player,
            Move::Twister
        )
    );
}

TEST(
    MoveExecution,
    TwisterDoesNotDamageDefenderWhenDefenderIsSubmerged
) {
    twister_does_no_damage_when_defender_is_semi_invulnerable(
        &Zapdos_7_3,
        MoveStatusWithStage::Submerged
    );
}

TEST(
    MoveExecution,
    TwisterDoesNotDamageDefenderWhenDefenderIsUnderground
) {
    twister_does_no_damage_when_defender_is_semi_invulnerable(
        &Zapdos_7_3,
        MoveStatusWithStage::Underground
    );
}

