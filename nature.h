#pragma once
#include "stat.h"

enum NatureEnum {
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
        HARDY,
        {HARDY, NoStat, NoStat}
    },
    {
        LONELY,
        {LONELY, Attack, Defense}
    },
    {
        BRAVE,
        {BRAVE, Attack, Speed}
    },
    {
        ADAMANT,
        {ADAMANT, Attack, SpecialAttack}
    },
    {
        NAUGHTY,
        {NAUGHTY, Attack, SpecialDefense}
    },
    {
        BOLD,
        {BOLD, Defense, Attack}
    },
    {
        DOCILE,
        {DOCILE, NoStat, NoStat}
    },
    {
        RELAXED,
        {RELAXED, Defense, Speed}
    },
    {
        IMPISH,
        {IMPISH, Defense, SpecialAttack}
    },
    {
        LAX,
        {LAX, Defense, SpecialDefense}
    },
    {
        TIMID,
        {TIMID, Speed, Attack}
    },
    {
        HASTY,
        {HASTY, Speed, Defense}
    },
    {
        SERIOUS,
        {SERIOUS, NoStat, NoStat}
    },
    {
        JOLLY,
        {JOLLY, Speed, SpecialAttack}
    },
    {
        NAIVE,
        {NAIVE, Speed, SpecialDefense}
    },
    {
        MODEST,
        {MODEST, SpecialAttack, Attack}
    },
    {
        MILD,
        {MILD, SpecialAttack, Defense}
    },
    {
        QUIET,
        {QUIET, SpecialAttack, Speed}
    },
    {
        BASHFUL,
        {BASHFUL, NoStat, NoStat}
    },
    {
        RASH,
        {RASH, SpecialAttack, SpecialDefense}
    },
    {
        CALM,
        {CALM, SpecialDefense, Attack}
    },
    {
        GENTLE,
        {GENTLE, SpecialDefense, Defense}
    },
    {
        SASSY,
        {SASSY, SpecialDefense, Speed}
    },
    {
        CAREFUL,
        {CAREFUL, SpecialDefense, SpecialAttack}
    },
    {
        QUIRKY,
        {QUIRKY, NoStat, NoStat}
    }
};

const std::unordered_map<std::string, NatureEnum> STRING_TO_NATURE = {
    {"Hardy", HARDY},
    {"Lonely", LONELY},
    {"Brave", BRAVE},
    {"Adamant", ADAMANT},
    {"Naughty", NAUGHTY},
    {"Bold", BOLD},
    {"Docile", DOCILE},
    {"Relaxed", RELAXED},
    {"Impish", IMPISH},
    {"Lax", LAX},
    {"Timid", TIMID},
    {"Hasty", HASTY},
    {"Serious", SERIOUS},
    {"Jolly", JOLLY},
    {"Naive", NAIVE},
    {"Modest", MODEST},
    {"Mild", MILD},
    {"Quiet", QUIET},
    {"Bashful", BASHFUL},
    {"Rash", RASH},
    {"Calm", CALM},
    {"Gentle", GENTLE},
    {"Sassy", SASSY},
    {"Careful", CAREFUL},
    {"Quirky", QUIRKY}
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
    if (stat == Health) {
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
