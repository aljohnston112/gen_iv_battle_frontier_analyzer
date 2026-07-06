#include "../mocks.h"
#include "move_execution.h"
#include "gtest/gtest.h"

template <IsPolicyTestCase Case>
void random_does_correct_damage_for_struggle_case() {
    using EffectPolicyType = Case::EffectPolicyType;
    const EffectPolicyType effect_policy{};
    using RNGPolicyType = Case::RNGPolicyType;
    const RNGPolicyType rng_policy{};
    static constexpr int32_t expected_damage = Case::ExpectedValue;

    const BattleState battle_state{
        PokemonState{&Cresselia},
        PokemonState{&Cresselia}
    };
    EXPECT_EQ(
        expected_damage,
        get_struggle_damage(
            effect_policy,
            rng_policy,
            battle_state.player,
            battle_state.opponent,
            Who::Player
        )
    );
}

template <IsPolicyTestCase... Cases>
void random_does_correct_damage_for_struggle() {
    (random_does_correct_damage_for_struggle_case<Cases>(),
        ...
    );
}

TEST(Engine, RandomDoesCorrectDamageForStruggle) {
    random_does_correct_damage_for_struggle<
        PolicyTestCase<LowRandomEffectPolicy, FalseRNGPolicy, 10>,
        PolicyTestCase<HighRandomEffectPolicy, FalseRNGPolicy, 12>
    >();
}

TEST(Engine, StruggleDoesTheRightAmountOfRecoil) {
    BattleState battle_state{
        PokemonState{&Cresselia},
        PokemonState{&Cresselia}
    };

    execute_struggle(
        HighRandomEffectPolicy{},
        FalseRNGPolicy{},
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