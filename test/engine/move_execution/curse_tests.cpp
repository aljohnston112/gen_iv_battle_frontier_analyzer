#include "../mocks.h"
#include "../test_policies.h"

#include "move_execution.h"

#include "gtest/gtest.h"

TEST(MoveExecution, CurseCursesDefenderWhenUsedByNonGhostTypeWithGhostType) {
    BattleState battle_state{
        PokemonState{&Regirock_7_3},
        PokemonState{&Regirock_7_3}
    };
    battle_state.player.set_type(PokemonType::Ghost);

    ASSERT_TRUE(battle_state.player.has_type(PokemonType::Ghost));
    ASSERT_TRUE(battle_state.player.has_type(PokemonType::NoType));

    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state,
        Who::Player,
        Move::Curse
    );

    ASSERT_TRUE(battle_state.opponent.has_status(Status::Cursed));
}

TEST(
    MoveExecution,
    WhenUsedByNonGhostTypeWithGhostTypeCurseTakesHalfOfTheirMaxHPInDamage
) {
    BattleState battle_state{
        PokemonState{&Regirock_7_3},
        PokemonState{&Regirock_7_3}
    };
    const uint16_t hp_before =
        battle_state.player.get_current_stat(Stat::Health);
    battle_state.player.set_type(PokemonType::Ghost);

    ASSERT_TRUE(battle_state.player.has_type(PokemonType::Ghost));
    ASSERT_TRUE(battle_state.player.has_type(PokemonType::NoType));

    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state,
        Who::Player,
        Move::Curse
    );

    ASSERT_EQ(
        hp_before - (battle_state.player.get_original_stat(Stat::Health) / 2),
        battle_state.player.get_current_stat(Stat::Health)
    );
}


TEST(
    MoveExecution,
    AttackDefenseAndSpeedStageStaysTheSameWhenCurseIsUsedByNonGhostTypeWithGhostType
) {
    BattleState battle_state{
        PokemonState{&Regirock_7_3},
        PokemonState{&Regirock_7_3}
    };
    battle_state.player.set_type(PokemonType::Ghost);

    ASSERT_TRUE(battle_state.player.has_type(PokemonType::Ghost));
    ASSERT_TRUE(battle_state.player.has_type(PokemonType::NoType));

    const uint16_t attack_before =
        battle_state.player.get_current_stat(Stat::Attack);
    const uint16_t defense_before =
        battle_state.player.get_current_stat(Stat::Defense);
    const uint16_t speed_before =
        battle_state.player.get_current_stat(Stat::Speed);

    ASSERT_EQ(0, battle_state.player.get_stat_stage(Stat::Attack));
    ASSERT_EQ(0, battle_state.player.get_stat_stage(Stat::Defense));
    ASSERT_EQ(0, battle_state.player.get_stat_stage(Stat::Speed));

    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state,
        Who::Player,
        Move::Curse
    );

    ASSERT_EQ(
        attack_before,
        battle_state.player.get_current_stat(Stat::Attack)
    );
    ASSERT_EQ(
        defense_before,
        battle_state.player.get_current_stat(Stat::Defense)
    );
    ASSERT_EQ(
        speed_before,
        battle_state.player.get_current_stat(Stat::Speed)
    );
    ASSERT_EQ(0, battle_state.player.get_stat_stage(Stat::Attack));
    ASSERT_EQ(0, battle_state.player.get_stat_stage(Stat::Defense));
    ASSERT_EQ(0, battle_state.player.get_stat_stage(Stat::Speed));
}


static void
curse_misses_when_used_by_non_ghost_type_with_ghost_type_and_defender_is_semi_invulnerable(
    const MoveStatusWithStage move_status_with_stage
) {
    BattleState battle_state{
        PokemonState{&Regirock_7_3},
        PokemonState{&Regirock_7_3}
    };
    battle_state.player.set_type(PokemonType::Ghost);

    ASSERT_TRUE(battle_state.player.has_type(PokemonType::Ghost));
    ASSERT_TRUE(battle_state.player.has_type(PokemonType::NoType));

    battle_state.opponent.set_move_status_with_stage(
        move_status_with_stage,
        Move::ShadowForce,
        1
    );

    ASSERT_TRUE(
        battle_state.opponent.has_move_status_with_stage(
            move_status_with_stage
        )
    );
    ASSERT_TRUE(
        battle_state.opponent.is_semi_invulnerable()
    );

    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state,
        Who::Player,
        Move::Curse
    );

    ASSERT_FALSE(battle_state.opponent.has_status(Status::Cursed));
}

TEST(
    MoveExecution,
    CurseMissesDefenderWhenUsedByNonGhostTypeWithGhostTypeAndDefenderIsConcealed
) {
    curse_misses_when_used_by_non_ghost_type_with_ghost_type_and_defender_is_semi_invulnerable(
        MoveStatusWithStage::Concealed
    );
}


TEST(
    MoveExecution,
    CurseMissesDefenderWhenUsedByNonGhostTypeWithGhostTypeAndDefenderIsSkyHigh
) {
    curse_misses_when_used_by_non_ghost_type_with_ghost_type_and_defender_is_semi_invulnerable(
        MoveStatusWithStage::SkyHigh
    );
}


