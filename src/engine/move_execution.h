#ifndef GEN_IV_BATTLE_FRONTIER_ANALYZER_MOVE_EXECUTION_H
#define GEN_IV_BATTLE_FRONTIER_ANALYZER_MOVE_EXECUTION_H

#include "battle_state.h"
#include "policies.h"

// TODO tests
// Smeargle, sketch a low PP move, get a life orb, and test damage with and without the life orb
// Same with metronome

// Get Pickachu confused, test hit danage with and without Light Ball
// Get Cubone/Marowak coinfused, test hit damage with and without Thick Club

// TODO Flash fire does not work when frozen
//      A frozen Sky Forme Shaymin will revert to its Land Forme.

inline std::array<int16_t, LEVEL + 1> DAMAGE_CACHE = [] {
    std::array<int16_t, LEVEL + 1> array{};
    array.fill(-1.0);
    return array;
}();


template <typename... Policies>
uint16_t get_damage_of_power_move(
    const PolicyContainer<Policies...>& policy_container,
    const BattleState& battle_state,
    const PokemonState& attacker,
    const PokemonState& defender,
    const MoveInfo* move,
    const Who who_attacker_is
) {
    // NOTE: If you add a new damage modifier here,
    // check if it should apply to hit_from_confusion or struggle.

    const uint8_t attacker_level = attacker.level;
    int32_t damage = DAMAGE_CACHE[attacker_level];
    if (damage < 0) {
        damage = 2 * attacker_level / 5 + 2;
        DAMAGE_CACHE[attacker_level] = static_cast<int16_t>(damage);
    }

    const uint16_t power = move->power;
    const bool is_special = move->category == Category::SPECIAL;
    const Stat attack_category =
        is_special ? Stat::SpecialAttack : Stat::Attack;
    const Stat defense_category = is_special
                                      ? Stat::SpecialDefense
                                      : Stat::Defense;

    const Ability attacker_ability = attacker.get_current_ability();
    const Ability defender_ability = defender.get_current_ability();
    const bool is_crit =
        move->move != Move::FutureSight && move->move != Move::DoomDesire &&
        defender_ability != Ability::BattleArmor && defender_ability !=
        Ability::ShellArmor &&
        !defender.has_status(StatusWithStage::LuckyChanted) &&
        policy_container.roll_for_crit(
            calculate_crit_chance_based_on_stage(
                attacker.get_status_value(StatusWithStage::CritChanceModified)
            )
        );

    const uint16_t attacker_attack =
        is_crit && attacker.get_stat_stage(attack_category) < 0
            ? attacker.get_original_stat(attack_category)
            : attacker.get_current_stat(attack_category);
    const uint16_t defender_defense =
        is_crit && defender.get_stat_stage(defense_category) > 0
            ? defender.get_original_stat(defense_category)
            : defender.get_current_stat(defense_category);
    damage = damage * power * attacker_attack / defender_defense;
    const uint8_t screen =
    (!is_crit &&
        ((is_special && defender.has_status(StatusWithStage::LightScreening))
            || (!is_special && defender.
                has_status(StatusWithStage::Reflecting))))
        ? 2
        : 1;
    const uint8_t burn = attacker.get_current_status_condition() ==
                         StatusCondition::Burn && !
                         is_special
                             ? 2
                             : 1;
    damage = damage / 50 / burn / screen;

    const PokemonType move_type = move->type;
    const Weather weather = battle_state.weather;
    if (weather == Weather::Rain) {
        if (move_type == PokemonType::Water) {
            damage = damage * 3 / 2;
        } else if (move_type == PokemonType::Fire) {
            damage = damage / 2;
        }
    } else if (weather == Weather::Sun) {
        if (move_type == PokemonType::Fire) {
            damage = damage * 3 / 2;
        } else if (move_type == PokemonType::Water) {
            damage = damage / 2;
        }
    }

    if (attacker.has_status(Status::FlashFired) &&
        move_type == PokemonType::Fire
    ) {
        damage = damage * 3 / 2;
    }
    damage = damage + 2;

    const uint8_t crit = is_crit ? 2 : 1;
    damage = damage * crit;

    const Item attacker_item = attacker.get_current_item_for_effect();
    if (attacker_item == Item::LifeOrb) {
        damage = damage * 13 / 10;
    } else if (const int8_t n =
            attacker.get_status_value(MoveStatusWithStage::MetronomeActive);
        n > 0
    ) {
        damage = (damage * 10 + damage * n) / 10;
    }
    if (attacker.has_status(Status::StoleMoveByMeFirst)) [[unlikely]] {
        damage = damage * 3 / 2;
    }
    const uint8_t random =
        move->move == Move::SpitUp
            ? 100
            : policy_container.roll_random(who_attacker_is);
    damage = damage * random / 100;
    const bool is_stab = attacker.has_type(move_type);
    if (is_stab) {
        if (attacker_ability == Ability::Adaptability) [[unlikely]]{
            damage = damage * 2;
        } else {
            damage = damage * 3 / 2;
        }
    }

    const uint16_t effectiveness = get_effectiveness(
        defender.get_types(),
        move_type
    );
    if (move->move != Move::Struggle &&
        move->move != Move::FutureSight &&
        move->move != Move::BeatUp &&
        move->move != Move::DoomDesire
    ) [[likely]] {
        damage = damage * effectiveness / 16;
    }
    if (effectiveness > 16) {
        if (attacker_ability != Ability::MoldBreaker &&
            (defender_ability == Ability::SolidRock ||
                defender_ability == Ability::Filter)
        ) [[unlikely]] {
            damage = damage * 3 / 4;
        }

        if (attacker_item == Item::ExpertBelt) [[unlikely]] {
            damage = damage * 6 / 5;
        }
    }
    if (effectiveness < 16 &&
        attacker_ability == Ability::TintedLens
    ) [[unlikely]] {
        damage = damage * 2;
    }
    const auto defender_item = defender.get_current_item_for_effect();
    if (DAMAGE_REDUCING_BERRIES.contains(defender_item) &&
        DAMAGE_REDUCING_BERRIES.at(defender_item) == move->type
    ) [[unlikely]] {
        damage = damage / 2;
    }

    damage = std::max(1, damage);
    return static_cast<uint16_t>(damage);
}

