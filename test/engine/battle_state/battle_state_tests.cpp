#include "battle_state.h"
#include "gtest/gtest.h"

const CustomPokemon Cresselia{
    .name = Pokemon::Cresselia,
    .ability = Ability::Levitate,
    .level = 50,
    .item = Item::WhiteHerb,
    .types = {PokemonType::Psychic, PokemonType::NoType},
    .moves = {Move::Psychic, Move::IceBeam, Move::SignalBeam, Move::Moonlight},
    .stats = {213, 78, 158, 101, 168, 102},
    .pounds = 188.7
};

TEST(BattleState, WhiteHerbClearsNegativeStatus) {
    auto state = PokemonState{&Cresselia};
    state.decrease_stat_stage(Stat::Attack, 1);
    EXPECT_EQ(
        0,
        state.get_stat_stage(Stat::Attack)
    );
    EXPECT_EQ(
        Item::NoItem,
        state.get_current_item_for_effect()
    );
}
