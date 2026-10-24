#include "../mocks.h"
#include "../test_policies.h"

#include "damage_util.h"
#include "move_execution.h"

#include "gtest/gtest.h"

template <IsDamageTestCase Case>
static void random_does_correct_damage_for_struggle_case() {
    constexpr PolicyContainer<
        typename Case::CritRNGPolicyType,
        typename Case::DamageRandomFactorPolicyType
    > policy_container{};

    static constexpr int32_t expected_damage = Case::ExpectedValue;

    const BattleState battle_state{
        PokemonState{&Cresselia_7_4},
        PokemonState{&Cresselia_7_4}
    };
    EXPECT_EQ(
        expected_damage,
        get_struggle_damage(
            policy_container,
            battle_state.player,
            battle_state.opponent,
            Who::Player
        )
    );
}

template <IsDamageTestCase... Cases>
static void random_does_correct_damage_for_struggle() {
    (random_does_correct_damage_for_struggle_case<Cases>(),
        ...
    );
}

TEST(MoveExecution, RandomDoesCorrectDamageForStruggle) {
    random_does_correct_damage_for_struggle<
        DamageTestCase<NeverCritRNGPolicy, LowDamageRandomFactorPolicy, 10>,
        DamageTestCase<NeverCritRNGPolicy, HighDamageRandomFactorPolicy, 12>
    >();
}

TEST(MoveExecution, StruggleDoesTheRightAmountOfRecoil) {
    BattleState battle_state{
        PokemonState{&Cresselia_7_4},
        PokemonState{&Cresselia_7_4}
    };

    constexpr auto policy_container =
        HIGH_RANDOM_DAMAGE_FACTOR_POLICY_CONTAINER;

    execute_struggle(
        policy_container,
        battle_state,
        battle_state.player,
        battle_state.opponent,
        Who::Player
    );

    const auto original_player_health =
        battle_state.player.get_original_stat(Stat::Health);
    EXPECT_EQ(
        battle_state.player.get_current_stat(Stat::Health),
        original_player_health - (original_player_health / 4)
    );
}

TEST(
    MoveExecution,
    AttackerTakesRecoilWhenDamageExceedsSubstitutesHPWhenUsingStruggle
) {
    BattleState battle_state{
        PokemonState{&Latias_7_2},
        PokemonState{&Regigigas_7_2}
    };
    const auto original_player_health =
        battle_state.player.get_original_stat(Stat::Health);
    constexpr uint16_t expected_damage = 22;
    constexpr auto policy_container =
        HIGH_RANDOM_DAMAGE_FACTOR_POLICY_CONTAINER;
    execute_move(
        policy_container,
        battle_state,
        Who::Opponent,
        Move::Substitute
    );
    battle_state.opponent.set_move_status_with_stage(
        MoveStatusWithStage::BehindSubstitute,
        Move::Substitute,
        expected_damage
    );

    execute_struggle(
        policy_container,
        battle_state,
        battle_state.player,
        battle_state.opponent,
        Who::Player
    );

    EXPECT_FALSE(
        battle_state.opponent.has_move_status_with_stage(
            MoveStatusWithStage::BehindSubstitute
        )
    );
    EXPECT_EQ(
        battle_state.player.get_current_stat(Stat::Health),
        original_player_health - (original_player_health / 4)
    );
}

TEST(MoveExecution, StruggleMissesWhenDefenderIsSemiInvulnerable) {
    move_does_no_damage_when_defender_is_semi_invulnerable<Move::Struggle>(
        &Latias_7_2,
        MoveStatusWithStage::Concealed
    );
    move_does_no_damage_when_defender_is_semi_invulnerable<Move::Struggle>(
        &Latias_7_2,
        MoveStatusWithStage::SkyHigh
    );
    move_does_no_damage_when_defender_is_semi_invulnerable<Move::Struggle>(
        &Latias_7_2,
        MoveStatusWithStage::Submerged
    );
    move_does_no_damage_when_defender_is_semi_invulnerable<Move::Struggle>(
        &Latias_7_2,
        MoveStatusWithStage::Underground
    );
}
