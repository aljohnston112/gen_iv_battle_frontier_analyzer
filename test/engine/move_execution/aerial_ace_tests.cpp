#include "../mocks.h"
#include "../test_policies.h"

#include "battle_state.h"
#include "damage_util.h"
#include "move_execution.h"

#include "gtest/gtest.h"

TEST(MoveExecution, AerialAceAlwaysHit) {
    BattleState battle_state{
        PokemonState{&Latias_7_2},
        PokemonState{&Suicune_7_3}
    };

    EXPECT_LT(
        0,
        execute_move(
            ALWAYS_MISS_POLICY_CONTAINER,
            battle_state,
            Who::Player,
            Move::AerialAce
        )
    );
}

TEST(MoveExecution, AerialAceMissesWhenDefenderIsSemiInvulnerable) {
    move_does_no_damage_when_defender_is_semi_invulnerable<Move::AerialAce>(
        &Latias_7_2,
        MoveStatusWithStage::Concealed
    );
    move_does_no_damage_when_defender_is_semi_invulnerable<Move::AerialAce>(
        &Latias_7_2,
        MoveStatusWithStage::SkyHigh
    );
    move_does_no_damage_when_defender_is_semi_invulnerable<Move::AerialAce>(
        &Latias_7_2,
        MoveStatusWithStage::Submerged
    );
    move_does_no_damage_when_defender_is_semi_invulnerable<Move::AerialAce>(
        &Latias_7_2,
        MoveStatusWithStage::Underground
    );
}
