#ifndef GEN_IV_BATTLE_FRONTIER_ANALYZER_POLICIES_H
#define GEN_IV_BATTLE_FRONTIER_ANALYZER_POLICIES_H

#include <iostream>
#include <random>

#include "battle_state.h"

// Accuracy / Evasion
// =============================================================================
template <typename T>
struct AccuracyEvasionFactorPolicy {
    bool does_move_miss_due_to_accuracy_and_evasion(
        const BattleState& battle_state,
        const MoveInfo* move,
        const Who who
    ) const {
        return static_cast<const T*>(this)->
            does_move_miss_due_to_accuracy_and_evasion_impl(
                battle_state,
                move,
                who
            );
    }
};

template <typename T>
concept IsAccuracyEvasionFactorPolicy =
    std::derived_from<T, AccuracyEvasionFactorPolicy<T>>;

struct NeverMissAccuracyEvasionFactorPolicy :
    AccuracyEvasionFactorPolicy<NeverMissAccuracyEvasionFactorPolicy> {
    static bool does_move_miss_due_to_accuracy_and_evasion_impl(
        const BattleState&,
        const MoveInfo*,
        const Who) {
        return false;
    }
};

struct AlwaysMissAccuracyEvasionFactorPolicy :
    AccuracyEvasionFactorPolicy<AlwaysMissAccuracyEvasionFactorPolicy> {
    static bool does_move_miss_due_to_accuracy_and_evasion_impl(
        const BattleState&,
        const MoveInfo*,
        const Who) {
        return true;
    }
};

struct RealAccuracyEvasionFactorPolicy :
    AccuracyEvasionFactorPolicy<RealAccuracyEvasionFactorPolicy> {
    explicit RealAccuracyEvasionFactorPolicy(std::mt19937 generator) :
        m_generator(std::move(generator)) {}

    static uint16_t get_accuracy_evasion_value(
        const BattleState& battle_state,
        const MoveInfo* move,
        const Who who_attacker_is
    ) {
        const bool is_player_attacker = who_attacker_is == Who::Player;
        const PokemonState& attacker_state =
            is_player_attacker
                ? battle_state.player
                : battle_state.opponent;
        const PokemonState& defender_state =
            is_player_attacker
                ? battle_state.opponent
                : battle_state.player;
        uint16_t accuracy_evasion_value =
            calculate_accuracy_and_evasion_based_on_stage(
                move->accuracy,
                attacker_state.get_status_stage(
                    StatusWithStage::Accuracy
                ),
                defender_state.get_status_stage(
                    StatusWithStage::Evasion
                )
            );
        const auto defender_item = defender_state.get_current_item_for_effect();
        if (defender_item == Item::BrightPowder ||
            defender_item == Item::LaxIncense
        ) {
            accuracy_evasion_value =
                static_cast<uint16_t>(accuracy_evasion_value * 9 / 10);
        }
        if (move->move == Move::Thunder &&
            battle_state.has_weather(Weather::Sun)
        ) {
            accuracy_evasion_value /= 2;
        }

        return accuracy_evasion_value;
    }

    bool does_move_miss_due_to_accuracy_and_evasion_impl(
        const BattleState& battle_state,
        const MoveInfo* move_info,
        const Who who_attacker_is
    ) const {
        const uint16_t accuracy_evasion_value =
            get_accuracy_evasion_value(
                battle_state,
                move_info,
                who_attacker_is
            );
        return roll_accuracy_threshold(who_attacker_is) >=
            accuracy_evasion_value;
    }

private:
    mutable std::mt19937 m_generator;

    uint8_t roll_accuracy_threshold(const Who) const {
        static std::uniform_int_distribution<uint8_t> dist(1, 100);
        return dist(m_generator);
    }
};

// =============================================================================
template <typename T>
struct CanUseLessAccurateMovesPolicy {
    bool can_use_less_accurate_moves(
        const Who who
    ) const {
        return static_cast<const T*>(this)->
            can_use_less_accurate_moves_impl(who);
    }
};

template <typename T>
concept IsCanUseLessAccurateMovesPolicy =
    std::derived_from<T, CanUseLessAccurateMovesPolicy<T>>;

struct OnlyOpponentCanUseLessAccurateMovesPolicy :
    CanUseLessAccurateMovesPolicy<OnlyOpponentCanUseLessAccurateMovesPolicy> {
    static bool can_use_less_accurate_moves_impl(
        const Who who
    ) {
        return who == Who::Opponent;
    }
};


