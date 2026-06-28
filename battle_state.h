#pragma once

#include <cassert>

#include "pokemon.h"
#include "serebii/serebii_pokemon_data_source.h"

enum class FieldStatus {
    GravityActive,
    TrickRoomActive,
    FieldStatusCount
};

struct FieldStatusStage {
    FieldStatus status;
    int8_t stage;
};

enum class Status {
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
    StoleMoveByMeFirst,
    StatusCount
};

enum class StatusWithStage {
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

enum class MoveStatusWithStage {
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

enum class StatusCondition {
    Burn,
    Freeze,
    Paralysis,
    PoisonStatus,
    BadlyPoisoned,
    Sleep,
    NoCondition
};

class PokemonState {
    const CustomPokemon* pokemon;

    Item current_item;
    StatusCondition current_status_condition;
    std::array<uint16_t, to_int(Stat::NoStat)> current_stats{};
    std::array<bool, to_int(Status::StatusCount)> statuses{};
    std::array<
        bool,
        to_int(StatusWithStage::StatusWithStageCount)
    > statuses_with_stage{};
    std::array<
        int8_t,
        to_int(StatusWithStage::StatusWithStageCount)
    > status_stages{};
    std::array<
        bool,
        to_int(MoveStatusWithStage::MoveStatusWithStageCount)
    > move_statuses_with_stage{};
    std::array<
        MoveStatusStage,
        to_int(MoveStatusWithStage::MoveStatusWithStageCount)
    > move_status_stages{};
    std::array<int8_t, to_int(Stat::NoStat)> stat_stages = {0, 0, 0, 0, 0, 0};
    std::array<int8_t, to_int(Move::MoveCount)> power_points;
    std::vector<Move> current_moves;
    std::array<PokemonType, 2> current_types;
    // void set_stat(const Stat stat, const uint16_t value) {
    //     current_stats[to_int(stat)] = value;
    // }

public:
    const uint8_t level;

    explicit PokemonState(const CustomPokemon* pokemon_in)
        : pokemon(pokemon_in),
          current_item(pokemon_in->item),
          current_status_condition(StatusCondition::NoCondition),
          current_moves(pokemon_in->moves),
          current_types(pokemon_in->types),
          level(pokemon_in->level) {
        for (int i = 0; i < to_int(Stat::NoStat); i++) {
            current_stats[to_int(i)] =
                pokemon_in->get_stat(static_cast<Stat>(i));
        }

        power_points.fill(0);
        const auto& all_move_infos =
            get_all_moves();
        for (const auto& move : pokemon->moves) {
            power_points[to_int(move)] =
                static_cast<uint8_t>(all_move_infos[to_int(move)].power_points);
        }
    }

    [[nodiscard]] Ability get_current_ability() const {
        return pokemon->ability;
    }

    [[nodiscard]] const std::vector<Move>& get_moves() const {
        return current_moves;
    }

    [[nodiscard]] const std::array<PokemonType, 2>& get_types() const {
        return current_types;
    }

    void add_hp(const uint16_t hp_gained) {
        current_stats[to_int(Stat::Health)] = std::min(
            pokemon->get_stat(Stat::Health),
            static_cast<uint16_t>(get_current_stat(Stat::Health) + hp_gained)
        );
    }

    void add_damage(const int16_t hp_lost) {
        current_stats[to_int(Stat::Health)] =
            static_cast<uint16_t>(
                std::max(
                    0,
                    get_current_stat(Stat::Health) - hp_lost
                )
            );
    }

    [[nodiscard]] bool has_status(const Status status) const {
        return statuses[to_int(status)];
    }

    [[nodiscard]] bool has_status(const StatusWithStage status) const {
        return statuses_with_stage[to_int(status)];
    }

    [[nodiscard]] bool has_status(const MoveStatusWithStage status) const {
        return move_statuses_with_stage[to_int(status)];
    }

    [[nodiscard]] uint8_t get_status_value(const StatusWithStage status) const {
        if (!has_status(status)) {
            return 0;
        }
        return static_cast<uint8_t>(status_stages[to_int(status)]);
    }

