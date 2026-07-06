#include "move_execution.h"

#include <gtest/gtest.h>

#include "end_of_turn_effects.h"
#include "../mocks.h"
#include "pokemon.h"
#include "policies.h"

TEST(Engine, LeftoversHealsTheCorrectAmountOfHPAtTurnEnd) {
    const auto& all_move_infos =
        get_all_moves();

    BattleState battle_state{
        PokemonState{&Cresselia},
        PokemonState{&Cresselia}
    };

    constexpr auto expected_damage = 42;
    constexpr auto effect_policy = HighRandomEffectPolicy{};
    EXPECT_EQ(
        expected_damage,
        execute_move(
            effect_policy,
            FalseRNGPolicy{},
            battle_state,
            Who::Player,
            &all_move_infos[to_int(Move::SignalBeam)]
        )
    );
    EXPECT_EQ(
        expected_damage,
        execute_move(
            effect_policy,
            FalseRNGPolicy{},
            battle_state,
            Who::Player,
            &all_move_infos[to_int(Move::SignalBeam)]
        )
    );


    constexpr auto total_damage = (2 * expected_damage);
    const auto original_opponent_health =
        battle_state.opponent.get_original_stat(Stat::Health);
    EXPECT_EQ(
        battle_state.opponent.get_current_stat(Stat::Health),
        original_opponent_health - total_damage
    );

    apply_end_of_turn(effect_policy, battle_state);

    EXPECT_EQ(
        battle_state.opponent.get_current_stat(Stat::Health),
        original_opponent_health - total_damage + (original_opponent_health / 16)
    );
}



