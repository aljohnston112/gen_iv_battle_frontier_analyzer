#include "../mocks.h"
#include "move_execution.h"
#include "gtest/gtest.h"

template <IsDamageTestCase Case>
void random_does_correct_damage_for_special_attacks(
    const BattleState& battle_state,
    const MoveInfo* move
) {
    using CritRNGPolicyType = Case::CritRNGPolicyType;
    const CritRNGPolicyType crit_rng_policy{};
    using DamageRandomFactorPolicyType = Case::DamageRandomFactorPolicyType;
    const DamageRandomFactorPolicyType random_factor_policy{};
    static constexpr int32_t expected_damage = Case::ExpectedValue;

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
void random_does_correct_damage_for_special_attack(
const BattleState& battle_state,
    const Move move
    ) {
    const auto& all_move_infos =
        get_all_moves();
    (random_does_correct_damage_for_special_attacks<Cases>(
        battle_state,
            &all_move_infos[to_int(move)]
        ),
        ...
    );
}

// TODO use regular effectiveness
TEST(Engine, STABDoesCorrectDamageForSpecialAttack) {
    const BattleState battle_state{
        PokemonState{&Cresselia},
        PokemonState{&Cresselia}
    };
    random_does_correct_damage_for_special_attack<
        DamageTestCase<NeverCritRNGPolicy, LowDamageRandomFactorPolicy, 15>,
        DamageTestCase<NeverCritRNGPolicy, HighDamageRandomFactorPolicy, 18>
    >(battle_state, Move::Psychic);
}

// TODO use non-STAB
TEST(Engine, NotVeryEffectiveDoesCorrectDamageForSpecialAttack) {
    const BattleState battle_state{
        PokemonState{&Cresselia},
        PokemonState{&Cresselia}
    };
    random_does_correct_damage_for_special_attack<
        DamageTestCase<NeverCritRNGPolicy, LowDamageRandomFactorPolicy, 15>,
        DamageTestCase<NeverCritRNGPolicy, HighDamageRandomFactorPolicy, 18>
    >(battle_state, Move::Psychic);
}

TEST(Engine, RandomDoesCorrectDamageForSpecialAttack) {
    const BattleState battle_state{
        PokemonState{&Cresselia},
        PokemonState{&Cresselia}
    };
    random_does_correct_damage_for_special_attack<
        DamageTestCase<NeverCritRNGPolicy, LowDamageRandomFactorPolicy, 22>,
        DamageTestCase<NeverCritRNGPolicy, HighDamageRandomFactorPolicy, 27>
    >(battle_state, Move::IceBeam);
}

TEST(Engine, SuperEffectiveDoesTheCorrectDamageForSpecialAttack) {
    const BattleState battle_state{
        PokemonState{&Cresselia},
        PokemonState{&Cresselia}
    };
    random_does_correct_damage_for_special_attack<
        DamageTestCase<NeverCritRNGPolicy, LowDamageRandomFactorPolicy, 34>,
        DamageTestCase<NeverCritRNGPolicy, HighDamageRandomFactorPolicy, 42>
    >(battle_state, Move::SignalBeam);
}

TEST(Engine, CriticalHitDoesTheCorrectDamageForSpecialAttack) {
    const BattleState battle_state{
        PokemonState{&Cresselia},
        PokemonState{&Cresselia}
    };
    random_does_correct_damage_for_special_attack<
        DamageTestCase<AlwaysCritRNGPolicy, LowDamageRandomFactorPolicy, 31>,
        DamageTestCase<AlwaysCritRNGPolicy, HighDamageRandomFactorPolicy, 37>
    >(battle_state, Move::Psychic);
}

TEST(Engine, CriticalHitWithSpecialAttackBoostDoesTheCorrectDamageForSpecialAttack) {
    BattleState battle_state{
        PokemonState{&Cresselia},
        PokemonState{&Cresselia}
    };
    battle_state.player.increase_stat_stage(Stat::SpecialAttack, 6);
    random_does_correct_damage_for_special_attack<
        DamageTestCase<AlwaysCritRNGPolicy, LowDamageRandomFactorPolicy, 123>,
        DamageTestCase<AlwaysCritRNGPolicy, HighDamageRandomFactorPolicy, 145>
    >(battle_state, Move::Psychic);
}

TEST(Engine, CriticalHitWithSpecialDefenseLossDoesTheCorrectDamageForSpecialAttack) {
    BattleState battle_state{
        PokemonState{&Cresselia},
        PokemonState{&Cresselia}
    };
    battle_state.opponent.decrease_stat_stage(Stat::SpecialDefense, 5);
    random_does_correct_damage_for_special_attack<
        DamageTestCase<AlwaysCritRNGPolicy, LowDamageRandomFactorPolicy, 108>,
        DamageTestCase<AlwaysCritRNGPolicy, HighDamageRandomFactorPolicy, 127>
    >(battle_state, Move::Psychic);
}

TEST(Engine, CriticalHitWithSpecialAttackLossDoesTheCorrectDamageForSpecialAttack) {
    BattleState battle_state{
        PokemonState{&Cresselia},
        PokemonState{&Cresselia}
    };
    battle_state.player.decrease_stat_stage(Stat::SpecialAttack, 6);
    random_does_correct_damage_for_special_attack<
        DamageTestCase<AlwaysCritRNGPolicy, LowDamageRandomFactorPolicy, 31>,
        DamageTestCase<AlwaysCritRNGPolicy, HighDamageRandomFactorPolicy, 37>
    >(battle_state, Move::Psychic);
}

TEST(Engine, CriticalHitWithSpecialDefenseBoostDoesTheCorrectDamageForSpecialAttack) {
    BattleState battle_state{
        PokemonState{&Cresselia},
        PokemonState{&Cresselia}
    };
    battle_state.opponent.increase_stat_stage(Stat::SpecialDefense, 5);
    random_does_correct_damage_for_special_attack<
        DamageTestCase<AlwaysCritRNGPolicy, LowDamageRandomFactorPolicy, 31>,
        DamageTestCase<AlwaysCritRNGPolicy, HighDamageRandomFactorPolicy, 37>
    >(battle_state, Move::Psychic);
}