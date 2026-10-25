#include "../mocks.h"
#include "../test_policies.h"

#include "move_execution.h"
#include "policies.h"

#include "gtest/gtest.h"

TEST(MoveExecution, SubstituteMakesAttackerLoseOneQuarterOfMaxHP) {
    BattleState battle_state{
        PokemonState{&Regigigas_7_2},
        PokemonState{&Heatran_7_3}
    };
    const uint16_t max_hp = battle_state.player.get_original_stat(Stat::Health);

    EXPECT_EQ(
        0,
        execute_move(
            REAL_ACCURACY_EVASION_POLICY_CONTAINER,
            battle_state,
            Who::Player,
            Move::Substitute
        )
    );
    EXPECT_EQ(
        max_hp - (max_hp / 4),
        battle_state.player.get_current_stat(Stat::Health)
    );
}

TEST(MoveExecution, SubstituteMakesAttackerHaveSubstitute) {
    BattleState battle_state{
        PokemonState{&Regigigas_7_2},
        PokemonState{&Heatran_7_3}
    };

    EXPECT_EQ(
        0,
        execute_move(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state,
            Who::Player,
            Move::Substitute
        )
    );
    EXPECT_TRUE(
        battle_state.player.has_move_status_with_stage(
            MoveStatusWithStage::BehindSubstitute
        )
    );
}

TEST(MoveExecution, SubstituteHasCorrectHP) {
    BattleState battle_state{
        PokemonState{&Regigigas_7_2},
        PokemonState{&Heatran_7_3}
    };
    const uint16_t max_hp = battle_state.player.get_original_stat(Stat::Health);

    EXPECT_EQ(
        0,
        execute_move(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state,
            Who::Player,
            Move::Substitute
        )
    );
    EXPECT_EQ(
        max_hp / 4,
        battle_state.player.get_move_status_stage(
            MoveStatusWithStage::BehindSubstitute
        )
    );
}

TEST(MoveExecution, SubstituteFailsIfAttackerHasSubstitute) {
    BattleState battle_state{
        PokemonState{&Regigigas_7_2},
        PokemonState{&Heatran_7_3}
    };
    const uint16_t max_hp = battle_state.player.get_original_stat(Stat::Health);

    EXPECT_EQ(
        0,
        execute_move(
            REAL_ACCURACY_EVASION_POLICY_CONTAINER,
            battle_state,
            Who::Player,
            Move::Substitute
        )
    );
    EXPECT_EQ(
        max_hp - (max_hp / 4),
        battle_state.player.get_current_stat(Stat::Health)
    );
    EXPECT_EQ(
        0,
        execute_move(
            REAL_ACCURACY_EVASION_POLICY_CONTAINER,
            battle_state,
            Who::Player,
            Move::Substitute
        )
    );
    EXPECT_EQ(
        max_hp - (max_hp / 4),
        battle_state.player.get_current_stat(Stat::Health)
    );
    EXPECT_EQ(
        max_hp / 4,
        battle_state.player.get_move_status_stage(
            MoveStatusWithStage::BehindSubstitute
        )
    );
}

TEST(MoveExecution, SubstituteTakesDamageInsteadOfDefender) {
    BattleState battle_state{
        PokemonState{&Regigigas_7_2},
        PokemonState{&Heatran_7_3}
    };
    const uint16_t max_hp = battle_state.player.get_original_stat(Stat::Health);

    EXPECT_EQ(
        0,
        execute_move(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state,
            Who::Player,
            Move::Substitute
        )
    );
    EXPECT_EQ(
        max_hp / 4,
        battle_state.player.get_move_status_stage(
            MoveStatusWithStage::BehindSubstitute
        )
    );
    EXPECT_EQ(
        max_hp - (max_hp / 4),
        battle_state.player.get_current_stat(Stat::Health)
    );
    EXPECT_EQ(
        0,
        execute_move(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state,
            Who::Opponent,
            Move::DarkPulse
        )
    );
    EXPECT_EQ(
        (max_hp / 4) - 44,
        battle_state.player.get_move_status_stage(
            MoveStatusWithStage::BehindSubstitute
        )
    );
    EXPECT_EQ(
        max_hp - (max_hp / 4),
        battle_state.player.get_current_stat(Stat::Health)
    );
}

