#include "../mocks.h"
#include "move_execution.h"
#include "policies.h"
#include "gtest/gtest.h"

struct NeverDropStatPolicy :
    StatChangePolicy<NeverDropStatPolicy> {
    static bool roll_stat_drop(const uint8_t, const Who) {
        return false;
    }
};

struct NeverChangeStatPolicy :
    StatChangePolicy<NeverChangeStatPolicy> {
        static bool roll_stat_drop(const uint8_t, const Who) {
            return false;
        }

        static bool roll_stat_increase(const uint8_t, const Who) {
            return false;
        }
};

template<bool ALWAYS_DROP_STAT>
struct AlwaysBoostStatPolicy :
    StatChangePolicy<AlwaysBoostStatPolicy<ALWAYS_DROP_STAT>> {

    static bool roll_stat_drop(const uint8_t, const Who) {
        return ALWAYS_DROP_STAT;
    }

    static bool roll_stat_increase(const uint8_t, const Who) {
        return true;
    }
};

static void move_does_not_boost_attackers_stat_past_six_on_true_roll(
    BattleState& battle_state,
    const Move move,
    const Stat stat,
    const uint8_t n
) {
    const auto& all_move_infos =
        get_all_moves();

    constexpr PolicyContainer<
        OpponentOptimizedConfusionStatusPolicy,
        NeverConfuseRNGPolicy,
        NeverCritRNGPolicy,
        OpponentOptimizedRandomFactorPolicy,
        NeverFreezeRNGPolicy,
        AlwaysBoostStatPolicy<false>,
        NeverParalyzeRNGPolicy
    > policy_container{};

    const uint8_t m = 10u / n;
    for (uint8_t i = 0; i < m; i++) {
        execute_move(
            policy_container,
            battle_state,
            Who::Player,
            &all_move_infos[to_int(move)]
        );

        EXPECT_EQ(
            battle_state.player.get_stat_stage(stat),
            std::min(6, (i * n) + n)
        );

        battle_state.opponent.increment_power_point(move, 1);
    }
}

static void move_does_not_boost_attackers_stat_on_false_roll(
    BattleState& battle_state,
    const Move move,
    const Stat stat
) {
    const auto& all_move_infos =
        get_all_moves();

    constexpr PolicyContainer<
        OpponentOptimizedConfusionStatusPolicy,
        NeverConfuseRNGPolicy,
        NeverCritRNGPolicy,
        OpponentOptimizedRandomFactorPolicy,
        NeverFreezeRNGPolicy,
        NeverChangeStatPolicy,
        NeverParalyzeRNGPolicy
    > policy_container{};

    for (uint8_t i = 0; i < 6; i++) {
        execute_move(
            policy_container,
            battle_state,
            Who::Player,
            &all_move_infos[to_int(move)]
        );

        EXPECT_EQ(
            battle_state.opponent.get_stat_stage(stat),
            0
        );
        battle_state.player.increment_power_point(move, 6);
    }
}


static void move_drops_targets_stat_on_true_roll(
    BattleState& battle_state,
    const Move move,
    const Stat stat,
    const uint8_t n
) {
    const auto& all_move_infos =
        get_all_moves();

    constexpr PolicyContainer<
        OpponentOptimizedConfusionStatusPolicy,
        NeverConfuseRNGPolicy,
        NeverCritRNGPolicy,
        OpponentOptimizedRandomFactorPolicy,
        NeverFreezeRNGPolicy,
        OpponentOptimizedStatChangePolicy,
        NeverParalyzeRNGPolicy
    > policy_container{};

    const uint8_t m = 6u / n;
    for (uint8_t i = 0; i < m; i++) {
        execute_move(
            policy_container,
            battle_state,
            Who::Opponent,
            &all_move_infos[to_int(move)]
        );

        EXPECT_EQ(
            battle_state.player.get_stat_stage(stat),
            -(i * n) - n
        );

        battle_state.opponent.increment_power_point(move, 1);
    }
}

