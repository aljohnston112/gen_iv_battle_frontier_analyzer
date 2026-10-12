#include "battle_state.h"
#include "move_execution.h"

#include "../mocks.h"
#include "../test_policies.h"

#include "gtest/gtest.h"

TEST(MoveExecution, SolarBeamRequiresChargingTurnInClearWeather) {
    BattleState battle_state{
        PokemonState{&Entei_7_3},
        PokemonState{&Suicune_7_3}
    };
    const int8_t initial_power_points =
        battle_state.player.get_power_points(Move::SolarBeam);
    const uint16_t initial_hp =
        battle_state.opponent.get_current_stat(Stat::Health);

    EXPECT_EQ(
        0,
        execute_move(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state,
            Who::Player,
            Move::SolarBeam
        )
    );

    EXPECT_TRUE(
        battle_state.player.has_move_status_with_stage(
            MoveStatusWithStage::Charging
        )
    );
    EXPECT_EQ(
        Move::SolarBeam,
        battle_state.player.get_move_status_move(MoveStatusWithStage::Charging)
    );
    EXPECT_EQ(initial_hp, battle_state.opponent.get_current_stat(Stat::Health));
    EXPECT_EQ(
        initial_power_points,
        battle_state.player.get_power_points(Move::SolarBeam)
    );

    const uint16_t damage =
        execute_move(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state,
            Who::Player,
            Move::SolarBeam
        );

    EXPECT_FALSE(
        battle_state.player.has_move_status_with_stage(
            MoveStatusWithStage::Charging
        )
    );
    EXPECT_EQ(
        initial_hp - damage,
        battle_state.opponent.get_current_stat(Stat::Health)
    );
    EXPECT_EQ(
        initial_power_points - 2,
        battle_state.player.get_power_points(Move::SolarBeam)
    );
}

TEST(MoveExecution, SolarBeamInterruptedDuringChargeDoesNotDeductPP) {
    BattleState battle_state{
        PokemonState{&Entei_7_3},
        PokemonState{&Entei_7_3}
    };

    const uint8_t initial_power_points =
        battle_state.player.get_power_points(Move::SolarBeam);

    EXPECT_EQ(
        0,
        execute_move(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state,
            Who::Player,
            Move::SolarBeam
        )
    );

    EXPECT_EQ(
        initial_power_points,
        battle_state.player.get_power_points(Move::SolarBeam)
    );

    battle_state.player.set_status(Status::Flinched);

    EXPECT_EQ(
        0,
        execute_move(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state,
            Who::Player,
            Move::SolarBeam
        )
    );
    EXPECT_EQ(
        initial_power_points,
        battle_state.player.get_power_points(Move::SolarBeam)
    );
}

TEST(
    MoveExecution,
    SolarBeamInterruptedDuringChargeDoesNotCountAsLastMoveUsed
) {
    BattleState battle_state{
        PokemonState{&Entei_7_3},
        PokemonState{&Entei_7_3}
    };

    EXPECT_EQ(
        Move::MoveCount,
        battle_state.player.get_last_used_move()
    );
    EXPECT_LT(
        0,
        execute_move(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state,
            Who::Player,
            Move::FireBlast
        )
    );
    EXPECT_EQ(
        Move::FireBlast,
        battle_state.player.get_last_used_move()
    );
    EXPECT_EQ(
        0,
        execute_move(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state,
            Who::Player,
            Move::SolarBeam
        )
    );
    EXPECT_EQ(
        Move::MoveCount,
        battle_state.player.get_last_used_move()
    );

    battle_state.player.set_status(Status::Flinched);

    EXPECT_EQ(
        0,
        execute_move(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state,
            Who::Player,
            Move::SolarBeam
        )
    );
    EXPECT_EQ(
        Move::MoveCount,
        battle_state.player.get_last_used_move()
    );
}

TEST(MoveExecution, SolarBeamDoesNotRequireChargingTurnInTheSun) {
    BattleState battle_state{
        PokemonState{&Entei_7_3},
        PokemonState{&Suicune_7_3}
    };
    const int8_t initial_power_points =
        battle_state.player.get_power_points(Move::SolarBeam);
    const uint16_t initial_hp =
        battle_state.opponent.get_current_stat(Stat::Health);
    battle_state.set_weather(Weather::Sun, 5);
    const uint16_t damage =
        execute_move(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state,
            Who::Player,
            Move::SolarBeam
        );

    EXPECT_LT(0, damage);
    EXPECT_FALSE(
        battle_state.player.has_move_status_with_stage(
            MoveStatusWithStage::Charging
        )
    );
    EXPECT_ANY_THROW(
        (void)battle_state.player.get_move_status_move(
            MoveStatusWithStage::Charging
        )
    );
    EXPECT_EQ(
        initial_hp - damage,
        battle_state.opponent.get_current_stat(Stat::Health)
    );
    EXPECT_EQ(
        initial_power_points - 2,
        battle_state.player.get_power_points(Move::SolarBeam)
    );
}