    [[nodiscard]] uint8_t get_status_value(
        const MoveStatusWithStage status
    ) const {
        if (!has_status(status)) {
            return 0;
        }
        return static_cast<uint8_t>(
            move_status_stages[to_int(status)].stage
        );
    }

    void decrement_status_value(const StatusWithStage status) {
        status_stages[to_int(status)] =
            static_cast<int8_t>(
                std::max(0, status_stages[to_int(status)] + 1)
            );
    }

    void clear_status_value(const StatusWithStage status) {
        statuses[to_int(status)] = false;
    }

    [[nodiscard]] int8_t get_stat_stage(const Stat stat) const {
        return stat_stages[to_int(stat)];
    }

    [[nodiscard]] bool has_type(const PokemonType type) const {
        return pokemon->types[0] == type || pokemon->types[1] == type;
    }

    void set_confused(const uint8_t n) {
        statuses_with_stage[to_int(StatusWithStage::Confused)] = true;
        status_stages[to_int(StatusWithStage::Confused)] = n;
    }

    [[nodiscard]] uint16_t get_original_stat(const Stat stat) const {
        return pokemon->get_stat(stat);
    }


    [[nodiscard]] uint16_t get_current_stat(const Stat stat) const {
        return current_stats[to_int(stat)];
    }

    void set_stat(const Stat stat, const uint16_t new_stat) {
        current_stats[to_int(stat)] = new_stat;
    }

    void lower_stat_stage(const Stat stat, const int n) {
        stat_stages[to_int(stat)] =
            static_cast<int8_t>(std::max(-6, get_stat_stage(stat) - n));
        set_stat(
            stat,
            calculate_stat_based_on_stage(
                pokemon->get_stat(stat),
                get_stat_stage(stat)
            )
        );
    }

    [[nodiscard]] StatusCondition get_current_status_condition() const {
        return current_status_condition;
    }

    void try_set_status(const StatusCondition status_condition) {
        if (current_status_condition == StatusCondition::NoCondition) {
            current_status_condition = status_condition;
        }
    }

    void clear_status_condition() {
        current_status_condition = StatusCondition::NoCondition;
    }

    [[nodiscard]] Item get_current_item_for_effect() const {
        return current_item;
    }

    void clear_current_item() {
        const Item held_item = current_item;
        // Make sure to update any state if the old item set any!

        current_item = Item::NoItem;
    }

    [[nodiscard]] bool has_power_points() const {
        bool result = false;
        for (size_t i = 0; i < current_moves.size(); ++i) {
            result |= has_power_points(current_moves[i]);
        }
        return result;
    }

    [[nodiscard]] bool has_power_points(const Move move) const {
        if (move == Move::Struggle) {
            return true;
        }
        return power_points[to_int(move)] > 0;
    }

    void decrement_power_point(const Move move) {
        assert(
            power_points[to_int(move)] > 0 ||
            (move == Move::Struggle && !has_power_points())
        );
        if (move != Move::Struggle) [[likely]] {
            power_points[to_int(move)]--;
            if (power_points[to_int(move)] == 0) {
                std::erase(current_moves, move);
            }
            if (!has_power_points() && current_moves.empty()) {
                current_moves.emplace_back(Move::Struggle);
            }
        }
    }
};

enum class Weather {
    Sun,
    Rain,
    Sandstorm,
    Hail,
    Fog,
    Clear
};

class BattleState {
    std::array<bool, to_int(FieldStatus::FieldStatusCount)> field_statuses{};
    std::array<
        FieldStatusStage,
        to_int(FieldStatus::FieldStatusCount)
    > field_status_stages{};

public:
    PokemonState player;
    PokemonState opponent;
    Weather weather;

    BattleState(
        PokemonState&& player_in,
        PokemonState&& opponent_in
    ) : player(player_in),
        opponent(opponent_in),
        weather(Weather::Clear) {}
};
