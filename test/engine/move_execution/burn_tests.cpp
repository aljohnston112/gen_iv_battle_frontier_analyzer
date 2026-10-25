#include "end_of_turn_effects.h"
#include "../mocks.h"
#include "../test_policies.h"

#include "move_execution.h"

#include "gtest/gtest.h"

namespace {
    template <Move M>
    void move_causes_burn_on_true_roll(const CustomPokemon& custom_pokemon) {
        BattleState battle_state{
            PokemonState{&Suicune_7_2},
            PokemonState{&custom_pokemon}
        };

        EXPECT_FALSE(
            battle_state.player.has_status_condition(StatusCondition::Burn)
        );

        execute_move(
            ALWAYS_BURN_POLICY_CONTAINER,
            battle_state,
            Who::Opponent,
            M
        );

        EXPECT_TRUE(
            battle_state.player.has_status_condition(StatusCondition::Burn)
        );
    }

    template <Move M>
    void move_does_not_cause_burn_on_false_roll(
        const CustomPokemon& custom_pokemon
    ) {
        BattleState battle_state{
            PokemonState{&Suicune_7_2},
            PokemonState{&custom_pokemon}
        };

        EXPECT_FALSE(
            battle_state.player.has_status_condition(StatusCondition::Burn)
        );

        execute_move(
            NEVER_BURN_POLICY_CONTAINER,
            battle_state,
            Who::Opponent,
            M
        );

        EXPECT_FALSE(
            battle_state.player.has_status_condition(StatusCondition::Burn)
        );
    }

    template <Move M>
    void move_does_not_burn_fire_type(const CustomPokemon& custom_pokemon) {
        BattleState battle_state{
            PokemonState{&Entei_7_3},
            PokemonState{&custom_pokemon}
        };

        execute_move(
            ALWAYS_BURN_POLICY_CONTAINER,
            battle_state,
            Who::Opponent,
            M
        );

        EXPECT_FALSE(
            battle_state.player.has_status_condition(StatusCondition::Burn)
        );
    }
}

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

    roll_burn(
        ALWAYS_BURN_POLICY_CONTAINER,
        defender,
        Who::Player,
        10
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
    move_causes_burn_on_true_roll<Move::Flamethrower>(
        Heatran_7_3
    );
}

TEST(MoveExecution, FlamethrowerDoesNotBurnsOnFalseRoll) {
    move_does_not_cause_burn_on_false_roll<Move::Flamethrower>(
        Heatran_7_3
    );
}

TEST(MoveExecution, FlamethrowerDoesNotBurnFireTypeDefender) {
    move_does_not_burn_fire_type<Move::Flamethrower>(
        Heatran_7_3
    );
}

TEST(MoveExecution, FireBlastBurnsOnTrueRoll) {
    move_causes_burn_on_true_roll<Move::FireBlast>(Entei_7_3);
}

TEST(MoveExecution, FireBlastDoesNotBurnsOnFalseRoll) {
    move_does_not_cause_burn_on_false_roll<Move::FireBlast>(
        Entei_7_3
    );
}

TEST(MoveExecution, FireBlastDoesNotBurnFireTypeDefender) {
    move_does_not_burn_fire_type<Move::FireBlast>(
        Entei_7_3
    );
}

TEST(MoveExecution, FireFangBurnsOnTrueRoll) {
    move_causes_burn_on_true_roll<Move::FireFang>(Entei_7_2);
}

TEST(MoveExecution, FireFangDoesNotBurnsOnFalseRoll) {
    move_does_not_cause_burn_on_false_roll<Move::FireFang>(
        Entei_7_2
    );
}

TEST(MoveExecution, FireFangDoesNotBurnFireTypeDefender) {
    move_does_not_burn_fire_type<Move::FireFang>(
        Entei_7_2
    );
}