#pragma once

#include <cmath>

enum class Stat {
    Health,
    Attack,
    Defense,
    SpecialAttack,
    SpecialDefense,
    Speed,
    NoStat
};

struct BaseStats {
    int16_t health;
    uint16_t attack;
    uint16_t defense;
    uint16_t special_attack;
    uint16_t special_defense;
    uint16_t speed;
};

enum class StatusCondition {
    Burn,
    Freeze,
    Paralysis,
    PoisonStatus,
    BadlyPoisoned,
    NoCondition
};

inline const std::unordered_map<std::string, Stat> STRING_TO_STAT_MAP{
    {"health", Stat::Health},
    {"attack", Stat::Attack},
    {"defense", Stat::Defense},
    {"special_attack", Stat::SpecialAttack},
    {"special_defense", Stat::SpecialDefense},
    {"speed", Stat::Speed}
};

inline uint8_t get_iv_for_battle_factory(const uint8_t round_number) {
    if (round_number == 0) return 0;
    const int iv = (round_number - 1) * 4;
    return static_cast<uint8_t>((round_number < 8) ? iv : 31);
}

inline u_int16_t calculate_hp_stat(
    const uint8_t level,
    const uint16_t base,
    const uint8_t iv,
    const u_int16_t ev
) {
    return static_cast<u_int16_t>(
        (2 * base + iv + ev / 4) * level / 100 + level + 10
    );
}

inline uint16_t calculate_accuracy_and_evasion_based_on_stage(
    const int move_accuracy,
    const int accuracy_stage,
    const int evasion_stage
) {
    static constexpr std::array<std::pair<uint16_t, uint16_t>, 13>
        multipliers =
        {
            {
                {33, 100},
                {36, 100},
                {43, 100},
                {50, 100},
                {60, 100},
                {75, 100},
                {100, 100},
                {133, 100},
                {166, 100},
                {200, 100},
                {233, 100},
                {266, 100},
                {300, 100}
            }
        };
    if (accuracy_stage < -6 || accuracy_stage > 6 ||
        evasion_stage < -6 || evasion_stage > 6
    ) [[unlikely]] {
        throw std::runtime_error("Bad stage");
    }
    const auto [num, den] =
        multipliers[(accuracy_stage - evasion_stage) + 6];
    const uint32_t modified_stat_value = num * move_accuracy / den;
    return static_cast<uint16_t>(modified_stat_value);
}


template <Stat stat>
uint16_t calculate_stat_based_on_stage(
    const int stat_value,
    const int stage,
    const StatusCondition status_condition
) {
    static constexpr std::array<std::pair<uint16_t, uint16_t>, 13>
        multipliers =
        {
            {
                {2, 8},
                {2, 7},
                {2, 6},
                {2, 5},
                {2, 4},
                {2, 3},
                {1, 1},
                {3, 2},
                {4, 2},
                {5, 2},
                {6, 2},
                {7, 2},
                {8, 2}
            }
        };
    if (stage < -6 || stage > 6) [[unlikely]] {
        throw std::runtime_error("Bad stage");
    }
    const auto [num, den] =
        multipliers[stage + 6];
    uint32_t modified_stat_value = num * stat_value / den;
    if (status_condition == StatusCondition::Paralysis) [[unlikely]] {
        modified_stat_value = modified_stat_value / 4;
    }
    return static_cast<uint16_t>(modified_stat_value);
}

inline double calculate_crit_chance_based_on_stage(const uint8_t stage) {
    static constexpr std::array crit_chances =
        {6.25, 12.5, 25.0, 1.0 / 3.0, 50.0};
    return crit_chances[std::min(static_cast<uint8_t>(4), stage)];
}
