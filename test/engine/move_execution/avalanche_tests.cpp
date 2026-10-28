#include "../mocks.h"
#include "../test_policies.h"

#include "damage_util.h"
#include "end_of_turn_effects.h"
#include "policies.h"
#include "turn_execution.h"

TEST(MoveExecution, AvalancheDoublesPowerOfMoveAfterGettingHitByDefender) {
    BattleState battle_state{
        PokemonState{&Regice_7_2},
        PokemonState{&Regice_7_2}
    };
    battle_state.player.add_damage(1, DamageSource::OtherPokemonPowerMove);

    EXPECT_EQ(
        14,
        execute_move(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state,
            Who::Player,
            Move::Avalanche
        )
    );
}

TEST(MoveExecution, AvalancheDoesNotDoublePowerOfMoveIfNotHitByDefender) {
    BattleState battle_state{
        PokemonState{&Regice_7_2},
        PokemonState{&Regice_7_2}
    };

    EXPECT_EQ(
        7,
        execute_move(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state,
            Who::Player,
            Move::Avalanche
        )
    );
}

TEST(MoveExecution, AvalancheGoesAfterNormalPriorityMove) {
    const BattleState battle_state{
        PokemonState{&Regice_7_2},
        PokemonState{&Regice_7_2}
    };

    EXPECT_EQ(
        Who::Player,
        who_goes_first(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state,
            Move::HammerArm,
            Move::Avalanche
        )
    );
}
