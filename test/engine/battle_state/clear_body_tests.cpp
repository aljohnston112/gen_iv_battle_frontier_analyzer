#include "../mocks.h"
#include "../test_policies.h"

#include "move_execution.h"

#include "gtest/gtest.h"

TEST(BattleState, ClearBodyPreventsStatDropFromOpponentMove) {
    BattleState battle_state{
        PokemonState{&Regirock_7_3},
        PokemonState{&Cresselia_7_4}
    };

    EXPECT_EQ(0, battle_state.player.get_stat_stage(Stat::SpecialDefense));

    execute_move(
        OPPONENT_OPTIMIZED_POLICY_CONTAINER,
        battle_state,
        Who::Opponent,
        Move::Psychic
    );

    EXPECT_EQ(0, battle_state.player.get_stat_stage(Stat::SpecialDefense));
}

TEST(BattleState, ClearBodyDoesNotPreventStatDropFromOwnMove) {
    BattleState battle_state{
        PokemonState{&Regirock_7_3},
        PokemonState{&Cresselia_7_4}
    };

    EXPECT_EQ(0, battle_state.player.get_stat_stage(Stat::Speed));

    execute_move(
        OPPONENT_OPTIMIZED_POLICY_CONTAINER,
        battle_state,
        Who::Player,
        Move::HammerArm
    );

    EXPECT_EQ(-1, battle_state.player.get_stat_stage(Stat::Speed));
}

TEST(BattleState, ClearBodyDoesNotPreventSpeedDropFromParalysis) {
    BattleState battle_state{
        PokemonState{&Regirock_7_3},
        PokemonState{&Cresselia_7_4}
    };

    const uint16_t speed_before = battle_state.player.get_current_stat(
        Stat::Speed);
    battle_state.player.try_set_status_condition(StatusCondition::Paralysis);

    EXPECT_LT(battle_state.player.get_current_stat(Stat::Speed), speed_before);
}

TEST(BattleState, ClearBodyDoesNotPreventAttackDropFromBurn) {
    BattleState battle_state{
        PokemonState{&Regirock_7_3},
        PokemonState{&Cresselia_7_4}
    };
    BattleState battle_state1{
        PokemonState{&Regirock_7_3},
        PokemonState{&Cresselia_7_4}
    };
    battle_state1.player.try_set_status_condition(StatusCondition::Burn);

    uint16_t damage_before = execute_move(
        OPPONENT_OPTIMIZED_POLICY_CONTAINER,
        battle_state,
        Who::Player,
        Move::HammerArm
    );

    EXPECT_LT(
        execute_move(
            OPPONENT_OPTIMIZED_POLICY_CONTAINER,
            battle_state1,
            Who::Player,
            Move::HammerArm
        ),
        damage_before
    );
}
