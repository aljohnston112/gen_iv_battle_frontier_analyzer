#include <iostream>

#include "round_robin.h"
#include "factory_data_source.h"
#include "serebii_pokemon_data_source.h"

// TODO Run the battle enough times to perf it and see if it can be made faster.

int main() {
    printf("OpenMP version: %d\n", _OPENMP);

    const auto start =
        std::chrono::high_resolution_clock::now();

    // const auto all_player_pokemon =
    // construct_all_pokemon_forms(Player);
    // const auto all_opponent_pokemon =
    //     construct_all_pokemon_forms(Opponent);
    //
    // const auto pokemon_to_battle_result_entries =
    // do_round_robin(
    //     std::span(
    //         all_player_pokemon.begin(),
    //         all_player_pokemon.size()
    //     ),
    //     std::span(
    //         all_opponent_pokemon.begin(),
    //         all_opponent_pokemon.size()
    //     )
    // );

    const auto battle_factory_player_pokemon =
        construct_all_custom_batle_factory_pokemon(Who::Player);
    const auto battle_factory_opponent_pokemon =
        construct_all_custom_batle_factory_pokemon(Who::Opponent);

    const auto rr_start =
    std::chrono::high_resolution_clock::now();

    constexpr size_t n = 2;
    const auto pokemon_to_battle_result_entries =
        do_round_robin(
            std::span(
                battle_factory_player_pokemon.begin(),
                n
            ),
            std::span(
                battle_factory_opponent_pokemon.begin(),
                n
            )
        );

    // const auto pokemon_to_battle_result_entries =
    // do_round_robin(
    //     std::span(
    //         battle_factory_player_pokemon.begin(),
    //         battle_factory_opponent_pokemon.size()
    //     ),
    //     std::span(
    //         battle_factory_opponent_pokemon.begin(),
    //         battle_factory_opponent_pokemon.size()
    //     )
    // );

    const auto end =
        std::chrono::high_resolution_clock::now();

    const std::chrono::duration<double> rr_elapsed = end - rr_start;
    std::cout << "RR took " << rr_elapsed.count() << " seconds.\n";

    const std::chrono::duration<double> elapsed = end - start;
    std::cout << "Took " << elapsed.count() << " seconds.\n";
    return 0;
}
