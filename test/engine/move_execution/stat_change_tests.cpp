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

void move_drops_targets_stat_on_true_roll(
    BattleState& battle_state,
    const Move move,
    const Stat stat,
    const uint8_t n
) {
    const auto& all_move_infos =
        get_all_moves();

    constexpr auto confusion_status_policy =
        OpponentOptimizedConfusionStatusPolicy{};
    constexpr auto confusion_status_rng_policy = NeverConfuseRNGPolicy{};
    constexpr auto crit_rng_policy = NeverCritRNGPolicy{};
    constexpr auto random_factor_policy =
        OpponentOptimizedRandomFactorPolicy{};
    constexpr auto freeze_rng_policy = NeverFreezeRNGPolicy{};
    constexpr auto stat_change_policy = OpponentOptimizedStatChangePolicy{};

    const uint8_t m = 6u / n;
    for (uint8_t i = 0; i < m; i++) {
        execute_move(
            confusion_status_policy,
            confusion_status_rng_policy,
            crit_rng_policy,
            random_factor_policy,
            freeze_rng_policy,
            stat_change_policy,
            battle_state,
            Who::Opponent,
            &all_move_infos[to_int(move)]
        );

        EXPECT_EQ(
            battle_state.player.get_stat_stage(stat),
            -(i * n) - n
        );

        battle_state.opponent.increment_power_point(move, n);
    }
}

void move_does_not_drop_targets_stat_past_negative_six_on_true_roll(
    BattleState& battle_state,
    const Move move,
    const Stat stat,
    const uint8_t n
) {
    const auto& all_move_infos =
        get_all_moves();

    constexpr auto confusion_status_policy =
        OpponentOptimizedConfusionStatusPolicy{};
    constexpr auto confusion_status_rng_policy = NeverConfuseRNGPolicy{};
    constexpr auto crit_rng_policy = NeverCritRNGPolicy{};
    constexpr auto random_factor_policy =
        OpponentOptimizedRandomFactorPolicy{};
    constexpr auto freeze_rng_policy = NeverFreezeRNGPolicy{};
    constexpr auto stat_change_policy = OpponentOptimizedStatChangePolicy{};

    const uint8_t m = 10u / n;
    for (uint8_t i = 0; i < m; i++) {
        execute_move(
            confusion_status_policy,
            confusion_status_rng_policy,
            crit_rng_policy,
            random_factor_policy,
            freeze_rng_policy,
            stat_change_policy,
            battle_state,
            Who::Opponent,
            &all_move_infos[to_int(move)]
        );

        EXPECT_EQ(
            battle_state.player.get_stat_stage(stat),
            std::max(-6, -(i * n) - n)
        );

        battle_state.opponent.increment_power_point(move, n);
    }
}

void move_does_not_drop_targets_stat_on_false_roll(
    BattleState& battle_state,
    const Move move,
    const Stat stat
) {
    const auto& all_move_infos =
        get_all_moves();

    constexpr auto confusion_status_policy =
        OpponentOptimizedConfusionStatusPolicy{};
    constexpr auto confusion_status_rng_policy = NeverConfuseRNGPolicy{};
    constexpr auto crit_rng_policy = NeverCritRNGPolicy{};
    constexpr auto random_factor_policy =
        OpponentOptimizedRandomFactorPolicy{};
    constexpr auto freeze_rng_policy = NeverFreezeRNGPolicy{};
    constexpr auto stat_change_policy = NeverDropStatPolicy{};

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
            &all_move_infos[to_int(move)]
        );

        EXPECT_EQ(
            battle_state.opponent.get_stat_stage(stat),
            0
        );
        battle_state.player.increment_power_point(move, 6);
    }
}

// Special Attack
// =============================================================================

const CustomPokemon Latias{
    .name = Pokemon::Latias,
    .ability = Ability::Levitate,
    .level = 50,
    .item = Item::NoItem,
    .types = {PokemonType::Psychic, PokemonType::NoType},
    .moves = {
        Move::MistBall,
        Move::DracoMeteor,
        Move::Thunderbolt,
        Move::Surf
    },
    .stats = {152, 87, 107, 173, 147, 158},
    .pounds = 88.2
};

const CustomPokemon LatiasWhiteHerb{
    .name = Pokemon::Latias,
    .ability = Ability::Levitate,
    .level = 50,
    .item = Item::WhiteHerb,
    .types = {PokemonType::Psychic, PokemonType::NoType},
    .moves = {
        Move::MistBall,
        Move::DracoMeteor,
        Move::Thunderbolt,
        Move::Surf
    },
    .stats = {152, 87, 107, 173, 147, 158},
    .pounds = 88.2
};

TEST(MoveExecution, MistBallDropsSpecialAttackOnTrueRoll) {
    BattleState battle_state{
        PokemonState{&Latias},
        PokemonState{&Latias}
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
        PokemonState{&Latias},
        PokemonState{&Latias}
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
        PokemonState{&LatiasWhiteHerb},
        PokemonState{&LatiasWhiteHerb}
    };

    move_does_not_drop_targets_stat_on_false_roll(
        battle_state,
        Move::MistBall,
        Stat::SpecialAttack
    );
}

TEST(MoveExecution, SpecialAttackDropCausesSpecialAttacksToDoLessDamage) {
    const auto& all_move_infos =
        get_all_moves();

    BattleState battle_state{
        PokemonState{&CresseliaLeftovers},
        PokemonState{&LatiasWhiteHerb}
    };

    constexpr auto low_effect = LowDamageRandomFactorPolicy{};
    constexpr auto high_effect = HighDamageRandomFactorPolicy{};
    constexpr std::array expected_low_rolls{18, 12, 9, 7, 6, 5, 4};
    constexpr std::array expected_high_rolls{21, 15, 11, 9, 7, 6, 6};

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
                Who::Player,
                &all_move_infos[to_int(Move::Psychic)]
            )
        );

        execute_move(
            confusion_status_policy,
            confusion_status_rng_policy,
            crit_rng_policy,
            low_effect,
            freeze_rng_policy,
            stat_change_policy,
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
                confusion_status_policy,
                confusion_status_rng_policy,
                crit_rng_policy,
                high_effect,
                freeze_rng_policy,
                stat_change_policy,
                battle_state,
                Who::Player,
                &all_move_infos[to_int(Move::Psychic)]
            )
        );

        execute_move(
            confusion_status_policy,
            confusion_status_rng_policy,
            crit_rng_policy,
            low_effect,
            freeze_rng_policy,
            stat_change_policy,
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
        PokemonState{&CresseliaLeftovers},
        PokemonState{&CresseliaLeftovers}
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
        PokemonState{&CresseliaLeftovers},
        PokemonState{&CresseliaLeftovers}
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
        PokemonState{&CresseliaLeftovers},
        PokemonState{&CresseliaLeftovers}
    };

    move_does_not_drop_targets_stat_on_false_roll(
        battle_state,
        Move::Psychic,
        Stat::SpecialDefense
    );
}

TEST(MoveExecution, SpecialDefenseDropsCauseSpecialAttacksToDoMoreDamage) {
    const auto& all_move_infos =
        get_all_moves();

    BattleState battle_state{
        PokemonState{&CresseliaLeftovers},
        PokemonState{&CresseliaLeftovers}
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
