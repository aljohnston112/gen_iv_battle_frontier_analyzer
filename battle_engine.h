#pragma once
#include <ranges>
#include <vector>

#include "battle_state.h"
#include "pokemon.h"
#include "thread_pool.h"

inline
std::vector<PokemonBattleEntries> get_battle_entries(
    const std::vector<CustomPokemon>& all_player_pokemon,
    const std::vector<CustomPokemon>& all_opponent_pokemon
) {
    std::vector<PokemonBattleEntries> pokemon_to_battles{};
    pokemon_to_battles.reserve(
        all_player_pokemon.size() + all_opponent_pokemon.size()
    );

    for (auto [
             player_index,
             player_pokemon
         ] : std::views::enumerate(all_player_pokemon)
    ) {
        // auto player_name = player_pokemon.name;
        // if constexpr (TEAM_ONLY && !team.contains(player_name)) {
        //     continue;
        // }
        // if (TEAM_ONLY) {
        //     change_stats(&player_pokemon);
        // }

        std::vector<BattleEntry> battles_for_player{};
        battles_for_player.reserve(all_opponent_pokemon.size());
        for (const auto [
                 opponent_index,
                 opponent_pokemon
             ] : std::views::enumerate(all_opponent_pokemon)
        ) {
            battles_for_player.emplace_back(
                BattleEntry{
                    .player_index = static_cast<size_t>(player_index),
                    .opponent_index = static_cast<size_t>(opponent_index),
                }
            );
        }
        pokemon_to_battles.push_back(
            PokemonBattleEntries{
                player_pokemon.name,
                player_pokemon.ability,
                std::move(battles_for_player)
            }
        );
    }
    return pokemon_to_battles;
}

inline BattleResultEntry single_battle(
    const std::vector<CustomPokemon>& all_player_pokemon,
    const std::vector<CustomPokemon>& all_opponent_pokemon,
    const size_t player_index,
    const size_t opponent_index
) {
    bool won = false;
    std::vector<MoveResults> player_moves{};
    std::vector<MoveResults> opponent_moves{};

    const auto& player_pokemon = all_player_pokemon[player_index];
    const auto& opponent_pokemon = all_opponent_pokemon[opponent_index];
    BattleState battle_state{
        PokemonState{player_pokemon},
        PokemonState{opponent_pokemon}
    };



    return BattleResultEntry{
        player_index,
        opponent_index,
        won,
        std::move(player_moves),
        std::move(opponent_moves)
    };
}

inline std::vector<PokemonBattleResultEntries> battle_all(
    const std::vector<CustomPokemon>& all_player_pokemon,
    const std::vector<CustomPokemon>& all_opponent_pokemon,
    const std::span<const PokemonBattleEntries> all_battle_entries
) {
    std::vector<PokemonBattleResultEntries> all_results{};
    all_results.reserve(all_battle_entries.size());
    for (const auto& [
             pokemon,
             ability,
             battle_entries
         ] : all_battle_entries
    ) {
        std::vector<BattleResultEntry> results{};
        results.reserve(battle_entries.size());
        for (const auto [player_index, opponent_index] : battle_entries) {
            results.emplace_back(
                single_battle(
                    all_player_pokemon,
                    all_opponent_pokemon,
                    player_index,
                    opponent_index
                )
            );
        }
        all_results.emplace_back(PokemonBattleResultEntries{
            pokemon,
            ability,
            std::move(results)
        });
    }
    return all_results;
}

inline
std::vector<PokemonBattleResultEntries> do_battles(
    const std::vector<CustomPokemon>& all_player_pokemon,
    const std::vector<CustomPokemon>& all_opponent_pokemon,
    const std::vector<PokemonBattleEntries>& pokemon_to_battle_entries
) {
    std::vector<PokemonBattleResultEntries> all_battle_result_entries{};
    all_battle_result_entries.resize(pokemon_to_battle_entries.size());

    const unsigned int number_of_threads = getNumberOfThreads();
    ThreadPool thread_pool{number_of_threads};
    const size_t chunk_size =
        pokemon_to_battle_entries.size() / number_of_threads;

    for (uint8_t i = 0; i < number_of_threads; i++) {
        const size_t start_i = i * chunk_size;
        const size_t end_i = (i == number_of_threads - 1)
                                 ? pokemon_to_battle_entries.size()
                                 : (i + 1) * chunk_size;
        const size_t length = end_i - start_i;
        const std::span chunk_span(
            pokemon_to_battle_entries.data() + start_i,
            length
        );

        const std::span result_span(
            all_battle_result_entries.data() + start_i,
            length
        );
        thread_pool.submit(
            all_player_pokemon,
            all_opponent_pokemon,
            battle_all,
            chunk_span,
            result_span
        );
    }

    thread_pool.waitForTasks();
    return all_battle_result_entries;
}

inline std::vector<PokemonBattleResultEntries> do_round_robin(
    const std::vector<CustomPokemon>& all_pokemon
) {
    const auto pokemon_to_battles =
        get_battle_entries(
            all_pokemon,
            all_pokemon
        );

    const auto pokemon_to_battle_result_entries = do_battles(
        all_pokemon,
        all_pokemon,
        pokemon_to_battles
    );
    return pokemon_to_battle_result_entries;
}