// Burn 
// =============================================================================
template <typename T>
struct BurnRNGPolicy {
    bool roll_for_burn(const uint8_t percent, const Who who) const {
        return static_cast<const T*>(this)->roll_for_burn_impl(percent, who);
    }
};

template <typename T>
concept IsBurnRNGPolicy =
    std::derived_from<T, BurnRNGPolicy<T>>;

struct NeverBurnRNGPolicy :
    BurnRNGPolicy<NeverBurnRNGPolicy> {
    static bool roll_for_burn_impl(const int8_t, const Who) {
        return false;
    }
};

struct AlwaysBurnRNGPolicy :
    BurnRNGPolicy<AlwaysBurnRNGPolicy> {
    static bool roll_for_burn_impl(const int8_t, const Who) {
        return true;
    }
};

struct OpponentOptimizedBurnRNGPolicy :
    BurnRNGPolicy<OpponentOptimizedBurnRNGPolicy> {
    static bool roll_for_burn_impl(const int8_t, const Who who) {
        return who == Who::Player;
    }
};

// Crit
// =============================================================================
template <typename T>
struct CritRNGPolicy {
    bool roll_for_crit(const double percent, const Who who) const {
        return static_cast<const T*>(this)->roll_for_crit_impl(percent, who);
    }
};

template <typename T>
concept IsCritRNGPolicy = std::derived_from<T, CritRNGPolicy<T>>;

struct NeverCritRNGPolicy :
    CritRNGPolicy<NeverCritRNGPolicy> {
    static bool roll_for_crit_impl(const double, const Who) {
        return false;
    }
};

struct AlwaysCritRNGPolicy :
    CritRNGPolicy<AlwaysCritRNGPolicy> {
    static bool roll_for_crit_impl(const double, const Who) {
        return true;
    }
};

struct OpponentOptimizedCritRNGPolicy :
    CritRNGPolicy<OpponentOptimizedCritRNGPolicy> {
    static bool roll_for_crit_impl(const double, const Who who) {
        return who == Who::Player;
    }
};

// Confusion
// =============================================================================
template <typename T>
struct ConfusionStatusRNGPolicy {
    bool roll_for_confusion(const int8_t percent, const Who who) const {
        return static_cast<const T*>(this)->
            roll_for_confusion_impl(percent, who);
    }

    bool roll_for_self_hit(const int8_t percent, const Who who) const {
        return static_cast<const T*>(this)->
            roll_for_self_hit_impl(percent, who);
    }
};

template <typename T>
concept IsConfusionStatusRNGPolicy =
    std::derived_from<T, ConfusionStatusRNGPolicy<T>>;

struct NeverConfuseRNGPolicy :
    ConfusionStatusRNGPolicy<NeverConfuseRNGPolicy> {
    static bool roll_for_confusion_impl(const int8_t, const Who) {
        return false;
    }

    static bool roll_for_self_hit_impl(const int8_t, const Who) {
        return false;
    }
};

struct AlwaysConfuseRNGPolicy :
    ConfusionStatusRNGPolicy<AlwaysConfuseRNGPolicy> {
    static bool roll_for_confusion_impl(const int8_t, const Who) {
        return true;
    }

    static bool roll_for_self_hit_impl(const int8_t, const Who) {
        return true;
    }
};

struct OpponentOptimizedConfuseRNGPolicy :
    ConfusionStatusRNGPolicy<OpponentOptimizedConfuseRNGPolicy> {
    static bool roll_for_confusion_impl(const int8_t, const Who who) {
        return who == Who::Player;
    }

    static bool roll_for_self_hit_impl(const int8_t, const Who who) {
        return who == Who::Player;
    }
};

template <typename T>
struct ConfusionStatusDamagePolicy {
    uint8_t roll_turns_confused(const Who who) const {
        return static_cast<const T*>(this)->roll_turns_confused_impl(who);
    }

    uint8_t roll_random_confusion(const Who who) const {
        return static_cast<const T*>(this)->roll_random_confusion_impl(who);
    }
};

template <typename T>
concept IsConfusionStatusDamagePolicy =
    std::derived_from<T, ConfusionStatusDamagePolicy<T>>;

