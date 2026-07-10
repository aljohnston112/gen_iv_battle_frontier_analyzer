#include "../mocks.h"
#include "move_execution.h"
#include "policies.h"
#include "gtest/gtest.h"

class HighRandomConfusionEffectPolicy :
    public ConfusionStatusPolicy<HighRandomConfusionEffectPolicy> {
public:
    static uint8_t roll_turns_confused(const Who) {
        return 2;
    }

    static uint8_t roll_random_confusion(const Who) {
        return 100;
    }
};

class LowRandomConfusionEffectPolicy :
    public ConfusionStatusPolicy<LowRandomConfusionEffectPolicy> {
public:
    static uint8_t roll_turns_confused(const Who) {
        return 2;
    }

    static uint8_t roll_random_confusion(const Who) {
        return 85;
    }
};

TEST(MoveExecution, FalseRollDoesNotConfuse) {
    auto defender = PokemonState{&CresseliaLeftovers};
    roll_confusion(
        HighRandomConfusionEffectPolicy{},
        NeverConfuseRNGPolicy{},
        defender,
        Who::Player,
        100
    );
    EXPECT_FALSE(defender.has_status(StatusWithStage::Confused));
}

TEST(MoveExecution, TrueRollDoesConfuse) {
    auto defender = PokemonState{&CresseliaLeftovers};
    roll_confusion(
        HighRandomConfusionEffectPolicy{},
        AlwaysConfuseRNGPolicy{},
        defender,
        Who::Player,
        0
    );
    EXPECT_TRUE(defender.has_status(StatusWithStage::Confused));
}

TEST(MoveExecution, SignalBeamConfusesOnTrueRoll) {
    const auto& all_move_infos =
        get_all_moves();

    BattleState battle_state{
        PokemonState{&CresseliaLeftovers},
        PokemonState{&CresseliaLeftovers}
    };

    constexpr auto confusion_status_policy = HighRandomConfusionEffectPolicy{};
    constexpr auto confusion_status_rng_policy = AlwaysConfuseRNGPolicy{};
    constexpr auto crit_rng_policy = NeverCritRNGPolicy{};
    constexpr auto random_factor_policy = OpponentOptimizedRandomFactorPolicy{};
    constexpr auto freeze_rng_policy = NeverFreezeRNGPolicy{};
    constexpr auto stat_change_policy = OpponentOptimizedStatChangePolicy{};

    execute_move(
        confusion_status_policy,
        confusion_status_rng_policy,
        crit_rng_policy,
        random_factor_policy,
        freeze_rng_policy,
        stat_change_policy,
        battle_state,
        Who::Player,
        &all_move_infos[to_int(Move::SignalBeam)]
    );

    EXPECT_TRUE(
        battle_state.opponent.has_status(StatusWithStage::Confused)
    );
}

TEST(MoveExecution, SignalBeamDoesNotConfuseOnFalseRoll) {
    const auto& all_move_infos =
        get_all_moves();

    BattleState battle_state{
        PokemonState{&CresseliaLeftovers},
        PokemonState{&CresseliaLeftovers}
    };

    constexpr auto confusion_status_policy =
        HighRandomConfusionEffectPolicy{};
    constexpr auto confusion_status_rng_policy = NeverConfuseRNGPolicy{};
    constexpr auto crit_rng_policy = NeverCritRNGPolicy{};
    constexpr auto random_factor_policy =
        OpponentOptimizedRandomFactorPolicy{};
    constexpr auto freeze_rng_policy = NeverFreezeRNGPolicy{};
    constexpr auto stat_change_policy = OpponentOptimizedStatChangePolicy{};

    execute_move(
        confusion_status_policy,
        confusion_status_rng_policy,
        crit_rng_policy,
        random_factor_policy,
        freeze_rng_policy,
        stat_change_policy,
        battle_state,
        Who::Player,
        &all_move_infos[to_int(Move::SignalBeam)]
    );

    EXPECT_FALSE(
        battle_state.opponent.has_status(StatusWithStage::Confused)
    );
}