template <typename... Policies>
uint16_t execute_power_move(
    const PolicyContainer<Policies...>& policy_container,
    BattleState& battle_state,
    PokemonState& attacker,
    PokemonState& defender,
    const MoveInfo* move,
    const Who who_attacker_is
) {
    const auto defender_item = defender.get_current_item_for_effect();
    if (DAMAGE_REDUCING_BERRIES.contains(defender_item) &&
        DAMAGE_REDUCING_BERRIES.at(defender_item) == move->type
    ) [[unlikely]] {
        defender.clear_current_item();
    }

    const uint16_t hp_before = defender.get_current_stat(Stat::Health);
    defender.add_damage(
        get_damage_of_power_move(
            policy_container,
            battle_state,
            attacker,
            defender,
            move,
            who_attacker_is
        )
    );
    return hp_before - defender.get_current_stat(Stat::Health);
}

template <typename... Policies>
uint16_t calculate_confused_hit_damage(
    const PolicyContainer<Policies...>& policy_container,
    const PokemonState& attacker,
    const Who who_attacker_is
) {
    const uint8_t attacker_level = attacker.level;
    int32_t damage = DAMAGE_CACHE[attacker_level];
    if (damage < 0) {
        damage = 2 * attacker_level / 5 + 2;
        DAMAGE_CACHE[attacker_level] = static_cast<uint16_t>(damage);
    }
    uint32_t power = 40;
    if (attacker.get_current_ability() == Ability::Technician) {
        power = static_cast<uint16_t>(power * 3u / 2u);
    }
    const Item attacker_item = attacker.get_current_item_for_effect();
    if (attacker_item == Item::SilkScarf) {
        power = static_cast<uint16_t>(power * 6u / 5u);
    }
    // Power boosted by 50% if Helping Hand is in effect

    uint32_t attacker_attack = attacker.get_current_stat(Stat::Attack);
    if (attacker_item == Item::ChoiceBand) {
        attacker_attack = static_cast<uint16_t>(attacker_attack * 3u / 2u);
    }
    // TODO Attack possibly boosted Thick Club or Light Ball; but do they?

    const uint16_t defender_defense = attacker.get_current_stat(Stat::Defense);
    damage = damage * power * attacker_attack / defender_defense;
    const uint8_t burn = attacker.get_current_status_condition() ==
                         StatusCondition::Burn
                             ? 2
                             : 1;
    damage = damage / 50 / burn;
    damage = damage + 2;
    const uint8_t random =
        policy_container.roll_random_confusion(who_attacker_is);
    damage = damage * random / 100;
    damage = std::max(1, damage);
    return static_cast<uint16_t>(damage);
}