struct OpponentOptimizedConfusionStatusDamagePolicy :
    ConfusionStatusDamagePolicy<OpponentOptimizedConfusionStatusDamagePolicy> {
    static uint8_t roll_turns_confused_impl(const Who who) {
        return who == Who::Player ? 4 : 1;
    }

    static uint8_t roll_random_confusion_impl(const Who who) {
        return who == Who::Player ? 100 : 85;
    }
};

// Damage
// =============================================================================
template <typename T>
struct DamageRandomFactorPolicy {
    uint8_t roll_random(const Who who) const {
        return static_cast<const T*>(this)->roll_random_impl(who);
    }
};

template <typename T>
concept IsDamageRandomFactorPolicy =
    std::derived_from<T, DamageRandomFactorPolicy<T>>;

struct OpponentOptimizedRandomFactorPolicy :
    DamageRandomFactorPolicy<OpponentOptimizedRandomFactorPolicy> {
    static uint8_t roll_random_impl(const Who who) {
        return who == Who::Player ? 85 : 100;
    }
};

// Flinch
// =============================================================================
template <typename T>
struct FlinchRNGPolicy {
    bool roll_for_flinch(const uint8_t percent, const Who who) const {
        return static_cast<const T*>(this)->roll_for_flinch_impl(percent, who);
    }
};

template <typename T>
concept IsFlinchRNGPolicy =
    std::derived_from<T, FlinchRNGPolicy<T>>;

struct NeverFlinchRNGPolicy :
    FlinchRNGPolicy<NeverFlinchRNGPolicy> {
    static bool roll_for_flinch_impl(const int8_t, const Who) {
        return false;
    }
};

struct AlwaysFlinchRNGPolicy :
    FlinchRNGPolicy<AlwaysFlinchRNGPolicy> {
    static bool roll_for_flinch_impl(const int8_t, const Who) {
        return true;
    }
};

struct OpponentOptimizedFlinchRNGPolicy :
    FlinchRNGPolicy<OpponentOptimizedFlinchRNGPolicy> {
    static bool roll_for_flinch_impl(const int8_t, const Who who) {
        return who == Who::Player;
    }
};

// Focus Band
// =============================================================================
template <typename T>
struct FocusBandPolicy {
    bool roll_for_survival(const uint8_t percent, const Who who) const {
        return static_cast<const T*>(this)->
            roll_for_survival_impl(percent, who);
    }
};

template <typename T>
concept IsFocusBandPolicy =
    std::derived_from<T, FocusBandPolicy<T>>;

struct NeverSurviveFocusBandPolicy :
    FocusBandPolicy<NeverSurviveFocusBandPolicy> {
    static bool roll_for_survival_impl(const int8_t, const Who) {
        return false;
    }
};

struct AlwaysSurviveFocusBandPolicy :
    FocusBandPolicy<AlwaysSurviveFocusBandPolicy> {
    static bool roll_for_survival_impl(const int8_t, const Who) {
        return true;
    }
};

struct OpponentOptimizedFocusBandPolicy :
    FocusBandPolicy<OpponentOptimizedFocusBandPolicy> {
    static bool roll_for_survival_impl(const int8_t, const Who who) {
        return who == Who::Opponent;
    }
};

// Freeze
// =============================================================================
template <typename T>
struct FreezeRNGPolicy {
    bool roll_for_freeze(const uint8_t percent, const Who who) const {
        return static_cast<const T*>(this)->roll_for_freeze_impl(percent, who);
    }

    bool roll_for_thaw(const uint8_t percent, const Who who) const {
        return static_cast<const T*>(this)->roll_for_thaw_impl(percent, who);
    }
};

template <typename T>
concept IsFreezeRNGPolicy =
    std::derived_from<T, FreezeRNGPolicy<T>>;

struct NeverFreezeRNGPolicy :
    FreezeRNGPolicy<NeverFreezeRNGPolicy> {
    static bool roll_for_freeze_impl(const int8_t, const Who) {
        return false;
    }

    static bool roll_for_thaw_impl(const int8_t, const Who) {
        return true;
    }
};

struct AlwaysFreezeRNGPolicy :
    FreezeRNGPolicy<AlwaysFreezeRNGPolicy> {
    static bool roll_for_freeze_impl(const int8_t, const Who) {
        return true;
    }

    static bool roll_for_thaw_impl(const int8_t, const Who) {
        return false;
    }
};

