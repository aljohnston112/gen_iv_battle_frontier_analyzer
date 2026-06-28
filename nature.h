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
        {NatureEnum::HARDY, Stat::NoStat, Stat::NoStat}
    },
    {
        NatureEnum::LONELY,
        {NatureEnum::LONELY, Stat::Attack, Stat::Defense}
    },
    {
        NatureEnum::BRAVE,
        {NatureEnum::BRAVE, Stat::Attack, Stat::Speed}
    },
    {
        NatureEnum::ADAMANT,
        {NatureEnum::ADAMANT, Stat::Attack, Stat::SpecialAttack}
    },
    {
        NatureEnum::NAUGHTY,
        {NatureEnum::NAUGHTY, Stat::Attack, Stat::SpecialDefense}
    },
    {
        NatureEnum::BOLD,
        {NatureEnum::BOLD, Stat::Defense, Stat::Attack}
    },
    {
        NatureEnum::DOCILE,
        {NatureEnum::DOCILE, Stat::NoStat, Stat::NoStat}
    },
    {
        NatureEnum::RELAXED,
        {NatureEnum::RELAXED, Stat::Defense, Stat::Speed}
    },
    {
        NatureEnum::IMPISH,
        {NatureEnum::IMPISH, Stat::Defense, Stat::SpecialAttack}
    },
    {
        NatureEnum::LAX,
        {NatureEnum::LAX, Stat::Defense, Stat::SpecialDefense}
    },
    {
        NatureEnum::TIMID,
        {NatureEnum::TIMID, Stat::Speed, Stat::Attack}
    },
    {
        NatureEnum::HASTY,
        {NatureEnum::HASTY, Stat::Speed, Stat::Defense}
    },
    {
        NatureEnum::SERIOUS,
        {NatureEnum::SERIOUS, Stat::NoStat, Stat::NoStat}
    },
    {
        NatureEnum::JOLLY,
        {NatureEnum::JOLLY, Stat::Speed, Stat::SpecialAttack}
    },
    {
        NatureEnum::NAIVE,
        {NatureEnum::NAIVE, Stat::Speed, Stat::SpecialDefense}
    },
    {
        NatureEnum::MODEST,
        {NatureEnum::MODEST, Stat::SpecialAttack, Stat::Attack}
    },
    {
        NatureEnum::MILD,
        {NatureEnum::MILD, Stat::SpecialAttack, Stat::Defense}
    },
    {
        NatureEnum::QUIET,
        {NatureEnum::QUIET, Stat::SpecialAttack, Stat::Speed}
    },
    {
        NatureEnum::BASHFUL,
        {NatureEnum::BASHFUL, Stat::NoStat, Stat::NoStat}
    },
    {
        NatureEnum::RASH,
        {NatureEnum::RASH, Stat::SpecialAttack, Stat::SpecialDefense}
    },
    {
        NatureEnum::CALM,
        {NatureEnum::CALM, Stat::SpecialDefense, Stat::Attack}
    },
    {
        NatureEnum::GENTLE,
        {NatureEnum::GENTLE, Stat::SpecialDefense, Stat::Defense}
    },
    {
        NatureEnum::SASSY,
        {NatureEnum::SASSY, Stat::SpecialDefense, Stat::Speed}
    },
    {
        NatureEnum::CAREFUL,
        {NatureEnum::CAREFUL, Stat::SpecialDefense, Stat::SpecialAttack}
    },
    {
        NatureEnum::QUIRKY,
        {NatureEnum::QUIRKY, Stat::NoStat, Stat::NoStat}
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
    if (stat == Stat::Health) {
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
