#pragma once
#include "stat.h"

enum class NatureEnum {
    HARDY,
    LONELY,
    BRAVE,
    ADAMANT,
    NAUGHTY,
    BOLD,
    DOCILE,
    RELAXED,
    IMPISH,
    LAX,
    TIMID,
    HASTY,
    SERIOUS,
    JOLLY,
    NAIVE,
    MODEST,
    MILD,
    QUIET,
    BASHFUL,
    RASH,
    CALM,
    GENTLE,
    SASSY,
    CAREFUL,
    QUIRKY
};

struct Nature {
    NatureEnum nature;
    Stat up;
    Stat down;
};

const std::unordered_map<NatureEnum, Nature> NATURE_MAP = {
    {
        NatureEnum::HARDY,
        {NatureEnum::HARDY, Stat::NO_STAT, Stat::NO_STAT}
    },
    {
        NatureEnum::LONELY,
        {NatureEnum::LONELY, Stat::ATTACK, Stat::DEFENSE}
    },
    {
        NatureEnum::BRAVE,
        {NatureEnum::BRAVE, Stat::ATTACK, Stat::SPEED}
    },
    {
        NatureEnum::ADAMANT,
        {NatureEnum::ADAMANT, Stat::ATTACK, Stat::SPECIAL_ATTACK}
    },
    {
        NatureEnum::NAUGHTY,
        {NatureEnum::NAUGHTY, Stat::ATTACK, Stat::SPECIAL_DEFENSE}
    },
    {
        NatureEnum::BOLD,
        {NatureEnum::BOLD, Stat::DEFENSE, Stat::ATTACK}
    },
    {
        NatureEnum::DOCILE,
        {NatureEnum::DOCILE, Stat::NO_STAT, Stat::NO_STAT}
    },
    {
        NatureEnum::RELAXED,
        {NatureEnum::RELAXED, Stat::DEFENSE, Stat::SPEED}
    },
    {
        NatureEnum::IMPISH,
        {NatureEnum::IMPISH, Stat::DEFENSE, Stat::SPECIAL_ATTACK}
    },
    {
        NatureEnum::LAX,
        {NatureEnum::LAX, Stat::DEFENSE, Stat::SPECIAL_DEFENSE}
    },
    {
        NatureEnum::TIMID,
        {NatureEnum::TIMID, Stat::SPEED, Stat::ATTACK}
    },
    {
        NatureEnum::HASTY,
        {NatureEnum::HASTY, Stat::SPEED, Stat::DEFENSE}
    },
    {
        NatureEnum::SERIOUS,
        {NatureEnum::SERIOUS, Stat::NO_STAT, Stat::NO_STAT}
    },
    {
        NatureEnum::JOLLY,
        {NatureEnum::JOLLY, Stat::SPEED, Stat::SPECIAL_ATTACK}
    },
    {
        NatureEnum::NAIVE,
        {NatureEnum::NAIVE, Stat::SPEED, Stat::SPECIAL_DEFENSE}
    },
    {
        NatureEnum::MODEST,
        {NatureEnum::MODEST, Stat::SPECIAL_ATTACK, Stat::ATTACK}
    },
    {
        NatureEnum::MILD,
        {NatureEnum::MILD, Stat::SPECIAL_ATTACK, Stat::DEFENSE}
    },
    {
        NatureEnum::QUIET,
        {NatureEnum::QUIET, Stat::SPECIAL_ATTACK, Stat::SPEED}
    },
    {
        NatureEnum::BASHFUL,
        {NatureEnum::BASHFUL, Stat::NO_STAT, Stat::NO_STAT}
    },
    {
        NatureEnum::RASH,
        {NatureEnum::RASH, Stat::SPECIAL_ATTACK, Stat::SPECIAL_DEFENSE}
    },
    {
        NatureEnum::CALM,
        {NatureEnum::CALM, Stat::SPECIAL_DEFENSE, Stat::ATTACK}
    },
    {
        NatureEnum::GENTLE,
        {NatureEnum::GENTLE, Stat::SPECIAL_DEFENSE, Stat::DEFENSE}
    },
    {
        NatureEnum::SASSY,
        {NatureEnum::SASSY, Stat::SPECIAL_DEFENSE, Stat::SPEED}
    },
    {
        NatureEnum::CAREFUL,
        {NatureEnum::CAREFUL, Stat::SPECIAL_DEFENSE, Stat::SPECIAL_ATTACK}
    },
    {
        NatureEnum::QUIRKY,
        {NatureEnum::QUIRKY, Stat::NO_STAT, Stat::NO_STAT}
    }
};

const std::unordered_map<std::string, NatureEnum> STRING_TO_NATURE = {
    {"Hardy", NatureEnum::HARDY},
    {"Lonely", NatureEnum::LONELY},
    {"Brave", NatureEnum::BRAVE},
    {"Adamant", NatureEnum::ADAMANT},
    {"Naughty", NatureEnum::NAUGHTY},
    {"Bold", NatureEnum::BOLD},
    {"Docile", NatureEnum::DOCILE},
    {"Relaxed", NatureEnum::RELAXED},
    {"Impish", NatureEnum::IMPISH},
    {"Lax", NatureEnum::LAX},
    {"Timid", NatureEnum::TIMID},
    {"Hasty", NatureEnum::HASTY},
    {"Serious", NatureEnum::SERIOUS},
    {"Jolly", NatureEnum::JOLLY},
    {"Naive", NatureEnum::NAIVE},
    {"Modest", NatureEnum::MODEST},
    {"Mild", NatureEnum::MILD},
    {"Quiet", NatureEnum::QUIET},
    {"Bashful", NatureEnum::BASHFUL},
    {"Rash", NatureEnum::RASH},
    {"Calm", NatureEnum::CALM},
    {"Gentle", NatureEnum::GENTLE},
    {"Sassy", NatureEnum::SASSY},
    {"Careful", NatureEnum::CAREFUL},
    {"Quirky", NatureEnum::QUIRKY}
};

inline uint16_t calculate_non_hp_stat(
    const uint8_t level,
    const Stat stat,
    const uint16_t base,
    const uint8_t iv,
    const uint16_t ev,
    const Nature nature
) {
    const int intermediate = (2 * base + iv + ev / 4) * level / 100 + 5;
    double nature_multiplier = 1.0;
    if (nature.down == stat) {
        nature_multiplier = 0.9;
    } else if (nature.up == stat) {
        nature_multiplier = 1.1;
    }
    return static_cast<uint16_t>(std::floor(intermediate * nature_multiplier));
}

inline uint16_t get_stat(
    const uint8_t level,
    const Stat stat,
    const uint16_t base,
    const uint8_t iv,
    const u_int16_t ev,
    const Nature nature
) {
    if (stat == Stat::HEALTH) {
        return calculate_hp_stat(level, base, iv, ev);
    }
    return calculate_non_hp_stat(
        level,
        stat,
        base,
        iv,
        ev,
        nature
    );
}
