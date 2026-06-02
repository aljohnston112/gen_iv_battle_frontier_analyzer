#include "battle_factory/factory_data_source.h"
#include "serebii/serebii_pokemon_data_source.h"

int main() {
    const auto serebii_pokemon =
        get_all_serebii_pokemon();
    const auto battle_factory_pokemon =
        get_all_custom_batle_factory_pokemon();
    return 0;
}
