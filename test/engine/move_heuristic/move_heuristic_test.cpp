#include "../mocks.h"
#include "../test_policies.h"

#include "move_heuristic.h"

#include "battle_engine.h"
#include "gtest/gtest.h"

TEST(
    MoveHeuristic,
    PlayerCresselia_7_4ChoosesSignalBeamAndOpponentCresselia_7_4ChoosesPsychic
) {
    const BattleState battle_state{
        PokemonState{&Cresselia_7_4},
        PokemonState{&Cresselia_7_4}
    };
    auto [attacker_results, defender_results] =
        choose_move_against_defender(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state,
            battle_state.player.get_moves(true),
            Who::Player,
            std::nullopt,
            std::nullopt
        );
    ASSERT_EQ(attacker_results.move, Move::SignalBeam);
    ASSERT_EQ(defender_results.move, Move::Psychic);
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
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state,
            battle_state.player.get_moves(true),
            Who::Player,
            std::nullopt,
            std::nullopt
        );
    ASSERT_EQ(defender_results.move, Move::Thunderbolt);
    ASSERT_EQ(attacker_results.move, Move::IceBeam);
}

TEST(
    MoveHeuristic,
    Heatran_7_3ChoosesEarthPowerAndOpponentHeatran_7_3ChoosesEarthPower
) {
    const BattleState battle_state{
        PokemonState{&Heatran_7_3},
        PokemonState{&Heatran_7_3}
    };
    auto [attacker_results, defender_results] =
        choose_move_against_defender(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state,
            battle_state.player.get_moves(true),
            Who::Player,
            std::nullopt,
            std::nullopt
        );
    ASSERT_EQ(defender_results.move, Move::EarthPower);
    ASSERT_EQ(attacker_results.move, Move::EarthPower);
}

TEST(
    MoveHeuristic,
    Cresselia_7_4ChoosesPsychicAndOpponentRegirock_7_3ChoosesCurse
) {
    const BattleState battle_state{
        PokemonState{&Cresselia_7_4},
        PokemonState{&Regirock_7_3}
    };
    auto [attacker_results, defender_results] =
        choose_move_against_defender(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state,
            battle_state.opponent.get_moves(true),
            Who::Opponent,
            std::nullopt,
            std::nullopt
        );
    ASSERT_EQ(defender_results.move, Move::Psychic);
    ASSERT_EQ(attacker_results.move, Move::Curse);
}

TEST(
    MoveHeuristic,
    PlayerDoesNotChooseMoveCountWhenOutOfPowerPointsForAccurateMoves
) {
    BattleState battle_state{
        PokemonState{&Regirock_7_3},
        PokemonState{&Regirock_7_3}
    };
    for (const auto move :
         battle_state.player.get_moves(false)
    ) {
        battle_state.player.decrement_power_point(
            move,
            battle_state.player.get_power_points(move)
        );
    }
    auto [attacker_results, defender_results] =
        choose_move_against_defender(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state,
            battle_state.player.get_moves(false),
            Who::Player,
            std::nullopt,
            std::nullopt
        );
    ASSERT_NE(attacker_results.move, Move::MoveCount);
}

TEST(
    MoveHeuristic,
    PlayerDoesNotChooseStruggleWhenOutOfPowerPointsForAccurateMovesButHasPowerPointsForInaccurateMoves
) {
    BattleState battle_state{
        PokemonState{&Regirock_7_3},
        PokemonState{&Regirock_7_3}
    };
    for (const auto move :
         battle_state.player.get_moves(false)
    ) {
        battle_state.player.decrement_power_point(
            move,
            battle_state.player.get_power_points(move)
        );
    }
    auto [attacker_results, defender_results] =
        choose_move_against_defender(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state,
            battle_state.player.get_moves(false),
            Who::Player,
            std::nullopt,
            std::nullopt
        );
    ASSERT_NE(attacker_results.move, Move::Struggle);
}