TEST(
    MoveExecution,
    CurseMissesDefenderWhenUsedByNonGhostTypeWithGhostTypeAndDefenderIsSubmerged
) {
    curse_misses_when_used_by_non_ghost_type_with_ghost_type_and_defender_is_semi_invulnerable(
        MoveStatusWithStage::Submerged
    );
}


TEST(
    MoveExecution,
    CurseMissesDefenderWhenUsedByNonGhostTypeWithGhostTypeAndDefenderIsUnderground
) {
    curse_misses_when_used_by_non_ghost_type_with_ghost_type_and_defender_is_semi_invulnerable(
        MoveStatusWithStage::Underground
    );
}

TEST(
    MoveExecution,
    CurseDropsNonGhostTypeUsersSpeedByOneStageAndRaisesItsAttackAndDefenseByOneStage
) {
    BattleState battle_state{
        PokemonState{&Regirock_7_3},
        PokemonState{&Regirock_7_3}
    };

    const uint16_t hp_before =
        battle_state.player.get_current_stat(Stat::Health);
    const uint16_t attack_before =
        battle_state.player.get_current_stat(Stat::Attack);
    const uint16_t defense_before =
        battle_state.player.get_current_stat(Stat::Defense);
    const uint16_t speed_before =
        battle_state.player.get_current_stat(Stat::Speed);

    ASSERT_EQ(0, battle_state.player.get_stat_stage(Stat::Attack));
    ASSERT_EQ(0, battle_state.player.get_stat_stage(Stat::Defense));
    ASSERT_EQ(0, battle_state.player.get_stat_stage(Stat::Speed));

    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state,
        Who::Player,
        Move::Curse
    );

    ASSERT_EQ(
        hp_before,
        battle_state.player.get_current_stat(Stat::Health)
    );
    ASSERT_LT(
        attack_before,
        battle_state.player.get_current_stat(Stat::Attack)
    );
    ASSERT_LT(
        defense_before,
        battle_state.player.get_current_stat(Stat::Defense)
    );
    ASSERT_GT(
        speed_before,
        battle_state.player.get_current_stat(Stat::Speed)
    );
    ASSERT_EQ(1, battle_state.player.get_stat_stage(Stat::Attack));
    ASSERT_EQ(1, battle_state.player.get_stat_stage(Stat::Defense));
    ASSERT_EQ(-1, battle_state.player.get_stat_stage(Stat::Speed));
}

TEST(MoveExecution, CurseDropsNotDropUsersHPWhenUsedByNonGhostTypeUser) {
    BattleState battle_state{
        PokemonState{&Regirock_7_3},
        PokemonState{&Regirock_7_3}
    };

    const uint16_t hp_before =
        battle_state.player.get_current_stat(Stat::Health);

    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state,
        Who::Player,
        Move::Curse
    );

    ASSERT_EQ(
        hp_before,
        battle_state.player.get_current_stat(Stat::Health)
    );
}

TEST(MoveExecution, CurseDropsNotCurseDefenderWhenUsedByNonGhostTypeUser) {
    BattleState battle_state{
        PokemonState{&Regirock_7_3},
        PokemonState{&Regirock_7_3}
    };

    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state,
        Who::Player,
        Move::Curse
    );

    ASSERT_FALSE(battle_state.opponent.has_status(Status::Cursed));
}

TEST(
    MoveExecution,
    CurseDropsUsersSpeedWhenAttackAndDefenseAreMaxedOutWhenUsedByNonGhostTypeUser
) {
    BattleState battle_state{
        PokemonState{&Regirock_7_3},
        PokemonState{&Regirock_7_3}
    };

    battle_state.player.increase_stat_stage<Stat::Attack>(6);
    battle_state.player.increase_stat_stage<Stat::Defense>(6);

    const uint16_t hp_before =
        battle_state.player.get_current_stat(Stat::Health);
    const uint16_t attack_before =
        battle_state.player.get_current_stat(Stat::Attack);
    const uint16_t defense_before =
        battle_state.player.get_current_stat(Stat::Defense);
    const uint16_t speed_before =
        battle_state.player.get_current_stat(Stat::Speed);

    ASSERT_EQ(6, battle_state.player.get_stat_stage(Stat::Attack));
    ASSERT_EQ(6, battle_state.player.get_stat_stage(Stat::Defense));
    ASSERT_EQ(0, battle_state.player.get_stat_stage(Stat::Speed));

    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state,
        Who::Player,
        Move::Curse
    );

    ASSERT_EQ(
        hp_before,
        battle_state.player.get_current_stat(Stat::Health)
    );
    ASSERT_EQ(
        attack_before,
        battle_state.player.get_current_stat(Stat::Attack)
    );
    ASSERT_EQ(
        defense_before,
        battle_state.player.get_current_stat(Stat::Defense)
    );
    ASSERT_GT(
        speed_before,
        battle_state.player.get_current_stat(Stat::Speed)
    );
    ASSERT_EQ(6, battle_state.player.get_stat_stage(Stat::Attack));
    ASSERT_EQ(6, battle_state.player.get_stat_stage(Stat::Defense));
    ASSERT_EQ(-1, battle_state.player.get_stat_stage(Stat::Speed));
}