template <typename... Policies>
void hit_from_confusion(
    const PolicyContainer<Policies...>& policy_container,
    PokemonState& attacker,
    const Who who_attacker_is
) {
    attacker.add_damage(
        calculate_confused_hit_damage(
            policy_container,
            attacker,
            who_attacker_is
        )
    );
}

inline void execute_moonlight(PokemonState& player, const Weather weather) {
    const uint16_t max_hp = player.get_original_stat(Stat::Health);
    uint16_t hp_gained;
    if (weather == Weather::Clear) [[likely]] {
        hp_gained = static_cast<uint16_t>(max_hp / 2);
    } else if (weather == Weather::Sun) {
        hp_gained = static_cast<uint16_t>(max_hp * 2 / 3);
    } else {
        hp_gained = static_cast<uint16_t>(max_hp / 4);
    }
    player.add_hp(hp_gained);
}

template <typename... Policies>
void roll_confusion(
    const PolicyContainer<Policies...>& policy_container,
    PokemonState& defender,
    const Who who,
    const int8_t chance
) {
    if (policy_container.roll_for_confusion(chance)) {
        // 1 to 4 since the game decrements before acting,
        // but this engine decrements after the confusion check
        defender.set_confused(policy_container.roll_turns_confused(who));
    }
}

template <typename... Policies>
void roll_freeze(
    const PolicyContainer<Policies...>& policy_container,
    const Weather weather,
    PokemonState& defender,
    const int8_t chance
) {
    if (weather != Weather::Sun &&
        policy_container.roll_for_freeze(chance)
    ) {
        defender.try_set_status(StatusCondition::Freeze);
    }
}

template <typename... Policies>
void roll_paralysis(
    const PolicyContainer<Policies...>& policy_container,
    PokemonState& defender,
    const int8_t chance
) {
    if (defender.get_current_ability() != Ability::MagicGuard &&
        policy_container.roll_for_paralysis(chance)
    ) {
        defender.try_set_status(StatusCondition::Paralysis);
    }
}

inline bool move_does_nothing(
    const BattleState& battle_state,
    const MoveInfo* move,
    const Who who_attacker_is
) {
    const bool is_player_attacker = who_attacker_is == Who::Player;
    const auto move_type = move->type;

    const PokemonState* defender_state;
    if (is_player_attacker) {
        defender_state = &battle_state.opponent;
    } else {
        defender_state = &battle_state.player;
    }
    const Ability ability = defender_state->get_current_ability();
    if (ability == Ability::Levitate &&
        move_type == PokemonType::Ground
    ) [[unlikely]] {
        return false;
    }

    return true;
}