static void move_does_not_drop_targets_stat_past_negative_six_on_true_roll(
    BattleState& battle_state,
    const Move move,
    const Stat stat,
    const uint8_t n
) {
    const auto& all_move_infos =
        get_all_moves();

    constexpr PolicyContainer<
        OpponentOptimizedConfusionStatusPolicy,
        NeverConfuseRNGPolicy,
        NeverCritRNGPolicy,
        OpponentOptimizedRandomFactorPolicy,
        NeverFreezeRNGPolicy,
        OpponentOptimizedStatChangePolicy,
        NeverParalyzeRNGPolicy
    > policy_container{};

    const uint8_t m = 10u / n;
    for (uint8_t i = 0; i < m; i++) {
        execute_move(
            policy_container,
            battle_state,
            Who::Opponent,
            &all_move_infos[to_int(move)]
        );

        EXPECT_EQ(
            battle_state.player.get_stat_stage(stat),
            std::max(-6, -(i * n) - n)
        );

        battle_state.opponent.increment_power_point(move, 1);
    }
}

static void move_does_not_drop_targets_stat_on_false_roll(
    BattleState& battle_state,
    const Move move,
    const Stat stat
) {
    const auto& all_move_infos =
        get_all_moves();

    constexpr PolicyContainer<
        OpponentOptimizedConfusionStatusPolicy,
        NeverConfuseRNGPolicy,
        NeverCritRNGPolicy,
        OpponentOptimizedRandomFactorPolicy,
        NeverFreezeRNGPolicy,
        NeverDropStatPolicy,
        NeverParalyzeRNGPolicy
    > policy_container{};

    for (uint8_t i = 0; i < 6; i++) {
        execute_move(
            policy_container,
            battle_state,
            Who::Player,
            &all_move_infos[to_int(move)]
        );

        EXPECT_EQ(
            battle_state.opponent.get_stat_stage(stat),
            0
        );
        battle_state.player.increment_power_point(move, 6);
    }
}

TEST(MoveExecution, AncientPowerIncreasesAllStatsByOneStage) {
    BattleState battle_state{
        PokemonState{&Regigias_7_3},
        PokemonState{&Regigias_7_3}
    };

    const auto& all_move_infos =
        get_all_moves();

    constexpr PolicyContainer<
        OpponentOptimizedConfusionStatusPolicy,
        NeverConfuseRNGPolicy,
        NeverCritRNGPolicy,
        OpponentOptimizedRandomFactorPolicy,
        NeverFreezeRNGPolicy,
        OpponentOptimizedStatChangePolicy,
        NeverParalyzeRNGPolicy
    > policy_container{};

    for (uint8_t i = 0; i < 7; i++) {
        execute_move(
            policy_container,
            battle_state,
            Who::Opponent,
            &all_move_infos[to_int(Move::Ancientpower)]
        );

        EXPECT_EQ(
            battle_state.opponent.get_stat_stage(Stat::Attack),
            std::min(6, i + 1)
        );
        EXPECT_EQ(
            battle_state.opponent.get_stat_stage(Stat::Defense),
            std::min(6, i + 1)
        );
        EXPECT_EQ(
            battle_state.opponent.get_stat_stage(Stat::SpecialAttack),
            std::min(6, i + 1)
        );
        EXPECT_EQ(
            battle_state.opponent.get_stat_stage(Stat::SpecialDefense),
            std::min(6, i + 1)
        );
        EXPECT_EQ(
            battle_state.opponent.get_stat_stage(Stat::Speed),
            std::min(6, i + 1)
        );

        battle_state.opponent.increment_power_point(Move::Ancientpower, 1);
    }
}

TEST(MoveExecution, AncientPowerDoesNotIncreaseAnyStatsOnFalseRoll) {
    BattleState battle_state{
        PokemonState{&Regigias_7_3},
        PokemonState{&Regigias_7_3}
    };

    const auto& all_move_infos =
        get_all_moves();

    constexpr PolicyContainer<
        OpponentOptimizedConfusionStatusPolicy,
        NeverConfuseRNGPolicy,
        NeverCritRNGPolicy,
        OpponentOptimizedRandomFactorPolicy,
        NeverFreezeRNGPolicy,
        NeverChangeStatPolicy,
        NeverParalyzeRNGPolicy
    > policy_container{};

    for (uint8_t i = 0; i < 7; i++) {
        execute_move(
            policy_container,
            battle_state,
            Who::Opponent,
            &all_move_infos[to_int(Move::Ancientpower)]
        );

        EXPECT_EQ(
            battle_state.opponent.get_stat_stage(Stat::Attack),
            0
        );
        EXPECT_EQ(
            battle_state.opponent.get_stat_stage(Stat::Defense),
            0
        );
        EXPECT_EQ(
            battle_state.opponent.get_stat_stage(Stat::SpecialAttack),
            0
        );
        EXPECT_EQ(
            battle_state.opponent.get_stat_stage(Stat::SpecialDefense),
            0
        );
        EXPECT_EQ(
            battle_state.opponent.get_stat_stage(Stat::Speed),
            0
        );

        battle_state.opponent.increment_power_point(Move::Ancientpower, 1);
    }
}

