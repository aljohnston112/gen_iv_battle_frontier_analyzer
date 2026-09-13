#include "../mocks.h"
#include "../test_policies.h"

#include "move_execution.h"
#include "policies.h"
#include "gtest/gtest.h"

TEST(MoveExecution, FalseRollDoesNotConfuse) {
    auto defender = PokemonState{&Cresselia_7_4};

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
    EXPECT_FALSE(defender.has_status_with_stage(StatusWithStage::Confused));
}

TEST(MoveExecution, TrueRollDoesConfuse) {
    auto defender = PokemonState{&Cresselia_7_4};

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
    EXPECT_TRUE(defender.has_status_with_stage(StatusWithStage::Confused));
}

TEST(MoveExecution, SignalBeamConfusesOnTrueRoll) {
    BattleState battle_state{
        PokemonState{&Cresselia_7_4},
        PokemonState{&Cresselia_7_4}
    };

    execute_move(
        ALWAYS_CONFUSE_HIGH_RANDOM_CONFUSION_POLICY_CONTAINER,
        battle_state,
        Who::Player,
        Move::SignalBeam
    );

    EXPECT_TRUE(
        battle_state.opponent.has_status_with_stage(StatusWithStage::Confused)
    );
}

TEST(MoveExecution, SignalBeamDoesNotConfuseOnFalseRoll) {
    BattleState battle_state{
        PokemonState{&Cresselia_7_4},
        PokemonState{&Cresselia_7_4}
    };

    execute_move(
        NEVER_CONFUSE_POLICY_CONTAINER,
        battle_state,
        Who::Player,
        Move::SignalBeam
    );

    EXPECT_FALSE(
        battle_state.opponent.has_status_with_stage(StatusWithStage::Confused)
    );
}

TEST(MoveExecution, BeingConfusedPreventsAttackingOnTrueRoll) {
    BattleState battle_state{
        PokemonState{&Cresselia_7_4},
        PokemonState{&Cresselia_7_4}
    };

    roll_confusion(
        ALWAYS_CONFUSE_HIGH_RANDOM_CONFUSION_POLICY_CONTAINER,
        battle_state.player,
        Who::Player,
        0
    );
    EXPECT_TRUE(
        battle_state.player.has_status_with_stage(StatusWithStage::Confused)
    );

    EXPECT_EQ(
        0,
        execute_move(
            ALWAYS_CONFUSE_HIGH_RANDOM_CONFUSION_POLICY_CONTAINER,
            battle_state,
            Who::Player,
            Move::Psychic
        )
    );

    EXPECT_TRUE(
        battle_state.player.has_status_with_stage(StatusWithStage::Confused)
    );
}

template <typename T>
concept IsConfusionTestCase = requires {
    requires IsConfusionStatusPolicy<typename T::ConfusionStatusPolicyType>;
    requires IsConfusionStatusRNGPolicy<typename
        T::ConfusionStatusRNGPolicyType>;
    { +T::ExpectedValue } -> std::same_as<int32_t>;
};

namespace {
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
}

template <IsConfusionTestCase Case>
static void confusion_damage_is_correct(
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
        player.has_status_with_stage(StatusWithStage::Confused)
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
            PokemonState{&Cresselia_7_4_NoItem}
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
static void confused_damage_is_correct_on_true_roll(
    BattleState&& battle_state
) {
    roll_confusion(
        ALWAYS_CONFUSE_POLICY_CONTAINER<T>,
        battle_state.player,
        Who::Player,
        0
    );
    EXPECT_TRUE(
        battle_state.player.has_status_with_stage(StatusWithStage::Confused)
    );

    const int32_t expected_damage =
        calculate_confused_hit_damage(
            ALWAYS_CONFUSE_POLICY_CONTAINER<T>,
            battle_state.player,
            Who::Player
        );

    EXPECT_EQ(
        0,
        execute_move(
            ALWAYS_CONFUSE_POLICY_CONTAINER<T>,
            battle_state,
            Who::Player,
           Move::Psychic
        )
    );

    EXPECT_EQ(
        battle_state.player.get_original_stat(Stat::Health) -
        battle_state.player.get_current_stat(Stat::Health),
        expected_damage
    );
}

template <IsConfusionStatusPolicy... Policies>
static void confused_damage_is_correct_on_true_roll() {

    (
        confused_damage_is_correct_on_true_roll<Policies>(
            {
                PokemonState{&Cresselia_7_4_NoItem},
                PokemonState{&Cresselia_7_4}
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
    BattleState battle_state{
        PokemonState{&Cresselia_7_4},
        PokemonState{&Cresselia_7_4}
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
    EXPECT_TRUE(
        battle_state.player.has_status_with_stage(StatusWithStage::Confused)
    );

    EXPECT_NE(
        0,
        execute_move(
            NEVER_CONFUSE_POLICY_CONTAINER,
            battle_state,
            Who::Player,
            Move::Psychic
        )
    );

    EXPECT_TRUE(
        battle_state.player.has_status_with_stage(StatusWithStage::Confused)
    );
}

TEST(MoveExecution, ConfusionEndsOnCorrectTurn) {
    BattleState battle_state{
        PokemonState{&Cresselia_7_4},
        PokemonState{&Cresselia_7_4}
    };

    roll_confusion(
        ALWAYS_CONFUSE_LOW_RANDOM_CONFUSION_POLICY_CONTAINER,
        battle_state.player,
        Who::Player,
        0
    );
    EXPECT_TRUE(
        battle_state.player.has_status_with_stage(StatusWithStage::Confused)
    );

    EXPECT_EQ(
        0,
        execute_move(
            ALWAYS_CONFUSE_LOW_RANDOM_CONFUSION_POLICY_CONTAINER,
            battle_state,
            Who::Player,
            Move::Psychic
        )
    );
    battle_state.player.apply_end_of_turn();

    EXPECT_TRUE(
        battle_state.player.has_status_with_stage(StatusWithStage::Confused)
    );

    EXPECT_EQ(
        0,
        execute_move(
            ALWAYS_CONFUSE_LOW_RANDOM_CONFUSION_POLICY_CONTAINER,
            battle_state,
            Who::Player,
            Move::Psychic
        )
    );
    battle_state.player.apply_end_of_turn();

    EXPECT_FALSE(
        battle_state.player.has_status_with_stage(StatusWithStage::Confused)
    );

    EXPECT_NE(
        0,
        execute_move(
            ALWAYS_CONFUSE_LOW_RANDOM_CONFUSION_POLICY_CONTAINER,
            battle_state,
            Who::Player,
            Move::Psychic
        )
    );
}