template <typename... Policies>
uint16_t get_struggle_damage(
    const PolicyContainer<Policies...>& policy_container,
    const PokemonState& attacker,
    const PokemonState& defender,
    const Who who_attacker_is
) {
    const auto attacker_level = attacker.level;
    int32_t damage = DAMAGE_CACHE[attacker_level];
    if (damage < 0) {
        damage = 2 * attacker_level / 5 + 2;
        DAMAGE_CACHE[attacker_level] = static_cast<int16_t>(damage);
    }

    constexpr uint16_t power = 50;
    constexpr auto attack_category = Stat::Attack;
    constexpr auto defense_category = Stat::Defense;

    const Ability defender_ability = defender.get_current_ability();
    const bool is_crit =
        defender_ability != Ability::BattleArmor &&
        defender_ability != Ability::ShellArmor &&
        !defender.has_status(StatusWithStage::LuckyChanted) &&
        policy_container.roll_for_crit(
            calculate_crit_chance_based_on_stage(
                attacker.get_status_value(StatusWithStage::CritChanceModified)
            )
        );

    const uint16_t attacker_attack =
        is_crit && attacker.get_stat_stage(attack_category) < 0
            ? attacker.get_original_stat(attack_category)
            : attacker.get_current_stat(attack_category);
    const uint16_t defender_defense =
        is_crit && defender.get_stat_stage(defense_category) > 0
            ? defender.get_original_stat(defense_category)
            : defender.get_current_stat(defense_category);
    damage = damage * power * attacker_attack / defender_defense;
    const uint8_t screen =
        (!is_crit && defender.has_status(StatusWithStage::Reflecting))
            ? 2
            : 1;
    const uint8_t burn =
        attacker.get_current_status_condition() == StatusCondition::Burn
            ? 2
            : 1;
    damage = damage / 50 / burn / screen;
    damage = damage + 2;

    const uint8_t crit = is_crit ? 2 : 1;
    damage = damage * crit;

    const Item attacker_item = attacker.get_current_item_for_effect();
    if (attacker_item == Item::LifeOrb) {
        damage = damage * 4 / 3;
    } else if (const int8_t n =
            attacker.get_status_value(MoveStatusWithStage::MetronomeActive);
        n > 0
    ) {
        damage = (damage * 10 + damage * n) / 10;
    }
    const uint8_t random = policy_container.roll_random(who_attacker_is);
    damage = damage * random / 100;
    damage = std::max(1, damage);
    return static_cast<uint16_t>(damage);
}

template <typename... Policies>
uint16_t execute_struggle(
    const PolicyContainer<Policies...>& policy_container,
    [[maybe_unused]] BattleState& battle_state,
    PokemonState& attacker,
    PokemonState& defender,
    const Who who_attacker_is
) {
    // TODO all of the comments before the code

    // Used when all moves are blocked by the moves
    // Disable, Gravity, Heal Block, Imprison, Taunt, or Torment,
    // or by the user's held choice item.

    // If a Pokémon is forced to use a single move by Encore
    // but that move runs out of PP, Encore's effect ends;
    // otherwise, if the move affected by Encore is unavailable for other reasons,
    // it will use Struggle.

    // Struggle can hit through Wonder Guard.

    // Struggle does not gain a boost from Reckless even though the user takes recoil damage.
    // The user still takes recoil damage even if its Ability is Magic Guard or Rock Head.

    // Struggle cannot be called by
    // Assist, Me First, Metronome, or Sleep Talk, copied by Mimic, Sketch, Transform,
    // repeated by a Pokémon as a result of Encore, Copycat, or a held choice item.

    // Struggle cannot be blocked by means such as Disable, Imprison,
    // or prevented from use multiple times in a row by Torment.

    // Struggle deals typeless damage

    // Self-inflicted recoil damage from Struggle from the previous turn
    // can be countered if the opponent did not make a move on the following turn.

    // The user will take recoil damage even if Struggle breaks a substitute.

    // Struggle now bypasses accuracy checks to always hit,
    // unless the target is in the semi-invulnerable turn of a move such as Dig or Fly.

    // Struggle will activate a target's held Chilan Berry.

    // Despite having a base power of 50 in every generation,
    // Struggle's power is not boosted by Technician in Generation IV.

    uint16_t damage = get_struggle_damage(
        policy_container,
        attacker,
        defender,
        who_attacker_is
    );
    const auto defender_item = defender.get_current_item_for_effect();
    if (defender_item == Item::ChilanBerry) {
        damage = damage / 2;
        defender.clear_current_item();
    }

    const uint16_t hp_before = defender.get_current_stat(Stat::Health);
    defender.add_damage(damage);

    attacker.add_damage(attacker.get_original_stat(Stat::Health) / 4);

    return hp_before - defender.get_current_stat(Stat::Health);
}

template <typename... Policies>
void roll_stat_drop(
    const PolicyContainer<Policies...>& policy_container,
    PokemonState& state,
    const Who whose_stat_dropped,
    const Stat stat,
    const int8_t stage_diff,
    const uint8_t probability
) {
    if (policy_container.roll_stat_drop(probability, whose_stat_dropped)) {
        state.decrease_stat_stage(stat, stage_diff);
    }
}