// Special Attack Boost
// =============================================================================
TEST(MoveExecution, ChargeBeamSpecialAttackBoostDoesNotGoPastSix) {
    BattleState battle_state{
        PokemonState{&Cresselia_7_3},
        PokemonState{&Cresselia_7_3}
    };

    move_does_not_boost_attackers_stat_past_six_on_true_roll(
        battle_state,
        Move::ChargeBeam,
        Stat::SpecialAttack,
        1
    );
}

TEST(MoveExecution, ChargeBeamDoesNotBoostSpecialAttackOnFalseRoll) {
    BattleState battle_state{
        PokemonState{&Cresselia_7_3},
        PokemonState{&Cresselia_7_3}
    };

    move_does_not_boost_attackers_stat_on_false_roll(
        battle_state,
        Move::ChargeBeam,
        Stat::SpecialAttack
    );
}


// Special Attack Drop
// =============================================================================
TEST(MoveExecution, MistBallDropsSpecialAttackOnTrueRoll) {
    BattleState battle_state{
        PokemonState{&LatiasNoItem},
        PokemonState{&LatiasNoItem}
    };

    move_drops_targets_stat_on_true_roll(
        battle_state,
        Move::MistBall,
        Stat::SpecialAttack,
        1
    );
}

TEST(MoveExecution, MistBallSpecialAttackDropDoesNotGoBelowNegativeSix) {
    BattleState battle_state{
        PokemonState{&LatiasNoItem},
        PokemonState{&LatiasNoItem}
    };

    move_does_not_drop_targets_stat_past_negative_six_on_true_roll(
        battle_state,
        Move::MistBall,
        Stat::SpecialAttack,
        1
    );
}

TEST(MoveExecution, MistBallDoesNotDropSpecialAttackOnFalseRoll) {
    BattleState battle_state{
        PokemonState{&Latias_7_4},
        PokemonState{&Latias_7_4}
    };

    move_does_not_drop_targets_stat_on_false_roll(
        battle_state,
        Move::MistBall,
        Stat::SpecialAttack
    );
}

TEST(MoveExecution, DracoMeteorDropsSpecialAtttack) {
    BattleState battle_state{
        PokemonState{&LatiasNoItem},
        PokemonState{&LatiasNoItem}
    };
    constexpr PolicyContainer<
        OpponentOptimizedConfusionStatusPolicy,
        NeverConfuseRNGPolicy,
        NeverCritRNGPolicy,
        OpponentOptimizedRandomFactorPolicy,
        NeverFreezeRNGPolicy,
        OpponentOptimizedStatChangePolicy,
        NeverParalyzeRNGPolicy
    > policy_container{};
    execute_move(
        policy_container,
        battle_state,
        Who::Player,
        get_move_info(Move::DracoMeteor)
    );
    execute_move(
        policy_container,
        battle_state,
        Who::Opponent,
        get_move_info(Move::DracoMeteor)
    );
    EXPECT_EQ(battle_state.player.get_stat_stage(Stat::SpecialAttack), -2);
    EXPECT_EQ(battle_state.opponent.get_stat_stage(Stat::SpecialAttack), -2);
}

