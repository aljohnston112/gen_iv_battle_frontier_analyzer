#include "../mocks.h"

#include "battle_state.h"

#include "gtest/gtest.h"

TEST(
    BattleEngine,
    CursedPokemonTakesOneFourthOfItsMaxHPInDamageAtTheEndOfTheTurn
) {
    PokemonState defender{&Regirock_7_3};
    defender.set_status(Status::Cursed);
    uint16_t hp_before = defender.get_current_stat(Stat::Health);

    ASSERT_TRUE(defender.has_status(Status::Cursed));

    defender.apply_end_of_turn();

    ASSERT_EQ(
        hp_before - (defender.get_original_stat(Stat::Health) / 4),
        defender.get_current_stat(Stat::Health)
    );
}
