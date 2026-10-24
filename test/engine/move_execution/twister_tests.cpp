#include "../mocks.h"
#include "../test_policies.h"

#include "battle_state.h"
#include "damage_util.h"
#include "move_execution.h"

#include "gtest/gtest.h"

TEST(
    MoveExecution,
    TwisterDoesNotDamageDefenderWhenDefenderIsConcealed
) {
    move_does_no_damage_when_defender_is_semi_invulnerable<Move::Twister>(
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
    move_does_no_damage_when_defender_is_semi_invulnerable<Move::Twister>(
        &Zapdos_7_3,
        MoveStatusWithStage::Submerged
    );
}

TEST(
    MoveExecution,
    TwisterDoesNotDamageDefenderWhenDefenderIsUnderground
) {
    move_does_no_damage_when_defender_is_semi_invulnerable<Move::Twister>(
        &Zapdos_7_3,
        MoveStatusWithStage::Underground
    );
}

