#ifndef GEN_IV_BATTLE_FRONTIER_ANALYZER_MOCKS_H
#define GEN_IV_BATTLE_FRONTIER_ANALYZER_MOCKS_H
#include "pokemon.h"
#include "policies.h"

const CustomPokemon Cresselia{
    .name = Pokemon::Cresselia,
    .ability = Ability::Levitate,
    .level = 50,
    .item = Item::Leftovers,
    .types = {PokemonType::Psychic, PokemonType::NoType},
    .moves = {Move::Psychic, Move::IceBeam, Move::SignalBeam, Move::Moonlight},
    .stats = {213, 78, 158, 101, 168, 102},
    .pounds = 188.7
};

const CustomPokemon CresseliaNoItem{
    .name = Pokemon::Cresselia,
    .ability = Ability::Levitate,
    .level = 50,
    .item = Item::NoItem,
    .types = {PokemonType::Psychic, PokemonType::NoType},
    .moves = {Move::Psychic, Move::IceBeam, Move::SignalBeam, Move::Moonlight},
    .stats = {213, 78, 158, 101, 168, 102},
    .pounds = 188.7
};

class LowRandomEffectPolicy :
    public OpponentKnowledgePolicy<LowRandomEffectPolicy> {
public:
    static bool is_player_faster(const BattleState& battle_state) {
        return battle_state.player.get_current_stat(Stat::Speed) >
            battle_state.opponent.get_current_stat(Stat::Speed);
    }

    static uint8_t roll_random(const Who) {
        return 85;
    }

    static bool roll_stat_drop(const uint8_t, const Who) {
        return false;
    }
};

class HighRandomEffectPolicy :
    public OpponentKnowledgePolicy<HighRandomEffectPolicy> {
public:
    static bool is_player_faster(const BattleState& battle_state) {
        return battle_state.player.get_current_stat(Stat::Speed) >
            battle_state.opponent.get_current_stat(Stat::Speed);
    }

    static uint8_t roll_random(const Who) {
        return 100;
    }

    static bool roll_stat_drop(const uint8_t, const Who) {
        return false;
    }
};

template <typename T>
concept IsPolicyTestCase = requires {
    requires IsOpponentKnowledgePolicy<typename T::EffectPolicyType>;
    requires IsRNGPolicy<typename  T::RNGPolicyType>;
    { +T::ExpectedValue } -> std::same_as<int32_t>;
};

template <typename EffectPolicy, typename RNGPolicy, int32_t Expected>
struct PolicyTestCase {
    using EffectPolicyType = EffectPolicy;
    using RNGPolicyType = RNGPolicy;
    static constexpr int32_t ExpectedValue = Expected;
};


#endif //GEN_IV_BATTLE_FRONTIER_ANALYZER_MOCKS_H
