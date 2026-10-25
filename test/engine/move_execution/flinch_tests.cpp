#include <queue>
#include <stack>

#include "../mocks.h"
#include "../test_policies.h"

#include "move_execution.h"

#include "gtest/gtest.h"

namespace {
    template <Move M>
    void move_causes_flinch_on_true_roll(const CustomPokemon& custom_pokemon) {
        BattleState battle_state{
            PokemonState{&Heatran_7_3},
            PokemonState{&custom_pokemon}
        };

        EXPECT_FALSE(battle_state.player.has_status(Status::Flinched));

        execute_move(
            ALWAYS_FLINCH_POLICY_CONTAINER,
            battle_state,
            Who::Opponent,
            M
        );

        EXPECT_TRUE(battle_state.player.has_status(Status::Flinched));
    }

    template <Move M>
    void move_does_not_cause_flinch_on_false_roll(
        const CustomPokemon& custom_pokemon
    ) {
        BattleState battle_state{
            PokemonState{&Heatran_7_3},
            PokemonState{&custom_pokemon}
        };

        EXPECT_FALSE(battle_state.player.has_status(Status::Flinched));

        execute_move(
            NEVER_FLINCH_POLICY_CONTAINER,
            battle_state,
            Who::Opponent,
            M
        );

        EXPECT_FALSE(battle_state.player.has_status(Status::Flinched));
    }
}

TEST(MoveExecution, FlinchedStatusOnAttackerPreventsItsMove) {
    BattleState battle_state{
        PokemonState{&Heatran_7_3},
        PokemonState{&Heatran_7_3}
    };

    battle_state.player.set_status(Status::Flinched);

    EXPECT_TRUE(battle_state.player.has_status(Status::Flinched));
    EXPECT_EQ(
        0,
        execute_move(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state,
            Who::Player,
            Move::Flamethrower
        )
    );
}

TEST(MoveExecution, FlinchedStatusIsClearedAfterMoveFails) {
    BattleState battle_state{
        PokemonState{&Heatran_7_3},
        PokemonState{&Heatran_7_3}
    };

    battle_state.player.set_status(Status::Flinched);

    EXPECT_TRUE(battle_state.player.has_status(Status::Flinched));
    EXPECT_EQ(
        0,
        execute_move(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state,
            Who::Player,
            Move::Flamethrower
        )
    );
    EXPECT_FALSE(battle_state.player.has_status(Status::Flinched));
}

TEST(MoveExecution, DarkPulseCausesFlinchOnTrueRoll) {
    move_causes_flinch_on_true_roll<Move::DarkPulse>(Heatran_7_3);
}

TEST(MoveExecution, DarkPulseDoesNotCauseFlinchOnFalseRoll) {
    move_does_not_cause_flinch_on_false_roll<Move::DarkPulse>(
        Heatran_7_3
    );
}

TEST(MoveExecution, ExtrasensoryCausesFlinchOnTrueRoll) {
    move_causes_flinch_on_true_roll<Move::Extrasensory>(
        Raikou_7_3
    );
}

TEST(MoveExecution, ExtrasensoryDoesNotCauseFlinchOnFalseRoll) {
    move_does_not_cause_flinch_on_false_roll<Move::Extrasensory>(
        Raikou_7_3
    );
}

TEST(MoveExecution, KingsRockWithAffectedMoveCausesFlinchOnTrueRoll) {
    BattleState battle_state{
        PokemonState{&Heatran_7_3},
        PokemonState{&Zapdos_7_3}
    };

    EXPECT_FALSE(battle_state.player.has_status(Status::Flinched));

    execute_move(
        ALWAYS_FLINCH_POLICY_CONTAINER,
        battle_state,
        Who::Opponent,
        Move::DrillPeck
    );

    EXPECT_TRUE(battle_state.player.has_status(Status::Flinched));
}

TEST(MoveExecution, KingsRockWithAffectedMoveDoesNotCauseFlinchOnFalseRoll) {
    BattleState battle_state{
        PokemonState{&Heatran_7_3},
        PokemonState{&Zapdos_7_3}
    };

    EXPECT_FALSE(battle_state.player.has_status(Status::Flinched));

    execute_move(
        NEVER_FLINCH_POLICY_CONTAINER,
        battle_state,
        Who::Opponent,
        Move::DrillPeck
    );

    EXPECT_FALSE(battle_state.player.has_status(Status::Flinched));
}

TEST(MoveExecution, KingsRockWithNonAffectedMoveDoesNotCauseFlinchOnTrueRoll) {
    BattleState battle_state{
        PokemonState{&Heatran_7_3},
        PokemonState{&Cresselia_7_4}
    };
    battle_state.opponent.set_item(Item::KingsRock);

    EXPECT_FALSE(battle_state.player.has_status(Status::Flinched));
    EXPECT_EQ(
        Item::KingsRock,
        battle_state.opponent.get_current_item_for_effect()
    );

    execute_move(
        ALWAYS_FLINCH_POLICY_CONTAINER,
        battle_state,
        Who::Opponent,
        Move::IceBeam
    );

    EXPECT_FALSE(battle_state.player.has_status(Status::Flinched));
}

TEST(MoveExecution, TwisterCausesFlinchOnTrueRoll) {
    move_causes_flinch_on_true_roll<Move::Twister>(
        Zapdos_7_3_NoItem
    );
}

TEST(MoveExecution, TwisterDoesNotCauseFlinchOnFalseRoll) {
    move_does_not_cause_flinch_on_false_roll<Move::Twister>(
        Zapdos_7_3_NoItem
    );
}

