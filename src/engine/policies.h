#ifndef GEN_IV_BATTLE_FRONTIER_ANALYZER_POLICIES_H
#define GEN_IV_BATTLE_FRONTIER_ANALYZER_POLICIES_H

#include "battle_state.h"

template <typename T>
struct CritRNGPolicy {
    bool roll(const double percent) const {
        return static_cast<const T*>(this)->roll(percent);
    }
};

template <typename T>
concept IsCritRNGPolicy = std::derived_from<T, CritRNGPolicy<T>>;

struct NeverCritRNGPolicy :
    CritRNGPolicy<NeverCritRNGPolicy> {
    static bool roll(const double) {
        return false;
    }
};

struct AlwaysCritRNGPolicy :
    CritRNGPolicy<AlwaysCritRNGPolicy> {
    static bool roll(const double) {
        return true;
    }
};

template <typename T>
struct ConfusionStatusRNGPolicy {
    bool roll(const double percent) const {
        return static_cast<const T*>(this)->roll(percent);
    }
};

template <typename T>
concept IsConfusionStatusRNGPolicy =
    std::derived_from<T, ConfusionStatusRNGPolicy<T>>;

struct NeverConfuseRNGPolicy :
    ConfusionStatusRNGPolicy<NeverConfuseRNGPolicy> {
    static bool roll(const int8_t) {
        return false;
    }
};

struct AlwaysConfuseRNGPolicy :
    ConfusionStatusRNGPolicy<AlwaysConfuseRNGPolicy> {
    static bool roll(const int8_t) {
        return true;
    }
};

template <typename T>
struct FreezeRNGPolicy {
    bool roll_for_freeze(const double percent) const {
        return static_cast<const T*>(this)->roll_for_freeze(percent);
    }
    bool roll_for_thaw(const double percent) const {
        return static_cast<const T*>(this)->roll_for_freeze(percent);
    }
};

template <typename T>
concept IsFreezeRNGPolicy =
    std::derived_from<T, FreezeRNGPolicy<T>>;

struct NeverFreezeRNGPolicy :
    FreezeRNGPolicy<NeverFreezeRNGPolicy> {
    static bool roll_for_freeze(const int8_t) {
        return false;
    }
    static bool roll_for_thaw(const int8_t) {
        return true;
    }
};

struct AlwaysFreezeRNGPolicy :
    FreezeRNGPolicy<AlwaysFreezeRNGPolicy> {
    static bool roll_for_freeze(const int8_t) {
        return true;
    }
    static bool roll_for_thaw(const int8_t) {
        return false;
    }
};

template <typename T>
struct SpeedAdvantagePolicy {
    bool is_player_faster(const BattleState& battle_state) const {
        return static_cast<const T*>(this)->is_player_faster_impl(battle_state);
    }

protected:
    static bool is_player_speed_higher(const BattleState& battle_state) {
        return battle_state.player.get_current_stat(Stat::Speed) >
            battle_state.opponent.get_current_stat(Stat::Speed);
    }
};

template <typename T>
concept IsSpeedAdvantagePolicy = std::derived_from<T, SpeedAdvantagePolicy<T>>;

class OpponentOptimizedSpeedAdvantagePolicy :
    public SpeedAdvantagePolicy<OpponentOptimizedSpeedAdvantagePolicy> {
    static bool is_player_faster_impl(const BattleState& battle_state) {
        return is_player_speed_higher(battle_state);
    }
};


template <typename T>
struct DamageRandomFactorPolicy {
    uint8_t roll_random(const Who who) const {
        return static_cast<const T*>(this)->roll_random(who);
    }
};

template <typename T>
concept IsDamageRandomFactorPolicy =
    std::derived_from<T, DamageRandomFactorPolicy<T>>;

class OpponentOptimizedDamageRandomFactorPolicy :
    public DamageRandomFactorPolicy<OpponentOptimizedDamageRandomFactorPolicy> {
    static uint8_t roll_random(const Who who) {
        return who == Who::Player ? 85 : 100;
    }
};


template <typename T>
struct ConfusionStatusPolicy {
    uint8_t roll_turns_confused(const Who who) const {
        return static_cast<const T*>(this)->roll_turns_confused(who);
    }

    uint8_t roll_random_confusion(const Who who) const {
        return static_cast<const T*>(this)->roll_random_confusion(who);
    }
};

template <typename T>
concept IsConfusionStatusPolicy =
    std::derived_from<T, ConfusionStatusPolicy<T>>;

class OpponentOptimizedConfusionStatusPolicy :
    public ConfusionStatusPolicy<OpponentOptimizedConfusionStatusPolicy> {
    static uint8_t roll_turns_confused(const Who who) {
        return who == Who::Player ? 4 : 1;
    }

    static uint8_t roll_random_confusion(const Who who) {
        return who == Who::Player ? 100 : 85;
    }
};


template <typename T>
struct StatChangePolicy {
    bool roll_stat_drop(const uint8_t percent, const Who who) {
        return static_cast<const T*>(this)->roll_stat_drop(percent, who);
    }
};

template <typename T>
concept IsStatChangePolicy = std::derived_from<T, StatChangePolicy<T>>;

class OpponentOptimizedStatChangePolicy :
    public StatChangePolicy<OpponentOptimizedStatChangePolicy> {
    static bool roll_stat_drop(const uint8_t, const Who who) {
        return who == Who::Player;
    }
};

template <typename T>
struct OpponentKnowledgePolicy {
    bool opponent_knows_player_move() {
        return static_cast<const T*>(this)->opponent_knows_player_move();
    }
};

template <typename T>
concept IsOpponentKnowledgePolicy =
    std::derived_from<T, OpponentKnowledgePolicy<T>>;

class OpponentOptimizedKnowledgePolicy :
    public OpponentKnowledgePolicy<OpponentOptimizedKnowledgePolicy> {
public:
    static bool opponent_knows_player_move() {
        return true;
    }
};

template <
    IsCritRNGPolicy CR,
    IsConfusionStatusRNGPolicy CSR,
    IsFreezeRNGPolicy F,
    IsOpponentKnowledgePolicy E,
    IsSpeedAdvantagePolicy S,
    IsDamageRandomFactorPolicy D,
    IsConfusionStatusPolicy C,
    IsStatChangePolicy SC
>
struct PolicyContainer {
    CR crit_rng_policy;
    CSR confusion_status_rng_policy;
    F freeze_rng_policy;
    E effect_policy;
    S speed_advantage_policy;
    D damage_random_factor_policy;
    C confusion_status_policy;
    SC stat_change_policy;
};


#endif //GEN_IV_BATTLE_FRONTIER_ANALYZER_POLICIES_H
