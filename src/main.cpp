#include <iostream>

#include "round_robin.h"
#include "factory_data_source.h"
#include "serebii_pokemon_data_source.h"

// TODO Run the battle enough times to perf it and see if it can be made faster.

int main() {

    std::cout << "Starting Program" << std::endl;

    const auto start =
        std::chrono::high_resolution_clock::now();

    std::cout << "Start Time Recorded" << std::endl;

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

    std::cout << "Loading Pokemon From Disk" << std::endl;

    const auto battle_factory_player_pokemon =
        construct_all_custom_batle_factory_pokemon();
    const auto battle_factory_opponent_pokemon =
        construct_all_custom_batle_factory_pokemon();

    const auto rr_start =
        std::chrono::high_resolution_clock::now();

    std::cout << "RR Start Time Recorded; Starting Battles" << std::endl;

    constexpr size_t n = 9;
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

    std::cout << "Battles Over" << std::endl;

    const auto end =
        std::chrono::high_resolution_clock::now();

    const std::chrono::duration<double> rr_elapsed = end - rr_start;
    std::cout << "RR took " << rr_elapsed.count() << " seconds.\n";

    const std::chrono::duration<double> elapsed = end - start;
    std::cout << "Took " << elapsed.count() << " seconds.\n";
    return 0;
}