struct OpponentOptimizedFreezeRNGPolicy :
    FreezeRNGPolicy<OpponentOptimizedFreezeRNGPolicy> {
    static bool roll_for_freeze_impl(const int8_t, const Who who) {
        return who == Who::Player;
    }

    static bool roll_for_thaw_impl(const int8_t, const Who who) {
        return who == Who::Opponent;
    }
};


// Opponent Knowledge
// =============================================================================
template <typename T>
struct OpponentKnowledgePolicy {
    bool opponent_knows_player_move() const {
        return static_cast<const T*>(this)->
            opponent_knows_player_move_impl();
    }
};

template <typename T>
concept IsOpponentKnowledgePolicy =
    std::derived_from<T, OpponentKnowledgePolicy<T>>;

struct OpponentOptimizedKnowledgePolicy :
    OpponentKnowledgePolicy<OpponentOptimizedKnowledgePolicy> {
    static bool opponent_knows_player_move_impl() {
        return true;
    }
};

// Paralysis
// =============================================================================
template <typename T>
struct ParalysisRNGPolicy {
    bool roll_for_paralysis(const uint8_t percent, const Who who) const {
        return static_cast<const T*>(this)->
            roll_for_paralysis_impl(percent, who);
    }

    bool can_move_while_paralyzed(const uint8_t percent, const Who who) const {
        return static_cast<const T*>(this)->can_move_while_paralyzed_impl(
            percent,
            who
        );
    }
};

template <typename T>
concept IsParalysisRNGPolicy =
    std::derived_from<T, ParalysisRNGPolicy<T>>;

struct NeverParalyzeRNGPolicy :
    ParalysisRNGPolicy<NeverParalyzeRNGPolicy> {
    static bool roll_for_paralysis_impl(const int8_t, const Who) {
        return false;
    }

    static bool can_move_while_paralyzed_impl(const int8_t, const Who) {
        return true;
    }
};

struct AlwaysParalyzeRNGPolicy :
    ParalysisRNGPolicy<AlwaysParalyzeRNGPolicy> {
    static bool roll_for_paralysis_impl(const int8_t, const Who) {
        return true;
    }

    static bool can_move_while_paralyzed_impl(const int8_t, const Who) {
        return false;
    }
};

struct OpponentOptimizedParalysisRNGPolicy :
    ParalysisRNGPolicy<OpponentOptimizedParalysisRNGPolicy> {
    static bool roll_for_paralysis_impl(const int8_t, const Who who) {
        return who == Who::Player;
    }

    static bool can_move_while_paralyzed_impl(const int8_t, const Who who) {
        return who == Who::Opponent;
    }
};

// Sleep
// =============================================================================
template <typename T>
struct SleepStatusRNGPolicy {
    bool roll_for_sleep(const int8_t percent) const {
        return static_cast<const T*>(this)->
            roll_for_sleep_impl(percent);
    }

    bool roll_for_awakening(const int8_t percent) const {
        return static_cast<const T*>(this)->roll_for_awakening_impl(percent);
    }
};

template <typename T>
concept IsSleepStatusRNGPolicy =
    std::derived_from<T, SleepStatusRNGPolicy<T>>;

struct NeverSleepRNGPolicy :
    SleepStatusRNGPolicy<NeverSleepRNGPolicy> {
    static bool roll_for_sleep_impl(const int8_t) {
        return false;
    }

    static bool roll_for_awakening_impl(const int8_t) {
        return false;
    }
};

struct AlwaysSleepRNGPolicy :
    SleepStatusRNGPolicy<AlwaysSleepRNGPolicy> {
    static bool roll_for_sleep_impl(const int8_t) {
        return true;
    }

    static bool roll_for_awakening_impl(const int8_t) {
        return true;
    }
};

template <typename T>
struct SleepStatusPolicy {
    uint8_t roll_turns_asleep(const Who who) const {
        return static_cast<const T*>(this)->roll_turns_asleep_impl(who);
    }
};

template <typename T>
concept IsSleepStatusPolicy =
    std::derived_from<T, SleepStatusPolicy<T>>;

struct OpponentOptimizedSleepStatusPolicy :
    SleepStatusPolicy<OpponentOptimizedSleepStatusPolicy> {
    static uint8_t roll_turns_asleep_impl(const Who who) {
        return who == Who::Player ? 4 : 1;
    }
};


