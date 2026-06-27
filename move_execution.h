#ifndef GEN_IV_BATTLE_FRONTIER_ANALYZER_MOVE_EXECUTION_H
#define GEN_IV_BATTLE_FRONTIER_ANALYZER_MOVE_EXECUTION_H

#include "battle_state.h"
#include "policies.h"

static inline std::array<int16_t, LEVEL + 1> DAMAGE_CACHE = [] {
    std::array<int16_t, LEVEL + 1> array{};
    array.fill(-1.0);
    return array;
}();


template <IsRNGPolicy R>
void execute_power_move(
    const R& rng_policy,
    BattleState& battle_state,
    const MoveInfo* move,
    const Who who_is_attacker
) {
    const bool is_player_attacker = who_is_attacker == Player;

    PokemonState* attacker;
    if (is_player_attacker) {
        attacker = &battle_state.player;
    } else {
        attacker = &battle_state.opponent;
    }

    PokemonState* defender;
    if (is_player_attacker) {
        defender = &battle_state.opponent;
    } else {
        defender = &battle_state.player;
    }

    const uint8_t attacker_level = attacker->pokemon->level;
    int16_t damage = DAMAGE_CACHE[attacker_level];
    if (damage < 0) {
        damage = static_cast<int16_t>(2 * attacker_level / 5 + 2);
        DAMAGE_CACHE[attacker_level] = damage;
    }

    const uint16_t power = move->power;
    const bool is_special = move->category == SPECIAL;
    const Stat attack_category = is_special ? SpecialAttack : Attack;
    const Stat defense_category = is_special ? SpecialDefense : Defense;

    const Ability attacker_ability = attacker->pokemon->ability;
    const Ability defender_ability = defender->pokemon->ability;
    const bool is_crit =
        move->move != FutureSight && move->move != DoomDesire &&
        defender_ability != BattleArmor && defender_ability != ShellArmor &&
        !defender->has_status(LuckyChanted) &&
        rng_policy.roll(
            calculate_crit_chance_based_on_stage(
                attacker->get_status_value(CritChanceModified)
            )
        );

    const uint16_t attacker_attack =
        is_crit && attacker->get_stat_stage(attack_category) < 0
            ? attacker->pokemon->get_stat(attack_category)
            : is_special
            ? attacker->current_special_attack
            : attacker->current_attack;
    const uint16_t defender_defense =
        is_crit && defender->get_stat_stage(defense_category) > 0
            ? defender->pokemon->get_stat(defense_category)
            : is_special
            ? defender->current_special_defense
            : defender->current_defense;
    damage = static_cast<int16_t>(
        damage * power * attacker_attack / defender_defense
    );
    const uint8_t screen =
        (!is_crit &&
        ((is_special && defender->has_status(LightScreening))
         || (!is_special && defender->has_status(Reflecting))))
             ? 2
             : 1;
    const uint8_t burn = attacker->current_status == Burn && !is_special
                             ? 2
                             : 1;
    damage = static_cast<int16_t>(damage / 50 / burn / screen);

    const PokemonType move_type = move->type;
    const Weather weather = battle_state.weather;
    if (weather == Rain) {
        if (move_type == Water) {
            damage = static_cast<int16_t>(damage * 3 / 2);
        } else if (move_type == Fire) {
            damage = static_cast<int16_t>(damage / 2);
        }
    } else if (weather == Sun) {
        if (move_type == Fire) {
            damage = static_cast<int16_t>(damage * 3 / 2);
        } else if (move_type == Water) {
            damage = static_cast<int16_t>(damage / 2);
        }
    }

    if (attacker->has_status(FlashFired) && move_type == Fire) {
        damage = static_cast<int16_t>(damage * 3 / 2);
    }
    damage = static_cast<int16_t>(damage + 2);

    const uint8_t crit = is_crit ? 2 : 1;
    damage = static_cast<int16_t>(damage * crit);

    const Item attacker_item = attacker->current_item;
    if (attacker_item == LifeOrb) {
        damage = static_cast<int16_t>(damage * 4 / 3);
    } else if (const int8_t n = defender->get_status_value(MetronomeActive);
        n > 0
    ) {
        damage = static_cast<int16_t>((damage * 10 + damage * n) / 10);
    }
    if (attacker->has_status(StoleMove)) [[unlikely]] {
        damage = static_cast<int16_t>(damage * 3 / 2);
    }
    const uint8_t random =
        move->move == SpitUp
            ? 100
            : rng_policy.roll_random(is_player_attacker);
    damage = static_cast<int16_t>(damage * random / 100);
    const bool is_stab = attacker->has_type(move_type);
    if (is_stab) {
        if (attacker_ability == Adaptability) [[unlikely]]{
            damage = static_cast<int16_t>(damage * 2);
        } else {
            damage = static_cast<int16_t>(damage * 3 / 2);
        }
    }

    const double effectiveness = get_effectiveness(
        defender->pokemon->types,
        move_type
    );
    if (move->move != Struggle &&
        move->move != FutureSight &&
        move->move != BeatUp &&
        move->move != DoomDesire
    ) [[likely]] {
        damage = static_cast<int16_t>(
            std::floor(
                damage * effectiveness
            )
        );
    }
    if (effectiveness > 1) {
        if (attacker_ability != MoldBreaker &&
            (defender_ability == SolidRock || defender_ability == Filter)
        ) [[unlikely]] {
            damage = static_cast<int16_t>(damage * 3 / 4);
        }

        if (attacker_item == ExpertBelt) [[unlikely]] {
            damage = static_cast<int16_t>(damage * 6 / 5);
        }
    }
    if (effectiveness < 1 && attacker_ability == TintedLens) [[unlikely]] {
        damage = static_cast<int16_t>(damage * 2);
    }
    const auto defender_item = defender->current_item;
    if (DAMAGE_REDUCING_BERRIES.contains(defender_item) &&
        DAMAGE_REDUCING_BERRIES.at(defender_item) == move_type
    ) {
        damage = static_cast<int16_t>(damage / 2);
        defender->current_item = NoItem;
    }

    defender->add_damage(damage);
}