TEST(MoveExecution, BeingConfusedPreventsAttackingOnTrueRoll) {
    const auto& all_move_infos =
        get_all_moves();

    BattleState battle_state{
        PokemonState{&CresseliaLeftovers},
        PokemonState{&CresseliaLeftovers}
    };

    constexpr auto confusion_status_policy =
        HighRandomConfusionEffectPolicy{};
    constexpr auto confusion_status_rng_policy = AlwaysConfuseRNGPolicy{};
    constexpr auto crit_rng_policy = NeverCritRNGPolicy{};
    constexpr auto random_factor_policy =
        OpponentOptimizedRandomFactorPolicy{};
    constexpr auto freeze_rng_policy = NeverFreezeRNGPolicy{};
    constexpr auto stat_change_policy = OpponentOptimizedStatChangePolicy{};

    roll_confusion(
        confusion_status_policy,
        confusion_status_rng_policy,
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
            confusion_status_policy,
            confusion_status_rng_policy,
            crit_rng_policy,
            random_factor_policy,
            freeze_rng_policy,
            stat_change_policy,
            battle_state,
            Who::Player,
            &all_move_infos[to_int(Move::Psychic)]
        )
    );

    EXPECT_TRUE(
        battle_state.player.has_status(StatusWithStage::Confused)
    );
}

template <typename T>
concept IsConfusionTestCase = requires {
    requires IsConfusionStatusPolicy<typename T::ConfusionStatusPolicyType>;
    requires IsConfusionStatusRNGPolicy<typename
        T::ConfusionStatusRNGPolicyType>;
    { +T::ExpectedValue } -> std::same_as<int32_t>;
};

template <
    IsConfusionStatusPolicy ConfusionStatusPolicy,
    IsConfusionStatusRNGPolicy ConfusionStatusRNGPolicy,
    int32_t Value
>
struct ConfusionTestCase {
    using ConfusionStatusPolicyType = ConfusionStatusPolicy;
    using ConfusionStatusRNGPolicyType = ConfusionStatusRNGPolicy;
    static constexpr int32_t ExpectedValue = Value;
};

template <IsConfusionTestCase Case>
void confusion_damage_is_correct(
    PokemonState&& player
) {
    using ConfusionStatusPolicyType = Case::ConfusionStatusPolicyType;
    const ConfusionStatusPolicyType confusion_status_policy{};
    using ConfusionStatusRNGPolicyType = Case::ConfusionStatusRNGPolicyType;
    const ConfusionStatusRNGPolicyType confusion_status_rng_policy{};
    static constexpr int32_t expected_damage = Case::ExpectedValue;

    roll_confusion(
        confusion_status_policy,
        confusion_status_rng_policy,
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
            confusion_status_policy,
            player,
            Who::Player
        )
    );
}

template <IsConfusionTestCase... Cases>
void confusion_damage_is_correct() {
    (
        confusion_damage_is_correct<Cases>(
            PokemonState{&CresseliaNoItem}
        ),
        ...
    );
}

TEST(MoveExecution, RandomConfusionDamageIsCorrect) {
    confusion_damage_is_correct<
        ConfusionTestCase<HighRandomConfusionEffectPolicy,
                          AlwaysConfuseRNGPolicy, 10>,
        ConfusionTestCase<LowRandomConfusionEffectPolicy, AlwaysConfuseRNGPolicy
                          , 8>
    >();
}

