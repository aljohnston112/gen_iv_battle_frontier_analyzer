#include "move_execution.h"

#include <gtest/gtest.h>

#include "pokemon.h"
#include "policies.h"

const CustomPokemon Cresselia{
    .name = Pokemon::Cresselia,
    .ability = Ability::Levitate,
    .level = 50,
    .item = Item::Leftovers,
    .types = {PokemonType::Psychic, PokemonType::NoType},
    .moves = {Move::Psychic, Move::IceBeam, Move::SignalBeam, Move::Moonlight},
    .stats = {213, 78, 158, 101, 168, 102},
    .pounds = 188.7
};

const CustomPokemon CresseliaNoItem{
    .name = Pokemon::Cresselia,
    .ability = Ability::Levitate,
    .level = 50,
    .item = Item::NoItem,
    .types = {PokemonType::Psychic, PokemonType::NoType},
    .moves = {Move::Psychic, Move::IceBeam, Move::SignalBeam, Move::Moonlight},
    .stats = {213, 78, 158, 101, 168, 102},
    .pounds = 188.7
};

class LowRandomEffectPolicy :
    public EffectPolicy<LowRandomEffectPolicy> {
public:
    static uint8_t roll_random(const Who) {
        return 85;
    }
};

class HighRandomEffectPolicy :
    public EffectPolicy<HighRandomEffectPolicy> {
public:
    static uint8_t roll_random(const Who) {
        return 100;
    }
};

template <typename T>
concept IsEffectPolicyTestCase = requires {
    requires IsEffectPolicy<typename T::PolicyType>;
    { +T::ExpectedValue } -> std::same_as<int32_t>;
};

template <typename Policy, int32_t Expected>
struct EffectPolicyTestCase {
    using PolicyType = Policy;
    static constexpr int32_t ExpectedValue = Expected;
};

template <IsEffectPolicyTestCase Case>
void random_does_correct_damage_for_special_attacks(
    const std::array<MoveInfo, to_int(Move::MoveCount)>& all_move_infos) {
    using PolicyType = Case::PolicyType;
    const PolicyType effect_policy{};
    static constexpr int32_t expected_damage = Case::ExpectedValue;

    const BattleState battle_state{
        PokemonState{&Cresselia},
        PokemonState{&Cresselia}
    };
    EXPECT_EQ(
        expected_damage,
        get_damage_of_power_move(
            effect_policy,
            FalseRNGPolicy{},
            battle_state,
            &all_move_infos[to_int(Move::Psychic)],
            Who::Player
        )
    );
}

template <IsEffectPolicyTestCase... Cases>
void random_does_correct_damage_for_special_attacks() {
    const auto& all_move_infos =
        get_all_moves();
    (random_does_correct_damage_for_special_attacks<Cases>(all_move_infos),
        ...
    );
}

TEST(Engine, RandomDoesCorrectDamageForSpecialAttacks) {
    random_does_correct_damage_for_special_attacks<
        EffectPolicyTestCase<LowRandomEffectPolicy, 15>,
        EffectPolicyTestCase<HighRandomEffectPolicy, 18>
    >();
}

TEST(Engine, FalseRollDoesNotFreeze) {
    auto defender = PokemonState{&Cresselia};
    roll_freeze(
        FalseRNGPolicy{},
        Weather::Clear,
        defender,
        100
    );
    EXPECT_TRUE(
        defender.get_current_status_condition() != StatusCondition::Freeze
    );
}


TEST(Engine, TrueRollDoesFreeze) {
    auto defender = PokemonState{&Cresselia};
    roll_freeze(
        TrueRNGPolicy{},
        Weather::Clear,
        defender,
        0
    );
    EXPECT_TRUE(
        defender.get_current_status_condition() == StatusCondition::Freeze
    );
}

TEST(Engine, TrueRollDoesNotFreezeInSun) {
    auto defender = PokemonState{&Cresselia};
    roll_freeze(
        TrueRNGPolicy{},
        Weather::Sun,
        defender,
        0
    );
    EXPECT_TRUE(
        defender.get_current_status_condition() != StatusCondition::Freeze
    );
}