namespace {
    template <Weather W>
    void solarBeamDamageIsHalvedInWeather() {
        BattleState battle_state{
            PokemonState{&Entei_7_3},
            PokemonState{&Suicune_7_3}
        };
        const int8_t initial_power_points =
            battle_state.player.get_power_points(Move::SolarBeam);
        const uint16_t initial_hp =
            battle_state.opponent.get_current_stat(Stat::Health);
        battle_state.set_weather(W, 5);

        EXPECT_EQ(
            0,
            execute_move(
                DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
                battle_state,
                Who::Player,
                Move::SolarBeam
            )
        );

        EXPECT_TRUE(
            battle_state.player.has_move_status_with_stage(
                MoveStatusWithStage::Charging
            )
        );
        EXPECT_EQ(
            Move::SolarBeam,
            battle_state.player.get_move_status_move(MoveStatusWithStage::Charging)
        );
        EXPECT_EQ(initial_hp, battle_state.opponent.get_current_stat(Stat::Health));
        EXPECT_EQ(
            initial_power_points,
            battle_state.player.get_power_points(Move::SolarBeam)
        );

        const uint16_t damage =
            execute_move(
                DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
                battle_state,
                Who::Player,
                Move::SolarBeam
            );

        EXPECT_EQ(
            54,
            damage
        );
        EXPECT_FALSE(
            battle_state.player.has_move_status_with_stage(
                MoveStatusWithStage::Charging
            )
        );
        EXPECT_EQ(
            initial_hp - damage,
            battle_state.opponent.get_current_stat(Stat::Health)
        );
        EXPECT_EQ(
            initial_power_points - 2,
            battle_state.player.get_power_points(Move::SolarBeam)
        );
    }
}

TEST(MoveExecution, SolarBeamDamageIsHalvedInRain) {
    solarBeamDamageIsHalvedInWeather<Weather::Rain>();
}

TEST(MoveExecution, SolarBeamDamageIsHalvedInHail) {
    solarBeamDamageIsHalvedInWeather<Weather::Hail>();
}

TEST(MoveExecution, SolarBeamDamageIsHalvedInFog) {
    solarBeamDamageIsHalvedInWeather<Weather::Fog>();
}

TEST(MoveExecution, SolarBeamDamageIsHalvedInSandstorm) {
    solarBeamDamageIsHalvedInWeather<Weather::Sandstorm>();
}

TEST(MoveExecution, SolarBeamDoesHasPowerPointsDeductedWhenFlinchedInTheSun) {
    BattleState battle_state{
        PokemonState{&Entei_7_3},
        PokemonState{&Suicune_7_3}
    };
    const int8_t initial_power_points =
        battle_state.player.get_power_points(Move::SolarBeam);
    const uint16_t initial_hp =
        battle_state.opponent.get_current_stat(Stat::Health);
    battle_state.set_weather(Weather::Sun, 5);
    battle_state.player.set_status(Status::Flinched);

    EXPECT_EQ(
        0,
        execute_move(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state,
            Who::Player,
            Move::SolarBeam
        )
    );
    EXPECT_FALSE(
        battle_state.player.has_move_status_with_stage(
            MoveStatusWithStage::Charging
        )
    );
    EXPECT_ANY_THROW(
        (void)battle_state.player.get_move_status_move(
            MoveStatusWithStage::Charging
        )
    );
    EXPECT_EQ(
        initial_hp,
        battle_state.opponent.get_current_stat(Stat::Health)
    );
    EXPECT_EQ(
        initial_power_points - 2,
        battle_state.player.get_power_points(Move::SolarBeam)
    );
}

TEST(MoveExecution, SolarBeamDoesHasPowerPointsDeductedWhenParalyzedInTheSun) {
    BattleState battle_state{
        PokemonState{&Entei_7_3},
        PokemonState{&Suicune_7_3}
    };
    const int8_t initial_power_points =
        battle_state.player.get_power_points(Move::SolarBeam);
    const uint16_t initial_hp =
        battle_state.opponent.get_current_stat(Stat::Health);
    battle_state.set_weather(Weather::Sun, 5);
    battle_state.player.try_set_status_condition(StatusCondition::Paralysis);

    EXPECT_EQ(
        0,
        execute_move(
            ALWAYS_PARALYZE_POLICY_CONTAINER,
            battle_state,
            Who::Player,
            Move::SolarBeam
        )
    );
    EXPECT_FALSE(
        battle_state.player.has_move_status_with_stage(
            MoveStatusWithStage::Charging
        )
    );
    EXPECT_ANY_THROW(
        (void)battle_state.player.get_move_status_move(
            MoveStatusWithStage::Charging
        )
    );
    EXPECT_EQ(
        initial_hp,
        battle_state.opponent.get_current_stat(Stat::Health)
    );
    EXPECT_EQ(
        initial_power_points - 2,
        battle_state.player.get_power_points(Move::SolarBeam)
    );
}