// Speed
// =============================================================================
template <typename T>
struct SpeedAdvantagePolicy {
    bool is_player_faster(const BattleState& battle_state) const {
        return static_cast<const T*>(this)->is_player_faster_impl(
            battle_state);
    }

protected:
    static bool is_player_speed_higher(const BattleState& battle_state) {
        return battle_state.player.get_current_stat(Stat::Speed) >
            battle_state.opponent.get_current_stat(Stat::Speed);
    }
};

template <typename T>
concept IsSpeedAdvantagePolicy = std::derived_from<
    T, SpeedAdvantagePolicy<T>>;

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
    bool roll_stat_drop(const uint8_t percent, const Who who) const {
        return static_cast<const T*>(this)->roll_stat_drop_impl(
            percent, who);
    }

    bool roll_stat_increase(const uint8_t percent, const Who who) const {
        return static_cast<const T*>(this)->roll_stat_increase_impl(
            percent, who);
    }
};

template <typename T>
concept IsStatChangePolicy = std::derived_from<T, StatChangePolicy<T>>;

struct OpponentOptimizedStatChangePolicy :
    StatChangePolicy<OpponentOptimizedStatChangePolicy> {
    static bool roll_stat_drop_impl(const uint8_t, const Who who) {
        return who == Who::Player;
    }

    static bool roll_stat_increase_impl(const uint8_t, const Who who) {
        return who == Who::Opponent;
    }
};

// Logging
//==============================================================================
#define FORMAT_LAMBDA(...) \
[&] { return std::format(__VA_ARGS__); }

template <typename... Loggers>
struct LoggingPolicy : Loggers... {
    template <typename Func>
    static void log(Func&& func) {
        (Loggers::log(std::forward<Func>(func)), ...);
    }
};

template <>
struct LoggingPolicy<> {
    template <typename Func>
    static void log(Func&&) {}
};

template <typename T>
concept IsLoggingPolicy = std::derived_from<T, LoggingPolicy<T>>;


struct HeuristicLogger {
    template <typename Func>
    static void log(Func&& func) {
        std::cout << func() << std::endl;
    }
};

using NoLogging = LoggingPolicy<>;
using DebugLogging = LoggingPolicy<HeuristicLogger>;

// Templates
// =============================================================================

template <template <typename> typename TemplateBase, typename T>
concept derives_from_self =
    std::derived_from<T, TemplateBase<T>>;

template <template <typename...> typename TemplateBase, typename T>
concept derives_from_template = requires(T t) {
    []<typename... U>(const TemplateBase<U...>&) {}(t);
};

template <template <typename> typename BaseTemplate, typename... Ts>
constexpr std::size_t count_base =
(static_cast<std::size_t>(derives_from_template<BaseTemplate, Ts>) + ...
);

template <template <typename> typename BaseTemplate, typename... Ts>
constexpr bool contains_at_most_one =
    count_base<BaseTemplate, Ts...> <= 1;

