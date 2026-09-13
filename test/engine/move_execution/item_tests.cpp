#include "../mocks.h"
#include "../test_policies.h"

#include "damage_util.h"
#include "end_of_turn_effects.h"
#include "move_execution.h"
#include "pokemon.h"
#include "policies.h"

#include <gtest/gtest.h>

TEST(MoveExecution, LeftoversHealsTheCorrectAmountOfHPAtTurnEnd) {
    BattleState battle_state{
        PokemonState{&Cresselia_7_4},
        PokemonState{&Cresselia_7_4}
    };
    constexpr auto expected_damage = 34;

    EXPECT_EQ(
        expected_damage,
        execute_move(
            OPPONENT_OPTIMIZED_POLICY_CONTAINER,
            battle_state,
            Who::Player,
            Move::SignalBeam
        )
    );
    EXPECT_EQ(
        expected_damage,
        execute_move(
            OPPONENT_OPTIMIZED_POLICY_CONTAINER,
            battle_state,
            Who::Player,
            Move::SignalBeam
        )
    );


    constexpr auto total_damage = (2 * expected_damage);
    const auto original_opponent_health =
        battle_state.opponent.get_original_stat(Stat::Health);
    EXPECT_EQ(
        battle_state.opponent.get_current_stat(Stat::Health),
        original_opponent_health - total_damage
    );

    apply_end_of_turn(OPPONENT_OPTIMIZED_POLICY_CONTAINER, battle_state);

    EXPECT_EQ(
        battle_state.opponent.get_current_stat(Stat::Health),
        original_opponent_health - total_damage + (original_opponent_health / 16
        )
    );
}

TEST(MoveExecution, DracoMeteorActivatesWhiteHerb) {
    BattleState battle_state{
        PokemonState{&Latias_7_4},
        PokemonState{&LatiasNoItem}
    };
    const uint16_t expected_special_attack =
        battle_state.player.get_current_stat(Stat::SpecialAttack);

    execute_move(
        OPPONENT_OPTIMIZED_POLICY_CONTAINER,
        battle_state,
        Who::Player,
        Move::DracoMeteor
    );
    EXPECT_EQ(battle_state.player.get_stat_stage(Stat::SpecialAttack), 0);
    EXPECT_EQ(
        battle_state.player.get_current_stat(Stat::SpecialAttack),
        expected_special_attack
    );
}

TEST(BattleState, WhiteHerbClearsNegativeStatus) {
    auto state = PokemonState{&Latias_7_4};
    state.decrease_stat_stage<Stat::Attack>(
        1,
        StatDropSource::StatDropSourceCount
    );
    EXPECT_EQ(
        0,
        state.get_stat_stage(Stat::Attack)
    );
    EXPECT_EQ(
        Item::NoItem,
        state.get_current_item_for_effect()
    );
}

TEST(
    MoveExecution,
    WiseGlassesIncreasesSpecialAttackPowerBy10Percent
) {
    const BattleState battle_state{
        PokemonState{&Regigias_7_3},
        PokemonState{&Regigias_7_3}
    };
    random_does_correct_damage_for_attack<
        DamageTestCase<NeverCritRNGPolicy, LowDamageRandomFactorPolicy, 112>,
        DamageTestCase<NeverCritRNGPolicy, HighDamageRandomFactorPolicy, 132>
    >(battle_state, Move::FocusBlast);
}


TEST(
    MoveExecution,
    BrightPowderLowersOthersAccuracyByTenPercent
) {
    const BattleState battle_state{
        PokemonState{&Regigias_7_3},
        PokemonState{&Heatran_7_3}
    };
    const MoveInfo* move_info = get_move_info(Move::Flamethrower);
    const uint16_t accuracy_evasion_value =
        calculate_accuracy_and_evasion_based_on_stage(
            move_info->accuracy,
            battle_state.player.get_status_stage(
                StatusWithStage::Accuracy
            ),
            battle_state.opponent.get_status_stage(
                StatusWithStage::Evasion
            )
        );
    EXPECT_EQ(
        accuracy_evasion_value * 9 / 10,
        RealAccuracyEvasionFactorPolicy::get_accuracy_evasion_value(
            battle_state.player,
            battle_state.opponent,
            move_info
        )
    );
}