TEST(MoveExecution, SpecialAttackDropCausesSpecialAttacksToDoLessDamage) {
    const auto& all_move_infos =
        get_all_moves();

    BattleState battle_state{
        PokemonState{&Cresselia_7_4},
        PokemonState{&Latias_7_4}
    };

    constexpr std::array expected_low_rolls{18, 12, 9, 7, 6, 5, 4};
    constexpr std::array expected_high_rolls{21, 15, 11, 9, 7, 6, 6};

    constexpr PolicyContainer<
        OpponentOptimizedConfusionStatusPolicy,
        NeverConfuseRNGPolicy,
        NeverCritRNGPolicy,
        LowDamageRandomFactorPolicy,
        NeverFreezeRNGPolicy,
        OpponentOptimizedStatChangePolicy,
        NeverParalyzeRNGPolicy
    > low_random_policy_container{};

    constexpr PolicyContainer<
        OpponentOptimizedConfusionStatusPolicy,
        NeverConfuseRNGPolicy,
        NeverCritRNGPolicy,
        HighDamageRandomFactorPolicy,
        NeverFreezeRNGPolicy,
        OpponentOptimizedStatChangePolicy,
        NeverParalyzeRNGPolicy
    > high_random_policy_container{};

    for (uint8_t i = 0; i < 6; i++) {
        EXPECT_EQ(
            expected_low_rolls[i],
            execute_move(
                low_random_policy_container,
                battle_state,
                Who::Player,
                &all_move_infos[to_int(Move::Psychic)]
            )
        );

        execute_move(
            low_random_policy_container,
            battle_state,
            Who::Opponent,
            &all_move_infos[to_int(Move::MistBall)]
        );

        EXPECT_EQ(
            battle_state.player.get_stat_stage(Stat::SpecialAttack),
            -i - 1
        );
        battle_state.player.increase_stat_stage(Stat::SpecialAttack, 1);

        EXPECT_EQ(
            battle_state.player.get_stat_stage(Stat::SpecialAttack),
            -i
        );
        EXPECT_EQ(
            expected_high_rolls[i],
            execute_move(
                high_random_policy_container,
                battle_state,
                Who::Player,
                &all_move_infos[to_int(Move::Psychic)]
            )
        );

        execute_move(
            low_random_policy_container,
            battle_state,
            Who::Opponent,
            &all_move_infos[to_int(Move::MistBall)]
        );

        EXPECT_EQ(
            battle_state.player.get_stat_stage(Stat::SpecialAttack),
            -i - 1
        );

        battle_state.player.add_hp(
            battle_state.player.get_original_stat(Stat::Health)
        );
        battle_state.opponent.add_hp(
            battle_state.opponent.get_original_stat(Stat::Health)
        );
        battle_state.player.increment_power_point(Move::Psychic, 2);
        battle_state.opponent.increment_power_point(Move::MistBall, 2);
    }
}

// Special Defense
// =============================================================================

TEST(MoveExecution, PsychicDropsSpecialDefenseOnTrueRoll) {
    BattleState battle_state{
        PokemonState{&Cresselia_7_4},
        PokemonState{&Cresselia_7_4}
    };

    move_drops_targets_stat_on_true_roll(
        battle_state,
        Move::Psychic,
        Stat::SpecialDefense,
        1
    );
}

TEST(MoveExecution, PsychicSpecialDefenseDropDoesNotGoBelowNegativeSix) {
    BattleState battle_state{
        PokemonState{&Cresselia_7_4},
        PokemonState{&Cresselia_7_4}
    };

    move_does_not_drop_targets_stat_past_negative_six_on_true_roll(
        battle_state,
        Move::Psychic,
        Stat::SpecialDefense,
        1
    );
}

TEST(MoveExecution, PsychicDoesNotDropSpecialDefenseOnFalseRoll) {
    BattleState battle_state{
        PokemonState{&Cresselia_7_4},
        PokemonState{&Cresselia_7_4}
    };

    move_does_not_drop_targets_stat_on_false_roll(
        battle_state,
        Move::Psychic,
        Stat::SpecialDefense
    );
}

TEST(MoveExecution, EarthPowerMakesSpecialDefenseStageOfOpponentDropByOne) {
    BattleState battle_state{
        PokemonState{&Regigias_7_3},
        PokemonState{&Regigias_7_3}
    };

    move_does_not_drop_targets_stat_past_negative_six_on_true_roll(
        battle_state,
        Move::EarthPower,
        Stat::SpecialDefense,
        1
    );
}

TEST(MoveExecution, EarthPowerDoesNotDropSpecialDefenseOnFalseRoll) {
    BattleState battle_state{
        PokemonState{&Regigias_7_3},
        PokemonState{&Regigias_7_3}
    };

    move_does_not_drop_targets_stat_on_false_roll(
        battle_state,
        Move::EarthPower,
        Stat::SpecialDefense
    );
}

TEST(MoveExecution, ShadowBallMakesSpecialDefenseStageOfOpponentDropByOne) {
    BattleState battle_state{
        PokemonState{&Cresselia_7_3},
        PokemonState{&Cresselia_7_3}
    };

    move_does_not_drop_targets_stat_past_negative_six_on_true_roll(
        battle_state,
        Move::ShadowBall,
        Stat::SpecialDefense,
        1
    );
}