template <typename T>
concept IsAllowedPolicy =
    (derives_from_template<LoggingPolicy, T> &&
        requires(const T& t) {
            {
                T::log(
                    [] {
                        return std::string{};
                    }
                )
            } -> std::same_as<void>;
        }
    ) ||
    (derives_from_self<AccuracyEvasionFactorPolicy, T> &&
        requires(const T& t) {
            {
                t.does_move_miss_due_to_accuracy_and_evasion_impl(
                    BattleState{
                        PokemonState{nullptr},
                        PokemonState{nullptr}
                    },
                    nullptr,
                    Who::Player
                )
            } -> std::same_as<bool>;
        })
    ||
    (derives_from_self<CanUseLessAccurateMovesPolicy, T> &&
        requires(const T& t) {
            {
                t.can_use_less_accurate_moves_impl(
                    Who::Player
                )
            } -> std::same_as<bool>;
        })
    ||
    (derives_from_self<BurnRNGPolicy, T> &&
        requires(const T& t) {
            {
                t.roll_for_burn_impl(static_cast<uint8_t>(0), Who::Player)
            } -> std::same_as<bool>;
        }) ||
    (derives_from_self<CritRNGPolicy, T> &&
        requires(const T& t) {
            {
                t.roll_for_crit_impl(static_cast<double>(0.0), Who::Player)
            } -> std::same_as<bool>;
        }) ||
    (derives_from_self<ConfusionStatusDamagePolicy, T> &&
        requires(const T& t) {
            {
                t.roll_turns_confused_impl(Who::Player)
            } -> std::same_as<uint8_t>;
            {
                t.roll_random_confusion_impl(Who::Player)
            } -> std::same_as<uint8_t>;
        }) ||
    (derives_from_self<ConfusionStatusRNGPolicy, T> &&
        requires(const T& t) {
            {
                t.roll_for_confusion_impl(static_cast<double>(0.0), Who::Player)
            } -> std::same_as<bool>;
            {
                t.roll_for_self_hit_impl(static_cast<double>(0.0), Who::Player)
            } -> std::same_as<bool>;
        }) ||
    (derives_from_self<DamageRandomFactorPolicy, T> &&
        requires(const T& t) {
            { t.roll_random_impl(Who::Player) } -> std::same_as<uint8_t>;
        }) ||
    (derives_from_self<FlinchRNGPolicy, T> &&
        requires(const T& t) {
            {
                t.roll_for_flinch_impl(static_cast<uint8_t>(0), Who::Player)
            } -> std::same_as<bool>;
        }) ||
    (derives_from_self<FocusBandPolicy, T> &&
        requires(const T& t) {
            {
                t.roll_for_survival_impl(static_cast<uint8_t>(0), Who::Player)
            } -> std::same_as<bool>;
        }) ||
    (derives_from_self<FreezeRNGPolicy, T> &&
        requires(const T& t) {
            {
                t.roll_for_freeze_impl(static_cast<uint8_t>(0), Who::Player)
            } -> std::same_as<bool>;
            {
                t.roll_for_thaw_impl(static_cast<uint8_t>(0), Who::Player)
            } -> std::same_as<bool>;
        }) ||
    (derives_from_self<OpponentKnowledgePolicy, T> &&
        requires(const T& t) {
            { t.opponent_knows_player_move_impl() } -> std::same_as<bool>;
        }) ||
    (derives_from_self<ParalysisRNGPolicy, T> &&
        requires(const T& t) {
            {
                t.roll_for_paralysis_impl(static_cast<uint8_t>(0), Who::Player)
            } -> std::same_as<bool>;
            {
                t.can_move_while_paralyzed_impl(
                    static_cast<uint8_t>(0),
                    Who::Player
                )
            } -> std::same_as<bool>;
        }) ||
    (derives_from_self<SpeedAdvantagePolicy, T> &&
        requires(const T& t, const BattleState& state) {
            { t.is_player_faster_impl(state) } -> std::same_as<bool>;
        })
    ||
    (derives_from_self<SleepStatusPolicy, T> &&
        requires(const T& t) {
            {
                t.roll_turns_asleep_impl(Who::Player)
            } -> std::same_as<uint8_t>;
        }) ||
    (derives_from_self<SleepStatusRNGPolicy, T> &&
        requires(const T& t) {
            {
                t.roll_for_sleep_impl(static_cast<double>(0.0))
            } -> std::same_as<bool>;
            {
                t.roll_for_awakening_impl(static_cast<double>(0.0))
            } -> std::same_as<bool>;
        }) ||
    (derives_from_self<StatChangePolicy, T> && requires(const T& t) {
        {
            t.roll_stat_drop_impl(static_cast<uint8_t>(0), Who::Player)
        } -> std::same_as<bool>;
    });

template <typename... Policies>
    requires
    (IsAllowedPolicy<Policies> && ...) &&
    contains_at_most_one<AccuracyEvasionFactorPolicy, Policies...> &&
    contains_at_most_one<CanUseLessAccurateMovesPolicy, Policies...> &&
    contains_at_most_one<BurnRNGPolicy, Policies...> &&
    contains_at_most_one<CritRNGPolicy, Policies...> &&
    contains_at_most_one<ConfusionStatusDamagePolicy, Policies...> &&
    contains_at_most_one<ConfusionStatusRNGPolicy, Policies...> &&
    contains_at_most_one<DamageRandomFactorPolicy, Policies...> &&
    contains_at_most_one<FlinchRNGPolicy, Policies...> &&
    contains_at_most_one<FocusBandPolicy, Policies...> &&
    contains_at_most_one<FreezeRNGPolicy, Policies...> &&
    contains_at_most_one<LoggingPolicy, Policies...> &&
    contains_at_most_one<OpponentKnowledgePolicy, Policies...> &&
    contains_at_most_one<ParalysisRNGPolicy, Policies...> &&
    contains_at_most_one<SleepStatusPolicy, Policies...> &&
    contains_at_most_one<SleepStatusRNGPolicy, Policies...> &&
    contains_at_most_one<SpeedAdvantagePolicy, Policies...> &&
    contains_at_most_one<StatChangePolicy, Policies...>
