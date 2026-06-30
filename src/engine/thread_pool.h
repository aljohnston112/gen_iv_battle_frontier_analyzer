#ifndef WAVELET_THREADPOOL_H
#define WAVELET_THREADPOOL_H

#include <condition_variable>
#include <functional>
#include <queue>
#include <thread>

#include "battle_state.h"
#include "config.h"
#include "move.h"
#include "pokemon.h"

struct BattleEntry {
    size_t player_index;
    size_t opponent_index;
};

struct TurnResult {
    BattleState battle_state;
    Move player_move_used;
    uint32_t player_move_damage;
    Move opponent_move_used;
    uint32_t opponent_move_damage;
};

struct PokemonBattleEntries {
    Pokemon pokemon;
    Ability ability;
    std::vector<BattleEntry> battle_entries;

    PokemonBattleEntries(
        const Pokemon pokemon_in,
        const Ability ability_in,
        const std::vector<BattleEntry>&& battle_entries_in
    ) : pokemon(pokemon_in),
        ability(ability_in),
        battle_entries(std::move(battle_entries_in)) {}
};

class BattleResultEntry {
public:
    size_t player_index;
    size_t opponent_index;
    bool won;
    std::vector<TurnResult> results{};

    BattleResultEntry(
        const size_t player_index_in,
        const size_t opponent_index_in,
        const bool won_in,
        const std::vector<TurnResult>&& results_in
    )
        : player_index(player_index_in),
          opponent_index(opponent_index_in),
          won(won_in),
          results(std::move(results_in)) {}

    BattleResultEntry() = default;
};

struct PokemonBattleResultEntries {
    Pokemon pokemon;
    Ability ability;
    std::vector<BattleResultEntry> battle_result_entries;

    PokemonBattleResultEntries(
        const Pokemon pokemon_in,
        const Ability ability_in,
        const std::vector<BattleResultEntry>&& battle_result_entries_in
    ) : pokemon(pokemon_in),
        ability(ability_in),
        battle_result_entries(std::move(battle_result_entries_in)) {}

    PokemonBattleResultEntries() = default;
};

inline unsigned int getNumberOfThreads() {
    static unsigned int numThreads = std::thread::hardware_concurrency();
    if (MULTI_THREADED) {
        return numThreads;
    }
    return 1;
}

using Function = std::move_only_function<void()>;

class ThreadPool {
    std::atomic<size_t> number_of_submitted_tasks{0};

    std::vector<std::jthread> threads{};

    std::mutex mutex;
    std::queue<Function> tasks;

    std::condition_variable task_condition;
    bool stop = false;

public:
    explicit ThreadPool(size_t numThreads);

    void addTasks(std::vector<Function>& functions);

    void addTask(Function&& function);

    void waitForTasks();

    ~ThreadPool();

    void submit(
        const std::span<const CustomPokemon>& all_player_pokemon,
        const std::span<const CustomPokemon>& all_opponent_pokemon,
        const std::function<
            std::vector<PokemonBattleResultEntries>(
                const std::span<const CustomPokemon>&,
                const std::span<const CustomPokemon>&,
                const std::span<const PokemonBattleEntries>&
            )
        >& function,
        const std::span<const PokemonBattleEntries> battle_entries,
        std::span<PokemonBattleResultEntries> results
    ) {
        addTask(
            [
                function = function,
                battle_entry = battle_entries,
                results = results,
                &all_player_pokemon = all_player_pokemon,
                &all_opponent_pokemon = all_opponent_pokemon
            ] mutable {
                std::ranges::move(
                    function(
                        all_player_pokemon,
                        all_opponent_pokemon,
                        battle_entry
                    ),
                    results.begin()
                );
            }
        );
    }
};

#endif //WAVELET_THREADPOOL_H
