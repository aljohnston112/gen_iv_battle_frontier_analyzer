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
    const MoveResults player_move_results =
        choose_move_against_defender(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state,
            battle_state.player.get_moves(false),
            Who::Player,
            std::nullopt,
            std::nullopt,
            0
        );


    EXPECT_EQ(
        player_move_results.attacker_results.evaluated_move,
        Move::SignalBeam
    );
    EXPECT_EQ(
        player_move_results.defender_results.evaluated_move,
        Move::Psychic
    );
}

TEST(
    MoveHeuristic,
    PlayerCresselia_7_4ChoosesIceBeamAndOpponentLatias_7_4WithNoItemChoosesThunderBolt
) {
    const BattleState battle_state{
        PokemonState{&Cresselia_7_4},
        PokemonState{&Latias_7_4_No_Item}
    };
    const MoveResults player_move_results =
        choose_move_against_defender(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state,
            battle_state.player.get_moves(false),
            Who::Player,
            std::nullopt,
            std::nullopt,
            0
        );

    EXPECT_EQ(
        player_move_results.defender_results.evaluated_move,
        Move::Thunderbolt
    );
    EXPECT_EQ(
        player_move_results.attacker_results.evaluated_move,
        Move::IceBeam
    );
}

TEST(
    MoveHeuristic,
    Heatran_7_3ChoosesEarthPowerAndOpponentHeatran_7_3ChoosesEarthPower
) {
    const BattleState battle_state{
        PokemonState{&Heatran_7_3},
        PokemonState{&Heatran_7_3}
    };
    const MoveResults player_move_results =
        choose_move_against_defender(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state,
            battle_state.player.get_moves(false),
            Who::Player,
            std::nullopt,
            std::nullopt,
            0
        );

    EXPECT_EQ(
        player_move_results.attacker_results.evaluated_move,
        Move::EarthPower
    );
    EXPECT_EQ(
        player_move_results.defender_results.evaluated_move,
        Move::EarthPower
    );
}

TEST(
    MoveHeuristic,
    Cresselia_7_4ChoosesPsychicAndOpponentRegirock_7_3ChoosesCurse
) {
    const BattleState battle_state{
        PokemonState{&Cresselia_7_4},
        PokemonState{&Regirock_7_3}
    };
    const MoveResults player_move_results =
        choose_move_against_defender(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state,
            battle_state.player.get_moves(false),
            Who::Player,
            std::nullopt,
            std::nullopt,
            0
        );

    EXPECT_EQ(
        player_move_results.attacker_results.evaluated_move,
        Move::Psychic
    );
    EXPECT_EQ(player_move_results.defender_results.evaluated_move, Move::Curse);
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
         battle_state.player.get_moves(true)
    ) {
        battle_state.player.clear_power_points(move);
    }
    const MoveResults player_move_results =
        choose_move_against_defender(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state,
            battle_state.player.get_moves(false),
            Who::Player,
            std::nullopt,
            std::nullopt,
            0
        );

    EXPECT_NE(
        player_move_results.attacker_results.evaluated_move,
        Move::MoveCount
    );
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
         battle_state.player.get_moves(true)
    ) {
        battle_state.player.clear_power_points(move);
    }
    const MoveResults player_move_results =
        choose_move_against_defender(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state,
            battle_state.player.get_moves(false),
            Who::Player,
            std::nullopt,
            std::nullopt,
            0
        );

    EXPECT_NE(
        player_move_results.attacker_results.evaluated_move,
        Move::Struggle
    );
}

TEST(
    MoveHeuristic,
    PlayerSuicune_7_3DoesNotChooseShadowBallAgainstRegigigas_7_3
) {
    BattleState battle_state{
        PokemonState{&Regigigas_7_3},
        PokemonState{&Suicune_7_3}
    };
    const MoveResults player_move_results =
        choose_move_against_defender(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state,
            battle_state.player.get_moves(false),
            Who::Player,
            std::nullopt,
            std::nullopt,
            0
        );

    EXPECT_NE(
        player_move_results.defender_results.evaluated_move,
        Move::ShadowBall
    );
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
    const MoveResults player_move_results =
        choose_move_against_defender(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state,
            battle_state.player.get_moves(false),
            Who::Player,
            std::nullopt,
            std::nullopt,
            0
        );

    EXPECT_EQ(
        player_move_results.attacker_results.evaluated_move,
        Move::Blizzard
    );
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
    opponent_chooses_moves_against_player(
        Cresselia_7_4,
        Regigigas_7_3,
        Move::Ancientpower,
        Move::FocusBlast,
        Move::Ancientpower,
        Move::Thunderbolt
    );
}

