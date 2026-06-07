#include "battle_engine.h"
#include "battle_factory/factory_data_source.h"
#include "serebii/serebii_pokemon_data_source.h"

int main() {
    const auto start =
        std::chrono::high_resolution_clock::now();

    const auto battle_factory_pokemon =
        construct_all_custom_batle_factory_pokemon();
    const auto pokemon_to_battle_result_entries = do_round_robin(
        battle_factory_pokemon
    );

    const auto end =
        std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double> elapsed = end - start;
    std::cout << "Took " << elapsed.count() << " seconds.\n";
    return 0;
}