TEST(MoveExecution, SubstituteFailsIfAttackerDoesNotHaveEnoughHP) {
    BattleState battle_state{
        PokemonState{&Regigigas_7_2},
        PokemonState{&Heatran_7_3}
    };
    const uint16_t max_hp = battle_state.player.get_original_stat(Stat::Health);

    battle_state.player.add_damage(max_hp - (max_hp / 4), DamageSource::DontCare);

    EXPECT_EQ(
        max_hp / 4,
        battle_state.player.get_current_stat(Stat::Health)
    );
    EXPECT_EQ(
        0,
        execute_move(
            REAL_ACCURACY_EVASION_POLICY_CONTAINER,
            battle_state,
            Who::Player,
            Move::Substitute
        )
    );
    EXPECT_FALSE(
        battle_state.player.has_move_status_with_stage(
            MoveStatusWithStage::BehindSubstitute
        )
    );
}

TEST(
    MoveExecution,
    StatDropFromOthersMoveDoesNotApplyToDefenderBehindSubstitute
) {
    BattleState battle_state{
        PokemonState{&Regigigas_7_2},
        PokemonState{&Latias_7_4}
    };

    EXPECT_EQ(
        0,
        execute_move(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state,
            Who::Player,
            Move::Substitute
        )
    );

    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state,
        Who::Opponent,
        Move::MistBall
    );

    EXPECT_EQ(
        0,
        battle_state.player.get_stat_stage(Stat::SpecialAttack)
    );
}

TEST(
    MoveExecution,
    StatDropFromAttackersMoveAppliesToAttackerBehindSubstitute
) {
    // TODO
    BattleState battle_state{
        PokemonState{&Latias_7_4_No_Item},
        PokemonState{&Latias_7_4}
    };
    battle_state.player.set_move_status_with_stage(
        MoveStatusWithStage::BehindSubstitute,
        Move::Substitute,
        100
    );
    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state,
        Who::Player,
        Move::DracoMeteor
    );

    EXPECT_EQ(
        -2,
        battle_state.player.get_stat_stage(Stat::SpecialAttack)
    );
}

TEST(
    MoveExecution,
    PoisonDoesNotApplyToDefenderBehindSubstitute
) {
    // TODO
    // BattleState battle_state{
    //     PokemonState{&Regigigas_7_2},
    //     PokemonState{&Heatran_7_3}
    // };
    // constexpr auto policy_container = OPPONENT_OPTIMIZED_POLICY_CONTAINER;
    //
    // EXPECT_EQ(
    //     0,
    //     execute_move(
    //         policy_container,
    //         battle_state,
    //         Who::Player,
    //         Move::Substitute
    //     )
    // );
    //
    // execute_move(
    //     policy_container,
    //     battle_state,
    //     Who::Opponent,
    //     Move::SignalBeam
    // );
    //
    // EXPECT_EQ(
    //     StatusCondition::NoCondition,
    //     battle_state.player.get_current_status_condition()
    // );
    // EXPECT_FALSE(
    //     battle_state.player.has_status_condition(StatusCondition::Freeze)
    // );
}


TEST(
    MoveExecution,
    BadPoisonDoesNotApplyToDefenderBehindSubstitute
) {
    // TODO
    // BattleState battle_state{
    //     PokemonState{&Regigigas_7_2},
    //     PokemonState{&Heatran_7_3}
    // };
    // constexpr auto policy_container = OPPONENT_OPTIMIZED_POLICY_CONTAINER;
    //
    // EXPECT_EQ(
    //     0,
    //     execute_move(
    //         policy_container,
    //         battle_state,
    //         Who::Player,
    //         Move::Substitute
    //     )
    // );
    //
    // execute_move(
    //     policy_container,
    //     battle_state,
    //     Who::Opponent,
    //     Move::SignalBeam
    // );
    //
    // EXPECT_EQ(
    //     StatusCondition::NoCondition,
    //     battle_state.player.get_current_status_condition()
    // );
    // EXPECT_FALSE(
    //     battle_state.player.has_status_condition(StatusCondition::Freeze)
    // );
}

TEST(
    MoveExecution,
    BurnDoesNotApplyToDefenderBehindSubstitute
) {
    BattleState battle_state{
        PokemonState{&Regigigas_7_2},
        PokemonState{&Heatran_7_3}
    };
    constexpr auto policy_container = OPPONENT_OPTIMIZED_POLICY_CONTAINER;

    EXPECT_EQ(
        0,
        execute_move(
            policy_container,
            battle_state,
            Who::Player,
            Move::Substitute
        )
    );

    execute_move(
        policy_container,
        battle_state,
        Who::Opponent,
        Move::Flamethrower
    );

    EXPECT_FALSE(
        battle_state.player.has_status_condition(StatusCondition::Burn)
    );
}

