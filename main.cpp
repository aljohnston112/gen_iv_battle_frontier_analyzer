#include "round_robin.h"
#include "battle_factory/factory_data_source.h"
#include "serebii/serebii_pokemon_data_source.h"

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
        construct_all_custom_batle_factory_pokemon(Player);
    const auto battle_factory_opponent_pokemon =
        construct_all_custom_batle_factory_pokemon(Opponent);

    const auto pokemon_to_battle_result_entries =
        do_round_robin(
            std::span(
                battle_factory_player_pokemon.begin(),
                1
            ),
            std::span(
                battle_factory_opponent_pokemon.begin(),
                1
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
    const std::chrono::duration<double> elapsed = end - start;
    std::cout << "Took " << elapsed.count() << " seconds.\n";
    return 0;
}
