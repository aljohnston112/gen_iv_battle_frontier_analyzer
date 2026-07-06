#include "../mocks.h"
#include "move_execution.h"
#include "policies.h"
#include "gtest/gtest.h"

class HighRandomConfusionEffectPolicy :
    public OpponentKnowledgePolicy<HighRandomConfusionEffectPolicy> {
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
    public OpponentKnowledgePolicy<LowRandomConfusionEffectPolicy> {
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
            OpponentOptimizedKnowledgePolicy{},
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

template <IsPolicyTestCase Case>
void confusion_damage_is_correct(
    PokemonState&& player
) {
    using EffectPolicyType = Case::EffectPolicyType;
    const EffectPolicyType effect_policy{};
    using RNGPolicyType = Case::RNGPolicyType;
    const RNGPolicyType rng_policy{};
    static constexpr int32_t expected_damage = Case::ExpectedValue;

    roll_confusion(
        effect_policy,
        rng_policy,
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
            effect_policy,
            player,
            Who::Player
        )
    );
}

template <IsPolicyTestCase... Cases>
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
        PolicyTestCase<HighRandomConfusionEffectPolicy, TrueRNGPolicy, 10>,
        PolicyTestCase<LowRandomConfusionEffectPolicy, TrueRNGPolicy, 8>
    >();
}

template <IsOpponentKnowledgePolicy T>
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

template <IsOpponentKnowledgePolicy... Policies>
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