TEST(MoveExecution, ShadowBallDoesNotDropSpecialDefenseOnFalseRoll) {
    BattleState battle_state{
        PokemonState{&Cresselia_7_3},
        PokemonState{&Cresselia_7_3}
    };

    move_does_not_drop_targets_stat_on_false_roll(
        battle_state,
        Move::ShadowBall,
        Stat::SpecialDefense
    );
}

TEST(MoveExecution, EnergyBallMakesSpecialDefenseStageOfOpponentDropByOne) {
    BattleState battle_state{
        PokemonState{&Cresselia_7_3},
        PokemonState{&Cresselia_7_3}
    };

    move_does_not_drop_targets_stat_past_negative_six_on_true_roll(
        battle_state,
        Move::EnergyBall,
        Stat::SpecialDefense,
        1
    );
}

TEST(MoveExecution, EnergyBallDoesNotDropSpecialDefenseOnFalseRoll) {
    BattleState battle_state{
        PokemonState{&Cresselia_7_3},
        PokemonState{&Cresselia_7_3}
    };

    move_does_not_drop_targets_stat_on_false_roll(
        battle_state,
        Move::EnergyBall,
        Stat::SpecialDefense
    );
}

TEST(MoveExecution, FocusBlastMakesSpecialDefenseStageOfOpponentDropByOne) {
    BattleState battle_state{
        PokemonState{&Regigias_7_3},
        PokemonState{&Regigias_7_3}
    };

    move_does_not_drop_targets_stat_past_negative_six_on_true_roll(
        battle_state,
        Move::FocusBlast,
        Stat::SpecialDefense,
        1
    );
}

TEST(MoveExecution, FocusBlastDoesNotDropSpecialDefenseOnFalseRoll) {
    BattleState battle_state{
        PokemonState{&Regigias_7_3},
        PokemonState{&Regigias_7_3}
    };

    move_does_not_drop_targets_stat_on_false_roll(
        battle_state,
        Move::FocusBlast,
        Stat::SpecialDefense
    );
}

TEST(MoveExecution, SpecialDefenseDropsCauseSpecialAttacksToDoMoreDamage) {
    const auto& all_move_infos =
        get_all_moves();

    BattleState battle_state{
        PokemonState{&Cresselia_7_4},
        PokemonState{&Cresselia_7_4}
    };

    constexpr std::array expected_low_rolls{15, 23, 30, 38, 46, 54, 61};
    constexpr std::array expected_high_rolls{18, 27, 36, 45, 54, 63, 72};

    constexpr PolicyContainer<
        OpponentOptimizedConfusionStatusPolicy,
        NeverConfuseRNGPolicy,
        NeverCritRNGPolicy,
        LowDamageRandomFactorPolicy,
        NeverFreezeRNGPolicy,
        OpponentOptimizedStatChangePolicy,
        NeverParalyzeRNGPolicy
    > low_random_policy_container{};

    constexpr PolicyContainer<
        OpponentOptimizedConfusionStatusPolicy,
        NeverConfuseRNGPolicy,
        NeverCritRNGPolicy,
        HighDamageRandomFactorPolicy,
        NeverFreezeRNGPolicy,
        OpponentOptimizedStatChangePolicy,
        NeverParalyzeRNGPolicy
    > high_random_policy_container{};

    for (uint8_t i = 0; i < 6; i++) {
        EXPECT_EQ(
            expected_low_rolls[i],
            execute_move(
                low_random_policy_container,
                battle_state,
                Who::Opponent,
                &all_move_infos[to_int(Move::Psychic)]
            )
        );
        EXPECT_EQ(
            battle_state.player.get_stat_stage(Stat::SpecialDefense),
            -i - 1
        );
        battle_state.player.increase_stat_stage(Stat::SpecialDefense, 1);

        EXPECT_EQ(
            battle_state.player.get_stat_stage(Stat::SpecialDefense),
            -i
        );
        EXPECT_EQ(
            expected_high_rolls[i],
            execute_move(
                high_random_policy_container,
                battle_state,
                Who::Opponent,
                &all_move_infos[to_int(Move::Psychic)]
            )
        );

        EXPECT_EQ(
            battle_state.player.get_stat_stage(Stat::SpecialDefense),
            -i - 1
        );

        battle_state.player.add_hp(
            battle_state.player.get_original_stat(Stat::Health)
        );
        battle_state.opponent.increment_power_point(Move::Psychic, 2);
    }
}