TEST(
    MoveExecution,
    ParalysisDoesNotApplyToDefenderBehindSubstitute
) {
    BattleState battle_state{
        PokemonState{&Regigigas_7_2},
        PokemonState{&Latias_7_4}
    };
    constexpr auto policy_container = OPPONENT_OPTIMIZED_POLICY_CONTAINER;

    EXPECT_EQ(
        0,
        execute_move(
            policy_container,
            battle_state,
            Who::Player,
            Move::Substitute
        )
    );

    execute_move(
        policy_container,
        battle_state,
        Who::Opponent,
        Move::Thunderbolt
    );

    EXPECT_FALSE(
        battle_state.player.has_status_condition(StatusCondition::Paralysis)
    );
}

TEST(
    MoveExecution,
    FreezeDoesNotApplyToDefenderBehindSubstitute
) {
    BattleState battle_state{
        PokemonState{&Regigigas_7_2},
        PokemonState{&Articuno_7_3}
    };
    constexpr auto policy_container = OPPONENT_OPTIMIZED_POLICY_CONTAINER;

    EXPECT_EQ(
        0,
        execute_move(
            policy_container,
            battle_state,
            Who::Player,
            Move::Substitute
        )
    );

    execute_move(
        policy_container,
        battle_state,
        Who::Opponent,
        Move::IceBeam
    );

    EXPECT_FALSE(
        battle_state.player.has_status_condition(StatusCondition::Freeze)
    );
}

TEST(
    MoveExecution,
    SleepDoesNotApplyToDefenderBehindSubstitute
) {
    // TODO
    // BattleState battle_state{
    //     PokemonState{&Regigigas_7_2},
    //     PokemonState{&Articuno_7_3}
    // };
    //
    // EXPECT_EQ(
    //     0,
    //     execute_move(
    //         DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
    //         battle_state,
    //         Who::Player,
    //         Move::Substitute
    //     )
    // );
    //
    // execute_move(
    //     OPPONENT_OPTIMIZED_POLICY_CONTAINER,
    //     battle_state,
    //     Who::Opponent,
    //     Move::SignalBeam
    // );
    //
    // EXPECT_FALSE(
    //     battle_state.player.has_status_condition(StatusCondition::Freeze)
    // );
}

TEST(
    MoveExecution,
    ConfusionDoesNotApplyToDefenderBehindSubstitute
) {
    BattleState battle_state{
        PokemonState{&Regigigas_7_2},
        PokemonState{&Cresselia_7_4}
    };
    constexpr auto policy_container = OPPONENT_OPTIMIZED_POLICY_CONTAINER;

    EXPECT_EQ(
        0,
        execute_move(
            policy_container,
            battle_state,
            Who::Player,
            Move::Substitute
        )
    );

    execute_move(
        policy_container,
        battle_state,
        Who::Opponent,
        Move::SignalBeam
    );

    EXPECT_FALSE(
        battle_state.player.has_status_with_stage(StatusWithStage::Confused)
    );
}

TEST(MoveExecution, SubstituteOnDefenderPreventsFlinchFromOpponentOnTrueRoll) {
    BattleState battle_state{
        PokemonState{&Regigigas_7_2},
        PokemonState{&Regigigas_7_2}
    };
    constexpr auto policy_container = ALWAYS_FLINCH_POLICY_CONTAINER;

    EXPECT_FALSE(battle_state.player.has_status(Status::Flinched));
    EXPECT_EQ(
        0,
        execute_move(
            policy_container,
            battle_state,
            Who::Player,
            Move::Substitute
        )
    );

    execute_move(
        policy_container,
        battle_state,
        Who::Opponent,
        Move::ZenHeadbutt
    );

    EXPECT_FALSE(battle_state.player.has_status(Status::Flinched));
}

TEST(MoveExecution, DamageExceedingSubstitutesHPDoesNotApplyToDefender) {
    BattleState battle_state{
        PokemonState{&Regigigas_7_2},
        PokemonState{&Regirock_7_3}
    };
    const uint16_t max_hp = battle_state.player.get_original_stat(Stat::Health);
    constexpr auto policy_container = OPPONENT_OPTIMIZED_POLICY_CONTAINER;

    EXPECT_EQ(
        0,
        execute_move(
            policy_container,
            battle_state,
            Who::Player,
            Move::Substitute
        )
    );
    EXPECT_EQ(
        max_hp - (max_hp / 4),
        battle_state.player.get_current_stat(Stat::Health)
    );

    execute_move(
        policy_container,
        battle_state,
        Who::Opponent,
        Move::HammerArm
    );

    EXPECT_EQ(
        max_hp - (max_hp / 4),
        battle_state.player.get_current_stat(Stat::Health)
    );
    EXPECT_FALSE(
        battle_state.player.has_move_status_with_stage(
            MoveStatusWithStage::BehindSubstitute
        )
    );
}
