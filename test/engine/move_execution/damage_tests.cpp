#include "../mocks.h"
#include "move_execution.h"
#include "gtest/gtest.h"

template <IsDamageTestCase Case>
void random_does_correct_damage_for_special_attacks(
    const MoveInfo* move
) {
    using CritRNGPolicyType = Case::CritRNGPolicyType;
    const CritRNGPolicyType crit_rng_policy{};
    using DamageRandomFactorPolicyType = Case::DamageRandomFactorPolicyType;
    const DamageRandomFactorPolicyType random_factor_policy{};
    static constexpr int32_t expected_damage = Case::ExpectedValue;

    const BattleState battle_state{
        PokemonState{&Cresselia},
        PokemonState{&Cresselia}
    };
    EXPECT_EQ(
        expected_damage,
        get_damage_of_power_move(
            crit_rng_policy,
            random_factor_policy,
            battle_state,
            battle_state.player,
            battle_state.opponent,
            move,
            Who::Player
        )
    );
}

template <IsDamageTestCase... Cases>
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
        DamageTestCase<NeverCritRNGPolicy, LowDamageRandomFactorPolicy, 15>,
        DamageTestCase<NeverCritRNGPolicy, HighDamageRandomFactorPolicy, 18>
    >(Move::Psychic);
}

// TODO use non-STAB
TEST(Engine, NotVeryEffectiveDoesCorrectDamageForSpecialAttack) {
    random_does_correct_damage_for_special_attack<
        DamageTestCase<NeverCritRNGPolicy, LowDamageRandomFactorPolicy, 15>,
        DamageTestCase<NeverCritRNGPolicy, HighDamageRandomFactorPolicy, 18>
    >(Move::Psychic);
}

TEST(Engine, RandomDoesCorrectDamageForSpecialAttack) {
    random_does_correct_damage_for_special_attack<
        DamageTestCase<NeverCritRNGPolicy, LowDamageRandomFactorPolicy, 22>,
        DamageTestCase<NeverCritRNGPolicy, HighDamageRandomFactorPolicy, 27>
    >(Move::IceBeam);
}

TEST(Engine, SuperEffectiveDoesTheCorrectDamageForSpecialAttack) {
    random_does_correct_damage_for_special_attack<
        DamageTestCase<NeverCritRNGPolicy, LowDamageRandomFactorPolicy, 34>,
        DamageTestCase<NeverCritRNGPolicy, HighDamageRandomFactorPolicy, 42>
    >(Move::SignalBeam);
}

TEST(Engine, CriticalHitDoesTheCorrectDamageForSpecialAttack) {
    random_does_correct_damage_for_special_attack<
        DamageTestCase<AlwaysCritRNGPolicy, LowDamageRandomFactorPolicy, 31>,
        DamageTestCase<AlwaysCritRNGPolicy, HighDamageRandomFactorPolicy, 37>
    >(Move::Psychic);
}
