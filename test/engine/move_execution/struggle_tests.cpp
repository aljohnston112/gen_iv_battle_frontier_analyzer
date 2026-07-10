#include "../mocks.h"
#include "move_execution.h"
#include "gtest/gtest.h"


template <IsDamageTestCase Case>
void random_does_correct_damage_for_struggle_case() {
    using CritRNGPolicyType = Case::CritRNGPolicyType;
    const CritRNGPolicyType crit_rng_policy{};

    using DamageRandomFactorPolicyType = Case::DamageRandomFactorPolicyType;
    const DamageRandomFactorPolicyType random_factor_policy{};

    static constexpr int32_t expected_damage = Case::ExpectedValue;

    const BattleState battle_state{
        PokemonState{&CresseliaLeftovers},
        PokemonState{&CresseliaLeftovers}
    };
    EXPECT_EQ(
        expected_damage,
        get_struggle_damage(
            random_factor_policy,
            crit_rng_policy,
            battle_state.player,
            battle_state.opponent,
            Who::Player
        )
    );
}

template <IsDamageTestCase... Cases>
void random_does_correct_damage_for_struggle() {
    (random_does_correct_damage_for_struggle_case<Cases>(),
        ...
    );
}

TEST(MoveExecution, RandomDoesCorrectDamageForStruggle) {
    random_does_correct_damage_for_struggle<
        DamageTestCase<NeverCritRNGPolicy, LowDamageRandomFactorPolicy, 10>,
        DamageTestCase<NeverCritRNGPolicy, HighDamageRandomFactorPolicy, 12>
    >();
}

TEST(MoveExecution, StruggleDoesTheRightAmountOfRecoil) {
    BattleState battle_state{
        PokemonState{&CresseliaLeftovers},
        PokemonState{&CresseliaLeftovers}
    };

    execute_struggle(
        HighDamageRandomFactorPolicy{},
        NeverCritRNGPolicy{},
        battle_state,
        battle_state.player,
        battle_state.opponent,
        Who::Player
    );

    const auto original_player_health =
        battle_state.player.get_original_stat(Stat::Health);
    EXPECT_EQ(
        battle_state.player.get_current_stat(Stat::Health),
        original_player_health - (original_player_health / 4)
    );
}