struct PolicyContainer : Policies... {
    PolicyContainer() = default;

    template <typename AccuracyPolicy>
        requires IsAccuracyEvasionFactorPolicy<AccuracyPolicy>
    explicit PolicyContainer(AccuracyPolicy policy) :
        AccuracyPolicy(std::move(policy)) {}
};

// Accuracy / Evasion
static_assert(IsAllowedPolicy<NeverMissAccuracyEvasionFactorPolicy>);
static_assert(IsAllowedPolicy<AlwaysMissAccuracyEvasionFactorPolicy>);
static_assert(IsAllowedPolicy<RealAccuracyEvasionFactorPolicy>);

// Can use less accurate moves
static_assert(IsAllowedPolicy<OnlyOpponentCanUseLessAccurateMovesPolicy>);

// Burn
static_assert(IsAllowedPolicy<NeverBurnRNGPolicy>);
static_assert(IsAllowedPolicy<AlwaysBurnRNGPolicy>);
static_assert(IsAllowedPolicy<OpponentOptimizedBurnRNGPolicy>);

// Critical hit
static_assert(IsAllowedPolicy<NeverCritRNGPolicy>);
static_assert(IsAllowedPolicy<AlwaysCritRNGPolicy>);
static_assert(IsAllowedPolicy<OpponentOptimizedCritRNGPolicy>);

// Confusion RNG
static_assert(IsAllowedPolicy<NeverConfuseRNGPolicy>);
static_assert(IsAllowedPolicy<AlwaysConfuseRNGPolicy>);
static_assert(IsAllowedPolicy<OpponentOptimizedConfuseRNGPolicy>);

// Confusion duration / damage
static_assert(IsAllowedPolicy<OpponentOptimizedConfusionStatusDamagePolicy>);

// Damage random factor
static_assert(IsAllowedPolicy<OpponentOptimizedRandomFactorPolicy>);

// Flinch
static_assert(IsAllowedPolicy<NeverFlinchRNGPolicy>);
static_assert(IsAllowedPolicy<AlwaysFlinchRNGPolicy>);
static_assert(IsAllowedPolicy<OpponentOptimizedFlinchRNGPolicy>);

// Focus Band
static_assert(IsAllowedPolicy<AlwaysSurviveFocusBandPolicy>);
static_assert(IsAllowedPolicy<NeverSurviveFocusBandPolicy>);
static_assert(IsAllowedPolicy<OpponentOptimizedFocusBandPolicy>);

// Freeze / thaw
static_assert(IsAllowedPolicy<NeverFreezeRNGPolicy>);
static_assert(IsAllowedPolicy<AlwaysFreezeRNGPolicy>);
static_assert(IsAllowedPolicy<OpponentOptimizedFreezeRNGPolicy>);

// Opponent knowledge
static_assert(IsAllowedPolicy<OpponentOptimizedKnowledgePolicy>);

// Paralysis
static_assert(IsAllowedPolicy<NeverParalyzeRNGPolicy>);
static_assert(IsAllowedPolicy<AlwaysParalyzeRNGPolicy>);
static_assert(IsAllowedPolicy<OpponentOptimizedParalysisRNGPolicy>);

// Sleep RNG
static_assert(IsAllowedPolicy<NeverSleepRNGPolicy>);
static_assert(IsAllowedPolicy<AlwaysSleepRNGPolicy>);

// Sleep duration
static_assert(IsAllowedPolicy<OpponentOptimizedSleepStatusPolicy>);

// Speed advantage
static_assert(IsAllowedPolicy<OpponentOptimizedSpeedAdvantagePolicy>);

// Stat changes
static_assert(IsAllowedPolicy<OpponentOptimizedStatChangePolicy>);

// Logging
static_assert(IsAllowedPolicy<NoLogging>);
static_assert(IsAllowedPolicy<DebugLogging>);

#endif //GEN_IV_BATTLE_FRONTIER_ANALYZER_POLICIES_H
