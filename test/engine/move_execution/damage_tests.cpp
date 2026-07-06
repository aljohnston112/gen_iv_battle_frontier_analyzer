#include "../mocks.h"
#include "move_execution.h"
#include "gtest/gtest.h"

template <IsPolicyTestCase Case>
void random_does_correct_damage_for_special_attacks(
    const MoveInfo* move
) {
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
        get_damage_of_power_move(
            effect_policy,
            rng_policy,
            battle_state,
            battle_state.player,
            battle_state.opponent,
            move,
            Who::Player
        )
    );
}

template <IsPolicyTestCase... Cases>
void random_does_correct_damage_for_special_attack(const Move move) {
    const auto& all_move_infos =
        get_all_moves();
    (random_does_correct_damage_for_special_attacks<Cases>(
            &all_move_infos[to_int(move)]
        ),
        ...
    );
}

// TODO use regular effectiveness
TEST(Engine, STABDoesCorrectDamageForSpecialAttack) {
    random_does_correct_damage_for_special_attack<
        PolicyTestCase<LowRandomEffectPolicy, FalseRNGPolicy, 15>,
        PolicyTestCase<HighRandomEffectPolicy, FalseRNGPolicy, 18>
    >(Move::Psychic);
}

// TODO use non-STAB
TEST(Engine, NotVeryEffectiveDoesCorrectDamageForSpecialAttack) {
    random_does_correct_damage_for_special_attack<
        PolicyTestCase<LowRandomEffectPolicy, FalseRNGPolicy, 15>,
        PolicyTestCase<HighRandomEffectPolicy, FalseRNGPolicy, 18>
    >(Move::Psychic);
}

TEST(Engine, RandomDoesCorrectDamageForSpecialAttack) {
    random_does_correct_damage_for_special_attack<
        PolicyTestCase<LowRandomEffectPolicy, FalseRNGPolicy, 22>,
        PolicyTestCase<HighRandomEffectPolicy, FalseRNGPolicy, 27>
    >(Move::IceBeam);
}

TEST(Engine, SuperEffectiveDoesTheCorrectDamageForSpecialAttack) {
    random_does_correct_damage_for_special_attack<
        PolicyTestCase<LowRandomEffectPolicy, FalseRNGPolicy, 34>,
        PolicyTestCase<HighRandomEffectPolicy, FalseRNGPolicy, 42>
    >(Move::SignalBeam);
}

TEST(Engine, CriticalHitDoesTheCorrectDamageForSpecialAttack) {
    random_does_correct_damage_for_special_attack<
        PolicyTestCase<LowRandomEffectPolicy, TrueRNGPolicy, 15>,
        PolicyTestCase<HighRandomEffectPolicy, TrueRNGPolicy, 18>
    >(Move::Psychic);
}