TEST(
    MoveHeuristic,
    PlayerSuicune_7_3DoesNotChooseShadowBallAgainstRegigigas_7_3
) {
    BattleState battle_state{
        PokemonState{&Regigigas_7_3},
        PokemonState{&Suicune_7_3}
    };
    auto [attacker_results, defender_results] =
        choose_move_against_defender(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state,
            battle_state.opponent.get_moves(true),
            Who::Opponent,
            std::nullopt,
            std::nullopt
        );
    ASSERT_NE(attacker_results.move, Move::ShadowBall);
}

TEST(
    MoveHeuristic,
    PlayerSuicune_7_3ChoosesBlizzardAgainstRegigigas_7_3InHail
) {
    BattleState battle_state{
        PokemonState{&Suicune_7_3},
        PokemonState{&Regigigas_7_3}
    };
    battle_state.set_weather(Weather::Hail, 5);
    auto [attacker_results, defender_results] =
        choose_move_against_defender(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state,
            battle_state.player.get_moves(false),
            Who::Player,
            std::nullopt,
            std::nullopt
        );
    ASSERT_EQ(attacker_results.move, Move::Blizzard);
}

namespace {
    template <typename... Moves>
    void player_chooses_moves_against_opponent_impl(
        const std::vector<TurnResult>& results,
        const size_t index,
        const Move move,
        const Moves... moves
    ) {
        EXPECT_EQ(results[index].player_move_used, move);

        if constexpr (sizeof...(moves) > 0) {
            player_chooses_moves_against_opponent_impl(
                results,
                index + 1,
                moves...
            );
        }
    }

    template <typename... Moves>
    void player_chooses_moves_against_opponent(
        const CustomPokemon& player,
        const CustomPokemon& opponent,
        const Moves... moves
    ) {
        const auto results = single_battle(player, opponent);
        player_chooses_moves_against_opponent_impl(
            results.results,
            1,
            moves...
        );
    }

    template <typename... Moves>
    void opponent_chooses_moves_against_player_impl(
        const std::vector<TurnResult>& results,
        const size_t index,
        const Move move,
        const Moves... moves
    ) {
        EXPECT_EQ(results[index].opponent_move_used, move);

        if constexpr (sizeof...(moves) > 0) {
            opponent_chooses_moves_against_player_impl(
                results,
                index + 1,
                moves...
            );
        }
    }

    template <typename... Moves>
    void opponent_chooses_moves_against_player(
        const CustomPokemon& player,
        const CustomPokemon& opponent,
        const Moves... moves
    ) {
        const auto results = single_battle(player, opponent);
        opponent_chooses_moves_against_player_impl(
            results.results,
            1,
            moves...
        );
    }
}

