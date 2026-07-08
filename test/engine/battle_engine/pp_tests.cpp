#include "battle_engine.h"

#include "battle_state.h"
#include "../mocks.h"
#include "gtest/gtest.h"

TEST(Engine, PPLossTriggersStruggle) {
    BattleState battle_state{
        PokemonState{&Cresselia},
        PokemonState{&Cresselia}
    };

    const auto player_moves = battle_state.player.get_moves();
    for (const auto move : player_moves) {
        battle_state.player.clear_power_points(move);
    }

    constexpr auto confusion_status_policy =
        OpponentOptimizedConfusionStatusPolicy{};
    constexpr auto confusion_status_rng_policy = NeverConfuseRNGPolicy{};
    constexpr auto crit_rng_policy = NeverCritRNGPolicy{};
    constexpr auto random_factor_policy =
        OpponentOptimizedRandomFactorPolicy{};
    constexpr auto freeze_rng_policy = NeverFreezeRNGPolicy{};
    constexpr auto stat_change_policy = OpponentOptimizedStatChangePolicy{};

    EXPECT_EQ(
        Move::Struggle,
        choose_move_against_defender(
            confusion_status_policy,
            confusion_status_rng_policy,
            crit_rng_policy,
            random_factor_policy,
            freeze_rng_policy,
            stat_change_policy,
            battle_state,
            battle_state.player,
            battle_state.opponent,
            Who::Player
        )
    );
}