TEST(Engine, IceBeamFreezesOnTrueRoll) {
    const auto& all_move_infos =
        get_all_moves();

    BattleState battle_state{
        PokemonState{&Cresselia},
        PokemonState{&Cresselia}
    };

    execute_move(
        OpponentOptimizedEffectPolicy{},
        TrueRNGPolicy{},
        battle_state,
        Who::Player,
        &all_move_infos[to_int(Move::IceBeam)]
    );

    EXPECT_EQ(
        battle_state.opponent.get_current_status_condition(),
        StatusCondition::Freeze
    );
}

TEST(Engine, IceBeamDoesNotFreezeOnFalseRoll) {
    const auto& all_move_infos =
        get_all_moves();

    BattleState battle_state{
        PokemonState{&Cresselia},
        PokemonState{&Cresselia}
    };

    execute_move(
        OpponentOptimizedEffectPolicy{},
        FalseRNGPolicy{},
        battle_state,
        Who::Player,
        &all_move_infos[to_int(Move::IceBeam)]
    );

    EXPECT_NE(
        battle_state.opponent.get_current_status_condition(),
        StatusCondition::Freeze
    );
}

TEST(Engine, FreezePreventsAttackingOnFalseRoll) {
    const auto& all_move_infos =
        get_all_moves();

    BattleState battle_state{
        PokemonState{&Cresselia},
        PokemonState{&Cresselia}
    };
    roll_freeze(
        TrueRNGPolicy{},
        Weather::Clear,
        battle_state.player,
        0
    );
    EXPECT_EQ(
        battle_state.player.get_current_status_condition(),
        StatusCondition::Freeze
    );


    EXPECT_EQ(
        0,
        execute_move(
            OpponentOptimizedEffectPolicy{},
            FalseRNGPolicy{},
            battle_state,
            Who::Player,
            &all_move_infos[to_int(Move::Psychic)]
        )
    );

    EXPECT_EQ(
        battle_state.player.get_current_status_condition(),
        StatusCondition::Freeze
    );
    EXPECT_EQ(
        battle_state.opponent.get_current_stat(Stat::Health),
        battle_state.opponent.get_original_stat(Stat::Health)
    );
}

TEST(Engine, FreezeThawDoesNotPreventAttackingOnTrueRoll) {
    const auto& all_move_infos =
        get_all_moves();

    BattleState battle_state{
        PokemonState{&Cresselia},
        PokemonState{&Cresselia}
    };
    roll_freeze(
        TrueRNGPolicy{},
        Weather::Clear,
        battle_state.player,
        0
    );
    EXPECT_EQ(
        battle_state.player.get_current_status_condition(),
        StatusCondition::Freeze
    );


    EXPECT_NE(
        0,
        execute_move(
            OpponentOptimizedEffectPolicy{},
            TrueRNGPolicy{},
            battle_state,
            Who::Player,
            &all_move_infos[to_int(Move::Psychic)]
        )
    );

    EXPECT_NE(
        battle_state.player.get_current_status_condition(),
        StatusCondition::Freeze
    );
    EXPECT_NE(
        battle_state.opponent.get_current_stat(Stat::Health),
        battle_state.opponent.get_original_stat(Stat::Health)
    );
}

class HighRandomConfusionEffectPolicy :
    public EffectPolicy<HighRandomConfusionEffectPolicy> {
public:
    static uint8_t roll_random(const Who) {
        return 85;
    }

    static uint8_t roll_turns_confused(const Who who) {
        return 2;
    }

    static uint8_t roll_random_confusion(const Who) {
        return 100;
    }

    static bool roll_stat_drop(const uint8_t, const Who who) {
        return false;
    }
};

class LowRandomConfusionEffectPolicy :
    public EffectPolicy<LowRandomConfusionEffectPolicy> {
public:
    static uint8_t roll_random(const Who) {
        return 100;
    }

    static uint8_t roll_turns_confused(const Who who) {
        return 2;
    }

    static uint8_t roll_random_confusion(const Who) {
        return 85;
    }

    static bool roll_stat_drop(const uint8_t, const Who who) {
        return false;
    }
};

TEST(Engine, FalseRollDoesNotConfuse) {
    auto defender = PokemonState{&Cresselia};
    roll_confusion(
        HighRandomConfusionEffectPolicy{},
        FalseRNGPolicy{},
        defender,
        Who::Player,
        100
    );
    EXPECT_FALSE(defender.has_status(StatusWithStage::Confused));
}