TEST(
    MoveExecution,
    SolarBeamDoesHasPowerPointsDeductedWhenHitsInConfusionInTheSun
) {
    BattleState battle_state{
        PokemonState{&Entei_7_3},
        PokemonState{&Suicune_7_3}
    };
    const int8_t initial_power_points =
        battle_state.player.get_power_points(Move::SolarBeam);
    const uint16_t initial_hp =
        battle_state.opponent.get_current_stat(Stat::Health);
    battle_state.set_weather(Weather::Sun, 5);
    battle_state.player.set_status_with_stage(
        StatusWithStage::Confused,
        5
    );

    EXPECT_EQ(
        0,
        execute_move(
            ALWAYS_CONFUSE_LOW_RANDOM_CONFUSION_POLICY_CONTAINER,
            battle_state,
            Who::Player,
            Move::SolarBeam
        )
    );
    EXPECT_FALSE(
        battle_state.player.has_move_status_with_stage(
            MoveStatusWithStage::Charging
        )
    );
    EXPECT_ANY_THROW(
        (void)battle_state.player.get_move_status_move(
            MoveStatusWithStage::Charging
        )
    );
    EXPECT_EQ(
        initial_hp,
        battle_state.opponent.get_current_stat(Stat::Health)
    );
    EXPECT_EQ(
        initial_power_points - 2,
        battle_state.player.get_power_points(Move::SolarBeam)
    );
}

TEST(
    MoveExecution,
    SolarBeamDoesHasPowerPointsDeductedWhenFrozen
) {
    BattleState battle_state{
        PokemonState{&Entei_7_3},
        PokemonState{&Suicune_7_3}
    };
    const int8_t initial_power_points =
        battle_state.player.get_power_points(Move::SolarBeam);
    const uint16_t initial_hp =
        battle_state.opponent.get_current_stat(Stat::Health);
    battle_state.set_weather(Weather::Sun, 5);
    battle_state.player.try_set_status_condition(StatusCondition::Freeze);

    EXPECT_EQ(
        0,
        execute_move(
            ALWAYS_FREEZE_POLICY_CONTAINER,
            battle_state,
            Who::Player,
            Move::SolarBeam
        )
    );
    EXPECT_FALSE(
        battle_state.player.has_move_status_with_stage(
            MoveStatusWithStage::Charging
        )
    );
    EXPECT_ANY_THROW(
        (void)battle_state.player.get_move_status_move(
            MoveStatusWithStage::Charging
        )
    );
    EXPECT_EQ(
        initial_hp,
        battle_state.opponent.get_current_stat(Stat::Health)
    );
    EXPECT_EQ(
        initial_power_points - 2,
        battle_state.player.get_power_points(Move::SolarBeam)
    );
}

TEST(
    MoveExecution,
    SolarBeamDoesHasPowerPointsDeductedWhenAsleep
) {
    BattleState battle_state{
        PokemonState{&Entei_7_3},
        PokemonState{&Suicune_7_3}
    };
    const int8_t initial_power_points =
        battle_state.player.get_power_points(Move::SolarBeam);
    const uint16_t initial_hp =
        battle_state.opponent.get_current_stat(Stat::Health);
    battle_state.set_weather(Weather::Sun, 5);
    battle_state.player.set_status_with_stage(StatusWithStage::Asleep, 5);

    EXPECT_EQ(
        0,
        execute_move(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state,
            Who::Player,
            Move::SolarBeam
        )
    );
    EXPECT_FALSE(
        battle_state.player.has_move_status_with_stage(
            MoveStatusWithStage::Charging
        )
    );
    EXPECT_ANY_THROW(
        (void)battle_state.player.get_move_status_move(
            MoveStatusWithStage::Charging
        )
    );
    EXPECT_EQ(
        initial_hp,
        battle_state.opponent.get_current_stat(Stat::Health)
    );
    EXPECT_EQ(
        initial_power_points - 2,
        battle_state.player.get_power_points(Move::SolarBeam)
    );
}