template <typename... Policies>
uint16_t execute_move(
    const PolicyContainer<Policies...>& policy_container,
    BattleState& battle_state,
    const Who who_attacker_is,
    const MoveInfo* move
) {
    const bool is_player_attacker = who_attacker_is == Who::Player;
    PokemonState& attacker = is_player_attacker
                                 ? battle_state.player
                                 : battle_state.opponent;
    PokemonState& defender = is_player_attacker
                                 ? battle_state.opponent
                                 : battle_state.player;



    if (attacker.get_current_status_condition() ==
        StatusCondition::Freeze
    ) [[unlikely]] {
        if (policy_container.roll_for_thaw(20) ||
            move->move == Move::FlameWheel ||
            move->move == Move::FlareBlitz ||
            move->move == Move::SacredFire
        ) [[unlikely]] {
            attacker.clear_status_condition();
        } else {
            return 0;
        }
    }

    if (attacker.get_current_status_condition() ==
        StatusCondition::Paralysis
        )[[unlikely]] {
        if (!policy_container.can_move_while_paralyzed(25)) [[unlikely]] {
            return 0;
        }
    }

    // Sleep, paralysis and flinching must be checked for before confusion!
    // "Being unable to attack for other reasons"
    // also must return before the confusion check!

    if (attacker.get_status_value(StatusWithStage::Confused) > 0) {
        if (policy_container.roll_for_self_hit(50)) {
            hit_from_confusion(
                policy_container,
                attacker,
                who_attacker_is
            );
            attacker.decrement_status_value(StatusWithStage::Confused);
            return 0;
        }
        attacker.decrement_status_value(StatusWithStage::Confused);
    }

    // Moves should only be considered "executed" past this point!
    // =========================================================================

    if (!move_does_nothing(battle_state, move, who_attacker_is)) {
        attacker.decrement_power_point(move->move);
        return 0;
    }

    if (move->move == Move::Struggle) {
        return execute_struggle(
            policy_container,
            battle_state,
            attacker,
            defender,
            who_attacker_is
        );
    }

    const Weather weather = battle_state.weather;
    uint16_t damage = 0;
    if (move->move == Move::Moonlight) [[unlikely]] {
        execute_moonlight(attacker, weather);
    } else if (move_has_flag(move->move, MoveFlag::HAS_POWER)) {
        damage = execute_power_move(
            policy_container,
            battle_state,
            attacker,
            defender,
            move,
            who_attacker_is
        );
    }

    const Who who_defender_is =
        who_attacker_is == Who::Player
            ? Who::Opponent
            : Who::Player;
    if (move_has_flag(move->move, MoveFlag::CONFUSES_DEFENDER_10)) [[unlikely]
    ] {
        roll_confusion(
            policy_container,
            defender,
            who_defender_is,
            10
        );
    }
    if (move_has_flag(move->move, MoveFlag::FREEZES_DEFENDER_10)) [[unlikely]] {
        roll_freeze(policy_container, weather, defender, 10);
    }

    if (move_has_flag(move->move, MoveFlag::PARALYZES_DEFENDER_10)) [[unlikely]] {
        roll_paralysis(policy_container, defender, 10);
    }

    if (move_has_flag(
        move->move,
        MoveFlag::LOWERS_DEFENDER_SPECIAL_ATTACK_ONE_STAGE_50)) [[unlikely]] {
        roll_stat_drop(
            policy_container,
            defender,
            who_defender_is,
            Stat::SpecialAttack,
            1,
            50
        );
    }

    if (move_has_flag(
            move->move,
            MoveFlag::LOWERS_DEFENDER_SPECIAL_DEFENSE_ONE_STAGE_10)
    ) [[unlikely]] {
        roll_stat_drop(
            policy_container,
            defender,
            who_defender_is,
            Stat::SpecialDefense,
            1,
            10
        );
    }

    if (damage > 0 &&
        move->type == PokemonType::Fire &&
        defender.get_current_status_condition() == StatusCondition::Freeze
    ) [[unlikely]] {
        defender.clear_status_condition();
    }

    attacker.decrement_power_point(move->move);
    return damage;
}

#endif //GEN_IV_BATTLE_FRONTIER_ANALYZER_MOVE_EXECUTION_H
