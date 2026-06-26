#ifndef GEN_IV_BATTLE_FRONTIER_ANALYZER_POLICIES_H
#define GEN_IV_BATTLE_FRONTIER_ANALYZER_POLICIES_H

#include "battle_state.h"

template <typename T>
class EffectPolicy {
public:
    bool is_player_faster(const BattleState& battle_state) const {
        return static_cast<const T*>(this)->is_player_faster(battle_state);
    }
};

template <typename T>
concept IsEffectPolicy = std::derived_from<T, EffectPolicy<T>>;

class OpponentOptimizedEffectPolicy : public EffectPolicy<
        OpponentOptimizedEffectPolicy> {
public:
    static bool is_player_faster(const BattleState& battle_state) {
        return battle_state.player.current_speed >
            battle_state.opponent.current_speed;
    }
};


template <typename T>
class RNGPolicy {
public:
    bool roll(const uint8_t percent) const {
        return static_cast<const T*>(this)->roll(percent);
    }
};

template <typename T>
concept IsRNGPolicy = std::derived_from<T, RNGPolicy<T>>;

class NoRNGPolicy : public RNGPolicy<NoRNGPolicy> {
public:
    static bool roll(const uint8_t) {
        return false;
    }
};

template <IsEffectPolicy E, IsRNGPolicy R>
struct PolicyContainer {
    E effect_policy;
    R rng_policy;
};


#endif //GEN_IV_BATTLE_FRONTIER_ANALYZER_POLICIES_H
