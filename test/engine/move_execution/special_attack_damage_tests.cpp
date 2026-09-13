#include "../mocks.h"
#include "../test_policies.h"

#include "damage_util.h"
#include "end_of_turn_effects.h"
#include "move_execution.h"

#include "gtest/gtest.h"


TEST(MoveExecution, NormalEffectivenessDoesCorrectDamageForSpecialAttack) {
    const BattleState battle_state{
        PokemonState{&Regigias_7_3},
        PokemonState{&Cresselia_7_4}
    };
    random_does_correct_damage_for_attack<
        DamageTestCase<NeverCritRNGPolicy, LowDamageRandomFactorPolicy, 34>,
        DamageTestCase<NeverCritRNGPolicy, HighDamageRandomFactorPolicy, 40>
    >(battle_state, Move::Thunderbolt);
}


TEST(MoveExecution, STABDoesCorrectDamageForSpecialAttack) {
    const BattleState battle_state{
        PokemonState{&Cresselia_7_4},
        PokemonState{&Cresselia_7_4}
    };
    random_does_correct_damage_for_attack<
        DamageTestCase<NeverCritRNGPolicy, LowDamageRandomFactorPolicy, 15>,
        DamageTestCase<NeverCritRNGPolicy, HighDamageRandomFactorPolicy, 18>
    >(battle_state, Move::Psychic);
}

TEST(MoveExecution, NotVeryEffectiveSTABDoesCorrectDamageForSpecialAttack) {
    const BattleState battle_state{
        PokemonState{&Cresselia_7_4},
        PokemonState{&Cresselia_7_4}
    };
    random_does_correct_damage_for_attack<
        DamageTestCase<NeverCritRNGPolicy, LowDamageRandomFactorPolicy, 15>,
        DamageTestCase<NeverCritRNGPolicy, HighDamageRandomFactorPolicy, 18>
    >(battle_state, Move::Psychic);
}

TEST(MoveExecution, NotVeryEffectiveDoesCorrectDamageForSpecialAttack) {
    const BattleState battle_state{
        PokemonState{&Regigias_7_3},
        PokemonState{&Cresselia_7_4}
    };
    random_does_correct_damage_for_attack<
        DamageTestCase<NeverCritRNGPolicy, LowDamageRandomFactorPolicy, 21>,
        DamageTestCase<NeverCritRNGPolicy, HighDamageRandomFactorPolicy, 25>
    >(battle_state, Move::FocusBlast);
}

TEST(MoveExecution, RandomDoesCorrectDamageForSpecialAttack) {
    const BattleState battle_state{
        PokemonState{&Cresselia_7_4},
        PokemonState{&Cresselia_7_4}
    };
    random_does_correct_damage_for_attack<
        DamageTestCase<NeverCritRNGPolicy, LowDamageRandomFactorPolicy, 22>,
        DamageTestCase<NeverCritRNGPolicy, HighDamageRandomFactorPolicy, 27>
    >(battle_state, Move::IceBeam);
}

TEST(MoveExecution, SuperEffectiveDoesTheCorrectDamageForSpecialAttack) {
    const BattleState battle_state{
        PokemonState{&Cresselia_7_4},
        PokemonState{&Cresselia_7_4}
    };
    random_does_correct_damage_for_attack<
        DamageTestCase<NeverCritRNGPolicy, LowDamageRandomFactorPolicy, 34>,
        DamageTestCase<NeverCritRNGPolicy, HighDamageRandomFactorPolicy, 42>
    >(battle_state, Move::SignalBeam);
}

TEST(MoveExecution, CriticalHitDoesTheCorrectDamageForSpecialAttack) {
    const BattleState battle_state{
        PokemonState{&Cresselia_7_4},
        PokemonState{&Cresselia_7_4}
    };
    random_does_correct_damage_for_attack<
        DamageTestCase<AlwaysCritRNGPolicy, LowDamageRandomFactorPolicy, 31>,
        DamageTestCase<AlwaysCritRNGPolicy, HighDamageRandomFactorPolicy, 37>
    >(battle_state, Move::Psychic);
}

