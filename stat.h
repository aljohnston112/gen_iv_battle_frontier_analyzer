#pragma once

#include <cmath>

enum class Stat {
    HEALTH,
    ATTACK,
    DEFENSE,
    SPECIAL_ATTACK,
    SPECIAL_DEFENSE,
    SPEED,
    NO_STAT
};

struct BaseStats {
    int16_t health;
    uint16_t attack;
    uint16_t defense;
    uint16_t special_attack;
    uint16_t special_defense;
    uint16_t speed;
};

static const std::unordered_map<std::string, Stat> STRING_TO_STAT_MAP{
    {"health", Stat::HEALTH},
    {"attack", Stat::ATTACK},
    {"defense", Stat::DEFENSE},
    {"special_attack", Stat::SPECIAL_ATTACK},
    {"special_defense", Stat::SPECIAL_DEFENSE},
    {"speed", Stat::SPEED}
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
    return static_cast<u_int16_t>((2 * base + iv + ev / 4) * level / 100 + level + 10);
}
