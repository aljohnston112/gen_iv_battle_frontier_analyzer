#include "end_of_turn_effects.h"
#include "../mocks.h"
#include "../test_policies.h"

#include "move_execution.h"
#include "policies.h"
#include "gtest/gtest.h"

namespace {
    template <Move M>
    void move_confuses_on_true_roll(const CustomPokemon& custom_pokemon) {
        BattleState battle_state{
            PokemonState{&custom_pokemon},
            PokemonState{&Cresselia_7_4}
        };

        execute_move(
            ALWAYS_CONFUSE_HIGH_RANDOM_CONFUSION_POLICY_CONTAINER,
            battle_state,
            Who::Player,
            M
        );

        EXPECT_TRUE(
            battle_state.opponent.has_status_with_stage(
                StatusWithStage::Confused
            )
        );
    }

    template <Move M>
    void move_does_not_confuse_on_false_roll(
        const CustomPokemon& custom_pokemon
    ) {
        BattleState battle_state{
            PokemonState{&custom_pokemon},
            PokemonState{&Cresselia_7_4}
        };

        execute_move(
            NEVER_CONFUSE_POLICY_CONTAINER,
            battle_state,
            Who::Player,
            M
        );

        EXPECT_FALSE(
            battle_state.opponent.has_status_with_stage(
                StatusWithStage::Confused
            )
        );
    }

    template <Move M>
    void move_confuses_on_false_roll(
        const CustomPokemon& custom_pokemon
    ) {
        BattleState battle_state{
            PokemonState{&custom_pokemon},
            PokemonState{&Cresselia_7_4}
        };

        execute_move(
            NEVER_CONFUSE_POLICY_CONTAINER,
            battle_state,
            Who::Player,
            M
        );

        EXPECT_TRUE(
            battle_state.opponent.has_status_with_stage(
                StatusWithStage::Confused
            )
        );
    }
}


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
    move_confuses_on_true_roll<Move::SignalBeam>(Cresselia_7_4);
}

TEST(MoveExecution, SignalBeamDoesNotConfuseOnFalseRoll) {
    move_does_not_confuse_on_false_roll<Move::SignalBeam>(
        Cresselia_7_4
    );
}

TEST(MoveExecution, BeingConfusedPreventsAttackingOnTrueRoll) {
    BattleState battle_state{
        PokemonState{&Cresselia_7_4},
        PokemonState{&Cresselia_7_4}
    };
    constexpr auto policy_contaner =
        ALWAYS_CONFUSE_HIGH_RANDOM_CONFUSION_POLICY_CONTAINER;
    roll_confusion(
        policy_contaner,
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
            policy_contaner,
            battle_state,
            Who::Player,
            Move::Psychic
        )
    );
    EXPECT_TRUE(
        battle_state.player.has_status_with_stage(StatusWithStage::Confused)
    );
}


TEST(MoveExecution, BeingConfusedDoesNotDeductPowerPointsOnTrueRoll) {
    BattleState battle_state{
        PokemonState{&Cresselia_7_4},
        PokemonState{&Cresselia_7_4}
    };
    constexpr auto policy_contaner =
        ALWAYS_CONFUSE_HIGH_RANDOM_CONFUSION_POLICY_CONTAINER;
    roll_confusion(
        policy_contaner,
        battle_state.player,
        Who::Player,
        0
    );
    uint16_t power_points_before =
        battle_state.player.get_power_points(Move::Psychic);

    EXPECT_LT(0, power_points_before);
    EXPECT_TRUE(
        battle_state.player.has_status_with_stage(StatusWithStage::Confused)
    );
    EXPECT_EQ(
        0,
        execute_move(
            policy_contaner,
            battle_state,
            Who::Player,
            Move::Psychic
        )
    );
    EXPECT_TRUE(
        battle_state.player.has_status_with_stage(StatusWithStage::Confused)
    );
    EXPECT_EQ(
        power_points_before,
        battle_state.player.get_power_points(Move::Psychic)
    );
}

namespace {
    template <typename T>
    concept IsConfusionTestCase = requires {
        requires IsConfusionStatusDamagePolicy<typename
            T::ConfusionStatusPolicyType>;
        requires IsConfusionStatusRNGPolicy<typename
            T::ConfusionStatusRNGPolicyType>;
        { +T::ExpectedValue } -> std::same_as<int32_t>;
    };

