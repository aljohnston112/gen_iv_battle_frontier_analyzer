#include <queue>
#include <stack>

#include "../mocks.h"
#include "../test_policies.h"

#include "move_execution.h"

#include "gtest/gtest.h"

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

    execute_move(
        DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
        battle_state,
        Who::Player,
        Move::Flamethrower
    );

    EXPECT_FALSE(battle_state.player.has_status(Status::Flinched));
}

TEST(MoveExecution, DarkPulseCausesFlinchOnTrueRoll) {
    BattleState battle_state{
        PokemonState{&Heatran_7_3},
        PokemonState{&Heatran_7_3}
    };

    EXPECT_FALSE(battle_state.player.has_status(Status::Flinched));

    execute_move(
        ALWAYS_FLINCH_POLICY_CONTAINER,
        battle_state,
        Who::Opponent,
        Move::DarkPulse
    );

    EXPECT_TRUE(battle_state.player.has_status(Status::Flinched));
}

TEST(MoveExecution, DarkPulseDoesNotCauseFlinchOnFalseRoll) {
    BattleState battle_state{
        PokemonState{&Heatran_7_3},
        PokemonState{&Heatran_7_3}
    };

    EXPECT_FALSE(battle_state.player.has_status(Status::Flinched));

    execute_move(
        NEVER_FLINCH_POLICY_CONTAINER,
        battle_state,
        Who::Opponent,
        Move::DarkPulse
    );

    EXPECT_FALSE(battle_state.player.has_status(Status::Flinched));
}

TEST(MoveExecution, ExtrasensoryCausesFlinchOnTrueRoll) {
    BattleState battle_state{
        PokemonState{&Heatran_7_3},
        PokemonState{&Raikou_7_3}
    };

    EXPECT_FALSE(battle_state.player.has_status(Status::Flinched));

    execute_move(
        ALWAYS_FLINCH_POLICY_CONTAINER,
        battle_state,
        Who::Opponent,
        Move::Extrasensory
    );

    EXPECT_TRUE(battle_state.player.has_status(Status::Flinched));
}

TEST(MoveExecution, ExtrasensoryDoesNotCauseFlinchOnFalseRoll) {
    BattleState battle_state{
        PokemonState{&Heatran_7_3},
        PokemonState{&Raikou_7_3}
    };

    EXPECT_FALSE(battle_state.player.has_status(Status::Flinched));

    execute_move(
        NEVER_FLINCH_POLICY_CONTAINER,
        battle_state,
        Who::Opponent,
        Move::Extrasensory
    );

    EXPECT_FALSE(battle_state.player.has_status(Status::Flinched));
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
    BattleState battle_state{
        PokemonState{&Heatran_7_3},
        PokemonState{&Zapdos_7_3}
    };

    EXPECT_FALSE(battle_state.player.has_status(Status::Flinched));

    execute_move(
        ALWAYS_FLINCH_POLICY_CONTAINER,
        battle_state,
        Who::Opponent,
        Move::Twister
    );

    EXPECT_TRUE(battle_state.player.has_status(Status::Flinched));
}

TEST(MoveExecution, TwisterDoesNotCauseFlinchOnFalseRoll) {
    BattleState battle_state{
        PokemonState{&Heatran_7_3},
        PokemonState{&Zapdos_7_3_NoItem}
    };

    EXPECT_FALSE(battle_state.player.has_status(Status::Flinched));

    execute_move(
        NEVER_FLINCH_POLICY_CONTAINER,
        battle_state,
        Who::Opponent,
        Move::Twister
    );

    EXPECT_FALSE(battle_state.player.has_status(Status::Flinched));
}

namespace {
    template <bool... Rolls>
    struct FlinchSequencePolicy :
        FlinchRNGPolicy<FlinchSequencePolicy<Rolls...>> {
        static constexpr std::array<bool, sizeof...(Rolls)> rolls{Rolls...};
        mutable size_t next_roll = 0;

        constexpr bool roll_for_flinch_impl(const int8_t) const {
            if (next_roll >= rolls.size()) {
                throw std::runtime_error("No more rolls for you");
            }

            return rolls[next_roll++];
        }

        [[nodiscard]] constexpr size_t rolls_left() const {
            return rolls.size() - next_roll;
        }
    };
}

TEST(MoveExecution, TwisterWithKingsRockDoesNotCauseFlinchOnTwoFalseRolls) {
    BattleState battle_state{
        PokemonState{&Heatran_7_3},
        PokemonState{&Zapdos_7_3}
    };

    EXPECT_FALSE(battle_state.player.has_status(Status::Flinched));

    auto container =
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

    auto container =
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

    auto container =
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

    auto container =
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
