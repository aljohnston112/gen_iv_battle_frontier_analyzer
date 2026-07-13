#ifndef GEN_IV_BATTLE_FRONTIER_ANALYZER_POLICIES_H
#define GEN_IV_BATTLE_FRONTIER_ANALYZER_POLICIES_H

#include "battle_state.h"

// Crit
// =============================================================================
template <typename T>
struct CritRNGPolicy {
    bool roll_for_crit(const double percent) const {
        return static_cast<const T*>(this)->roll_for_crit(percent);
    }
};

template <typename T>
concept IsCritRNGPolicy = std::derived_from<T, CritRNGPolicy<T>>;

struct NeverCritRNGPolicy :
    CritRNGPolicy<NeverCritRNGPolicy> {
    static bool roll_for_crit(const double) {
        return false;
    }
};

struct AlwaysCritRNGPolicy :
    CritRNGPolicy<AlwaysCritRNGPolicy> {
    static bool roll_for_crit(const double) {
        return true;
    }
};

// Confusion
// =============================================================================
template <typename T>
struct ConfusionStatusRNGPolicy {
    bool roll_for_confusion(const double percent) const {
        return static_cast<const T*>(this)->roll_for_confusion(percent);
    }

    bool roll_for_self_hit(const double percent) const {
        return static_cast<const T*>(this)->roll_for_self_hit(percent);
    }
};

template <typename T>
concept IsConfusionStatusRNGPolicy =
    std::derived_from<T, ConfusionStatusRNGPolicy<T>>;

struct NeverConfuseRNGPolicy :
    ConfusionStatusRNGPolicy<NeverConfuseRNGPolicy> {
    static bool roll_for_confusion(const int8_t) {
        return false;
    }

    static bool roll_for_self_hit(const double) {
        return false;
    }
};