    template <
        IsConfusionStatusDamagePolicy ConfusionStatusPolicy,
        IsConfusionStatusRNGPolicy ConfusionStatusRNGPolicy,
        int32_t Value,
        typename... ExtraPolicies
    >
    struct ConfusionTestCase {
        using ConfusionStatusPolicyType = ConfusionStatusPolicy;
        using ConfusionStatusRNGPolicyType = ConfusionStatusRNGPolicy;
        static constexpr int32_t ExpectedValue = Value;
        using ExtraPoliciesType = std::tuple<ExtraPolicies...>;
    };

    template <typename Tuple>
    struct PolicyContainerFromTuple;

    template <typename... Policies>
    struct PolicyContainerFromTuple<std::tuple<Policies...>> {
        using Type = PolicyContainer<Policies...>;
    };

    template <IsConfusionTestCase Case>
    void confusion_damage_is_correct(
        PokemonState&& player
    ) {
        using AllPolicies = decltype(
            std::tuple_cat(
                std::declval<
                    std::tuple<
                        typename Case::ConfusionStatusPolicyType,
                        typename Case::ConfusionStatusRNGPolicyType
                    >
                >(),
                std::declval<typename Case::ExtraPoliciesType>()
            )
        );

        using PolicyContainerType = PolicyContainerFromTuple<AllPolicies>::Type;

        constexpr PolicyContainerType policy_container{};

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

    template <IsConfusionTestCase Case>
    void confusion_damage_is_correct_when_burned(
        PokemonState&& player
    ) {
        using AllPolicies = decltype(
            std::tuple_cat(
                std::declval<
                    std::tuple<
                        typename Case::ConfusionStatusPolicyType,
                        typename Case::ConfusionStatusRNGPolicyType
                    >
                >(),
                std::declval<typename Case::ExtraPoliciesType>()
            )
        );

        using PolicyContainerType = PolicyContainerFromTuple<AllPolicies>::Type;

        constexpr PolicyContainerType policy_container{};

        static constexpr int32_t expected_damage = Case::ExpectedValue;

        roll_confusion(
            policy_container,
            player,
            Who::Player,
            0
        );
        player.try_set_status_condition(StatusCondition::Burn);

        EXPECT_TRUE(
            player.has_status_with_stage(StatusWithStage::Confused)
        );
        EXPECT_TRUE(player.has_status_condition(StatusCondition::Burn));

        EXPECT_EQ(
            expected_damage,
            calculate_confused_hit_damage(
                policy_container,
                player,
                Who::Player
            )
        );
    }
}

namespace {
    template <IsConfusionTestCase... Cases>
    void confusion_damage_is_correct() {
        (
            confusion_damage_is_correct<Cases>(
                PokemonState{&Cresselia_7_4_NoItem}
            ),
            ...
        );
    }

