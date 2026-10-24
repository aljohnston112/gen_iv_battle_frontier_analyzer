#include "../mocks.h"

#include "battle_state.h"
#include "end_of_turn_effects.h"
#include "../test_policies.h"

#include "gtest/gtest.h"

TEST(
    BattleEngine,
    CursedPokemonTakesOneFourthOfItsMaxHPInDamageAtTheEndOfTheTurn
) {
    BattleState battle_state{
        PokemonState{&Regirock_7_3},
        PokemonState{&Regirock_7_3}
    };
    PokemonState& defender = battle_state.player;
    defender.set_status(Status::Cursed);
    const uint16_t hp_before = defender.get_current_stat(Stat::Health);

    EXPECT_TRUE(defender.has_status(Status::Cursed));

    apply_end_of_turn(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state
    );

    EXPECT_EQ(
        hp_before - (defender.get_original_stat(Stat::Health) / 4),
        defender.get_current_stat(Stat::Health)
    );
}
