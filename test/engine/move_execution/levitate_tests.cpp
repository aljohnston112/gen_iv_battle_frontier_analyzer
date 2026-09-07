#include "../mocks.h"
#include "../test_policies.h"

#include "battle_state.h"
#include "move_execution.h"

#include "gtest/gtest.h"

TEST(MoveExecution, GroundMoveDoesNoDamageToDefenderWithLevitate) {
    BattleState battle_state{
        PokemonState{&Regigias_7_3},
        PokemonState{&Cresselia_7_4}
    };

    EXPECT_EQ(
        0,
        execute_move(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state,
            Who::Player,
            Move::EarthPower
        )
    );
}

TEST(MoveExecution,
     NonGroundMovesCanHitDefenderWithLevitate
) {
    BattleState battle_state{
        PokemonState{&Cresselia_7_4},
        PokemonState{&Cresselia_7_4}
    };

    BattleState battle_state1{
        PokemonState{&Cresselia_7_3},
        PokemonState{&Cresselia_7_4}
    };

    BattleState battle_state2{
        PokemonState{&Heatran_7_3},
        PokemonState{&Cresselia_7_4}
    };

    BattleState battle_state3{
        PokemonState{&Latias_7_4},
        PokemonState{&Cresselia_7_4}
    };

    BattleState battle_state4{
        PokemonState{&Regigias_7_3},
        PokemonState{&Cresselia_7_4}
    };

    // Normal TODO

    // Fighting
    EXPECT_EQ(
        21,
        execute_move(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state4,
            Who::Player,
            Move::FocusBlast
        )
    );
    battle_state.opponent.add_hp(21);

    // Water
    EXPECT_EQ(
        38,
        execute_move(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state3,
            Who::Player,
            Move::Surf
        )
    );
    battle_state.opponent.add_hp(38);

    // Flying TODO

    // Grass
    EXPECT_EQ(
        28,
        execute_move(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state1,
            Who::Player,
            Move::EnergyBall
        )
    );
    battle_state.opponent.add_hp(28);

    // Poison TODO

    // Electric
    EXPECT_EQ(
        17,
        execute_move(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state1,
            Who::Player,
            Move::ChargeBeam
        )
    );
    battle_state.opponent.add_hp(17);

    // Fire
    EXPECT_EQ(
        63,
        execute_move(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state2,
            Who::Player,
            Move::Flamethrower
        )
    );
    battle_state.opponent.add_hp(63);

    // Psychic
    EXPECT_EQ(
        15,
        execute_move(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state,
            Who::Player,
            Move::Psychic
        )
    );
    battle_state.opponent.add_hp(15);

    //Rock
    EXPECT_EQ(
        22,
        execute_move(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state4,
            Who::Player,
            Move::Ancientpower
        )
    );
    battle_state.opponent.add_hp(22);

    // Ice
    EXPECT_EQ(
        22,
        execute_move(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state,
            Who::Player,
            Move::IceBeam
        )
    );
    battle_state.opponent.add_hp(22);

    // Bug
    EXPECT_EQ(
        34,
        execute_move(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state,
            Who::Player,
            Move::SignalBeam
        )
    );
    battle_state.opponent.add_hp(34);

    // Dragon
    EXPECT_EQ(
        39,
        execute_move(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state2,
            Who::Player,
            Move::DragonPulse
        )
    );
    battle_state.opponent.add_hp(39);

    // Ghost
    EXPECT_EQ(
        56,
        execute_move(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state1,
            Who::Player,
            Move::ShadowBall
        )
    );
    battle_state.opponent.add_hp(56);

    // Dark
    EXPECT_EQ(
        70,
        execute_move(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state2,
            Who::Player,
            Move::DarkPulse
        )
    );
    battle_state.opponent.add_hp(70);

    // Steel TODO
}
