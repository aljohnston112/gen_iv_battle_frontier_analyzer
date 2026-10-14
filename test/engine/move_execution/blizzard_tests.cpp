#include "../mocks.h"
#include "../test_policies.h"

#include "battle_state.h"
#include "move_execution.h"

#include "gtest/gtest.h"

TEST(MoveExecution, HailMakesBlizzardAlwaysHit) {
    BattleState battle_state{
        PokemonState{&Suicune_7_3},
        PokemonState{&Suicune_7_3}
    };

    EXPECT_EQ(Weather::Clear, battle_state.get_weather());
    EXPECT_EQ(
        0,
        execute_move(
            ALWAYS_MISS_POLICY_CONTAINER,
            battle_state,
            Who::Player,
            Move::Blizzard
        )
    );

    battle_state.set_weather(Weather::Hail, 5);

    EXPECT_EQ(Weather::Hail, battle_state.get_weather());
    EXPECT_LT(
        0,
        execute_move(
            ALWAYS_MISS_POLICY_CONTAINER,
            battle_state,
            Who::Player,
            Move::Blizzard
        )
    );
}

template <Move M>
static void
move_does_no_damage_when_defender_is_semi_invulnerable_and_it_is_hailing(
    const CustomPokemon* pokemon,
    const MoveStatusWithStage move_status_with_stage
) {
    BattleState battle_state{
        PokemonState{pokemon},
        PokemonState{&Regirock_7_3}
    };
    battle_state.opponent.set_move_status_with_stage(
        move_status_with_stage,
        Move::MoveCount,
        2
    );
    battle_state.set_weather(Weather::Hail, 5);

    EXPECT_EQ(Weather::Hail, battle_state.get_weather());
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

TEST(
    MoveExecution,
    BlizzardDoesNotDamageDefenderWhenDefenderIsConcealedDuringHail
) {
    move_does_no_damage_when_defender_is_semi_invulnerable_and_it_is_hailing<
        Move::Blizzard
    >(
        &Suicune_7_3,
        MoveStatusWithStage::Concealed
    );
}

TEST(
    MoveExecution,
    BlizzardDoesNotDamageDefenderWhenDefenderIsSkyHighDuringHail
) {
    move_does_no_damage_when_defender_is_semi_invulnerable_and_it_is_hailing<
        Move::Blizzard
    >(
        &Suicune_7_3,
        MoveStatusWithStage::SkyHigh
    );
}

TEST(
    MoveExecution,
    BlizzardDoesNotDamageDefenderWhenDefenderIsSubmergedDuringHail
) {
    move_does_no_damage_when_defender_is_semi_invulnerable_and_it_is_hailing<
        Move::Blizzard
    >(
        &Suicune_7_3,
        MoveStatusWithStage::Submerged
    );
}

TEST(
    MoveExecution,
    BlizzardDoesNotDamageDefenderWhenDefenderIsUndergroundDuringHail
) {
    move_does_no_damage_when_defender_is_semi_invulnerable_and_it_is_hailing<
        Move::Blizzard
    >(
        &Suicune_7_3,
        MoveStatusWithStage::Underground
    );
}
