#ifndef GEN_IV_BATTLE_FRONTIER_ANALYZER_TEST_POLICIES_H
#define GEN_IV_BATTLE_FRONTIER_ANALYZER_TEST_POLICIES_H

#include "policies.h"

// Burn
// =============================================================================
template <typename T>
constexpr PolicyContainer<
    AlwaysHitAccuracyEvasionFactorPolicy,
    OpponentOptimizedConfusionStatusPolicy,
    NeverConfuseRNGPolicy,
    NeverCritRNGPolicy,
    OpponentOptimizedRandomFactorPolicy,
    NeverFlinchRNGPolicy,
    NeverFreezeRNGPolicy,
    OpponentOptimizedStatChangePolicy,
    NeverParalyzeRNGPolicy,
    T
> BURN_POLICY_CONTAINER{};

constexpr auto ALWAYS_BURN_POLICY_CONTAINER =
    BURN_POLICY_CONTAINER<AlwaysBurnRNGPolicy>;

constexpr auto NEVER_BURN_POLICY_CONTAINER =
    BURN_POLICY_CONTAINER<NeverBurnRNGPolicy>;

// Confusion
// =============================================================================
class HighRandomConfusionEffectPolicy :
    public ConfusionStatusPolicy<HighRandomConfusionEffectPolicy> {
public:
    static uint8_t roll_turns_confused_impl(const Who) {
        return 2;
    }

    static uint8_t roll_random_confusion_impl(const Who) {
        return 100;
    }
};

class LowRandomConfusionEffectPolicy :
    public ConfusionStatusPolicy<LowRandomConfusionEffectPolicy> {
public:
    static uint8_t roll_turns_confused_impl(const Who) {
        return 2;
    }

    static uint8_t roll_random_confusion_impl(const Who) {
        return 85;
    }
};

constexpr PolicyContainer<
    AlwaysHitAccuracyEvasionFactorPolicy,
    LowRandomConfusionEffectPolicy,
    NeverConfuseRNGPolicy,
    NeverCritRNGPolicy,
    OpponentOptimizedRandomFactorPolicy,
    NeverFlinchRNGPolicy,
    NeverFreezeRNGPolicy,
    OpponentOptimizedStatChangePolicy,
    NeverParalyzeRNGPolicy,
    NeverBurnRNGPolicy
> NEVER_CONFUSE_POLICY_CONTAINER{};

template <typename T>
constexpr PolicyContainer<
    AlwaysHitAccuracyEvasionFactorPolicy,
    T,
    AlwaysConfuseRNGPolicy,
    NeverCritRNGPolicy,
    OpponentOptimizedRandomFactorPolicy,
    NeverFlinchRNGPolicy,
    NeverFreezeRNGPolicy,
    OpponentOptimizedStatChangePolicy,
    NeverParalyzeRNGPolicy,
    NeverBurnRNGPolicy
> ALWAYS_CONFUSE_POLICY_CONTAINER{};

constexpr auto ALWAYS_CONFUSE_HIGH_RANDOM_CONFUSION_POLICY_CONTAINER =
    ALWAYS_CONFUSE_POLICY_CONTAINER<HighRandomConfusionEffectPolicy>;

constexpr auto ALWAYS_CONFUSE_LOW_RANDOM_CONFUSION_POLICY_CONTAINER =
    ALWAYS_CONFUSE_POLICY_CONTAINER<LowRandomConfusionEffectPolicy>;

// Flinch
// =============================================================================
template <typename T>
constexpr PolicyContainer<
    AlwaysHitAccuracyEvasionFactorPolicy,
    OpponentOptimizedConfusionStatusPolicy,
    NeverConfuseRNGPolicy,
    NeverCritRNGPolicy,
    OpponentOptimizedRandomFactorPolicy,
    T,
    NeverFreezeRNGPolicy,
    OpponentOptimizedStatChangePolicy,
    NeverParalyzeRNGPolicy,
    NeverBurnRNGPolicy
> FLINCH_POLICY_CONTAINER{};

constexpr auto NEVER_FLINCH_POLICY_CONTAINER =
    FLINCH_POLICY_CONTAINER<NeverFlinchRNGPolicy>;

constexpr auto ALWAYS_FLINCH_POLICY_CONTAINER =
    FLINCH_POLICY_CONTAINER<AlwaysFlinchRNGPolicy>;

// Freeze
// =============================================================================
template <typename T>
constexpr PolicyContainer<
    AlwaysHitAccuracyEvasionFactorPolicy,
    OpponentOptimizedConfusionStatusPolicy,
    NeverConfuseRNGPolicy,
    NeverCritRNGPolicy,
    OpponentOptimizedRandomFactorPolicy,
    NeverFlinchRNGPolicy,
    T,
    OpponentOptimizedStatChangePolicy,
    NeverParalyzeRNGPolicy,
    NeverBurnRNGPolicy
