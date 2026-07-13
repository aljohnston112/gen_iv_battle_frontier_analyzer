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

    constexpr PolicyContainer<
        HighRandomConfusionEffectPolicy,
        NeverConfuseRNGPolicy
    > policy_container{};

    roll_confusion(
        policy_container,
        defender,
        Who::Player,
        100
    );
    EXPECT_FALSE(defender.has_status(StatusWithStage::Confused));
}

TEST(MoveExecution, TrueRollDoesConfuse) {
    auto defender = PokemonState{&CresseliaLeftovers};

    constexpr PolicyContainer<
        HighRandomConfusionEffectPolicy,
        AlwaysConfuseRNGPolicy
    > policy_container{};

    roll_confusion(
        policy_container,
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

    constexpr PolicyContainer<
        HighRandomConfusionEffectPolicy,
        AlwaysConfuseRNGPolicy,
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

    constexpr PolicyContainer<
        HighRandomConfusionEffectPolicy,
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

    constexpr PolicyContainer<
        HighRandomConfusionEffectPolicy,
        AlwaysConfuseRNGPolicy,
        NeverCritRNGPolicy,
        OpponentOptimizedRandomFactorPolicy,
        NeverFreezeRNGPolicy,
        OpponentOptimizedStatChangePolicy,
        NeverParalyzeRNGPolicy
    > policy_container{};

    roll_confusion(
        policy_container,
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
            policy_container,
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
    constexpr PolicyContainer<
        typename Case::ConfusionStatusPolicyType,
        typename Case::ConfusionStatusRNGPolicyType
    > policy_container{};

    static constexpr int32_t expected_damage = Case::ExpectedValue;

    roll_confusion(
        policy_container,
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
            policy_container,
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
    constexpr PolicyContainer<
        T,
        AlwaysConfuseRNGPolicy,
        NeverCritRNGPolicy,
        OpponentOptimizedRandomFactorPolicy,
        NeverFreezeRNGPolicy,
        OpponentOptimizedStatChangePolicy,
        NeverParalyzeRNGPolicy
    > policy_container{};

    roll_confusion(
        policy_container,
        battle_state.player,
        Who::Player,
        0
    );
    EXPECT_TRUE(battle_state.player.has_status(StatusWithStage::Confused));

    const int32_t expected_damage =
        calculate_confused_hit_damage(
            policy_container,
            battle_state.player,
            Who::Player
        );

    EXPECT_EQ(
        0,
        execute_move(
            policy_container,
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

    constexpr PolicyContainer<
        LowRandomConfusionEffectPolicy,
        AlwaysConfuseRNGPolicy
    > always_confuse_policy_container{};

    roll_confusion(
        always_confuse_policy_container,
        battle_state.player,
        Who::Player,
        0
    );
    EXPECT_TRUE(battle_state.player.has_status(StatusWithStage::Confused));

    constexpr PolicyContainer<
        LowRandomConfusionEffectPolicy,
        NeverConfuseRNGPolicy,
        NeverCritRNGPolicy,
        OpponentOptimizedRandomFactorPolicy,
        NeverFreezeRNGPolicy,
        OpponentOptimizedStatChangePolicy,
        NeverParalyzeRNGPolicy
    > never_confuse_policy_container{};

    EXPECT_NE(
        0,
        execute_move(
            never_confuse_policy_container,
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

    constexpr PolicyContainer<
        LowRandomConfusionEffectPolicy,
        AlwaysConfuseRNGPolicy,
        NeverCritRNGPolicy,
        OpponentOptimizedRandomFactorPolicy,
        NeverFreezeRNGPolicy,
        OpponentOptimizedStatChangePolicy,
        NeverParalyzeRNGPolicy
    > policy_container{};

    roll_confusion(
        policy_container,
        battle_state.player,
        Who::Player,
        0
    );
    EXPECT_TRUE(battle_state.player.has_status(StatusWithStage::Confused));

    EXPECT_EQ(
        0,
        execute_move(
            policy_container,
            battle_state,
            Who::Player,
            &all_move_infos[to_int(Move::Psychic)]
        )
    );

    EXPECT_TRUE(battle_state.player.has_status(StatusWithStage::Confused));

    EXPECT_EQ(
        0,
        execute_move(
            policy_container,
            battle_state,
            Who::Player,
            &all_move_infos[to_int(Move::Psychic)]
        )
    );

    EXPECT_FALSE(battle_state.player.has_status(StatusWithStage::Confused));

    EXPECT_NE(
        0,
        execute_move(
            policy_container,
            battle_state,
            Who::Player,
            &all_move_infos[to_int(Move::Psychic)]
        )
    );
}
