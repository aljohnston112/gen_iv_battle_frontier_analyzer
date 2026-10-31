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
        Who::Player,
        10
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
        Who::Player,
        10
    );
    EXPECT_EQ(
        StatusCondition::Burn,
        defender.get_current_status_condition()
    );
}

TEST(MoveExecution, EndOfTurnBurnDamageIsCorrect) {
    auto defender = PokemonState{&Cresselia_7_4};

    auto policy_container = ALWAYS_BURN_POLICY_CONTAINER;
    roll_burn(
        policy_container,
        defender,
        Who::Player,
        10
    );
    EXPECT_EQ(
        StatusCondition::Burn,
        defender.get_current_status_condition()
    );

    auto hp_before = defender.get_current_stat(Stat::Health);
    apply_end_of_turn_6(policy_container, defender, Who::Player);
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

namespace {
    struct BurnTestCase {
        const CustomPokemon& custom_pokemon;
        Move move;
    };

    void move_causes_burn_on_true_roll(const BurnTestCase& test_case) {
        BattleState battle_state{
            PokemonState{&Suicune_7_2},
            PokemonState{&test_case.custom_pokemon}
        };

        EXPECT_FALSE(
            battle_state.player.has_status_condition(StatusCondition::Burn)
        );

        execute_move(
            ALWAYS_BURN_POLICY_CONTAINER,
            battle_state,
            Who::Opponent,
            test_case.move
        );

        EXPECT_TRUE(
            battle_state.player.has_status_condition(StatusCondition::Burn)
        );
    }

    void move_does_not_cause_burn_on_false_roll(
        const BurnTestCase& test_case
    ) {
        BattleState battle_state{
            PokemonState{&Suicune_7_2},
            PokemonState{&test_case.custom_pokemon}
        };

        EXPECT_FALSE(
            battle_state.player.has_status_condition(StatusCondition::Burn)
        );

        execute_move(
            NEVER_BURN_POLICY_CONTAINER,
            battle_state,
            Who::Opponent,
            test_case.move
        );

        EXPECT_FALSE(
            battle_state.player.has_status_condition(StatusCondition::Burn)
        );
    }

    void move_does_not_burn_fire_type(const BurnTestCase& test_case) {
        BattleState battle_state{
            PokemonState{&Entei_7_3},
            PokemonState{&test_case.custom_pokemon}
        };

        execute_move(
            ALWAYS_BURN_POLICY_CONTAINER,
            battle_state,
            Who::Opponent,
            test_case.move
        );

        EXPECT_FALSE(
            battle_state.player.has_status_condition(StatusCondition::Burn)
        );
    }

    constexpr BurnTestCase test_cases[] = {
        {.custom_pokemon = Heatran_7_3, .move = Move::Flamethrower},
        {.custom_pokemon = Entei_7_3, .move = Move::FireBlast},
        {.custom_pokemon = Entei_7_2, .move = Move::FireFang},
        {.custom_pokemon = Heatran_7_1, .move = Move::HeatWave},
    };
}


TEST(MoveExecution, MovesBurnOnTrueRoll) {
    for (const auto test_case : test_cases) {
        move_causes_burn_on_true_roll(test_case);
    }
}


TEST(MoveExecution, MovesDoNotBurnsOnFalseRoll) {
    for (const auto test_case : test_cases) {
        move_does_not_cause_burn_on_false_roll(test_case);
    }
}

TEST(MoveExecution, MovesDoNotBurnFireTypeDefender) {
    for (const auto test_case : test_cases) {
        move_does_not_burn_fire_type(test_case);
    }
}
