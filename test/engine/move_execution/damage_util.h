#pragma once
#include "../mocks.h"

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