#include "../mocks.h"
#include "move_execution.h"
#include "policies.h"
#include "gtest/gtest.h"

class HighStatDropEffectPolicy :
    public OpponentKnowledgePolicy<HighStatDropEffectPolicy> {
public:
    static uint8_t roll_random(const Who) {
        return 100;
    }

    static bool roll_stat_drop(const uint8_t, const Who) {
        return true;
    }
};

class LowStatDropEffectPolicy :
    public OpponentKnowledgePolicy<LowStatDropEffectPolicy> {
public:
    static uint8_t roll_random(const Who) {
        return 85;
    }

    static bool roll_stat_drop(const uint8_t, const Who) {
        return true;
    }
};

class NoStatDropEffectPolicy :
    public OpponentKnowledgePolicy<NoStatDropEffectPolicy> {
public:
    static bool is_player_faster(const BattleState& battle_state) {
        return battle_state.player.get_current_stat(Stat::Speed) >
            battle_state.opponent.get_current_stat(Stat::Speed);
    }

    static uint8_t roll_random_confusion(const Who who) {
        return who == Who::Player ? 100 : 85;
    }

    static uint8_t roll_random(const Who) {
        return 100;
    }

    static bool roll_stat_drop(const uint8_t, const Who) {
        return false;
    }
};

TEST(Engine, PsychicDropsSpecialDefenseOnTrueRoll) {
    const auto& all_move_infos =
        get_all_moves();

    BattleState battle_state{
        PokemonState{&Cresselia},
        PokemonState{&Cresselia}
    };

    for (uint8_t i = 0; i < 6; i++) {
        execute_move(
            HighStatDropEffectPolicy{},
            FalseRNGPolicy{},
            battle_state,
            Who::Player,
            &all_move_infos[to_int(Move::Psychic)]
        );

        EXPECT_EQ(
            battle_state.opponent.get_stat_stage(Stat::SpecialDefense),
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

    for (uint8_t i = 0; i < 10; i++) {
        execute_move(
            HighStatDropEffectPolicy{},
            FalseRNGPolicy{},
            battle_state,
            Who::Player,
            &all_move_infos[to_int(Move::Psychic)]
        );

        EXPECT_EQ(
            battle_state.opponent.get_stat_stage(Stat::SpecialDefense),
            std::max(-6, -i - 1)
        );
    }
}

TEST(Engine, PsychicDoesNotDropSpecialDefenseOnFalseRoll) {
    const auto& all_move_infos =
        get_all_moves();

    BattleState battle_state{
        PokemonState{&Cresselia},
        PokemonState{&Cresselia}
    };

    for (uint8_t i = 0; i < 6; i++) {
        execute_move(
            NoStatDropEffectPolicy{},
            FalseRNGPolicy{},
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

    constexpr auto low_effect = LowStatDropEffectPolicy{};
    constexpr auto high_effect = HighStatDropEffectPolicy{};
    constexpr std::array expected_low_rolls{15, 23, 30, 38, 46, 54, 61};
    constexpr std::array expected_high_rolls{18, 27, 36, 45, 54, 63, 72};
    constexpr FalseRNGPolicy rng_policy{};
    for (uint8_t i = 0; i < 6; i++) {
        EXPECT_EQ(
            expected_low_rolls[i],
            execute_move(
                low_effect,
                rng_policy,
                battle_state,
                Who::Player,
                &all_move_infos[to_int(Move::Psychic)]
            )
        );
        EXPECT_EQ(
            battle_state.opponent.get_stat_stage(Stat::SpecialDefense),
            -i - 1
        );
        battle_state.opponent.increase_stat_stage(Stat::SpecialDefense, 1);

        EXPECT_EQ(
            battle_state.opponent.get_stat_stage(Stat::SpecialDefense),
            -i
        );
        EXPECT_EQ(
            expected_high_rolls[i],
            execute_move(
                high_effect,
                rng_policy,
                battle_state,
                Who::Player,
                &all_move_infos[to_int(Move::Psychic)]
            )
        );

        EXPECT_EQ(
            battle_state.opponent.get_stat_stage(Stat::SpecialDefense),
            -i - 1
        );

        battle_state.opponent.add_hp(
            battle_state.opponent.get_original_stat(Stat::Health)
        );
        battle_state.player.increment_power_point(Move::Psychic, 2);
    }
}