struct AlwaysConfuseRNGPolicy :
    ConfusionStatusRNGPolicy<AlwaysConfuseRNGPolicy> {
    static bool roll_for_confusion(const int8_t) {
        return true;
    }

    static bool roll_for_self_hit(const int8_t) {
        return true;
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

struct OpponentOptimizedConfusionStatusPolicy :
    ConfusionStatusPolicy<OpponentOptimizedConfusionStatusPolicy> {
    static uint8_t roll_turns_confused(const Who who) {
        return who == Who::Player ? 4 : 1;
    }

    static uint8_t roll_random_confusion(const Who who) {
        return who == Who::Player ? 100 : 85;
    }
};

// Damage
// =============================================================================
template <typename T>
struct DamageRandomFactorPolicy {
    uint8_t roll_random(const Who who) const {
        return static_cast<const T*>(this)->roll_random(who);
    }
};

template <typename T>
concept IsDamageRandomFactorPolicy =
    std::derived_from<T, DamageRandomFactorPolicy<T>>;

struct OpponentOptimizedRandomFactorPolicy :
    DamageRandomFactorPolicy<OpponentOptimizedRandomFactorPolicy> {
    static uint8_t roll_random(const Who who) {
        return who == Who::Player ? 85 : 100;
    }
};

// Freeze
// =============================================================================
template <typename T>
struct FreezeRNGPolicy {
    bool roll_for_freeze(const uint8_t percent) const {
        return static_cast<const T*>(this)->roll_for_freeze(percent);
    }

    bool roll_for_thaw(const uint8_t percent) const {
        return static_cast<const T*>(this)->roll_for_thaw(percent);
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

// Opponent Knowledge
// =============================================================================
template <typename T>
struct OpponentKnowledgePolicy {
    bool opponent_knows_player_move() {
        return static_cast<const T*>(this)->opponent_knows_player_move();
    }
};

template <typename T>
concept IsOpponentKnowledgePolicy =
    std::derived_from<T, OpponentKnowledgePolicy<T>>;

struct OpponentOptimizedKnowledgePolicy :
    OpponentKnowledgePolicy<OpponentOptimizedKnowledgePolicy> {
    static bool opponent_knows_player_move() {
        return true;
    }
};

// Paralysis
// =============================================================================
template <typename T>
struct ParalysisRNGPolicy {
    bool roll_for_paralysis(const uint8_t percent) const {
        return static_cast<const T*>(this)->roll_for_paralysis(percent);
    }

    bool can_move_while_paralyzed(const uint8_t percent) const {
        return static_cast<const T*>(this)->can_move_while_paralyzed(percent);
    }
};

template <typename T>
concept IsParalysisRNGPolicy =
    std::derived_from<T, ParalysisRNGPolicy<T>>;

struct NeverParalyzeRNGPolicy :
    ParalysisRNGPolicy<NeverParalyzeRNGPolicy> {
    static bool roll_for_paralysis(const int8_t) {
        return false;
    }

    static bool can_move_while_paralyzed(const int8_t) {
        return true;
    }
};

struct AlwaysParalyzeRNGPolicy :
    ParalysisRNGPolicy<AlwaysParalyzeRNGPolicy> {
    static bool roll_for_paralysis(const int8_t) {
        return true;
    }

    static bool can_move_while_paralyzed(const int8_t) {
        return false;
    }
};

// Speed
// =============================================================================
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

struct OpponentOptimizedSpeedAdvantagePolicy :
    SpeedAdvantagePolicy<OpponentOptimizedSpeedAdvantagePolicy> {
    static bool is_player_faster_impl(const BattleState& battle_state) {
        return is_player_speed_higher(battle_state);
    }
};

// Stat change
// =============================================================================
template <typename T>
struct StatChangePolicy {
    bool roll_stat_drop(const uint8_t percent, const Who who) {
        return static_cast<const T*>(this)->roll_stat_drop(percent, who);
    }
};

template <typename T>
concept IsStatChangePolicy = std::derived_from<T, StatChangePolicy<T>>;

struct OpponentOptimizedStatChangePolicy :
    StatChangePolicy<OpponentOptimizedStatChangePolicy> {
    static bool roll_stat_drop(const uint8_t, const Who who) {
        return who == Who::Player;
    }
};


template <template <typename> typename TemplateBase, typename T>
concept derives_from_template = requires(T t) {
    []<typename U>(const TemplateBase<U>&) {}(t);
};

template <template <typename> typename BaseTemplate, typename... Ts>
constexpr std::size_t count_base =
    (static_cast<std::size_t>(derives_from_template<BaseTemplate, Ts>) + ...);

template <template <typename> typename BaseTemplate, typename... Ts>
constexpr bool contains_at_most_one =
    count_base<BaseTemplate, Ts...> <= 1;

template <typename T>
concept IsAllowedPolicy =
    (derives_from_template<CritRNGPolicy, T> &&
        requires(const T& t) {
            { t.roll_for_crit(static_cast<double>(0.0)) } -> std::same_as<bool>;
        }) ||
    (derives_from_template<ConfusionStatusPolicy, T> &&
        requires(const T& t) {
            { t.roll_turns_confused(Who::Player) } -> std::same_as<uint8_t>;
            { t.roll_random_confusion(Who::Player) } -> std::same_as<uint8_t>;
        }) ||
    (derives_from_template<ConfusionStatusRNGPolicy, T> &&
        requires(const T& t) {
            {
                t.roll_for_confusion(static_cast<double>(0.0))
            } -> std::same_as<bool>;
            {
                t.roll_for_self_hit(static_cast<double>(0.0))
            } -> std::same_as<bool>;
        }) ||
    (derives_from_template<DamageRandomFactorPolicy, T> &&
        requires(const T& t) {
            { t.roll_random(Who::Player) } -> std::same_as<uint8_t>;
        }) ||
    (derives_from_template<FreezeRNGPolicy, T> &&
        requires(const T& t) {
            {
                t.roll_for_freeze(static_cast<uint8_t>(0))
            } -> std::same_as<bool>;
            { t.roll_for_thaw(static_cast<uint8_t>(0)) } -> std::same_as<bool>;
        }) ||
    (derives_from_template<OpponentKnowledgePolicy, T> &&
        requires(const T& t) {
            { t.opponent_knows_player_move() } -> std::same_as<bool>;
        }) ||

    (derives_from_template<ParalysisRNGPolicy, T> &&
        requires(const T& t) {
            {
                t.roll_for_paralysis(static_cast<uint8_t>(0))
            } -> std::same_as<bool>;
            {
                t.can_move_while_paralyzed(static_cast<uint8_t>(0))
            } -> std::same_as<bool>;
        }) ||
    (derives_from_template<SpeedAdvantagePolicy, T> &&
        requires(const T& t, const BattleState& state) {
            { t.is_player_faster(state) } -> std::same_as<bool>;
        })
    ||
    (derives_from_template<StatChangePolicy, T> && requires(const T& t) {
        {
            t.roll_stat_drop(static_cast<uint8_t>(0), Who::Player)
        } -> std::same_as<bool>;
    });

template <typename... Policies>
    requires
    (IsAllowedPolicy<Policies> && ...) &&
    contains_at_most_one<CritRNGPolicy, Policies...> &&
    contains_at_most_one<ConfusionStatusPolicy, Policies...> &&
    contains_at_most_one<ConfusionStatusRNGPolicy, Policies...> &&
    contains_at_most_one<DamageRandomFactorPolicy, Policies...> &&
    contains_at_most_one<FreezeRNGPolicy, Policies...> &&
    contains_at_most_one<OpponentKnowledgePolicy, Policies...> &&
    contains_at_most_one<SpeedAdvantagePolicy, Policies...> &&
    contains_at_most_one<StatChangePolicy, Policies...>
struct PolicyContainer : Policies... {};


#endif //GEN_IV_BATTLE_FRONTIER_ANALYZER_POLICIES_H