TEST(
    MoveHeuristic,
    OpponentRegigigas_7_3ChoosesAncientPowerThenFocusBlastThenAncientPowerAgainstCresselia_7_4
) {
    /*
    This particular battle is such a fascinating test case for the following reasons:
        - Regigigas has two state changing moves and any combination of them used
          during the first 3 turns where there are 2 ancient powers and 1 focus blast
          leads to the same optimal outcome
        - The order in which the moves are chosen is dependant on the order
          the moves appear in the move vector of the CustomPokemon
        - It proves the heuristic can find any path to the same outcome
        - It proves the heuristic chooses ancient power and focus blast
          when they lead to a better outcome

    Here are the damage caluculations;:
        Note that the calculated turns add 1 for each turn a move was used
        before the thunderbolt damage is used as the divisor

        Cresselia_7_4 vs. Regigigas_7_3:
            Regigigas_7_3
                Thunderbolt (no boost):
                252 HP / 40 damage = 7 turns
                Thunderbolt (1 special attack boost):
                (252 HP - 26 for ancient power) / 59 damage for thunderbolt = about 4.83 turns
                Thunderbolt (1 special defense drop):
                (252 HP - 25 for focus blast) / 59 damage for thunderbolt = about 4.84 turns
                1 special attack boost is better by 1 damage!

                Thunderbolt (2 special attack boosts):
                (252 HP - 26 for ancient power - 38 for ancient power) / 78 damage for thunderbolt = about 4.41 turns
                Thunderbolt (1 special attack boost, 1 special defense drop):
                (252 HP - 26 for ancient power - 37 for focus blast) / 87 damage for thunderbolt = about 4.17 turns

                Thunderbolt (2 special attack boost, 1 special defense drop):
                (252 HP - 26 for ancient power - 37 for focus blast - 56 for ancient power) / 116 damage for thunderbolt = about 4.15 turns
                Thunderbolt (1 special attack boost, 1 special defense drop):
                (252 HP - 26 for ancient power - 37 for focus blast - 55 for ancient power) / 116 damage for thunderbolt = about 4.16 turns
                By 1 damage again!

                Alternatively:
                Thunderbolt (1 special attack boost, 2 special defense drop):
                (252 HP - 26 for ancient power - 37 for focus blast - 55 for focus blast) / 116 damage for thunderbolt = about 4.16 turns

                Thunderbolt (3 special attack boost, 1 special defense drop):
                (252 HP - 26 for ancient power - 37 for focus blast - 56 for ancient power - 74 for ancient power) / 145 damage for thunderbolt = about 4.41 turns
                Thunderbolt (2 special attack boost, 2 special defense drop):
                (252 HP - 26 for ancient power - 37 for focus blast - 56 for ancient power - 73 focus blast) / 154 damage for thunderbolt = about 4.39 turns
    */
    opponent_chooses_moves_against_player(
        Cresselia_7_4,
        Regigigas_7_3,
        Move::Ancientpower,
        Move::FocusBlast,
        Move::Ancientpower
    );

    CustomPokemon other{Regigigas_7_3};
    other.moves = {
        Move::EarthPower, Move::FocusBlast, Move::Thunderbolt,
        Move::Ancientpower,
    };
    opponent_chooses_moves_against_player(
        Cresselia_7_4,
        other,
        Move::FocusBlast,
        Move::Ancientpower,
        Move::Ancientpower
    );
}

TEST(
    MoveHeuristic,
    OpponentCresselia_7_3ChoosesChargeBeamThenTwoShadowBallsAgainstCresselia_7_4
) {
    // Another fantastic test case!

    // This order means the first turn has 7 more damage,
    // but equal damage over three turns compared to the next battle
    opponent_chooses_moves_against_player(
        Cresselia_7_4,
        Cresselia_7_3,
        Move::Psychic,
        Move::ShadowBall,
        Move::ShadowBall
    );

    // And this order means the third turn has 7 more damage,
    // but equal damage over three turns compared to teh previous battle
    CustomPokemon other{Cresselia_7_3};
    other.moves = {
        Move::ChargeBeam, Move::Psychic, Move::ShadowBall, Move::EnergyBall
    };
    opponent_chooses_moves_against_player(
        Cresselia_7_4,
        other,
        Move::ChargeBeam,
        Move::ShadowBall,
        Move::ShadowBall
    );
}

TEST(
    MoveHeuristic,
    OpponentSuicune_7_3ChoosesTwoShadowBallsThenHydroPumpAgainstCresselia_7_4
) {
    opponent_chooses_moves_against_player(
        Cresselia_7_4,
        Suicune_7_3,
        Move::ShadowBall,
        Move::ShadowBall,
        Move::HydroPump
    );
}

TEST(
    MoveHeuristic,
    OpponentHeatran_7_3ChoosesEarthPowerThenFlamethrowerAgainstRegigigas_7_3
) {
    opponent_chooses_moves_against_player(
        Regigigas_7_3,
        Heatran_7_3,
        Move::EarthPower,
        Move::Flamethrower
    );
}

TEST(
    MoveHeuristic,
    PlayerSuicune_7_3ChoosesHailThenBlizzardAgainstRegirock_7_3
) {
    player_chooses_moves_against_opponent(
        Suicune_7_3,
        Regirock_7_3,
        Move::Hail,
        Move::Blizzard
    );
}
