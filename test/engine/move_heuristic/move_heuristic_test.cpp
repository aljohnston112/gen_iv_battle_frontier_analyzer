#include "move_heuristic.h"

#include "../mocks.h"

#include "gtest/gtest.h"

TEST(
    MoveHeuristic,
    PlayerCresselia_7_4ChoosesSignalBeamAndOpponentCresselia_7_4ChoosesSignalBeam
) {
    const BattleState battle_state{
        PokemonState{&Cresselia_7_4},
        PokemonState{&Cresselia_7_4}
    };
    auto [attacker_results, defender_results] =
        choose_move_against_defender(
            DEFAULT_POLICY,
            battle_state,
            battle_state.player,
            battle_state.player.get_moves(),
            battle_state.opponent,
            Who::Player,
            std::nullopt,
            std::nullopt
        );
    ASSERT_EQ(attacker_results.move, Move::SignalBeam);
    ASSERT_EQ(defender_results.move, Move::SignalBeam);
}

TEST(
    MoveHeuristic,
    PlayerCresselia_7_4ChoosesIceBeamAndOpponentLatias_7_4WithNoItemChoosesThunderBolt
) {
    const BattleState battle_state{
        PokemonState{&Cresselia_7_4},
        PokemonState{&LatiasNoItem}
    };
    auto [attacker_results, defender_results] =
        choose_move_against_defender(
            DEFAULT_POLICY_WITH_LOGGING,
            battle_state,
            battle_state.player,
            battle_state.player.get_moves(),
            battle_state.opponent,
            Who::Player,
            std::nullopt,
            std::nullopt
        );
    ASSERT_EQ(defender_results.move, Move::Thunderbolt);
    ASSERT_EQ(attacker_results.move, Move::IceBeam);
}