TEST(Engine, TrueRollDoesConfuse) {
    auto defender = PokemonState{&Cresselia};
    roll_confusion(
        HighRandomConfusionEffectPolicy{},
        TrueRNGPolicy{},
        defender,
        Who::Player,
        0
    );
    EXPECT_TRUE(defender.has_status(StatusWithStage::Confused));
}

TEST(Engine, SignalBeamConfusesOnTrueRoll) {
    const auto& all_move_infos =
        get_all_moves();

    BattleState battle_state{
        PokemonState{&Cresselia},
        PokemonState{&Cresselia}
    };

    execute_move(
        HighRandomConfusionEffectPolicy{},
        TrueRNGPolicy{},
        battle_state,
        Who::Player,
        &all_move_infos[to_int(Move::SignalBeam)]
    );

    EXPECT_TRUE(
        battle_state.opponent.has_status(StatusWithStage::Confused)
    );
}

TEST(Engine, SignalBeamDoesNotConfuseOnFalseRoll) {
    const auto& all_move_infos =
        get_all_moves();

    BattleState battle_state{
        PokemonState{&Cresselia},
        PokemonState{&Cresselia}
    };

    execute_move(
        HighRandomConfusionEffectPolicy{},
        FalseRNGPolicy{},
        battle_state,
        Who::Player,
        &all_move_infos[to_int(Move::SignalBeam)]
    );

    EXPECT_FALSE(
        battle_state.opponent.has_status(StatusWithStage::Confused)
    );
}

TEST(Engine, BeingConfusedPreventsAttackingOnTrueRoll) {
    const auto& all_move_infos =
        get_all_moves();

    BattleState battle_state{
        PokemonState{&Cresselia},
        PokemonState{&Cresselia}
    };
    roll_confusion(
        HighRandomConfusionEffectPolicy{},
        TrueRNGPolicy{},
        battle_state.player,
        Who::Player,
        0
    );
    EXPECT_TRUE(
        battle_state.player.has_status(StatusWithStage::Confused)
    );

    EXPECT_EQ(
        0,
        execute_move(
            OpponentOptimizedEffectPolicy{},
            TrueRNGPolicy{},
            battle_state,
            Who::Player,
            &all_move_infos[to_int(Move::Psychic)]
        )
    );

    EXPECT_TRUE(
        battle_state.player.has_status(StatusWithStage::Confused)
    );
}

template <IsEffectPolicyTestCase Case>
void confusion_damage_is_correct(
    PokemonState&& player
) {
    using PolicyType = Case::PolicyType;
    const PolicyType confusion_effect_policy{};
    static constexpr int32_t expected_damage = Case::ExpectedValue;

    roll_confusion(
        confusion_effect_policy,
        TrueRNGPolicy{},
        player,
        Who::Player,
        0
    );
    EXPECT_TRUE(
        player.has_status(StatusWithStage::Confused)
    );

    EXPECT_EQ(
        expected_damage,
        calculate_confused_hit_damage(
            confusion_effect_policy,
            player,
            Who::Player
        )
    );
}

template <IsEffectPolicyTestCase... Cases>
void confusion_damage_is_correct() {
    (
        confusion_damage_is_correct<Cases>(
            PokemonState{&CresseliaNoItem}
        ),
        ...
    );
}

TEST(Engine, RandomConfusionDamageIsCorrect) {
    confusion_damage_is_correct<
        EffectPolicyTestCase<HighRandomConfusionEffectPolicy, 10>,
        EffectPolicyTestCase<LowRandomConfusionEffectPolicy, 8>
    >();
}

