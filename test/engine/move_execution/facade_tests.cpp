#include "gtest/gtest.h"

#include "../mocks.h"
#include "../test_policies.h"

#include "battle_state.h"
#include "damage_util.h"
#include "policies.h"

TEST(MoveExecution, FacadeDoesCorrectDamageWhenAtackerIsHealthy) {
    const BattleState battle_state{
        PokemonState{&Regigigas_7_2},
        PokemonState{&Entei_7_3}
    };
    random_does_correct_damage_for_attack<
        DamageTestCase<NeverCritRNGPolicy, LowDamageRandomFactorPolicy, 34>,
        DamageTestCase<NeverCritRNGPolicy, HighDamageRandomFactorPolicy, 42>
    >(battle_state, Move::Facade);
}

namespace {
    void facadeDoesCorrectDamageWhenAttackerHasStatus(
        const StatusCondition status
    ) {
        BattleState battle_state{
            PokemonState{&Regigigas_7_2},
            PokemonState{&Entei_7_3}
        };
        battle_state.player.try_set_status_condition(status);

        EXPECT_TRUE(
            battle_state.player.has_status_condition(status)
        );

        random_does_correct_damage_for_attack<
            DamageTestCase<NeverCritRNGPolicy, LowDamageRandomFactorPolicy, 69>,
            DamageTestCase<NeverCritRNGPolicy, HighDamageRandomFactorPolicy, 82>
        >(battle_state, Move::Facade);
    }
}

TEST(MoveExecution, FacadeDoesCorrectDamageWhenAtackerIsPoisoned) {
    facadeDoesCorrectDamageWhenAttackerHasStatus(StatusCondition::PoisonStatus);
}

TEST(MoveExecution, FacadeDoesCorrectDamageWhenAtackerIsBadlyPoisoned) {
    facadeDoesCorrectDamageWhenAttackerHasStatus(StatusCondition::BadlyPoisoned);
}


TEST(MoveExecution, FacadeDoesCorrectDamageWhenAtackerIsParalyzed) {
    facadeDoesCorrectDamageWhenAttackerHasStatus(StatusCondition::Paralysis);
}


TEST(MoveExecution, FacadeDoesCorrectDamageWhenAtackerIsBurned) {
    BattleState battle_state{
        PokemonState{&Regigigas_7_2},
        PokemonState{&Entei_7_3}
    };
    battle_state.player.try_set_status_condition(StatusCondition::Burn);

    EXPECT_TRUE(
        battle_state.player.has_status_condition(StatusCondition::Burn)
    );
    random_does_correct_damage_for_attack<
        DamageTestCase<NeverCritRNGPolicy, LowDamageRandomFactorPolicy, 34>,
        DamageTestCase<NeverCritRNGPolicy, HighDamageRandomFactorPolicy, 42>
    >(battle_state, Move::Facade);
}


