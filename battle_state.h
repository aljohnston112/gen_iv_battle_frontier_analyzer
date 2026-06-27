#pragma once

#include "pokemon.h"

enum FieldStatus {
    GravityActive,
    TrickRoomActive,
    FieldStatusCount
};

struct FieldStatusStage {
    FieldStatus status;
    int8_t stage;
};

enum Status {
    AquaRingActive,
    PowerTrickActive,
    DestinyBound,
    FlashFired,
    Ingrained,
    MagnetRisen,
    Minimized,
    Imprisoned,
    CanNotEscape,
    Cursed,
    Flinched,
    Identified,
    Infatuated,
    LeechSeeded,
    Nightmared,
    AbilityDisabled,
    Tormented,
    StealthRocked,
    StoleMove,
    StatusCount
};

enum StatusWithStage {
    Charging,
    Recharging,
    ElectricBoosted,
    CritChanceModified,
    Rampaging,
    Stockpiling,
    Uproaring,
    Wished,
    LightScreening,
    Reflecting,
    Safeguarding,
    Tailwinded,
    Bounded,
    Confused,
    Drowsy,
    Embargoed,
    FutureSighted,
    HealBlocked,
    LockedOn,
    Taunted,
    Spiked,
    ToxicSpiked,
    Perishing,
    LuckyChanted,
    StatusWithStageCount
};

enum MoveStatusWithStage {
    Concealed,
    SkyHigh,
    Submerged,
    Underground,
    Encored,
    MoveDisabled,
    MetronomeActive,
    MoveStatusWithStageCount
};

struct MoveStatusStage {
    int8_t stage;
    Move move;
};

enum StatusCondition {
    Burn,
    Freeze,
    Paralysis,
    PoisonStatus,
    BadlyPoisoned,
    Sleep,
    NoCondition
};

class PokemonState {
    std::array<bool, StatusCount> statuses{};
    std::array<bool, StatusWithStageCount> statuses_with_stage{};
    std::array<int8_t, StatusWithStageCount> status_stages{};
    std::array<bool, MoveStatusWithStageCount> move_statuses_with_stage{};
    std::array<MoveStatusStage, MoveStatusWithStageCount> move_status_stages{};

    std::array<int8_t, 6> stat_stages = {0, 0, 0, 0, 0, 0};
public:
    const CustomPokemon* pokemon;
    uint16_t current_hp;
    uint16_t current_attack;
    uint16_t current_defense;
    uint16_t current_special_attack;
    uint16_t current_special_defense;
    uint16_t current_speed;
    Item current_item;
    StatusCondition current_status;

    explicit PokemonState(const CustomPokemon* pokemon_in)
        : pokemon(pokemon_in),
          current_hp(pokemon_in->get_stat(Health)),
          current_attack(pokemon_in->get_stat(Attack)),
          current_defense(pokemon_in->get_stat(Defense)),
          current_special_attack(pokemon_in->get_stat(SpecialAttack)),
          current_special_defense(pokemon_in->get_stat(SpecialDefense)),
          current_speed(pokemon_in->get_stat(Speed)),
          current_item(pokemon_in->item), current_status(NoCondition) {}

    void add_hp(const uint16_t hp_gained) {
        current_hp = std::min(
            pokemon->get_stat(Health),
            static_cast<uint16_t>(current_hp + hp_gained)
        );
    }

    void add_damage(int16_t hp_lost) {
        current_hp = std::max(0, current_hp - hp_lost);
    }

    bool has_status(const Status status) const {
        return statuses[status];
    }

    bool has_status(const StatusWithStage status_with_stage) const {
        return statuses_with_stage[status_with_stage];
    }

    bool has_status(const MoveStatusWithStage status_with_stage) const {
        return move_statuses_with_stage[status_with_stage];
    }

    uint8_t get_status_value(const StatusWithStage status_with_stage) const {
        if (!has_status(status_with_stage)) {
            return 0;
        }
        return static_cast<uint8_t>(status_stages[status_with_stage]);
    }

    uint8_t get_status_value(const MoveStatusWithStage status_with_stage) const {
        if (!has_status(status_with_stage)) {
            return 0;
        }
        return static_cast<uint8_t>(move_status_stages[status_with_stage].stage);
    }

    int8_t get_stat_stage(const Stat stat) const {
        return stat_stages[stat];
    }

    bool has_type(const PokemonType type) const {
        return pokemon->types[0] == type || pokemon->types[1] == type;
    }

    void set_confused(const uint8_t n) {
        statuses_with_stage[Confused] = true;
        status_stages[Confused] = n;
    }

};

enum Weather {
    Sun,
    Rain,
    Sandstorm,
    Hail,
    Fog,
    Clear
};

class BattleState {
    std::array<bool, FieldStatusCount> field_statuses{};
    std::array<FieldStatusStage, FieldStatusCount> field_status_stages{};
public:
    PokemonState player;
    PokemonState opponent;
    Weather weather;


    BattleState(
        const PokemonState&& player_in,
        const PokemonState&& opponent_in
    ) : player(player_in),
        opponent(opponent_in),
        weather(Clear) {}
};
