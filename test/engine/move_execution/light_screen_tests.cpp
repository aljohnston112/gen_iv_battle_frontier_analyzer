#include "damage_util.h"
#include "end_of_turn_effects.h"
#include "move_execution.h"
#include "../mocks.h"
#include "../test_policies.h"

#include "gtest/gtest.h"

TEST(MoveExecution, LightScreenFailsWhenItIsAlreadyUp) {
    BattleState battle_state{
        PokemonState{&Zapdos_7_2},
        PokemonState{&Suicune_7_3}
    };

    battle_state.player.set_status_with_stage(
        StatusWithStage::LightScreening,
        2
    );
    EXPECT_TRUE(
        battle_state.player.has_status_with_stage(
            StatusWithStage::LightScreening
        )
    );
    EXPECT_EQ(
        2,
        battle_state.player.get_status_stage(StatusWithStage::LightScreening)
    );

    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state,
        Who::Player,
        Move::LightScreen
    );
    apply_end_of_turn(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state
    );

    EXPECT_TRUE(
        battle_state.player.has_status_with_stage(
            StatusWithStage::LightScreening
        )
    );
    EXPECT_EQ(
        1,
        battle_state.player.get_status_stage(StatusWithStage::LightScreening)
    );
}

TEST(MoveExecution, LightScreenLastFiveTurns) {
    BattleState battle_state{
        PokemonState{&Zapdos_7_2},
        PokemonState{&Suicune_7_3}
    };

    EXPECT_FALSE(
        battle_state.player.has_status_with_stage(
            StatusWithStage::LightScreening
        )
    );
    EXPECT_EQ(
        0,
        battle_state.player.get_status_stage(
            StatusWithStage::LightScreening
        )
    );

    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state,
        Who::Player,
        Move::LightScreen
    );

    EXPECT_TRUE(
        battle_state.player.has_status_with_stage(
            StatusWithStage::LightScreening
        )
    );
    EXPECT_EQ(
        5,
        battle_state.player.get_status_stage(StatusWithStage::LightScreening)
    );

    for (uint8_t i = 0; i < 4; ++i) {
        apply_end_of_turn(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state
        );
        EXPECT_TRUE(
            battle_state.player.has_status_with_stage(
                StatusWithStage::LightScreening
            )
        );
        EXPECT_EQ(
            4 - i,
            battle_state.player.get_status_stage(
                StatusWithStage::LightScreening
            )
        );
    }

    apply_end_of_turn(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state
    );

    EXPECT_FALSE(
        battle_state.player.has_status_with_stage(
            StatusWithStage::LightScreening
        )
    );
    EXPECT_EQ(
        0,
        battle_state.player.get_status_stage(
            StatusWithStage::LightScreening
        )
    );
}

TEST(MoveExecution, LightScreenLastEightTurnsWhenUserIsHoldingLightClay) {
    BattleState battle_state{
        PokemonState{&Zapdos_7_2},
        PokemonState{&Suicune_7_3}
    };
    battle_state.player.set_item(Item::LightClay);

    EXPECT_FALSE(
        battle_state.player.has_status_with_stage(
            StatusWithStage::LightScreening
        )
    );
    EXPECT_EQ(
        0,
        battle_state.player.get_status_stage(
            StatusWithStage::LightScreening
        )
    );

    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state,
        Who::Player,
        Move::LightScreen
    );

    EXPECT_TRUE(
        battle_state.player.has_status_with_stage(
            StatusWithStage::LightScreening
        )
    );
    EXPECT_EQ(
        8,
        battle_state.player.get_status_stage(StatusWithStage::LightScreening)
    );

    for (uint8_t i = 0; i < 7; ++i) {
        apply_end_of_turn(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state
        );

        EXPECT_TRUE(
            battle_state.player.has_status_with_stage(
                StatusWithStage::LightScreening
            )
        );
        EXPECT_EQ(
            7 - i,
            battle_state.player.get_status_stage(
                StatusWithStage::LightScreening
            )
        );
    }

    apply_end_of_turn(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state
    );

    EXPECT_FALSE(
        battle_state.player.has_status_with_stage(
            StatusWithStage::LightScreening
        )
    );
    EXPECT_EQ(
        0,
        battle_state.player.get_status_stage(
            StatusWithStage::LightScreening
        )
    );
}

TEST(MoveExecution, LightScreenMakesSpecialMoveDoHalfDamage) {
    BattleState battle_state{
        PokemonState{&Suicune_7_3},
        PokemonState{&Zapdos_7_2}
    };

    EXPECT_FALSE(
        battle_state.opponent.has_status_with_stage(
            StatusWithStage::LightScreening
        )
    );
    EXPECT_EQ(
        0,
        battle_state.opponent.get_status_stage(
            StatusWithStage::LightScreening
        )
    );

    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state,
        Who::Opponent,
        Move::LightScreen
    );

    EXPECT_TRUE(
        battle_state.opponent.has_status_with_stage(
            StatusWithStage::LightScreening
        )
    );
    EXPECT_EQ(
        5,
        battle_state.opponent.get_status_stage(StatusWithStage::LightScreening)
    );


    random_does_correct_damage_for_attack<
        DamageTestCase<NeverCritRNGPolicy, LowDamageRandomFactorPolicy, 60>,
        DamageTestCase<NeverCritRNGPolicy, HighDamageRandomFactorPolicy, 72>
    >(battle_state, Move::Blizzard);
}

TEST(MoveExecution, LightScreenDoesNotAffectDamageOfPhysicalMoves) {
    BattleState battle_state{
        PokemonState{&Entei_7_2},
        PokemonState{&Zapdos_7_2}
    };

    EXPECT_FALSE(
        battle_state.opponent.has_status_with_stage(
            StatusWithStage::LightScreening
        )
    );
    EXPECT_EQ(
        0,
        battle_state.opponent.get_status_stage(
            StatusWithStage::LightScreening
        )
    );

    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state,
        Who::Opponent,
        Move::LightScreen
    );

    EXPECT_TRUE(
        battle_state.opponent.has_status_with_stage(
            StatusWithStage::LightScreening
        )
    );
    EXPECT_EQ(
        5,
        battle_state.opponent.get_status_stage(StatusWithStage::LightScreening)
    );


    random_does_correct_damage_for_attack<
        DamageTestCase<NeverCritRNGPolicy, LowDamageRandomFactorPolicy, 122>,
        DamageTestCase<NeverCritRNGPolicy, HighDamageRandomFactorPolicy, 144>
    >(battle_state, Move::StoneEdge);
}