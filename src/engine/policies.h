#ifndef GEN_IV_BATTLE_FRONTIER_ANALYZER_POLICIES_H
#define GEN_IV_BATTLE_FRONTIER_ANALYZER_POLICIES_H

#include "battle_state.h"

template <typename T>
class RNGPolicy {
public:
    bool roll(const uint8_t percent) const {
        return static_cast<const T*>(this)->roll(percent);
    }

    bool roll(const double percent) const {
        return static_cast<const T*>(this)->roll(percent);
    }
};

template <typename T>
concept IsRNGPolicy = std::derived_from<T, RNGPolicy<T>>;

template <typename T>
class EffectPolicy {
public:
    bool is_player_faster(const BattleState& battle_state) const {
        return static_cast<const T*>(this)->is_player_faster(battle_state);
    }

    uint8_t roll_random(const Who who) const {
        return static_cast<const T*>(this)->roll_random(who);
    }

    bool roll_stat_drop(const uint8_t percent, const Who who) {
        return static_cast<const T*>(this)->roll_stat_drop(percent, who);
    }

    bool opponent_knows_player_move() {
        return static_cast<const T*>(this)->opponent_knows_player_move();
    }
};

template <typename T>
concept IsEffectPolicy = std::derived_from<T, EffectPolicy<T>>;

class OpponentOptimizedEffectPolicy :
    public EffectPolicy<OpponentOptimizedEffectPolicy> {
public:
    static bool is_player_faster(const BattleState& battle_state) {
        return battle_state.player.get_current_stat(Stat::Speed) >
            battle_state.opponent.get_current_stat(Stat::Speed);
    }

    static uint8_t roll_random(const Who who) {
        return who == Who::Player ? 85 : 100;
    }

    static bool roll_stat_drop(const uint8_t, const Who who) {
        return who == Who::Player;
    }

    static bool opponent_knows_player_move() {
        return true;
    }
};

class TrueRNGPolicy : public RNGPolicy<TrueRNGPolicy> {
public:
    static bool roll(const uint8_t) {
        return true;
    }

    static bool roll(const double) {
        return true;
    }
};

class FalseRNGPolicy : public RNGPolicy<FalseRNGPolicy> {
public:
    static bool roll(const uint8_t) {
        return false;
    }

    static bool roll(const double) {
        return false;
    }
};

template <IsEffectPolicy E, IsRNGPolicy R>
struct PolicyContainer {
    E effect_policy;
    R rng_policy;
};


#endif //GEN_IV_BATTLE_FRONTIER_ANALYZER_POLICIES_H