    template <IsConfusionTestCase... Cases>
    void confusion_damage_is_correct_when_burned() {
        (
            confusion_damage_is_correct_when_burned<Cases>(
                PokemonState{&Cresselia_7_4_NoItem}
            ),
            ...
        );
    }
}

TEST(MoveExecution, RandomConfusionDamageIsCorrect) {
    confusion_damage_is_correct<
        ConfusionTestCase<
            HighRandomConfusionEffectPolicy,
            AlwaysConfuseRNGPolicy,
            10
        >,
        ConfusionTestCase<
            LowRandomConfusionEffectPolicy,
            AlwaysConfuseRNGPolicy,
            8
        >
    >();
}

TEST(MoveExecution, RandomConfusionDamageDoesNotCrit) {
    confusion_damage_is_correct<
        ConfusionTestCase<
            HighRandomConfusionEffectPolicy,
            AlwaysConfuseRNGPolicy,
            10,
            AlwaysCritRNGPolicy
        >,
        ConfusionTestCase<
            LowRandomConfusionEffectPolicy,
            AlwaysConfuseRNGPolicy,
            8,
            AlwaysCritRNGPolicy
        >
    >();
}

TEST(MoveExecution, RandomConfusionDamageIsHalvedByBurn) {
    confusion_damage_is_correct_when_burned<
        ConfusionTestCase<
            HighRandomConfusionEffectPolicy,
            AlwaysConfuseRNGPolicy,
            6,
            AlwaysCritRNGPolicy
        >,
        ConfusionTestCase<
            LowRandomConfusionEffectPolicy,
            AlwaysConfuseRNGPolicy,
            5,
            AlwaysCritRNGPolicy
        >
    >();
}

namespace {
    template <IsConfusionStatusDamagePolicy T>
    void confused_damage_is_correct_on_true_roll(
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
}

template <IsConfusionStatusDamagePolicy... Policies>
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

TEST(MoveExecution, BeingConfusedDamageIsCorrectOnTrueRoll) {
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
    constexpr auto policy_container =
        ALWAYS_CONFUSE_LOW_RANDOM_CONFUSION_POLICY_CONTAINER;
    roll_confusion(
        policy_container,
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
            policy_container,
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
            policy_container,
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
            policy_container,
            battle_state,
            Who::Player,
            Move::Psychic
        )
    );
}

TEST(MoveExecution, ConfusionCounterDoesNotDecrementOnRechargeTurn) {
    BattleState battle_state{
        PokemonState{&Entei_7_3},
        PokemonState{&Cresselia_7_4}
    };
    constexpr auto policy_container =
        ALWAYS_CONFUSE_LOW_RANDOM_CONFUSION_POLICY_CONTAINER;
    execute_move(
        policy_container,
        battle_state,
        Who::Player,
        Move::HyperBeam
    );
    apply_end_of_turn(policy_container, battle_state);
    roll_confusion(
        policy_container,
        battle_state.player,
        Who::Player,
        0
    );
    uint16_t expected_confused_counter =
        battle_state.player.get_status_stage(StatusWithStage::Confused);

    EXPECT_LT(0, expected_confused_counter);
    EXPECT_TRUE(
        battle_state.player.has_status_with_stage(StatusWithStage::Confused)
    );
    EXPECT_EQ(
        0,
        execute_move(
            policy_container,
            battle_state,
            Who::Player,
            Move::HyperBeam
        )
    );

    battle_state.player.apply_end_of_turn();

    EXPECT_EQ(
        expected_confused_counter,
        battle_state.player.get_status_stage(StatusWithStage::Confused)
    );
    EXPECT_TRUE(
        battle_state.player.has_status_with_stage(StatusWithStage::Confused)
    );
}

TEST(MoveExecution, ConfusionCounterDoesNotDecrementOnSleepTurn) {
    BattleState battle_state{
        PokemonState{&Entei_7_3},
        PokemonState{&Cresselia_7_4}
    };

    constexpr auto policy_container =
        ALWAYS_CONFUSE_LOW_RANDOM_CONFUSION_POLICY_CONTAINER;
    roll_confusion(
        policy_container,
        battle_state.player,
        Who::Player,
        0
    );
    uint16_t expected_confused_counter =
        battle_state.player.get_status_stage(StatusWithStage::Confused);
    battle_state.player.set_status_with_stage(StatusWithStage::Asleep, 2);

    EXPECT_TRUE(
        battle_state.player.has_status_with_stage(StatusWithStage::Asleep)
    );
    EXPECT_LT(0, expected_confused_counter);
    EXPECT_TRUE(
        battle_state.player.has_status_with_stage(StatusWithStage::Confused)
    );
    EXPECT_EQ(
        0,
        execute_move(
            policy_container,
            battle_state,
            Who::Player,
            Move::FireBlast
        )
    );

    battle_state.player.apply_end_of_turn();

    EXPECT_EQ(
        expected_confused_counter,
        battle_state.player.get_status_stage(StatusWithStage::Confused)
    );
    EXPECT_TRUE(
        battle_state.player.has_status_with_stage(StatusWithStage::Confused)
    );
}

TEST(MoveExecution, ConfusionCounterDoesNotDecrementOnFreezeTurn) {
    BattleState battle_state{
        PokemonState{&Entei_7_3},
        PokemonState{&Cresselia_7_4}
    };

    constexpr auto policy_container =
        ALWAYS_CONFUSE_LOW_RANDOM_CONFUSION_POLICY_CONTAINER;
    roll_confusion(
        policy_container,
        battle_state.player,
        Who::Player,
        0
    );
    uint16_t expected_confused_counter =
        battle_state.player.get_status_stage(StatusWithStage::Confused);
    battle_state.player.try_set_status_condition(StatusCondition::Freeze);

    EXPECT_TRUE(
        battle_state.player.has_status_condition(StatusCondition::Freeze)
    );
    EXPECT_LT(0, expected_confused_counter);
    EXPECT_TRUE(
        battle_state.player.has_status_with_stage(StatusWithStage::Confused)
    );
    EXPECT_EQ(
        0,
        execute_move(
            ALWAYS_FREEZE_POLICY_CONTAINER,
            battle_state,
            Who::Player,
            Move::FireBlast
        )
    );

    battle_state.player.apply_end_of_turn();

    EXPECT_EQ(
        expected_confused_counter,
        battle_state.player.get_status_stage(StatusWithStage::Confused)
    );
    EXPECT_TRUE(
        battle_state.player.has_status_with_stage(StatusWithStage::Confused)
    );
}

TEST(MoveExecution, ConfusionCounterDoesNotDecrementOnParalysisTurn) {
    BattleState battle_state{
        PokemonState{&Entei_7_3},
        PokemonState{&Cresselia_7_4}
    };

    constexpr auto policy_container =
        ALWAYS_CONFUSE_LOW_RANDOM_CONFUSION_POLICY_CONTAINER;
    roll_confusion(
        policy_container,
        battle_state.player,
        Who::Player,
        0
    );
    uint16_t expected_confused_counter =
        battle_state.player.get_status_stage(StatusWithStage::Confused);
    battle_state.player.try_set_status_condition(StatusCondition::Paralysis);

    EXPECT_TRUE(
        battle_state.player.has_status_condition(StatusCondition::Paralysis)
    );
    EXPECT_LT(0, expected_confused_counter);
    EXPECT_TRUE(
        battle_state.player.has_status_with_stage(StatusWithStage::Confused)
    );
    EXPECT_EQ(
        0,
        execute_move(
            ALWAYS_PARALYZE_POLICY_CONTAINER,
            battle_state,
            Who::Player,
            Move::FireBlast
        )
    );

    battle_state.player.apply_end_of_turn();

    EXPECT_EQ(
        expected_confused_counter,
        battle_state.player.get_status_stage(StatusWithStage::Confused)
    );
    EXPECT_TRUE(
        battle_state.player.has_status_with_stage(StatusWithStage::Confused)
    );
}

TEST(MoveExecution, ConfusionCounterDoesNotDecrementOnFlinchTurn) {
    BattleState battle_state{
        PokemonState{&Entei_7_3},
        PokemonState{&Cresselia_7_4}
    };

    constexpr auto policy_container =
        ALWAYS_CONFUSE_LOW_RANDOM_CONFUSION_POLICY_CONTAINER;
    roll_confusion(
        policy_container,
        battle_state.player,
        Who::Player,
        0
    );
    uint16_t expected_confused_counter =
        battle_state.player.get_status_stage(StatusWithStage::Confused);
    battle_state.player.set_status(Status::Flinched);

    EXPECT_TRUE(
        battle_state.player.has_status(Status::Flinched)
    );
    EXPECT_LT(0, expected_confused_counter);
    EXPECT_TRUE(
        battle_state.player.has_status_with_stage(StatusWithStage::Confused)
    );
    EXPECT_EQ(
        0,
        execute_move(
            policy_container,
            battle_state,
            Who::Player,
            Move::FireBlast
        )
    );

    battle_state.player.apply_end_of_turn();

    EXPECT_EQ(
        expected_confused_counter,
        battle_state.player.get_status_stage(StatusWithStage::Confused)
    );
    EXPECT_TRUE(
        battle_state.player.has_status_with_stage(StatusWithStage::Confused)
    );
}

TEST(MoveExecution, ConfusionDoesNotDoDamageOnRechargeTurn) {
    BattleState battle_state{
        PokemonState{&Entei_7_3},
        PokemonState{&Cresselia_7_4}
    };
    constexpr auto policy_container =
        ALWAYS_CONFUSE_LOW_RANDOM_CONFUSION_POLICY_CONTAINER;
    execute_move(
        policy_container,
        battle_state,
        Who::Player,
        Move::HyperBeam
    );
    apply_end_of_turn(policy_container, battle_state);
    roll_confusion(
        policy_container,
        battle_state.player,
        Who::Player,
        0
    );
    uint16_t expected_confused_counter =
        battle_state.player.get_status_stage(StatusWithStage::Confused);
    uint16_t expected_hp = battle_state.player.get_current_stat(Stat::Health);

    EXPECT_LT(0, expected_confused_counter);
    EXPECT_TRUE(
        battle_state.player.has_status_with_stage(StatusWithStage::Confused)
    );
    EXPECT_EQ(
        0,
        execute_move(
            policy_container,
            battle_state,
            Who::Player,
            Move::HyperBeam
        )
    );

    battle_state.player.apply_end_of_turn();

    EXPECT_EQ(
        expected_hp,
        battle_state.player.get_current_stat(Stat::Health)
    );
    EXPECT_EQ(
        expected_confused_counter,
        battle_state.player.get_status_stage(StatusWithStage::Confused)
    );
    EXPECT_TRUE(
        battle_state.player.has_status_with_stage(StatusWithStage::Confused)
    );
}

TEST(MoveExecution, ConfusionDoesNotDoDamageOnSleepTurn) {
    BattleState battle_state{
        PokemonState{&Entei_7_3},
        PokemonState{&Cresselia_7_4}
    };
    constexpr auto policy_container =
        ALWAYS_CONFUSE_LOW_RANDOM_CONFUSION_POLICY_CONTAINER;
    roll_confusion(
        policy_container,
        battle_state.player,
        Who::Player,
        0
    );
    battle_state.player.set_status_with_stage(StatusWithStage::Asleep, 2);
    uint16_t expected_confused_counter =
        battle_state.player.get_status_stage(StatusWithStage::Confused);
    uint16_t expected_hp = battle_state.player.get_current_stat(Stat::Health);

    EXPECT_TRUE(
        battle_state.player.has_status_with_stage(StatusWithStage::Asleep)
    );
    EXPECT_LT(0, expected_confused_counter);
    EXPECT_TRUE(
        battle_state.player.has_status_with_stage(StatusWithStage::Confused)
    );
    EXPECT_EQ(
        0,
        execute_move(
            policy_container,
            battle_state,
            Who::Player,
            Move::FireBlast
        )
    );

    battle_state.player.apply_end_of_turn();

    EXPECT_EQ(
        expected_hp,
        battle_state.player.get_current_stat(Stat::Health)
    );
    EXPECT_EQ(
        expected_confused_counter,
        battle_state.player.get_status_stage(StatusWithStage::Confused)
    );
    EXPECT_TRUE(
        battle_state.player.has_status_with_stage(StatusWithStage::Confused)
    );
}

TEST(MoveExecution, ConfusionDoesNotDoDamageOnFreezeTurn) {
    BattleState battle_state{
        PokemonState{&Entei_7_3},
        PokemonState{&Cresselia_7_4}
    };
    constexpr auto policy_container =
        ALWAYS_CONFUSE_LOW_RANDOM_CONFUSION_POLICY_CONTAINER;
    roll_confusion(
        policy_container,
        battle_state.player,
        Who::Player,
        0
    );
    battle_state.player.try_set_status_condition(StatusCondition::Freeze);
    uint16_t expected_confused_counter =
        battle_state.player.get_status_stage(StatusWithStage::Confused);
    uint16_t expected_hp = battle_state.player.get_current_stat(Stat::Health);

    EXPECT_TRUE(
        battle_state.player.has_status_condition(StatusCondition::Freeze)
    );
    EXPECT_LT(0, expected_confused_counter);
    EXPECT_TRUE(
        battle_state.player.has_status_with_stage(StatusWithStage::Confused)
    );
    EXPECT_EQ(
        0,
        execute_move(
            ALWAYS_FREEZE_POLICY_CONTAINER,
            battle_state,
            Who::Player,
            Move::FireBlast
        )
    );

    battle_state.player.apply_end_of_turn();

    EXPECT_EQ(
        expected_hp,
        battle_state.player.get_current_stat(Stat::Health)
    );
    EXPECT_EQ(
        expected_confused_counter,
        battle_state.player.get_status_stage(StatusWithStage::Confused)
    );
    EXPECT_TRUE(
        battle_state.player.has_status_with_stage(StatusWithStage::Confused)
    );
}

TEST(MoveExecution, ConfusionDoesNotDoDamageOnParalyzedTurn) {
    BattleState battle_state{
        PokemonState{&Entei_7_3},
        PokemonState{&Cresselia_7_4}
    };
    constexpr auto policy_container =
        ALWAYS_CONFUSE_LOW_RANDOM_CONFUSION_POLICY_CONTAINER;
    roll_confusion(
        policy_container,
        battle_state.player,
        Who::Player,
        0
    );
    battle_state.player.try_set_status_condition(StatusCondition::Paralysis);
    uint16_t expected_confused_counter =
        battle_state.player.get_status_stage(StatusWithStage::Confused);
    uint16_t expected_hp = battle_state.player.get_current_stat(Stat::Health);

    EXPECT_TRUE(
        battle_state.player.has_status_condition(StatusCondition::Paralysis)
    );
    EXPECT_LT(0, expected_confused_counter);
    EXPECT_TRUE(
        battle_state.player.has_status_with_stage(StatusWithStage::Confused)
    );
    EXPECT_EQ(
        0,
        execute_move(
            ALWAYS_PARALYZE_POLICY_CONTAINER,
            battle_state,
            Who::Player,
            Move::FireBlast
        )
    );

    battle_state.player.apply_end_of_turn();

    EXPECT_EQ(
        expected_hp,
        battle_state.player.get_current_stat(Stat::Health)
    );
    EXPECT_EQ(
        expected_confused_counter,
        battle_state.player.get_status_stage(StatusWithStage::Confused)
    );
    EXPECT_TRUE(
        battle_state.player.has_status_with_stage(StatusWithStage::Confused)
    );
}

TEST(MoveExecution, ConfusionDoesNotDoDamageOnFlinchTurn) {
    BattleState battle_state{
        PokemonState{&Entei_7_3},
        PokemonState{&Cresselia_7_4}
    };
    constexpr auto policy_container =
        ALWAYS_CONFUSE_LOW_RANDOM_CONFUSION_POLICY_CONTAINER;
    roll_confusion(
        policy_container,
        battle_state.player,
        Who::Player,
        0
    );
    battle_state.player.set_status(Status::Flinched);
    uint16_t expected_confused_counter =
        battle_state.player.get_status_stage(StatusWithStage::Confused);
    uint16_t expected_hp = battle_state.player.get_current_stat(Stat::Health);

    EXPECT_TRUE(
        battle_state.player.has_status(Status::Flinched)
    );
    EXPECT_LT(0, expected_confused_counter);
    EXPECT_TRUE(
        battle_state.player.has_status_with_stage(StatusWithStage::Confused)
    );
    EXPECT_EQ(
        0,
        execute_move(
            policy_container,
            battle_state,
            Who::Player,
            Move::FireBlast
        )
    );

    battle_state.player.apply_end_of_turn();

    EXPECT_EQ(
        expected_hp,
        battle_state.player.get_current_stat(Stat::Health)
    );
    EXPECT_EQ(
        expected_confused_counter,
        battle_state.player.get_status_stage(StatusWithStage::Confused)
    );
    EXPECT_TRUE(
        battle_state.player.has_status_with_stage(StatusWithStage::Confused)
    );
}

TEST(MoveExecution, WaterPulseConfusesOnTrueRoll) {
    move_confuses_on_true_roll<Move::WaterPulse>(Articuno_7_3);
}

TEST(MoveExecution, WaterPulseDoesNotConfuseOnFalseRoll) {
    move_does_not_confuse_on_false_roll<Move::WaterPulse>(
        Articuno_7_3
    );
}

TEST(MoveExecution, ConfuseRayConfusesOnTrueRoll) {
    move_confuses_on_true_roll<Move::ConfuseRay>(Regigigas_7_1);
}

TEST(MoveExecution, ConfuseRayConfuseOnFalseRoll) {
    move_confuses_on_false_roll<Move::ConfuseRay>(
        Regigigas_7_1
    );
}