TEST(
    MoveExecution,
    CriticalHitWithSpecialAttackBoostDoesTheCorrectDamageForSpecialAttack
) {
    BattleState battle_state{
        PokemonState{&Cresselia_7_4},
        PokemonState{&Cresselia_7_4}
    };
    battle_state.player.increase_stat_stage<Stat::SpecialAttack>(6);
    random_does_correct_damage_for_attack<
        DamageTestCase<AlwaysCritRNGPolicy, LowDamageRandomFactorPolicy, 123>,
        DamageTestCase<AlwaysCritRNGPolicy, HighDamageRandomFactorPolicy, 145>
    >(battle_state, Move::Psychic);
}

TEST(
    MoveExecution,
    CriticalHitWithSpecialDefenseLossDoesTheCorrectDamageForSpecialAttack
) {
    BattleState battle_state{
        PokemonState{&Cresselia_7_4},
        PokemonState{&Cresselia_7_4}
    };
    battle_state.opponent.decrease_stat_stage<Stat::SpecialDefense>(5, StatDropSource::StatDropSourceCount);
    random_does_correct_damage_for_attack<
        DamageTestCase<AlwaysCritRNGPolicy, LowDamageRandomFactorPolicy, 108>,
        DamageTestCase<AlwaysCritRNGPolicy, HighDamageRandomFactorPolicy, 127>
    >(battle_state, Move::Psychic);
}

TEST(
    MoveExecution,
    CriticalHitWithSpecialAttackLossDoesTheCorrectDamageForSpecialAttack
) {
    BattleState battle_state{
        PokemonState{&Cresselia_7_4},
        PokemonState{&Cresselia_7_4}
    };
    battle_state.player.decrease_stat_stage<Stat::SpecialAttack>(6, StatDropSource::StatDropSourceCount);
    random_does_correct_damage_for_attack<
        DamageTestCase<AlwaysCritRNGPolicy, LowDamageRandomFactorPolicy, 31>,
        DamageTestCase<AlwaysCritRNGPolicy, HighDamageRandomFactorPolicy, 37>
    >(battle_state, Move::Psychic);
}

TEST(
    MoveExecution,
    CriticalHitWithSpecialDefenseBoostDoesTheCorrectDamageForSpecialAttack
) {
    BattleState battle_state{
        PokemonState{&Cresselia_7_4},
        PokemonState{&Cresselia_7_4}
    };
    battle_state.opponent.increase_stat_stage<Stat::SpecialDefense>(5);
    random_does_correct_damage_for_attack<
        DamageTestCase<AlwaysCritRNGPolicy, LowDamageRandomFactorPolicy, 31>,
        DamageTestCase<AlwaysCritRNGPolicy, HighDamageRandomFactorPolicy, 37>
    >(battle_state, Move::Psychic);
}

TEST(
    MoveExecution,
    DamageMonotonicallyIncreasesWithIncreasingRandomForSpecialAttacks
) {
    BattleState battle_state{
        PokemonState{&Cresselia_7_4},
        PokemonState{&Cresselia_7_4}
    };
    battle_state.opponent.decrease_stat_stage<Stat::SpecialDefense>(5, StatDropSource::StatDropSourceCount);

    constexpr int16_t min_damage = 108;
    constexpr int16_t max_damage = 127;
    random_does_correct_damage_for_attack<
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
        get_damage_of_move(
            policy_container,
            battle_state,
            move,
            Who::Player
        );
    EXPECT_EQ(current_damage, min_damage);
    int16_t last_damage = current_damage;

    while (policy_container.peek_next_random() <= 100) {
        current_damage =
            get_damage_of_move(
                policy_container,
                battle_state,
                move,
                Who::Player
            );
        EXPECT_TRUE(current_damage >= last_damage);
        last_damage = current_damage;
    }
}


