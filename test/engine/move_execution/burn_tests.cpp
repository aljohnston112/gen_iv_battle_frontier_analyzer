#include "end_of_turn_effects.h"
#include "../mocks.h"
#include "../test_policies.h"

#include "move_execution.h"

#include "gtest/gtest.h"

TEST(MoveExecution, FalseRollDoesNotBurn) {
    auto defender = PokemonState{&Cresselia_7_4};

    constexpr PolicyContainer<
        NeverBurnRNGPolicy
    > policy_container{};

    roll_burn(
        policy_container,
        defender,
        10,
        Who::Player
    );
    EXPECT_NE(
        StatusCondition::Burn,
        defender.get_current_status_condition()
    );
}

TEST(MoveExecution, TrueRollDoesBurn) {
    auto defender = PokemonState{&Cresselia_7_4};

    constexpr PolicyContainer<
        AlwaysBurnRNGPolicy
    > policy_container{};

    roll_burn(
        policy_container,
        defender,
        10,
        Who::Player
    );
    EXPECT_EQ(
        StatusCondition::Burn,
        defender.get_current_status_condition()
    );
}

TEST(MoveExecution, BurnHalvesPhysicalDamage) {
    // TODO
}

TEST(MoveExecution, BurnHalvesPhysicalDamageWithStatStageChangesIncluded) {
    // TODO
}

TEST(MoveExecution, EndOfTurnBurnDamageIsCorrect) {
    auto defender = PokemonState{&Cresselia_7_4};

    roll_burn(
        ALWAYS_BURN_POLICY_CONTAINER,
        defender,
        10,
        Who::Player
    );
    EXPECT_EQ(
        StatusCondition::Burn,
        defender.get_current_status_condition()
    );

    auto hp_before = defender.get_current_stat(Stat::Health);
    apply_end_of_turn_6(defender);
    EXPECT_EQ(
        hp_before - (defender.get_original_stat(Stat::Health) / 8),
        defender.get_current_stat(Stat::Health)
    );
}

TEST(MoveExecution, BurnDoesNotAffectSpecialDamage) {
    BattleState battle_state{
        PokemonState{&Heatran_7_3},
        PokemonState{&Cresselia_7_3}
    };

    battle_state.opponent.try_set_status_condition(StatusCondition::Burn);

    EXPECT_TRUE(
        battle_state.opponent.has_status_condition(StatusCondition::Burn)
    );
    EXPECT_EQ(
        72u,
        execute_move(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state,
            Who::Player,
            Move::Flamethrower
        )
    );
}

TEST(MoveExecution, FlamethrowerBurnsOnTrueRoll) {
    BattleState battle_state{
        PokemonState{&Heatran_7_3},
        PokemonState{&Cresselia_7_3}
    };

    execute_move(
        ALWAYS_BURN_POLICY_CONTAINER,
        battle_state,
        Who::Player,
        Move::Flamethrower
    );

    EXPECT_TRUE(
        battle_state.opponent.has_status_condition(StatusCondition::Burn)
    );
}

TEST(MoveExecution, FlamethrowerDoesNotBurnsOnFalseRoll) {
    BattleState battle_state{
        PokemonState{&Heatran_7_3},
        PokemonState{&Cresselia_7_3}
    };

    execute_move(
        NEVER_BURN_POLICY_CONTAINER,
        battle_state,
        Who::Player,
        Move::Flamethrower
    );

    EXPECT_FALSE(
        battle_state.opponent.has_status_condition(StatusCondition::Burn)
    );
}

TEST(MoveExecution, FlamethrowerDoesNotBurnFireTypeDefender) {
    // BattleState battle_state{
    //     PokemonState{&Heatran_7_3},
    //
    // };
    //
    // execute_move(
    //     ALWAYS_BURN_POLICY_CONTAINER,
    //     battle_state,
    //     Who::Player,
    //     get_move_info(Move::Flamethrower)
    // );
    //
    // EXPECT_TRUE(
    //     battle_state.opponent.has_status_condition(StatusCondition::Burn)
    // );
    // TODO when there is a fire type without flash fire
}
