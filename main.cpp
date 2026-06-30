#include <iostream>

#include "round_robin.h"
#include "factory_data_source.h"
#include "serebii_pokemon_data_source.h"

/**
    TODO
    Start writing these tests:
    1. Damage calc for special attack is correct
      a. 85 random
      b. 100 random
    2. Ice Beam freezes
    3. Freeze prevents sttacking
    4. Signal Beam confuses
    5. Confusion prevents attacking
    6. Confusion damage is correct
    7. Confusion ends on the right turn
    8. Psychic drops special defense
    9. Special defense drop increases damage to the right amount
    10. Moonlight heals the right amount (including weather effects)
    11. Leftovers heals the right amount
    12. PP loss triggers Struggle
    13. Struggle does the right amount of damage
    14. Struggle does the right amount of recoil
    15. STAB damage
    16. Not effective damage
    17. Not very effective damage
    18. Super effective damage
    19. Crit damage
 */
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