namespace {
    template <bool... Rolls>
    struct FlinchSequencePolicy :
        FlinchRNGPolicy<FlinchSequencePolicy<Rolls...>> {
        static constexpr std::array<bool, sizeof...(Rolls)> rolls{Rolls...};
        mutable size_t next_roll = 0;

        constexpr bool roll_for_flinch_impl(const int8_t, const Who) const {
            if (next_roll >= rolls.size()) {
                throw std::runtime_error("No more rolls for you");
            }

            return rolls[next_roll++];
        }

        [[nodiscard]] constexpr size_t rolls_left() const {
            return rolls.size() - next_roll;
        }
    };

    static_assert(IsAllowedPolicy<FlinchSequencePolicy<false, false>>);
}

TEST(MoveExecution, TwisterWithKingsRockDoesNotCauseFlinchOnTwoFalseRolls) {
    BattleState battle_state{
        PokemonState{&Heatran_7_3},
        PokemonState{&Zapdos_7_3}
    };

    EXPECT_FALSE(battle_state.player.has_status(Status::Flinched));

    const auto container =
        FLINCH_POLICY_CONTAINER<FlinchSequencePolicy<false, false>>;
    execute_move(
        container,
        battle_state,
        Who::Opponent,
        Move::Twister
    );

    EXPECT_EQ(0, container.rolls_left());
    EXPECT_FALSE(battle_state.player.has_status(Status::Flinched));
}

TEST(
    MoveExecution,
    TwisterWithKingsRockCausesFlinchOnFalseRollFollowedByTrueRoll
) {
    BattleState battle_state{
        PokemonState{&Heatran_7_3},
        PokemonState{&Zapdos_7_3}
    };

    EXPECT_FALSE(battle_state.player.has_status(Status::Flinched));

    const auto container =
        FLINCH_POLICY_CONTAINER<FlinchSequencePolicy<false, true>>;
    execute_move(
        container,
        battle_state,
        Who::Opponent,
        Move::Twister
    );

    EXPECT_EQ(0, container.rolls_left());
    EXPECT_TRUE(battle_state.player.has_status(Status::Flinched));
}

TEST(
    MoveExecution,
    TwisterWithKingsRockCausesFlinchOnTrueRollFollowedByFalseRoll
) {
    BattleState battle_state{
        PokemonState{&Heatran_7_3},
        PokemonState{&Zapdos_7_3}
    };

    EXPECT_FALSE(battle_state.player.has_status(Status::Flinched));

    const auto container =
        FLINCH_POLICY_CONTAINER<FlinchSequencePolicy<true, false>>;
    execute_move(
        container,
        battle_state,
        Who::Opponent,
        Move::Twister
    );

    EXPECT_EQ(0, container.rolls_left());
    EXPECT_TRUE(battle_state.player.has_status(Status::Flinched));
}

TEST(MoveExecution, TwisterWithKingsRockCausesFlinchOnTwoTrueRolls) {
    BattleState battle_state{
        PokemonState{&Heatran_7_3},
        PokemonState{&Zapdos_7_3}
    };

    EXPECT_FALSE(battle_state.player.has_status(Status::Flinched));

    const auto container =
        FLINCH_POLICY_CONTAINER<FlinchSequencePolicy<true, true>>;
    execute_move(
        container,
        battle_state,
        Who::Opponent,
        Move::Twister
    );

    EXPECT_EQ(0, container.rolls_left());
    EXPECT_TRUE(battle_state.player.has_status(Status::Flinched));
}

TEST(MoveExecution, ZenHeadbuttCausesFlinchOnTrueRoll) {
    move_causes_flinch_on_true_roll<Move::ZenHeadbutt>(
        Regigigas_7_2
    );
}

TEST(MoveExecution, ZenHeadbuttDoesNotCauseFlinchOnFalseRoll) {
    move_does_not_cause_flinch_on_false_roll<Move::ZenHeadbutt>(
        Regigigas_7_2
    );
}

TEST(MoveExecution, BiteCausesFlinchOnTrueRoll) {
    move_causes_flinch_on_true_roll<Move::Bite>(Suicune_7_2);
}

TEST(MoveExecution, BiteDoesNotCauseFlinchOnFalseRoll) {
    move_does_not_cause_flinch_on_false_roll<Move::Bite>(
        Suicune_7_2
    );
}

TEST(MoveExecution, IronHeadCausesFlinchOnTrueRoll) {
    move_causes_flinch_on_true_roll<Move::IronHead>(Suicune_7_2);
}

TEST(MoveExecution, IronHeadDoesNotCauseFlinchOnFalseRoll) {
    move_does_not_cause_flinch_on_false_roll<Move::IronHead>(
        Suicune_7_2
    );
}

TEST(MoveExecution, IceFangCausesFlinchOnTrueRoll) {
    move_causes_flinch_on_true_roll<Move::IceFang>(Suicune_7_2);
}

TEST(MoveExecution, IceFangDoesNotCauseFlinchOnFalseRoll) {
    move_does_not_cause_flinch_on_false_roll<Move::IceFang>(
        Suicune_7_2
    );
}

TEST(MoveExecution, WaterfallCausesFlinchOnTrueRoll) {
    move_causes_flinch_on_true_roll<Move::Waterfall>(Suicune_7_2);
}

TEST(MoveExecution, WaterfallDoesNotCauseFlinchOnFalseRoll) {
    move_does_not_cause_flinch_on_false_roll<Move::Waterfall>(
        Suicune_7_2
    );
}