template <IsConfusionStatusPolicy T>
void confused_damage_is_correct_on_true_roll(
    const std::array<MoveInfo, to_int(Move::MoveCount)>& all_move_infos,
    BattleState&& battle_state
) {
    T confusion_status_policy{};
    roll_confusion(
        confusion_status_policy,
        AlwaysConfuseRNGPolicy{},
        battle_state.player,
        Who::Player,
        0
    );
    EXPECT_TRUE(battle_state.player.has_status(StatusWithStage::Confused));

    const int32_t expected_damage =
        calculate_confused_hit_damage(
            confusion_status_policy,
            battle_state.player,
            Who::Player
        );

    EXPECT_EQ(
        0,
        execute_move(
            confusion_status_policy,
            AlwaysConfuseRNGPolicy{},
            NeverCritRNGPolicy{},
            OpponentOptimizedRandomFactorPolicy{},
            NeverFreezeRNGPolicy{},
            OpponentOptimizedStatChangePolicy{},
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

template <IsConfusionStatusPolicy... Policies>
void confused_damage_is_correct_on_true_roll() {
    const auto& all_move_infos =
        get_all_moves();
    (
        confused_damage_is_correct_on_true_roll<Policies>(
            all_move_infos,
            {
                PokemonState{&CresseliaNoItem},
                PokemonState{&CresseliaLeftovers}
            }
        ),
        ...
    );
}

TEST(MoveExecution, BeingConfusedDamageIsCorrectOnFalseRoll) {
    confused_damage_is_correct_on_true_roll<
        LowRandomConfusionEffectPolicy,
        HighRandomConfusionEffectPolicy
    >();
}

TEST(MoveExecution, BeingConfusedDoesNotPreventAttackOnFalseRoll) {
    const auto& all_move_infos =
        get_all_moves();

    BattleState battle_state{
        PokemonState{&CresseliaLeftovers},
        PokemonState{&CresseliaLeftovers}
    };

    constexpr LowRandomConfusionEffectPolicy confusion_status_policy{};
    roll_confusion(
        confusion_status_policy,
        AlwaysConfuseRNGPolicy{},
        battle_state.player,
        Who::Player,
        0
    );
    EXPECT_TRUE(battle_state.player.has_status(StatusWithStage::Confused));

    EXPECT_NE(
        0,
        execute_move(
            confusion_status_policy,
            NeverConfuseRNGPolicy{},
            NeverCritRNGPolicy{},
            OpponentOptimizedRandomFactorPolicy{},
            NeverFreezeRNGPolicy{},
            OpponentOptimizedStatChangePolicy{},
            battle_state,
            Who::Player,
            &all_move_infos[to_int(Move::Psychic)]
        )
    );

    EXPECT_TRUE(battle_state.player.has_status(StatusWithStage::Confused));
}

TEST(MoveExecution, ConfusionEndsOnCorrectTurn) {
    const auto& all_move_infos =
        get_all_moves();

    BattleState battle_state{
        PokemonState{&CresseliaLeftovers},
        PokemonState{&CresseliaLeftovers}
    };

    constexpr LowRandomConfusionEffectPolicy random_confusion_policy{};
    constexpr auto confusion_rng_policy = AlwaysConfuseRNGPolicy{};
    constexpr auto crit_rng_policy = NeverCritRNGPolicy{};
    constexpr auto damage_random_factor_policy =
        OpponentOptimizedRandomFactorPolicy{};
    constexpr auto freeze_rng_policy = NeverFreezeRNGPolicy{};
    constexpr auto stat_change_policy = OpponentOptimizedStatChangePolicy{};

    roll_confusion(
        random_confusion_policy,
        confusion_rng_policy,
        battle_state.player,
        Who::Player,
        0
    );
    EXPECT_TRUE(battle_state.player.has_status(StatusWithStage::Confused));

    EXPECT_EQ(
        0,
        execute_move(
            random_confusion_policy,
            confusion_rng_policy,
            crit_rng_policy,
            damage_random_factor_policy,
            freeze_rng_policy,
            stat_change_policy,
            battle_state,
            Who::Player,
            &all_move_infos[to_int(Move::Psychic)]
        )
    );

    EXPECT_TRUE(battle_state.player.has_status(StatusWithStage::Confused));

    EXPECT_EQ(
        0,
        execute_move(
            random_confusion_policy,
            confusion_rng_policy,
            crit_rng_policy,
            damage_random_factor_policy,
            freeze_rng_policy,
            stat_change_policy,
            battle_state,
            Who::Player,
            &all_move_infos[to_int(Move::Psychic)]
        )
    );

    EXPECT_FALSE(battle_state.player.has_status(StatusWithStage::Confused));

    EXPECT_NE(
        0,
        execute_move(
            random_confusion_policy,
            confusion_rng_policy,
            crit_rng_policy,
            damage_random_factor_policy,
            freeze_rng_policy,
            stat_change_policy,
            battle_state,
            Who::Player,
            &all_move_infos[to_int(Move::Psychic)]
        )
    );
}