TEST(
    MoveHeuristic,
    OpponentCresselia_7_3ChoosesShadowBallAndEnergyBallAgainstCresselia_7_4
) {
    opponent_chooses_moves_against_player(
        Cresselia_7_4,
        Cresselia_7_3,
        Move::ShadowBall,
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
    OpponentHeatran_7_3ChoosesFlamethrowerThenFlamethrowerAgainstRegigigas_7_3
) {
    opponent_chooses_moves_against_player(
        Regigigas_7_3,
        Heatran_7_3,
        Move::Flamethrower,
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

TEST(
    MoveHeuristic,
    HeuristicReturnsChargingMoveWithDamageWhenAttackerIsCharging
) {
    BattleState battle_state{
        PokemonState{&Entei_7_3},
        PokemonState{&Suicune_7_3}
    };
    // To prevent immediate KO
    battle_state.opponent.clear_power_points(Move::HydroPump);

    battle_state.player.set_move_status_with_stage(
        MoveStatusWithStage::Charging,
        Move::SolarBeam,
        1
    );

    const MoveResults player_move_results =
        choose_move_against_defender(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state,
            battle_state.player.get_moves(false),
            Who::Player,
            std::nullopt,
            std::nullopt,
            0
        );

    EXPECT_EQ(Move::SolarBeam,
              player_move_results.attacker_results.evaluated_move);
    EXPECT_GT(player_move_results.attacker_results.line[0].damage, 0);
    EXPECT_TRUE(player_move_results.attacker_results.hits_to_ko.has_value());
    EXPECT_GT(player_move_results.attacker_results.total_damage, 0);
}

TEST(
    MoveHeuristic,
    HeuristicReturnsRechargingMoveWithNoDamageWhenAttackerIsRecharging
) {
    BattleState battle_state{
        PokemonState{&Entei_7_3},
        PokemonState{&Suicune_7_3}
    };

    battle_state.player.set_status_with_stage(
        StatusWithStage::Recharging,
        1
    );
    battle_state.player.set_last_used_move(Move::HyperBeam);

    const MoveResults player_move_results =
        choose_move_against_defender(
            DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING,
            battle_state,
            battle_state.player.get_moves(false),
            Who::Player,
            std::nullopt,
            std::nullopt,
            0
        );

    EXPECT_EQ(
        Move::HyperBeam,
        player_move_results.attacker_results.evaluated_move
    );
    EXPECT_EQ(0, player_move_results.attacker_results.line[0].damage);
}

TEST(
    MoveHeuristic,
    OpponentEntei_7_3ChoosesSunnyDayThenFireBlastAgainstCresselia_7_3
) {
    opponent_chooses_moves_against_player(
        Cresselia_7_3,
        Entei_7_3,
        Move::SunnyDay,
        Move::FireBlast,
        Move::FireBlast
    );
}

TEST(
    MoveHeuristic,
    PlayerEntei_7_3ChoosesSunnyDayThenSolarbeamAgainstCresselia_7_4
) {
    player_chooses_moves_against_opponent(
        Entei_7_3,
        Cresselia_7_4,
        Move::SunnyDay,
        Move::SolarBeam
    );
}

TEST(
    MoveHeuristic,
    OpponentEntei_7_3ChoosesHyperBeamTwoTimesAgainstHeatran_7_3
) {
    // 2nd hyper beam is the recharge turn
    opponent_chooses_moves_against_player(
        Heatran_7_3,
        Entei_7_3,
        Move::HyperBeam,
        Move::HyperBeam
    );
}

TEST(
    MoveHeuristic,
    PlayerRaikou_7_3ChoosesRainDanceThenThunderAgainstRegigigas_7_3
) {
    player_chooses_moves_against_opponent(
        Raikou_7_3,
        Regigigas_7_3,
        Move::RainDance,
        Move::Thunder
    );
}

TEST(
    MoveHeuristic,
    PlayerRaikou_7_3SetsUpRainDanceForThunderAgainstEntei_7_3
) {
    player_chooses_moves_against_opponent(
        Raikou_7_3,
        Entei_7_3,
        Move::RainDance,
        Move::Thunder
    );
    opponent_chooses_moves_against_player(
        Raikou_7_3,
        Entei_7_3,
        // Burns
        Move::FireBlast,
        // For the KO!
        Move::HyperBeam
    );
}

TEST(
    MoveHeuristic,
    OpponentCresselia_7_4ChoosesPsychicTwiceThenSignalBeamAgainstCresselia_7_4
) {
    opponent_chooses_moves_against_player(
        Cresselia_7_4,
        Cresselia_7_4,
        Move::Psychic,
        Move::Psychic,
        Move::SignalBeam,
        Move::SignalBeam
    );
}

TEST(
    MoveHeuristic,
    OpponentRegirock_7_3ChoosesCurseThenStoneEdgeAgainstCresselia_7_4
) {
    opponent_chooses_moves_against_player(
        Cresselia_7_4,
        Regirock_7_3,
        Move::Curse,
        Move::StoneEdge,
        Move::StoneEdge,
        Move::StoneEdge,
        Move::StoneEdge
    );
}

TEST(
    MoveHeuristic,
    OpponentCresselia_7_3ChoosesPsychicAgainstHeatran_7_4
) {
    opponent_chooses_moves_against_player(
        Heatran_7_3,
        Cresselia_7_3,
        Move::Psychic,
        Move::Psychic,
        Move::Psychic
    );
}

TEST(
    MoveHeuristic,
    OpponentEntei_7_3ChoosesSunnyDayThenSolarBeamAgainstRegirock_7_3
) {
    opponent_chooses_moves_against_player(
        Regirock_7_3,
        Entei_7_3,
        Move::SunnyDay,
        Move::SolarBeam,
        Move::SolarBeam
    );
}

TEST(
    MoveHeuristic,
    PlayerSuicune_7_3ChoosesHailThenBlizzardAgainstRegigigas_7_3
) {
    player_chooses_moves_against_opponent(
        Suicune_7_3,
        Regigigas_7_3,
        Move::Hail,
        Move::Blizzard
    );
}

TEST(
    MoveHeuristic,
    OpponentArticuno_7_3ChoosesOminousWindTwiceThenSignalBeamAgainstCresselia_7_4
) {
    opponent_chooses_moves_against_player(
        Cresselia_7_4,
        Articuno_7_3,
        Move::OminousWind,
        Move::OminousWind,
        Move::SignalBeam
    );
}

TEST(
    MoveHeuristic,
    OpponentRegigigas_7_2ChoosesSubstituteAgainstCresselia_7_4
) {
    opponent_chooses_moves_against_player(
        Cresselia_7_4,
        Regigigas_7_2,
        Move::Facade,
        Move::Facade,
        // 5 turns of leftovers and substitute
        // -100 HP for the subs
        // Stalling for slow start to wear off
        Move::Substitute,
        Move::Substitute,
        Move::Substitute,
        Move::Facade,
        Move::Facade,
        Move::Facade,
        Move::Facade,
        Move::Facade
    );
}

TEST(
    MoveHeuristic,
    OpponentHeatran_7_3ChoosesEarthPowerThenFlamethrowerAgainstRegigigas_7_2
) {
    opponent_chooses_moves_against_player(
        Regigigas_7_2,
        Heatran_7_3,
        Move::EarthPower,
        Move::Flamethrower,
        Move::DragonPulse
    );
}

TEST(
    MoveHeuristic,
    OpponentCresselia_7_2ChoosesToxicThenPsychicAgainstCresselia_7_4
) {
    opponent_chooses_moves_against_player(
        Cresselia_7_4,
        Cresselia_7_2,
        Move::Toxic,
        Move::Psychic,
        Move::Psychic,
        Move::Psychic,
        Move::Psychic
    );
}

TEST(
    MoveHeuristic,
    PlayerZapdos_7_2ChoosesLightScreenAgainstEntei_7_3
) {
    player_chooses_moves_against_opponent(
        Zapdos_7_2,
        Entei_7_3,
        Move::LightScreen,
        Move::Ancientpower,
        Move::Thunderbolt
    );
}

TEST(
    MoveHeuristic,
    OpponentHeatran_7_1ChoosesHeatWaveAgainstCresselia_7_4
) {
    opponent_chooses_moves_against_player(
        Cresselia_7_4,
        Heatran_7_1,
        Move::HeatWave,
        Move::Ancientpower,
        Move::FlashCannon
    );
}

TEST(
    MoveHeuristic,
    OpponentRaikou_7_2ChoosesCrunchAgainstHeatran_7_1
) {
    opponent_chooses_moves_against_player(
        Heatran_7_1,
        Raikou_7_2,
        Move::Crunch,
        Move::ThunderFang,
        Move::ThunderFang
    );
}

TEST(
    MoveHeuristic,
    OpponentLatios_7_1ChoosesCalmMindAgainstCresselia_7_4
) {
    opponent_chooses_moves_against_player(
        Cresselia_7_4,
        Latios_7_1,
        Move::CalmMind,
        Move::Psychic,
        Move::DragonPulse
    );
}