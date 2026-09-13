#include "../mocks.h"
#include "../test_policies.h"

#include "battle_state.h"
#include "move_execution.h"

#include "gtest/gtest.h"

TEST(BattleEngine, FlashFireIsActivatedAfterBeingHitWithAFireMove) {
    BattleState battle_state{
        PokemonState{&Heatran_7_3},
        PokemonState{&Heatran_7_3}
    };

    EXPECT_FALSE(battle_state.player.has_status(Status::FlashFired));

    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state,
        Who::Opponent,
        Move::Flamethrower
    );

    EXPECT_TRUE(battle_state.player.has_status(Status::FlashFired));
}

TEST(BattleEngine, FlamethrowerDoesExpectedDamageWithoutFlashFire) {
    BattleState battle_state{
        PokemonState{&Heatran_7_3},
        PokemonState{&Cresselia_7_3}
    };

    EXPECT_EQ(
        72u,
        execute_move(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state,
            Who::Player,
            Move::Flamethrower
        )
    );
}

TEST(BattleEngine, MoveThatHitsAPokemonWithFlashFireDoesZeroDamage) {
    BattleState battle_state{
        PokemonState{&Heatran_7_3},
        PokemonState{&Heatran_7_3}
    };

    EXPECT_FALSE(battle_state.player.has_status(Status::FlashFired));

    EXPECT_EQ(
        0u,
        execute_move(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state,
            Who::Opponent,
            Move::Flamethrower
        )
    );

    EXPECT_TRUE(battle_state.player.has_status(Status::FlashFired));

    EXPECT_EQ(
        0u,
        execute_move(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state,
            Who::Opponent,
            Move::Flamethrower
        )
    );
}

TEST(BattleEngine, FlashFireIsNotActivatedAfterBeingHitWithNonFireMoves) {
    BattleState battle_state{
        PokemonState{&Heatran_7_3},
        PokemonState{&Cresselia_7_3}
    };

    EXPECT_FALSE(battle_state.player.has_status(Status::FlashFired));

    BattleState battle_state1{
        PokemonState{&Heatran_7_3},
        PokemonState{&Cresselia_7_4}
    };

    EXPECT_FALSE(battle_state1.player.has_status(Status::FlashFired));

    BattleState battle_state2{
        PokemonState{&Heatran_7_3},
        PokemonState{&Heatran_7_3}
    };

    EXPECT_FALSE(battle_state2.player.has_status(Status::FlashFired));

    BattleState battle_state3{
        PokemonState{&Heatran_7_3},
        PokemonState{&Latias_7_4}
    };

    EXPECT_FALSE(battle_state3.player.has_status(Status::FlashFired));

    BattleState battle_state4{
        PokemonState{&Heatran_7_3},
        PokemonState{&Regigias_7_3}
    };

    EXPECT_FALSE(battle_state4.player.has_status(Status::FlashFired));

    // Normal TODO

    // Fighting
    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state4,
        Who::Opponent,
        Move::FocusBlast
    );

    EXPECT_FALSE(battle_state4.player.has_status(Status::FlashFired));

    // Water
    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state3,
        Who::Opponent,
        Move::Surf
    );

    EXPECT_FALSE(battle_state3.player.has_status(Status::FlashFired));

    // Flying TODO

    // Grass
    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state,
        Who::Opponent,
        Move::EnergyBall
    );

    EXPECT_FALSE(battle_state.player.has_status(Status::FlashFired));

    // Poison TODO

    // Electric
    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state,
        Who::Opponent,
        Move::ChargeBeam
    );

    EXPECT_FALSE(battle_state.player.has_status(Status::FlashFired));

    // Ground
    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state2,
        Who::Opponent,
        Move::EarthPower
    );

    EXPECT_FALSE(battle_state2.player.has_status(Status::FlashFired));

    // Psychic
    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state,
        Who::Opponent,
        Move::Psychic
    );

    EXPECT_FALSE(battle_state.player.has_status(Status::FlashFired));

    //Rock
    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state4,
        Who::Opponent,
        Move::Ancientpower
    );

    EXPECT_FALSE(battle_state4.player.has_status(Status::FlashFired));

    // Ice
    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state1,
        Who::Opponent,
        Move::IceBeam
    );

    EXPECT_FALSE(battle_state1.player.has_status(Status::FlashFired));

    // Bug
    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state1,
        Who::Opponent,
        Move::SignalBeam
    );

    EXPECT_FALSE(battle_state1.player.has_status(Status::FlashFired));

    // Dragon
    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state2,
        Who::Opponent,
        Move::DragonPulse
    );

    EXPECT_FALSE(battle_state2.player.has_status(Status::FlashFired));

    // Ghost
    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state,
        Who::Opponent,
        Move::ShadowBall
    );

    EXPECT_FALSE(battle_state.player.has_status(Status::FlashFired));

    // Dark
    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state2,
        Who::Opponent,
        Move::DarkPulse
    );

    EXPECT_FALSE(battle_state2.player.has_status(Status::FlashFired));

    // Steel TODO
}

