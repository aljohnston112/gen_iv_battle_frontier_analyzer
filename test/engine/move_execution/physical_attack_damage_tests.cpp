#include "../mocks.h"
#include "../test_policies.h"

#include "damage_util.h"
#include "end_of_turn_effects.h"
#include "move_execution.h"

#include "gtest/gtest.h"

TEST(MoveExecution, NormalEffectivenessDoesCorrectDamageForPhysicalAttack) {
    // TODO
}


TEST(MoveExecution, STABDoesCorrectDamageForPhysicalAttack) {
    const BattleState battle_state{
        PokemonState{&Regirock_7_3},
        PokemonState{&Cresselia_7_3}
    };
    random_does_correct_damage_for_attack<
        DamageTestCase<NeverCritRNGPolicy, LowDamageRandomFactorPolicy, 49>,
        DamageTestCase<NeverCritRNGPolicy, HighDamageRandomFactorPolicy, 58>
    >(battle_state, Move::StoneEdge);
}

TEST(MoveExecution, NotVeryEffectiveSTABDoesCorrectDamageForPhysicalAttack) {
    // TODO
}

TEST(MoveExecution, NotVeryEffectiveDoesCorrectDamageForPhysicalAttack) {
    const BattleState battle_state{
        PokemonState{&Regirock_7_3},
        PokemonState{&Cresselia_7_3}
    };
    random_does_correct_damage_for_attack<
        DamageTestCase<NeverCritRNGPolicy, LowDamageRandomFactorPolicy, 16>,
        DamageTestCase<NeverCritRNGPolicy, HighDamageRandomFactorPolicy, 19>
    >(battle_state, Move::HammerArm);
}

TEST(MoveExecution, SuperEffectiveDoesTheCorrectDamageForPhysicalAttack) {
    const BattleState battle_state{
        PokemonState{&Regirock_7_3},
        PokemonState{&Regigigas_7_3}
    };
    random_does_correct_damage_for_attack<
        DamageTestCase<NeverCritRNGPolicy, LowDamageRandomFactorPolicy, 70>,
        DamageTestCase<NeverCritRNGPolicy, HighDamageRandomFactorPolicy, 84>
    >(battle_state, Move::HammerArm);
}

TEST(MoveExecution, CriticalHitDoesTheCorrectDamageForPhysicalAttack) {
    const BattleState battle_state{
        PokemonState{&Regirock_7_3},
        PokemonState{&Cresselia_7_3}
    };
    random_does_correct_damage_for_attack<
        DamageTestCase<AlwaysCritRNGPolicy, LowDamageRandomFactorPolicy, 99>,
        DamageTestCase<AlwaysCritRNGPolicy, HighDamageRandomFactorPolicy, 117>
    >(battle_state, Move::StoneEdge);
}

TEST(
    MoveExecution,
    CriticalHitWithPhysicalAttackBoostDoesTheCorrectDamageForPhysicalAttack
) {
    BattleState battle_state{
        PokemonState{&Regirock_7_3},
        PokemonState{&Cresselia_7_3}
    };
    battle_state.player.increase_stat_stage<Stat::Attack>(6);
    random_does_correct_damage_for_attack<
        DamageTestCase<AlwaysCritRNGPolicy, LowDamageRandomFactorPolicy, 387>,
        DamageTestCase<AlwaysCritRNGPolicy, HighDamageRandomFactorPolicy, 456>
    >(battle_state, Move::StoneEdge);
}

TEST(
    MoveExecution,
    CriticalHitWithPhysicalDefenseLossDoesTheCorrectDamageForPhysicalAttack
) {
    BattleState battle_state{
        PokemonState{&Regirock_7_3},
        PokemonState{&Cresselia_7_3}
    };
    battle_state.opponent.decrease_stat_stage<Stat::Defense>(
        5,
        StatDropSource::StatDropSourceCount
    );
    random_does_correct_damage_for_attack<
        DamageTestCase<AlwaysCritRNGPolicy, LowDamageRandomFactorPolicy, 340>,
        DamageTestCase<AlwaysCritRNGPolicy, HighDamageRandomFactorPolicy, 402>
    >(battle_state, Move::StoneEdge);
}

TEST(
    MoveExecution,
    CriticalHitWithPhysicalAttackLossDoesTheCorrectDamageForPhysicalAttack
) {
    BattleState battle_state{
        PokemonState{&Regirock_7_3},
        PokemonState{&Cresselia_7_3}
    };
    battle_state.player.decrease_stat_stage<Stat::Attack>(
        6,
        StatDropSource::StatDropSourceCount
    );
    random_does_correct_damage_for_attack<
        DamageTestCase<AlwaysCritRNGPolicy, LowDamageRandomFactorPolicy, 99>,
        DamageTestCase<AlwaysCritRNGPolicy, HighDamageRandomFactorPolicy, 117>
    >(battle_state, Move::StoneEdge);
}