> FREEZE_POLICY_CONTAINER{};

constexpr auto NEVER_FREEZE_POLICY_CONTAINER =
    FREEZE_POLICY_CONTAINER<NeverFreezeRNGPolicy>;

constexpr auto ALWAYS_FREEZE_POLICY_CONTAINER =
    FREEZE_POLICY_CONTAINER<AlwaysFreezeRNGPolicy>;

// Paralysis
// =============================================================================
template <typename T>
constexpr PolicyContainer<
    AlwaysHitAccuracyEvasionFactorPolicy,
    OpponentOptimizedConfusionStatusPolicy,
    NeverConfuseRNGPolicy,
    NeverCritRNGPolicy,
    OpponentOptimizedRandomFactorPolicy,
    NeverFlinchRNGPolicy,
    NeverFreezeRNGPolicy,
    OpponentOptimizedStatChangePolicy,
    T,
    NeverBurnRNGPolicy
> PARALYSIS_POLICY_CONTAINER{};

constexpr auto ALWAYS_PARALYZE_POLICY_CONTAINER =
    PARALYSIS_POLICY_CONTAINER<AlwaysParalyzeRNGPolicy>;

constexpr auto NEVER_PARALYZE_POLICY_CONTAINER =
    PARALYSIS_POLICY_CONTAINER<NeverParalyzeRNGPolicy>;

// Sleep
// =============================================================================
class HighRandomSleepEffectPolicy :
    public SleepStatusPolicy<HighRandomSleepEffectPolicy> {
public:
    static uint8_t roll_turns_asleep_impl(const Who) {
        return 2;
    }

    static uint8_t roll_random_sleep_impl(const Who) {
        return 100;
    }
};

class LowRandomSleepEffectPolicy :
    public SleepStatusPolicy<LowRandomSleepEffectPolicy> {
public:
    static uint8_t roll_turns_asleep_impl(const Who) {
        return 2;
    }

    static uint8_t roll_random_sleep_impl(const Who) {
        return 85;
    }
};

constexpr PolicyContainer<
    AlwaysHitAccuracyEvasionFactorPolicy,
    NeverConfuseRNGPolicy,
    LowRandomConfusionEffectPolicy,
    LowRandomSleepEffectPolicy,
    NeverSleepRNGPolicy,
    NeverCritRNGPolicy,
    OpponentOptimizedRandomFactorPolicy,
    NeverFlinchRNGPolicy,
    NeverFreezeRNGPolicy,
    OpponentOptimizedStatChangePolicy,
    NeverParalyzeRNGPolicy,
    NeverBurnRNGPolicy
> NEVER_SLEEP_POLICY_CONTAINER{};

template <typename T>
constexpr PolicyContainer<
    AlwaysHitAccuracyEvasionFactorPolicy,
    NeverConfuseRNGPolicy,
    LowRandomConfusionEffectPolicy,
    T,
    AlwaysSleepRNGPolicy,
    NeverCritRNGPolicy,
    OpponentOptimizedRandomFactorPolicy,
    NeverFlinchRNGPolicy,
    NeverFreezeRNGPolicy,
    OpponentOptimizedStatChangePolicy,
    NeverParalyzeRNGPolicy,
    NeverBurnRNGPolicy
> ALWAYS_SLEEP_POLICY_CONTAINER{};

constexpr auto ALWAYS_SLEEP_HIGH_RANDOM_SLEEP_POLICY_CONTAINER =
    ALWAYS_SLEEP_POLICY_CONTAINER<HighRandomSleepEffectPolicy>;

constexpr auto ALWAYS_SLEEP_LOW_RANDOM_SLEEP_POLICY_CONTAINER =
    ALWAYS_SLEEP_POLICY_CONTAINER<LowRandomSleepEffectPolicy>;

// Stat Changes
// =============================================================================
template <bool ALWAYS_BOOST_STAT>
struct NeverDropStatPolicy :
    StatChangePolicy<NeverDropStatPolicy<ALWAYS_BOOST_STAT>> {
    static bool roll_stat_drop_impl(const uint8_t, const Who) {
        return false;
    }

    static bool roll_stat_increase_impl(const uint8_t, const Who) {
        return ALWAYS_BOOST_STAT;
    }
};

