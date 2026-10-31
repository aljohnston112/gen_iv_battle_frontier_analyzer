#include "battle_state.h"
#include "end_of_turn_effects.h"
#include "move_execution.h"
#include "../mocks.h"
#include "../test_policies.h"
#include "gtest/gtest.h"

TEST(MoveExecution, ToxicBadlyPoisonsDefender) {
    BattleState battle_state{
        PokemonState{&Cresselia_7_2},
        PokemonState{&Cresselia_7_4_NoItem}
    };

    EXPECT_FALSE(
        battle_state.opponent.has_status_with_stage(
            StatusWithStage::BadlyPoisoned
        )
    );
    EXPECT_EQ(
        0,
        battle_state.opponent.get_status_stage(
            StatusWithStage::BadlyPoisoned
        )
    );
    EXPECT_EQ(
        StatusCondition::NoCondition,
        battle_state.opponent.get_current_status_condition()
    );

    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state,
        Who::Player,
        Move::Toxic
    );

    EXPECT_TRUE(
        battle_state.opponent.has_status_with_stage(
            StatusWithStage::BadlyPoisoned
        )
    );
    EXPECT_EQ(
        1,
        battle_state.opponent.get_status_stage(
            StatusWithStage::BadlyPoisoned
        )
    );
    EXPECT_EQ(
        StatusCondition::BadlyPoisoned,
        battle_state.opponent.get_current_status_condition()
    );
}

TEST(MoveExecution, ToxicDamageIncreases) {
    BattleState battle_state{
        PokemonState{&Cresselia_7_2},
        PokemonState{&Cresselia_7_4_NoItem}
    };

    EXPECT_FALSE(
        battle_state.opponent.has_status_with_stage(
            StatusWithStage::BadlyPoisoned
        )
    );

    EXPECT_EQ(
        StatusCondition::NoCondition,
        battle_state.opponent.get_current_status_condition()
    );

    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state,
        Who::Player,
        Move::Toxic
    );
    EXPECT_TRUE(
        battle_state.opponent.has_status_with_stage(
            StatusWithStage::BadlyPoisoned
        )
    );
    EXPECT_EQ(
        1,
        battle_state.opponent.get_status_stage(
            StatusWithStage::BadlyPoisoned
        )
    );
    EXPECT_EQ(
        StatusCondition::BadlyPoisoned,
        battle_state.opponent.get_current_status_condition()
    );

    const uint16_t max_hp =
        battle_state.opponent.get_current_stat(Stat::Health);

    for (uint8_t i = 0; i < 16; i++) {
        apply_end_of_turn(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state
        );
        const uint16_t expected_damage = (i + 1) * (max_hp / 16);
        const uint16_t expected_hp = std::max(0, max_hp - expected_damage);

        EXPECT_EQ(
            expected_hp,
            battle_state.opponent.get_current_stat(Stat::Health)
        );
        EXPECT_TRUE(
            battle_state.opponent.has_status_with_stage(
                StatusWithStage::BadlyPoisoned
            )
        );
        EXPECT_EQ(
            i + 2,
            battle_state.opponent.get_status_stage(
                StatusWithStage::BadlyPoisoned
            )
        );
        EXPECT_EQ(
            StatusCondition::BadlyPoisoned,
            battle_state.opponent.get_current_status_condition()
        );

        battle_state.opponent.add_hp(expected_damage);
    }
}

TEST(MoveExecution, ToxicBDoesNotPosionSteelTypeDefender) {
    BattleState battle_state{
        PokemonState{&Registeel_7_1},
        PokemonState{&Cresselia_7_2}
    };

    EXPECT_FALSE(
        battle_state.player.has_status_with_stage(
            StatusWithStage::BadlyPoisoned
        )
    );
    EXPECT_EQ(
        0,
        battle_state.player.get_status_stage(
            StatusWithStage::BadlyPoisoned
        )
    );
    EXPECT_EQ(
        StatusCondition::NoCondition,
        battle_state.player.get_current_status_condition()
    );

    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state,
        Who::Opponent,
        Move::Toxic
    );

    EXPECT_FALSE(
        battle_state.player.has_status_with_stage(
            StatusWithStage::BadlyPoisoned
        )
    );
    EXPECT_EQ(
        0,
        battle_state.player.get_status_stage(
            StatusWithStage::BadlyPoisoned
        )
    );
    EXPECT_EQ(
        StatusCondition::NoCondition,
        battle_state.player.get_current_status_condition()
    );
}
