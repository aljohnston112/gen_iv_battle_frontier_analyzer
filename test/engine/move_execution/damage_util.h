#pragma once
#include "../mocks.h"
#include "../test_policies.h"

#include "end_of_turn_effects.h"
#include "move_execution.h"

#include "gtest/gtest.h"

struct IncreasingDamageRandomFactorPolicy :
    DamageRandomFactorPolicy<IncreasingDamageRandomFactorPolicy> {
    uint8_t roll_random_impl(const Who) const {
        return current_random++;
    }

    uint8_t peek_next_random() const {
        return current_random;
    }

private:
    mutable uint8_t current_random = 85;
};

template <IsDamageTestCase Case>
static void random_does_correct_damage_for_attack(
    const BattleState& battle_state,
    const MoveInfo* move
) {
    constexpr PolicyContainer<
        typename Case::CritRNGPolicyType,
        typename Case::DamageRandomFactorPolicyType
    > policy_container{};
    static constexpr int32_t expected_damage = Case::ExpectedValue;

    EXPECT_EQ(
        expected_damage,
        get_damage_of_move(
            policy_container,
            battle_state,
            move,
            Who::Player
        )
    );
}

template <IsDamageTestCase... Cases>
static void random_does_correct_damage_for_attack(
    const BattleState& battle_state,
    const Move move
) {
    const auto& all_move_infos =
        get_all_moves();
    (random_does_correct_damage_for_attack<Cases>(
            battle_state,
            &all_move_infos[to_int(move)]
        ),
        ...
    );
}

template< Move M>
static void move_does_no_damage_when_defender_is_semi_invulnerable(
    const CustomPokemon* attacker,
    const MoveStatusWithStage move_status_with_stage
) {
    BattleState battle_state{
        PokemonState{attacker},
        PokemonState{&Regirock_7_3}
    };
    battle_state.opponent.set_move_status_with_stage(
        move_status_with_stage,
        Move::MoveCount,
        2
    );

    if (M == Move::Struggle) {
        battle_state.player.clear_power_points();
    }

    EXPECT_TRUE(
        battle_state.opponent.has_move_status_with_stage(
            move_status_with_stage
        )
    );
    EXPECT_TRUE(
        battle_state.opponent.is_semi_invulnerable()
    );

    EXPECT_EQ(
        0,
        execute_move(
            NEVER_MISS_POLICY_CONTAINER,
            battle_state,
            Who::Player,
            M
        )
    );
}
