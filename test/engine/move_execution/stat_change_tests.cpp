#include "../mocks.h"
#include "move_execution.h"
#include "policies.h"
#include "gtest/gtest.h"

TEST(Engine, PsychicDropsSpecialDefenseOnTrueRoll) {
    const auto& all_move_infos =
        get_all_moves();

    BattleState battle_state{
        PokemonState{&Cresselia},
        PokemonState{&Cresselia}
    };

    constexpr auto confusion_status_policy =
        OpponentOptimizedConfusionStatusPolicy{};
    constexpr auto confusion_status_rng_policy = NeverConfuseRNGPolicy{};
    constexpr auto crit_rng_policy = NeverCritRNGPolicy{};
    constexpr auto random_factor_policy =
        OpponentOptimizedDamageRandomFactorPolicy{};
    constexpr auto freeze_rng_policy = NeverFreezeRNGPolicy{};
    constexpr auto stat_change_policy = OpponentOptimizedStatChangePolicy{};

    for (uint8_t i = 0; i < 6; i++) {
        execute_move(
            confusion_status_policy,
            confusion_status_rng_policy,
            crit_rng_policy,
            random_factor_policy,
            freeze_rng_policy,
            stat_change_policy,
            battle_state,
            Who::Opponent,
            &all_move_infos[to_int(Move::Psychic)]
        );

        EXPECT_EQ(
            battle_state.player.get_stat_stage(Stat::SpecialDefense),
            -i - 1
        );
    }
}

TEST(Engine, PsychicSpecialDefenseDropDoesNotGoBelowNegativeSix) {
    const auto& all_move_infos =
        get_all_moves();

    BattleState battle_state{
        PokemonState{&Cresselia},
        PokemonState{&Cresselia}
    };

    constexpr auto confusion_status_policy =
        OpponentOptimizedConfusionStatusPolicy{};
    constexpr auto confusion_status_rng_policy = NeverConfuseRNGPolicy{};
    constexpr auto crit_rng_policy = NeverCritRNGPolicy{};
    constexpr auto random_factor_policy =
        OpponentOptimizedDamageRandomFactorPolicy{};
    constexpr auto freeze_rng_policy = NeverFreezeRNGPolicy{};
    constexpr auto stat_change_policy = OpponentOptimizedStatChangePolicy{};

    for (uint8_t i = 0; i < 10; i++) {
        execute_move(
            confusion_status_policy,
            confusion_status_rng_policy,
            crit_rng_policy,
            random_factor_policy,
            freeze_rng_policy,
            stat_change_policy,
            battle_state,
            Who::Opponent,
            &all_move_infos[to_int(Move::Psychic)]
        );

        EXPECT_EQ(
            battle_state.player.get_stat_stage(Stat::SpecialDefense),
            std::max(-6, -i - 1)
        );
    }
}

struct NeverChangeStatPolicy :
    StatChangePolicy<NeverChangeStatPolicy> {
    static bool roll_stat_drop(const uint8_t, const Who who) {
        return false;
    }
};

TEST(Engine, PsychicDoesNotDropSpecialDefenseOnFalseRoll) {
    const auto& all_move_infos =
        get_all_moves();

    BattleState battle_state{
        PokemonState{&Cresselia},
        PokemonState{&Cresselia}
    };

    constexpr auto confusion_status_policy =
        OpponentOptimizedConfusionStatusPolicy{};
    constexpr auto confusion_status_rng_policy = NeverConfuseRNGPolicy{};
    constexpr auto crit_rng_policy = NeverCritRNGPolicy{};
    constexpr auto random_factor_policy =
        OpponentOptimizedDamageRandomFactorPolicy{};
    constexpr auto freeze_rng_policy = NeverFreezeRNGPolicy{};
    constexpr auto stat_change_policy = NeverChangeStatPolicy{};

    for (uint8_t i = 0; i < 6; i++) {
        execute_move(
            confusion_status_policy,
            confusion_status_rng_policy,
            crit_rng_policy,
            random_factor_policy,
            freeze_rng_policy,
            stat_change_policy,
            battle_state,
            Who::Player,
            &all_move_infos[to_int(Move::Psychic)]
        );

        EXPECT_EQ(
            battle_state.opponent.get_stat_stage(Stat::SpecialDefense),
            0
        );
    }
}

TEST(Engine, SpecialDefenseDropsCauseSpecialAttacksToDoMoreDamage) {
    const auto& all_move_infos =
        get_all_moves();

    BattleState battle_state{
        PokemonState{&Cresselia},
        PokemonState{&Cresselia}
    };

    constexpr auto low_effect = LowDamageRandomFactorPolicy{};
    constexpr auto high_effect = HighDamageRandomFactorPolicy{};
    constexpr std::array expected_low_rolls{15, 23, 30, 38, 46, 54, 61};
    constexpr std::array expected_high_rolls{18, 27, 36, 45, 54, 63, 72};

    constexpr auto confusion_status_policy =
        OpponentOptimizedConfusionStatusPolicy{};
    constexpr auto confusion_status_rng_policy = NeverConfuseRNGPolicy{};
    constexpr auto crit_rng_policy = NeverCritRNGPolicy{};

    constexpr auto freeze_rng_policy = NeverFreezeRNGPolicy{};
    constexpr auto stat_change_policy = OpponentOptimizedStatChangePolicy{};

    for (uint8_t i = 0; i < 6; i++) {
        EXPECT_EQ(
            expected_low_rolls[i],
            execute_move(
                confusion_status_policy,
                confusion_status_rng_policy,
                crit_rng_policy,
                low_effect,
                freeze_rng_policy,
                stat_change_policy,
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
                confusion_status_policy,
                confusion_status_rng_policy,
                crit_rng_policy,
                high_effect,
                freeze_rng_policy,
                stat_change_policy,
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