template <IsEffectPolicy T>
void confused_damage_is_correct_on_true_roll(
    const std::array<MoveInfo, to_int(Move::MoveCount)>& all_move_infos,
    BattleState&& battle_state
) {
    T confusion_effect_policy{};
    roll_confusion(
        confusion_effect_policy,
        TrueRNGPolicy{},
        battle_state.player,
        Who::Player,
        0
    );
    EXPECT_TRUE(battle_state.player.has_status(StatusWithStage::Confused));

    const int32_t expected_damage =
        calculate_confused_hit_damage(
            confusion_effect_policy,
            battle_state.player,
            Who::Player
        );

    EXPECT_EQ(
        0,
        execute_move(
            confusion_effect_policy,
            TrueRNGPolicy{},
            battle_state,
            Who::Player,
            &all_move_infos[to_int(Move::Psychic)]
        )
    );

    EXPECT_EQ(
        battle_state.player.get_original_stat(Stat::Health) -
        battle_state.player.get_current_stat(Stat::Health),
        expected_damage
    );
}

template <IsEffectPolicy... Policies>
void confused_damage_is_correct_on_true_roll() {
    const auto& all_move_infos =
        get_all_moves();
    (
        confused_damage_is_correct_on_true_roll<Policies>(
            all_move_infos,
            {
                PokemonState{&CresseliaNoItem},
                PokemonState{&Cresselia}
            }
        ),
        ...
    );
}

TEST(Engine, BeingConfusedDamageIsCorrectOnFalseRoll) {
    confused_damage_is_correct_on_true_roll<
        LowRandomConfusionEffectPolicy,
        HighRandomConfusionEffectPolicy
    >();
}

TEST(Engine, BeingConfusedDoesNotPreventAttackOnFalseRoll) {
    const auto& all_move_infos =
        get_all_moves();

    BattleState battle_state{
        PokemonState{&Cresselia},
        PokemonState{&Cresselia}
    };

    constexpr LowRandomConfusionEffectPolicy confusion_effect_policy{};
    roll_confusion(
        confusion_effect_policy,
        TrueRNGPolicy{},
        battle_state.player,
        Who::Player,
        0
    );
    EXPECT_TRUE(battle_state.player.has_status(StatusWithStage::Confused));

    EXPECT_NE(
        0,
        execute_move(
            confusion_effect_policy,
            FalseRNGPolicy{},
            battle_state,
            Who::Player,
            &all_move_infos[to_int(Move::Psychic)]
        )
    );

    EXPECT_TRUE(battle_state.player.has_status(StatusWithStage::Confused));
}

TEST(Engine, ConfusionEndsOnCorrectTurn) {
    const auto& all_move_infos =
        get_all_moves();

    BattleState battle_state{
        PokemonState{&Cresselia},
        PokemonState{&Cresselia}
    };

    constexpr LowRandomConfusionEffectPolicy confusion_effect_policy{};
    roll_confusion(
        confusion_effect_policy,
        TrueRNGPolicy{},
        battle_state.player,
        Who::Player,
        0
    );
    EXPECT_TRUE(battle_state.player.has_status(StatusWithStage::Confused));

    EXPECT_EQ(
        0,
        execute_move(
            confusion_effect_policy,
            TrueRNGPolicy{},
            battle_state,
            Who::Player,
            &all_move_infos[to_int(Move::Psychic)]
        )
    );

    EXPECT_TRUE(battle_state.player.has_status(StatusWithStage::Confused));

    EXPECT_EQ(
        0,
        execute_move(
            confusion_effect_policy,
            TrueRNGPolicy{},
            battle_state,
            Who::Player,
            &all_move_infos[to_int(Move::Psychic)]
        )
    );

    EXPECT_FALSE(battle_state.player.has_status(StatusWithStage::Confused));

    EXPECT_NE(
        0,
        execute_move(
            confusion_effect_policy,
            TrueRNGPolicy{},
            battle_state,
            Who::Player,
            &all_move_infos[to_int(Move::Psychic)]
        )
    );
}

class HighStatDropEffectPolicy :
    public EffectPolicy<HighStatDropEffectPolicy> {
public:
    static uint8_t roll_random(const Who) {
        return 100;
    }

    static bool roll_stat_drop(const uint8_t, const Who) {
        return true;
    }
};

class LowStatDropEffectPolicy :
    public EffectPolicy<LowStatDropEffectPolicy> {
public:
    static uint8_t roll_random(const Who) {
        return 85;
    }

    static bool roll_stat_drop(const uint8_t, const Who) {
        return true;
    }
};

class NoStatDropEffectPolicy :
    public EffectPolicy<NoStatDropEffectPolicy> {
public:
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
