#include "move_execution.h"

#include <gtest/gtest.h>

#include "pokemon.h"
#include "policies.h"

const CustomPokemon Cresselia{
    .name = Pokemon::Cresselia,
    .ability = Ability::Levitate,
    .level = 50,
    .item = Item::Leftovers,
    .types = {PokemonType::Psychic, PokemonType::NoType},
    .moves = {Move::Psychic, Move::IceBeam, Move::SignalBeam, Move::Moonlight},
    .stats = {213, 78, 158, 101, 168, 102},
    .pounds = 188.7
};

class LowRandomEffectPolicy :
    public EffectPolicy<LowRandomEffectPolicy> {
public:
    static uint8_t roll_random(const Who) {
        return 85;
    }
};

class HighRandomEffectPolicy :
    public EffectPolicy<HighRandomEffectPolicy> {
public:
    static uint8_t roll_random(const Who) {
        return 100;
    }
};

TEST(Engine, LowRandomDoesCorrectDamageForSpecialAttacks) {
    const auto& all_move_infos =
        get_all_moves();

    const BattleState battle_state{
        PokemonState{&Cresselia},
        PokemonState{&Cresselia}
    };
    EXPECT_EQ(
        15,
        get_damage_of_power_move(
            LowRandomEffectPolicy{},
            FalseRNGPolicy{},
            battle_state,
            &all_move_infos[to_int(Move::Psychic)],
            Who::Player
        )
    );
}

TEST(Engine, HighRandomDoesCorrectDamageForSpecialAttacks) {
    const auto& all_move_infos =
        get_all_moves();

    const BattleState battle_state{
        PokemonState{&Cresselia},
        PokemonState{&Cresselia}
    };
    EXPECT_EQ(
        18,
        get_damage_of_power_move(
            HighRandomEffectPolicy{},
            FalseRNGPolicy{},
            battle_state,
            &all_move_infos[to_int(Move::Psychic)],
            Who::Player
        )
    );
}

TEST(Engine, FalseRollDoesNotFreeze) {
    auto defender = PokemonState{&Cresselia};
    roll_freeze(
        FalseRNGPolicy{},
        Weather::Clear,
        defender,
        100
    );
    EXPECT_TRUE(
        defender.get_current_status_condition() != StatusCondition::Freeze
    );
}


TEST(Engine, TrueRollDoesFreeze) {
    auto defender = PokemonState{&Cresselia};
    roll_freeze(
        TrueRNGPolicy{},
        Weather::Clear,
        defender,
        0
    );
    EXPECT_TRUE(
        defender.get_current_status_condition() == StatusCondition::Freeze
    );
}

TEST(Engine, TrueRollDoesNotFreezeInSun) {
    auto defender = PokemonState{&Cresselia};
    roll_freeze(
        TrueRNGPolicy{},
        Weather::Sun,
        defender,
        0
    );
    EXPECT_TRUE(
        defender.get_current_status_condition() != StatusCondition::Freeze
    );
}

TEST(Engine, FreezePreventsAttackingOnFalseRoll) {
    const auto& all_move_infos =
        get_all_moves();

    BattleState battle_state{
        PokemonState{&Cresselia},
        PokemonState{&Cresselia}
    };
    roll_freeze(
        TrueRNGPolicy{},
        Weather::Clear,
        battle_state.player,
        0
    );
    EXPECT_EQ(
        battle_state.player.get_current_status_condition(),
        StatusCondition::Freeze
    );


    EXPECT_EQ(
        0,
        execute_move(
            OpponentOptimizedEffectPolicy{},
            FalseRNGPolicy{},
            battle_state,
            Who::Player,
            &all_move_infos[static_cast<int>(Move::Psychic)]
        )
    );

    EXPECT_EQ(
        battle_state.player.get_current_status_condition(),
        StatusCondition::Freeze
    );
    EXPECT_EQ(
        battle_state.opponent.get_current_stat(Stat::Health),
        battle_state.opponent.get_original_stat(Stat::Health)
    );
}

TEST(Engine, FreezeThawDoesNotPreventAttackingOnTrueRoll) {
    const auto& all_move_infos =
        get_all_moves();

    BattleState battle_state{
        PokemonState{&Cresselia},
        PokemonState{&Cresselia}
    };
    roll_freeze(
        TrueRNGPolicy{},
        Weather::Clear,
        battle_state.player,
        0
    );
    EXPECT_EQ(
        battle_state.player.get_current_status_condition(),
        StatusCondition::Freeze
    );


    EXPECT_NE(
        0,
        execute_move(
            OpponentOptimizedEffectPolicy{},
            TrueRNGPolicy{},
            battle_state,
            Who::Player,
            &all_move_infos[static_cast<int>(Move::Psychic)]
        )
    );

    EXPECT_NE(
        battle_state.player.get_current_status_condition(),
        StatusCondition::Freeze
    );
    EXPECT_NE(
        battle_state.opponent.get_current_stat(Stat::Health),
        battle_state.opponent.get_original_stat(Stat::Health)
    );
}
