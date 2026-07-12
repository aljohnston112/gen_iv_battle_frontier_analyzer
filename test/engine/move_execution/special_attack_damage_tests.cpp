#include "../mocks.h"
#include "move_execution.h"
#include "gtest/gtest.h"

template <IsDamageTestCase Case>
void random_does_correct_damage_for_attack(
    const BattleState& battle_state,
    const MoveInfo* move
) {
    constexpr PolicyContainer<
        typename Case::CritRNGPolicyType,
        typename Case::DamageRandomFactorPolicyType
    > policy_container{};
    static constexpr int32_t expected_damage = Case::ExpectedValue;

    EXPECT_EQ(
        expected_damage,
        get_damage_of_power_move(
            policy_container,
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
    (random_does_correct_damage_for_attack<Cases>(
            battle_state,
            &all_move_infos[to_int(move)]
        ),
        ...
    );
}

// TODO use regular effectiveness
TEST(MoveExecution, STABDoesCorrectDamageForSpecialAttack) {
    const BattleState battle_state{
        PokemonState{&CresseliaLeftovers},
        PokemonState{&CresseliaLeftovers}
    };
    random_does_correct_damage_for_special_attack<
        DamageTestCase<NeverCritRNGPolicy, LowDamageRandomFactorPolicy, 15>,
        DamageTestCase<NeverCritRNGPolicy, HighDamageRandomFactorPolicy, 18>
    >(battle_state, Move::Psychic);
}

// TODO use non-STAB
TEST(MoveExecution, NotVeryEffectiveDoesCorrectDamageForSpecialAttack) {
    const BattleState battle_state{
        PokemonState{&CresseliaLeftovers},
        PokemonState{&CresseliaLeftovers}
    };
    random_does_correct_damage_for_special_attack<
        DamageTestCase<NeverCritRNGPolicy, LowDamageRandomFactorPolicy, 15>,
        DamageTestCase<NeverCritRNGPolicy, HighDamageRandomFactorPolicy, 18>
    >(battle_state, Move::Psychic);
}

TEST(MoveExecution, RandomDoesCorrectDamageForSpecialAttack) {
    const BattleState battle_state{
        PokemonState{&CresseliaLeftovers},
        PokemonState{&CresseliaLeftovers}
    };
    random_does_correct_damage_for_special_attack<
        DamageTestCase<NeverCritRNGPolicy, LowDamageRandomFactorPolicy, 22>,
        DamageTestCase<NeverCritRNGPolicy, HighDamageRandomFactorPolicy, 27>
    >(battle_state, Move::IceBeam);
}

TEST(MoveExecution, SuperEffectiveDoesTheCorrectDamageForSpecialAttack) {
    const BattleState battle_state{
        PokemonState{&CresseliaLeftovers},
        PokemonState{&CresseliaLeftovers}
    };
    random_does_correct_damage_for_special_attack<
        DamageTestCase<NeverCritRNGPolicy, LowDamageRandomFactorPolicy, 34>,
        DamageTestCase<NeverCritRNGPolicy, HighDamageRandomFactorPolicy, 42>
    >(battle_state, Move::SignalBeam);
}

TEST(MoveExecution, CriticalHitDoesTheCorrectDamageForSpecialAttack) {
    const BattleState battle_state{
        PokemonState{&CresseliaLeftovers},
        PokemonState{&CresseliaLeftovers}
    };
    random_does_correct_damage_for_special_attack<
        DamageTestCase<AlwaysCritRNGPolicy, LowDamageRandomFactorPolicy, 31>,
        DamageTestCase<AlwaysCritRNGPolicy, HighDamageRandomFactorPolicy, 37>
    >(battle_state, Move::Psychic);
}

TEST(
    Engine,
    CriticalHitWithSpecialAttackBoostDoesTheCorrectDamageForSpecialAttack
) {
    BattleState battle_state{
        PokemonState{&CresseliaLeftovers},
        PokemonState{&CresseliaLeftovers}
    };
    battle_state.player.increase_stat_stage(Stat::SpecialAttack, 6);
    random_does_correct_damage_for_special_attack<
        DamageTestCase<AlwaysCritRNGPolicy, LowDamageRandomFactorPolicy, 123>,
        DamageTestCase<AlwaysCritRNGPolicy, HighDamageRandomFactorPolicy, 145>
    >(battle_state, Move::Psychic);
}

TEST(
    Engine,
    CriticalHitWithSpecialDefenseLossDoesTheCorrectDamageForSpecialAttack
) {
    BattleState battle_state{
        PokemonState{&CresseliaLeftovers},
        PokemonState{&CresseliaLeftovers}
    };
    battle_state.opponent.decrease_stat_stage(Stat::SpecialDefense, 5);
    random_does_correct_damage_for_special_attack<
        DamageTestCase<AlwaysCritRNGPolicy, LowDamageRandomFactorPolicy, 108>,
        DamageTestCase<AlwaysCritRNGPolicy, HighDamageRandomFactorPolicy, 127>
    >(battle_state, Move::Psychic);
}

TEST(
    Engine,
    CriticalHitWithSpecialAttackLossDoesTheCorrectDamageForSpecialAttack
) {
    BattleState battle_state{
        PokemonState{&CresseliaLeftovers},
        PokemonState{&CresseliaLeftovers}
    };
    battle_state.player.decrease_stat_stage(Stat::SpecialAttack, 6);
    random_does_correct_damage_for_special_attack<
        DamageTestCase<AlwaysCritRNGPolicy, LowDamageRandomFactorPolicy, 31>,
        DamageTestCase<AlwaysCritRNGPolicy, HighDamageRandomFactorPolicy, 37>
    >(battle_state, Move::Psychic);
}

TEST(
    Engine,
    CriticalHitWithSpecialDefenseBoostDoesTheCorrectDamageForSpecialAttack
) {
    BattleState battle_state{
        PokemonState{&CresseliaLeftovers},
        PokemonState{&CresseliaLeftovers}
    };
    battle_state.opponent.increase_stat_stage(Stat::SpecialDefense, 5);
    random_does_correct_damage_for_special_attack<
        DamageTestCase<AlwaysCritRNGPolicy, LowDamageRandomFactorPolicy, 31>,
        DamageTestCase<AlwaysCritRNGPolicy, HighDamageRandomFactorPolicy, 37>
    >(battle_state, Move::Psychic);
}

struct IncreasingDamageRandomFactorPolicy :
    DamageRandomFactorPolicy<IncreasingDamageRandomFactorPolicy> {
    uint8_t roll_random(const Who) const {
        return current_random++;
    }

    uint8_t peek_next_random() const {
        return current_random;
    }

private:
    mutable uint8_t current_random = 85;
};

TEST(MoveExecution,
     DamageMonotonicallyIncreasesWithIncreasingRandomForSpecialAttacks) {
    BattleState battle_state{
        PokemonState{&CresseliaLeftovers},
        PokemonState{&CresseliaLeftovers}
    };
    battle_state.opponent.decrease_stat_stage(Stat::SpecialDefense, 5);

    constexpr int16_t min_damage = 108;
    constexpr int16_t max_damage = 127;
    random_does_correct_damage_for_special_attack<
        DamageTestCase<
            AlwaysCritRNGPolicy,
            LowDamageRandomFactorPolicy,
            min_damage
        >,
        DamageTestCase<
            AlwaysCritRNGPolicy,
            HighDamageRandomFactorPolicy,
            max_damage
        >
    >(battle_state, Move::Psychic);

    constexpr PolicyContainer<
        IncreasingDamageRandomFactorPolicy,
        AlwaysCritRNGPolicy
    > policy_container{};

    const auto& all_move_infos =
        get_all_moves();
    const auto move = &all_move_infos[to_int(Move::Psychic)];

    int16_t current_damage =
        get_damage_of_power_move(
            policy_container,
            battle_state,
            battle_state.player,
            battle_state.opponent,
            move,
            Who::Player
        );
    EXPECT_EQ(current_damage, min_damage);
    int16_t last_damage = current_damage;

    while (policy_container.peek_next_random() <= 100) {
        current_damage =
            get_damage_of_power_move(
                policy_container,
                battle_state,
                battle_state.player,
                battle_state.opponent,
                move,
                Who::Player
            );
        EXPECT_TRUE(current_damage >= last_damage);
        last_damage = current_damage;
    }
}