TEST(
    MoveExecution,
    CriticalHitWithPhysicalDefenseBoostDoesTheCorrectDamageForPhysicalAttack
) {
    BattleState battle_state{
        PokemonState{&Regirock_7_3},
        PokemonState{&Cresselia_7_3}
    };
    battle_state.opponent.increase_stat_stage<Stat::Defense>(6);
    random_does_correct_damage_for_attack<
        DamageTestCase<AlwaysCritRNGPolicy, LowDamageRandomFactorPolicy, 99>,
        DamageTestCase<AlwaysCritRNGPolicy, HighDamageRandomFactorPolicy, 117>
    >(battle_state, Move::StoneEdge);
}


TEST(
    MoveExecution,
    DamageMonotonicallyIncreasesWithIncreasingRandomForPhysicalAttacks
) {
    BattleState battle_state{
        PokemonState{&Regirock_7_3},
        PokemonState{&Cresselia_7_3}
    };
    battle_state.opponent.decrease_stat_stage<Stat::Defense>(
        5,
        StatDropSource::StatDropSourceCount
    );

    constexpr int16_t min_damage = 340;
    constexpr int16_t max_damage = 402;
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
    >(battle_state, Move::StoneEdge);

    constexpr PolicyContainer<
        IncreasingDamageRandomFactorPolicy,
        AlwaysCritRNGPolicy
    > policy_container{};

    const auto& all_move_infos =
        get_all_moves();
    const auto move = &all_move_infos[to_int(Move::StoneEdge)];

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

TEST(
    MoveExecution,
    STABDoesCorrectDamageForPhysicalAttackWhenAttackerIsBurnedAndAfterBurnIsCured
) {
    BattleState battle_state{
        PokemonState{&Regirock_7_3},
        PokemonState{&Cresselia_7_3}
    };
    battle_state.player.try_set_status_condition(StatusCondition::Burn);
    random_does_correct_damage_for_attack<
        DamageTestCase<NeverCritRNGPolicy, LowDamageRandomFactorPolicy, 25>,
        DamageTestCase<NeverCritRNGPolicy, HighDamageRandomFactorPolicy, 30>
    >(battle_state, Move::StoneEdge);
    battle_state.player.clear_status_condition();
    random_does_correct_damage_for_attack<
        DamageTestCase<NeverCritRNGPolicy, LowDamageRandomFactorPolicy, 49>,
        DamageTestCase<NeverCritRNGPolicy, HighDamageRandomFactorPolicy, 58>
    >(battle_state, Move::StoneEdge);
}

TEST(
    MoveExecution,
    NormalEffectivenessDoesCorrectDamageForPhysicalAttackWhenAttackerIsBurned
) {
    // TODO
}


TEST(
    MoveExecution,
    STABDoesCorrectDamageForPhysicalAttackWhenAttackerIsBurned
) {
    BattleState battle_state{
        PokemonState{&Regirock_7_3},
        PokemonState{&Cresselia_7_3}
    };
    battle_state.player.try_set_status_condition(StatusCondition::Burn);
    random_does_correct_damage_for_attack<
        DamageTestCase<NeverCritRNGPolicy, LowDamageRandomFactorPolicy, 25>,
        DamageTestCase<NeverCritRNGPolicy, HighDamageRandomFactorPolicy, 30>
    >(battle_state, Move::StoneEdge);
}

TEST(
    MoveExecution,
    NotVeryEffectiveSTABDoesCorrectDamageForPhysicalAttackWhenAttackerIsBurned
) {
    // TODO
}

TEST(
    MoveExecution,
    NotVeryEffectiveDoesCorrectDamageForPhysicalAttackWhenAttackerIsBurned
) {
    BattleState battle_state{
        PokemonState{&Regirock_7_3},
        PokemonState{&Cresselia_7_3}
    };
    battle_state.player.try_set_status_condition(StatusCondition::Burn);
    random_does_correct_damage_for_attack<
        DamageTestCase<NeverCritRNGPolicy, LowDamageRandomFactorPolicy, 8>,
        DamageTestCase<NeverCritRNGPolicy, HighDamageRandomFactorPolicy, 10>
    >(battle_state, Move::HammerArm);
}

TEST(
    MoveExecution,
    SuperEffectiveDoesTheCorrectDamageForPhysicalAttackWhenAttackerIsBurned
) {
    BattleState battle_state{
        PokemonState{&Regirock_7_3},
        PokemonState{&Regigigas_7_3}
    };
    battle_state.player.try_set_status_condition(StatusCondition::Burn);
    random_does_correct_damage_for_attack<
        DamageTestCase<NeverCritRNGPolicy, LowDamageRandomFactorPolicy, 36>,
        DamageTestCase<NeverCritRNGPolicy, HighDamageRandomFactorPolicy, 44>
    >(battle_state, Move::HammerArm);
}

TEST(
    MoveExecution,
    CriticalHitDoesTheCorrectDamageForPhysicalAttackWhenAttackerIsBurned
) {
    BattleState battle_state{
        PokemonState{&Regirock_7_3},
        PokemonState{&Cresselia_7_3}
    };
    battle_state.player.try_set_status_condition(StatusCondition::Burn);
    random_does_correct_damage_for_attack<
        DamageTestCase<AlwaysCritRNGPolicy, LowDamageRandomFactorPolicy, 51>,
        DamageTestCase<AlwaysCritRNGPolicy, HighDamageRandomFactorPolicy, 60>
    >(battle_state, Move::StoneEdge);
}

TEST(
    MoveExecution,
    CriticalHitWithPhysicalAttackBoostDoesTheCorrectDamageForPhysicalAttackWhenAttackerIsBurned
) {
    BattleState battle_state{
        PokemonState{&Regirock_7_3},
        PokemonState{&Cresselia_7_3}
    };
    battle_state.player.try_set_status_condition(StatusCondition::Burn);
    battle_state.player.increase_stat_stage<Stat::Attack>(6);
    random_does_correct_damage_for_attack<
        DamageTestCase<AlwaysCritRNGPolicy, LowDamageRandomFactorPolicy, 195>,
        DamageTestCase<AlwaysCritRNGPolicy, HighDamageRandomFactorPolicy, 231>
    >(battle_state, Move::StoneEdge);
}

TEST(
    MoveExecution,
    CriticalHitWithPhysicalDefenseLossDoesTheCorrectDamageForPhysicalAttackWhenAttackerIsBurned
) {
    BattleState battle_state{
        PokemonState{&Regirock_7_3},
        PokemonState{&Cresselia_7_3}
    };
    battle_state.player.try_set_status_condition(StatusCondition::Burn);
    battle_state.opponent.decrease_stat_stage<Stat::Defense>(
        5,
        StatDropSource::StatDropSourceCount
    );
    random_does_correct_damage_for_attack<
        DamageTestCase<AlwaysCritRNGPolicy, LowDamageRandomFactorPolicy, 172>,
        DamageTestCase<AlwaysCritRNGPolicy, HighDamageRandomFactorPolicy, 204>
    >(battle_state, Move::StoneEdge);
}

TEST(
    MoveExecution,
    CriticalHitWithPhysicalAttackLossDoesTheCorrectDamageForPhysicalAttackWhenAttackerIsBurned
) {
    BattleState battle_state{
        PokemonState{&Regirock_7_3},
        PokemonState{&Cresselia_7_3}
    };
    battle_state.player.try_set_status_condition(StatusCondition::Burn);
    battle_state.player.decrease_stat_stage<Stat::Attack>(
        6,
        StatDropSource::StatDropSourceCount
    );
    random_does_correct_damage_for_attack<
        DamageTestCase<AlwaysCritRNGPolicy, LowDamageRandomFactorPolicy, 51>,
        DamageTestCase<AlwaysCritRNGPolicy, HighDamageRandomFactorPolicy, 60>
    >(battle_state, Move::StoneEdge);
}

TEST(
    MoveExecution,
    CriticalHitWithPhysicalDefenseBoostDoesTheCorrectDamageForPhysicalAttackWhenAttackerIsBurned
) {
    BattleState battle_state{
        PokemonState{&Regirock_7_3},
        PokemonState{&Cresselia_7_3}
    };
    battle_state.player.try_set_status_condition(StatusCondition::Burn);
    battle_state.opponent.increase_stat_stage<Stat::Defense>(6);
    random_does_correct_damage_for_attack<
        DamageTestCase<AlwaysCritRNGPolicy, LowDamageRandomFactorPolicy, 51>,
        DamageTestCase<AlwaysCritRNGPolicy, HighDamageRandomFactorPolicy, 60>
    >(battle_state, Move::StoneEdge);
}


TEST(
    MoveExecution,
    DamageMonotonicallyIncreasesWithIncreasingRandomForPhysicalAttacksWhenAttackerIsBurned
) {
    BattleState battle_state{
        PokemonState{&Regirock_7_3},
        PokemonState{&Cresselia_7_3}
    };
    battle_state.player.try_set_status_condition(StatusCondition::Burn);
    battle_state.opponent.decrease_stat_stage<Stat::Defense>(
        5,
        StatDropSource::StatDropSourceCount
    );

    constexpr int16_t min_damage = 172;
    constexpr int16_t max_damage = 204;
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
    >(battle_state, Move::StoneEdge);

    constexpr PolicyContainer<
        IncreasingDamageRandomFactorPolicy,
        AlwaysCritRNGPolicy
    > policy_container{};

    const auto& all_move_infos =
        get_all_moves();
    const auto move = &all_move_infos[to_int(Move::StoneEdge)];

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