inline void execute_moonlight(PokemonState& player, const Weather weather) {
    const uint16_t max_hp = player.pokemon->get_stat(Health);
    uint16_t hp_gained;
    if (weather == Clear) [[likely]] {
        hp_gained = static_cast<uint16_t>(max_hp / 2);
    } else if (weather == Sun) {
        hp_gained = static_cast<uint16_t>(max_hp * 2 / 3);
    } else {
        hp_gained = static_cast<uint16_t>(max_hp / 4);
    }
    player.add_hp(hp_gained);
}

template <IsRNGPolicy R>
void roll_confusion(
    const R& rng_policy,
    PokemonState& defender,
    const int chance
) {
    if (rng_policy.roll(static_cast<uint8_t>(chance))) {
        defender.set_confused(rng_policy.roll(static_cast<uint8_t>(3)) + 2);
    }
}

inline bool move_will_work(
    const BattleState& battle_state,
    const MoveInfo* move,
    const Who who_is_attacker
) {
    const bool is_player_attacker = who_is_attacker == Player;
    const auto move_type = move->type;

    const PokemonState* defender_state;
    if (is_player_attacker) {
        defender_state = &battle_state.opponent;
    } else {
        defender_state = &battle_state.player;
    }
    const CustomPokemon* defender = defender_state->pokemon;

    if (defender->ability == Levitate &&
        move_type == Ground
    ) [[unlikely]] {
        return false;
    }

    return true;
}

template <IsRNGPolicy R>
void execute_move(
    R rng_policy,
    BattleState& battle_state,
    const Who who,
    const MoveInfo* move
) {
    if (!move_will_work(battle_state, move, who)) {
        return;
    }
    const bool is_player = who == Player;
    PokemonState& attacker = is_player
                                 ? battle_state.player
                                 : battle_state.opponent;
    PokemonState& defender = is_player
                                 ? battle_state.opponent
                                 : battle_state.player;
    if (move->move == Moonlight) {
        execute_moonlight(attacker, battle_state.weather);
    } else if (move_has_flag(move->move, HAS_POWER)) {
        execute_power_move(
            rng_policy,
            battle_state,
            move,
            who
        );
    }

    if (move_has_flag(move->move, CONFUSES_DEFENDER_10)) {
        roll_confusion(rng_policy, defender, 10);
    }
}

#endif //GEN_IV_BATTLE_FRONTIER_ANALYZER_MOVE_EXECUTION_H