template <bool ALWAYS_DROP_STAT>
struct AlwaysBoostStatPolicy :
    StatChangePolicy<AlwaysBoostStatPolicy<ALWAYS_DROP_STAT>> {
    static bool roll_stat_drop_impl(const uint8_t, const Who) {
        return ALWAYS_DROP_STAT;
    }

    static bool roll_stat_increase_impl(const uint8_t, const Who) {
        return true;
    }
};

struct NeverChangeStatPolicy :
    StatChangePolicy<NeverChangeStatPolicy> {
    static bool roll_stat_drop_impl(const uint8_t, const Who) {
        return false;
    }

    static bool roll_stat_increase_impl(const uint8_t, const Who) {
        return false;
    }
};

template <typename T>
constexpr PolicyContainer<
    AlwaysHitAccuracyEvasionFactorPolicy,
    OpponentOptimizedConfusionStatusPolicy,
    NeverConfuseRNGPolicy,
    NeverCritRNGPolicy,
    OpponentOptimizedRandomFactorPolicy,
    NeverFlinchRNGPolicy,
    NeverFreezeRNGPolicy,
    T,
    NeverParalyzeRNGPolicy,
    NeverBurnRNGPolicy
> STAT_CHANGE_POLICY_CONTAINER{};

constexpr auto ALWAYS_BOOST_STAT_POLICY_CONTAINER =
    STAT_CHANGE_POLICY_CONTAINER<AlwaysBoostStatPolicy<false>>;

constexpr auto NEVER_DROP_STAT_POLICY_CONTAINER =
    STAT_CHANGE_POLICY_CONTAINER<NeverDropStatPolicy<false>>;

constexpr auto NEVER_CHANGE_STAT_POLICY_CONTAINER =
    STAT_CHANGE_POLICY_CONTAINER<NeverChangeStatPolicy>;

// Random Damage
// =============================================================================
struct LowDamageRandomFactorPolicy :
    DamageRandomFactorPolicy<LowDamageRandomFactorPolicy> {
    static uint8_t roll_random_impl(const Who) {
        return 85;
    }
};

struct HighDamageRandomFactorPolicy :
    DamageRandomFactorPolicy<HighDamageRandomFactorPolicy> {
    static uint8_t roll_random_impl(const Who) {
        return 100;
    }
};

template <typename T>
constexpr PolicyContainer<
    AlwaysHitAccuracyEvasionFactorPolicy,
    OpponentOptimizedConfusionStatusPolicy,
    NeverConfuseRNGPolicy,
    NeverCritRNGPolicy,
    T,
    NeverFlinchRNGPolicy,
    NeverFreezeRNGPolicy,
    OpponentOptimizedStatChangePolicy,
    OpponentOptimizedSpeedAdvantagePolicy,
    NeverParalyzeRNGPolicy,
    NeverBurnRNGPolicy
> RANDOM_DAMAGE_FACTOR_POLICY_CONTAINER{};

constexpr auto LOW_RANDOM_DAMAGE_FACTOR_POLICY_CONTAINER =
    RANDOM_DAMAGE_FACTOR_POLICY_CONTAINER<LowDamageRandomFactorPolicy>;

constexpr auto HIGH_RANDOM_DAMAGE_FACTOR_POLICY_CONTAINER =
    RANDOM_DAMAGE_FACTOR_POLICY_CONTAINER<HighDamageRandomFactorPolicy>;

constexpr auto OPPONENT_OPTIMIZED_POLICY_CONTAINER =
    RANDOM_DAMAGE_FACTOR_POLICY_CONTAINER<OpponentOptimizedRandomFactorPolicy>;

// Logging
template <typename T>
constexpr auto DEFAULT_POLICY_CONTAINER =
    PolicyContainer<
        AlwaysHitAccuracyEvasionFactorPolicy,
        OpponentOptimizedConfusionStatusPolicy,
        NeverConfuseRNGPolicy,
        NeverCritRNGPolicy,
        OpponentOptimizedRandomFactorPolicy,
        NeverFlinchRNGPolicy,
        NeverFreezeRNGPolicy,
        NeverParalyzeRNGPolicy,
        OpponentOptimizedKnowledgePolicy,
        OpponentOptimizedSpeedAdvantagePolicy,
        OpponentOptimizedStatChangePolicy,
        NeverBurnRNGPolicy,
        T
    >{};

constexpr auto DEFAULT_POLICY_CONTAINER_WITHOUT_LOGGING =
    DEFAULT_POLICY_CONTAINER<NoLogging>;

constexpr auto DEFAULT_POLICY_CONTAINER_WITH_LOGGING =
    DEFAULT_POLICY_CONTAINER<DebugLogging>;

#endif //GEN_IV_BATTLE_FRONTIER_ANALYZER_TEST_POLICIES_H