TEST(BattleEngine, FlashFireMakesPhysicalFireAttackUseBoostedAttackStat) {
    // TODO
}

TEST(
    BattleEngine,
    FlashFireMakesPhysicalFireAttackUseBoostedAttackStatWithStatStageModiferApplied
) {
    // TODO
}

TEST(BattleEngine, FlashFireMakesSpecialFireAttackUseBoostedAttackStat) {
    BattleState battle_state{
        PokemonState{&Heatran_7_3},
        PokemonState{&Cresselia_7_3}
    };

    battle_state.player.set_status(Status::FlashFired);

    EXPECT_EQ(
        106u,
        execute_move(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state,
            Who::Player,
            Move::Flamethrower
        )
    );
}

TEST(BattleEngine,
     FlashFireMakesSpecialFireAttackUseBoostedAttackStatWithStatStageModiferApplied
) {
    BattleState battle_state{
        PokemonState{&Heatran_7_3},
        PokemonState{&Cresselia_7_3}
    };

    battle_state.player.set_status(Status::FlashFired);
    battle_state.player.decrease_stat_stage<Stat::SpecialAttack>(2, StatDropSource::StatDropSourceCount);

    EXPECT_EQ(
        52u,
        execute_move(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state,
            Who::Player,
            Move::Flamethrower
        )
    );
}

TEST(BattleEngine,
     FlashFireDoesNotBoostNonFireAttacksThatArePhysical
) {
    //TODO
    // Normal
    // Fighting
    // Water
    // Flying
    // Grass
    // Poison
    // Electric
    // Ground
    // Psychic
    //Rock
    // Ice
    // Bug
    // Dragon
    // Ghost
    // Dark
    // Steel
}

TEST(BattleEngine,
     FlashFireDoesNotBoostNonFireAttacksThatAreSpecial
) {
    BattleState battle_state{
        PokemonState{&Heatran_7_3},
        PokemonState{&Cresselia_7_3}
    };

    battle_state.player.set_status(Status::FlashFired);

    BattleState battle_state1{
        PokemonState{&Heatran_7_3},
        PokemonState{&Regigias_7_3}
    };

    battle_state1.player.set_status(Status::FlashFired);

    //TODO
    // Normal
    // Fighting
    // Water
    // Flying
    // Grass
    // Poison
    // Electric

    // Ground
    EXPECT_EQ(
        52u,
        execute_move(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state1,
            Who::Player,
            Move::EarthPower
        )
    );
    battle_state1.opponent.add_hp(
        battle_state.opponent.get_original_stat(Stat::Health)
    );

    // TODO
    // Psychic
    //Rock
    // Ice
    // Bug

    // Dragon
    EXPECT_EQ(
    45u,
    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state,
        Who::Player,
        Move::DragonPulse
    )
);
    battle_state.opponent.add_hp(
        battle_state.opponent.get_original_stat(Stat::Health)
    );

    // Ghost TODO

    // Dark
    EXPECT_EQ(
        80u,
        execute_move(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state,
            Who::Player,
            Move::DarkPulse
        )
    );
    battle_state.opponent.add_hp(
        battle_state.opponent.get_original_stat(Stat::Health)
    );

    // Steel TODO
}

TEST(BattleEngine, FlashFireDoesNotActivateWhenFrozen) {
    BattleState battle_state{
        PokemonState{&Heatran_7_3},
        PokemonState{&Heatran_7_3}
    };

    EXPECT_FALSE(battle_state.player.has_status(Status::FlashFired));
    battle_state.opponent.try_set_status_condition(StatusCondition::Freeze);
    EXPECT_TRUE(
        battle_state.opponent.has_status_condition(StatusCondition::Freeze)
        );

    execute_move(
        ALWAYS_BURN_POLICY_CONTAINER,
        battle_state,
        Who::Player,
        Move::Flamethrower
    );

    EXPECT_FALSE(battle_state.player.has_status(Status::FlashFired));
}
