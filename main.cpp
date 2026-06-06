#include "battle_engine.h"
#include "battle_factory/factory_data_source.h"
#include "serebii/serebii_pokemon_data_source.h"

std::vector<
    std::pair<
        std::pair<Pokemon, Ability>,
        std::vector<BattleResultEntry>
    >
> do_round_robin(
    const std::vector<CustomPokemon>& player_pokemon,
    const std::vector<CustomPokemon>& opponent_pokemon
) {
    std::vector<
        std::pair<
            std::pair<Pokemon, Ability>,
            std::vector<BattleResultEntry>
        >
    > results{};

    return results;
}

int main() {
    const auto start =
        std::chrono::high_resolution_clock::now();

    const auto battle_factory_pokemon_p =
        get_all_custom_batle_factory_pokemon();
    const auto battle_factory_pokemon_o =
        get_all_custom_batle_factory_pokemon();
    std::vector<
        std::pair<
            std::pair<Pokemon, Ability>,
            std::vector<BattleResultEntry>
        >
    > pokemon_to_battle_result_entries = do_round_robin(
        battle_factory_pokemon_p,
        battle_factory_pokemon_o
    );

    const auto end =
        std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double> elapsed = end - start;
    std::cout << "Took " << elapsed.count() << " seconds.\n";
    return 0;
}
