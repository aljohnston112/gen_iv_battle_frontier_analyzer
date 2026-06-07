#ifndef WAVELET_THREADPOOL_H
#define WAVELET_THREADPOOL_H

#include <condition_variable>
#include <functional>
#include <queue>
#include <thread>

#include "config.h"
#include "move.h"
#include "pokemon.h"

struct BattleEntry {
    size_t player_index;
    size_t opponent_index;
};


struct PokemonBattleEntries {
    Pokemon pokemon;
    Ability ability;
    std::vector<BattleEntry> battle_entries;

    PokemonBattleEntries(
        const Pokemon pokemon,
        const Ability ability,
        const std::vector<BattleEntry>&& battle_entries
    ) : pokemon(pokemon),
        ability(ability),
        battle_entries(std::move(battle_entries)) {}
};

struct MoveResults {
    Move move;
    int damage;
};

class BattleResultEntry {
public:
    size_t player_index;
    size_t opponent_index;
    bool won;
    std::vector<MoveResults> player_moves;
    std::vector<MoveResults> opponent_moves;

    BattleResultEntry(
        const size_t player_index,
        const size_t opponent_index,
        const bool won,
        const std::vector<MoveResults>&& player_moves,
        const std::vector<MoveResults>&& opponent_moves
    )
        : player_index(player_index),
          opponent_index(opponent_index),
          won(won),
          player_moves(std::move(player_moves)),
          opponent_moves(std::move(opponent_moves)) {}

    BattleResultEntry() = default;
};

struct PokemonBattleResultEntries {
    Pokemon pokemon;
    Ability ability;
    std::vector<BattleResultEntry> battle_result_entries;

    PokemonBattleResultEntries(
        const Pokemon pokemon,
        const Ability ability,
        const std::vector<BattleResultEntry>&& battle_result_entries
    ) : pokemon(pokemon),
        ability(ability),
        battle_result_entries(std::move(battle_result_entries)) {}

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
        const std::vector<CustomPokemon>& all_player_pokemon,
        const std::vector<CustomPokemon>& all_opponent_pokemon,
        const std::function<
            std::vector<PokemonBattleResultEntries>(
                const std::vector<CustomPokemon>&,
                const std::vector<CustomPokemon>&,
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
