#ifndef GEN_IV_BATTLE_FRONTIER_ANALYZER_MOVE_EXECUTION_H
#define GEN_IV_BATTLE_FRONTIER_ANALYZER_MOVE_EXECUTION_H

#include "battle_state.h"
#include "item.h"
#include "policies.h"

// TODO tests
// Smeargle, sketch a low PP move, get a life orb, and test struggle damage with and without the life orb
// Same with metronome

// Get Pickachu confused, test hit damage with and without Light Ball
// Get Cubone/Marowak confused, test hit damage with and without Thick Club

// TODO
// A frozen Sky Forme Shaymin will revert to its Land Forme.

inline std::array<int16_t, LEVEL + 1> DAMAGE_CACHE = [] {
    std::array<int16_t, LEVEL + 1> array{};
    array.fill(-1);
    return array;
}();


inline uint8_t get_crit_stage_for_attacker(
    const PokemonState& attacker,
    const Move move
) {
    uint8_t crit_modifier_addition = 0;
    if (move == Move::StoneEdge) {
        crit_modifier_addition++;
    }
    return attacker.get_status_stage(StatusWithStage::CritChanceModifier) +
        crit_modifier_addition;
}

template <typename... Policies>
uint16_t get_damage_of_move(
    const PolicyContainer<Policies...>& policy_container,
    const BattleState& battle_state,
    const MoveInfo* move_info,
    const Who who_attacker_is
) {
    if (move_info->category == Category::STATUS) {
        return 0;
    }

    // NOTE: If you add a new damage modifier here,
    // check if it should apply to hit_from_confusion or struggle.

    const bool is_player_attacker = who_attacker_is == Who::Player;
    const PokemonState& attacker =
        is_player_attacker
            ? battle_state.player
            : battle_state.opponent;
    const PokemonState& defender =
        is_player_attacker
            ? battle_state.opponent
            : battle_state.player;
    const Move move = move_info->move;
    const Ability defender_ability = defender.get_current_ability();
    if (defender_ability == Ability::FlashFire &&
        move_info->type == PokemonType::Fire
    ) [[unlikely]] {
        return 0;
    }

    const uint8_t attacker_level = attacker.level;
    int32_t damage = DAMAGE_CACHE[attacker_level];
    if (damage < 0) [[unlikely]] {
        damage = 2 * attacker_level / 5 + 2;
        DAMAGE_CACHE[attacker_level] = static_cast<int16_t>(damage);
    }

    uint16_t power = move_info->power;
    if (attacker.get_current_item_for_effect() == Item::WiseGlasses &&
        move_info->category == Category::SPECIAL) [[unlikely]
    ] {
        power = power + (power / 10);
    }

    const bool is_special = move_info->category == Category::SPECIAL;
    const Stat attack_category =
        is_special ? Stat::SpecialAttack : Stat::Attack;
    const Stat defense_category = is_special
                                      ? Stat::SpecialDefense
                                      : Stat::Defense;

    const Ability attacker_ability = attacker.get_current_ability();

    const uint8_t crit_stage = get_crit_stage_for_attacker(attacker, move);
    const bool is_crit =
        move != Move::FutureSight && move != Move::DoomDesire &&
        defender_ability != Ability::BattleArmor && defender_ability !=
        Ability::ShellArmor &&
        !defender.has_status_with_stage(StatusWithStage::LuckyChanted) &&
        policy_container.roll_for_crit(
            calculate_crit_chance_based_on_stage(crit_stage)
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
        ((is_special && defender.has_status_with_stage(
                StatusWithStage::LightScreening))
            || (!is_special && defender.
                has_status_with_stage(StatusWithStage::Reflecting))))
        ? 2
        : 1;
    const uint8_t burn =
        attacker.has_status_condition(StatusCondition::Burn) &&
        !is_special &&
        defender_ability != Ability::Guts
            ? 2
            : 1;
    damage = damage / 50 / burn / screen;

    const PokemonType move_type = move_info->type;
    const Weather weather = battle_state.get_weather();
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
            attacker.get_move_status_stage(
                MoveStatusWithStage::MetronomeActive
            );
        n > 0
    ) {
        damage = (damage * 10 + damage * n) / 10;
    }
    if (attacker.has_status(Status::StoleMoveByMeFirst)) [[unlikely]] {
        damage = damage * 3 / 2;
    }
    const uint8_t random =
        move == Move::SpitUp
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
    if (move != Move::Struggle &&
        move != Move::FutureSight &&
        move != Move::BeatUp &&
        move != Move::DoomDesire
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
        DAMAGE_REDUCING_BERRIES.at(defender_item) == move_info->type
    ) [[unlikely]] {
        damage = damage / 2;
    }

    if (effectiveness != 0) {
        damage = std::max(1, damage);
    }
    return static_cast<uint16_t>(damage);
}

template <typename... Policies>
uint16_t execute_power_move(
    const PolicyContainer<Policies...>& policy_container,
    BattleState& battle_state,
    const MoveInfo* move,
    const Who who_attacker_is
) {
    const bool is_player_attacker = who_attacker_is == Who::Player;
    PokemonState& defender =
        is_player_attacker
            ? battle_state.opponent
            : battle_state.player;
    const auto defender_item = defender.get_current_item_for_effect();
    if (DAMAGE_REDUCING_BERRIES.contains(defender_item) &&
        DAMAGE_REDUCING_BERRIES.at(defender_item) == move->type
    ) [[unlikely]] {
        defender.clear_current_item();
    }

    const uint16_t hp_before = defender.get_current_stat(Stat::Health);
    defender.add_damage(
        get_damage_of_move(
            policy_container,
            battle_state,
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
    // TODO Attack possibly boosted by Thick Club or Light Ball; but do they?

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
void roll_sleep(
    const PolicyContainer<Policies...>& policy_container,
    PokemonState& defender,
    const Who who,
    const int8_t chance
) {
    if (policy_container.roll_for_sleep(chance)) {
        // 1 to 4 since the game decrements before acting,
        // but this engine decrements after the sleep check
        defender.set_sleep(policy_container.roll_turns_asleep(who));
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
        defender.try_set_status_condition(StatusCondition::Freeze);
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
        defender.try_set_status_condition(StatusCondition::Paralysis);
    }
}

template <typename... Policies>
void roll_burn(
    const PolicyContainer<Policies...>& policy_container,
    PokemonState& defender,
    const int8_t chance,
    Who who_defender_is
) {
    if (defender.get_current_ability() != Ability::MagicGuard &&
        policy_container.roll_for_burn(chance, who_defender_is)
    ) {
        defender.try_set_status_condition(StatusCondition::Burn);
    }
}

inline bool move_always_hits(
    const BattleState& battle_state,
    [[maybe_unused]] const Who who_attacker_is,
    const Move move
) {
    if (move == Move::Blizzard &&
        battle_state.has_weather(Weather::Hail)
    )[[unlikely]] {
        return true;
    }
    return false;
}

template <typename... Policies>
bool move_does_nothing(
    const PolicyContainer<Policies...>& policy_container,
    const BattleState& battle_state,
    const MoveInfo* attacker_move_info,
    const Who who_attacker_is
) {
    const bool is_player_attacker = who_attacker_is == Who::Player;
    const auto move_type = attacker_move_info->type;
    const PokemonState* attacker_state =
        is_player_attacker
            ? &battle_state.player
            : &battle_state.opponent;
    const PokemonState* defender_state =
        is_player_attacker
            ? &battle_state.opponent
            : &battle_state.player;

    if (policy_container.does_move_miss_due_to_accuracy_and_evasion(
            battle_state,
            attacker_move_info,
            who_attacker_is
        )
        &&
        !move_always_hits(
            battle_state,
            who_attacker_is,
            attacker_move_info->move
        )
    ) {
        return true;
    }

    if (get_effectiveness(defender_state->get_types(), move_type) == 0) {
        return true;
    }

    if (attacker_move_info->move == Move::Blizzard &&
        battle_state.has_weather(Weather::Hail) &&
        defender_state->is_semi_invulnerable()
    ) [[unlikely]] {
        return true;
    }

    const Ability defender_ability = defender_state->get_current_ability();
    if (defender_ability == Ability::Levitate &&
        move_type == PokemonType::Ground
    ) [[unlikely]] {
        return true;
    }

    if (attacker_move_info->move == Move::Rest &&
        (attacker_state->has_status_with_stage(StatusWithStage::Asleep) ||
            attacker_state->get_current_stat(Stat::Health) ==
            attacker_state->get_original_stat(Stat::Health))) {
        return true;
    }

    return false;
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
        !defender.has_status_with_stage(StatusWithStage::LuckyChanted) &&
        policy_container.roll_for_crit(
            calculate_crit_chance_based_on_stage(
                attacker.get_status_stage(StatusWithStage::CritChanceModifier)
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
    (!is_crit && defender.
        has_status_with_stage(StatusWithStage::Reflecting))
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
            attacker.get_move_status_stage(MoveStatusWithStage::MetronomeActive)
        ;
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

template <Stat stat, typename... Policies>
void roll_stat_drop(
    const PolicyContainer<Policies...>& policy_container,
    PokemonState& state,
    const Who whose_stat_dropped,
    const int8_t stage_diff,
    const uint8_t probability,
    const StatDropSource source
) {
    if (policy_container.roll_stat_drop(probability, whose_stat_dropped)) {
        state.decrease_stat_stage<stat>(stage_diff, source);
    }
}

template <typename... Policies>
void roll_flinch(
    const PolicyContainer<Policies...>& policy_container,
    PokemonState& state,
    const uint8_t probability
) {
    if (policy_container.roll_for_flinch(probability)) {
        state.set_status(Status::Flinched);
    }
}

template <typename... Policies>
uint16_t execute_move(
    const PolicyContainer<Policies...>& policy_container,
    BattleState& battle_state,
    const Who who_attacker_is,
    const Move attacker_move
) {
    const MoveInfo* attacker_move_info = get_move_info(attacker_move);
    if (attacker_move == Move::MoveCount) [[unlikely]] {
        throw std::runtime_error("Unable to execute no move");
    }

    const bool is_player_attacker = who_attacker_is == Who::Player;
    PokemonState& attacker =
        is_player_attacker
            ? battle_state.player
            : battle_state.opponent;
    if (attacker.get_current_stat(Stat::Health) <= 0) {
        return 0;
    }

    PokemonState& defender =
        is_player_attacker
            ? battle_state.opponent
            : battle_state.player;
    if (defender.get_current_stat(Stat::Health) <= 0) {
        return 0;
    }
    const Ability defender_ability = defender.get_current_ability();

    if (attacker.has_status(Status::Flinched)) {
        attacker.clear_status(Status::Flinched);
        return 0;
    }

    if (attacker.get_current_status_condition() ==
        StatusCondition::Freeze
    ) [[unlikely]] {
        if (policy_container.roll_for_thaw(20) ||
            attacker_move == Move::FlameWheel ||
            attacker_move == Move::FlareBlitz ||
            attacker_move == Move::SacredFire
        ) [[unlikely]] {
            attacker.clear_status_condition();
        } else {
            return 0;
        }
    }

    if (attacker.has_status_with_stage(StatusWithStage::Asleep))
    [[unlikely]] {
        return 0;
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

    if (attacker.get_status_stage(StatusWithStage::Confused) > 0) {
        if (policy_container.roll_for_self_hit(50)) {
            hit_from_confusion(
                policy_container,
                attacker,
                who_attacker_is
            );
            return 0;
        }
    }

    if (attacker_move == Move::Curse) {
        if (attacker.has_type(PokemonType::Ghost)) {
            if (!defender.is_semi_invulnerable()) {
                attacker.add_damage(
                    attacker.get_original_stat(Stat::Health) / 2
                );
                defender.set_status(Status::Cursed);
            }
        } else {
            attacker.increase_stat_stage<Stat::Attack>(1);
            attacker.increase_stat_stage<Stat::Defense>(1);
            attacker.decrease_stat_stage<Stat::Speed>(
                1,
                StatDropSource::Self
            );
        }
    }

    // Moves should only be considered "executed" past this point!
    // =========================================================================
    bool pressure_active = false;
    if (defender_ability == Ability::Pressure &&
        !(move_has_flag(attacker_move, MoveFlag::TARGETS_SELF) ||
            (!attacker.has_type(PokemonType::Ghost) &&
                attacker_move == Move::Curse))
    ) {
        pressure_active = true;
    }

    if (move_does_nothing(
            policy_container,
            battle_state,
            attacker_move_info,
            who_attacker_is
        )
    ) {
        attacker.decrement_power_point(attacker_move, pressure_active);
        return 0;
    }

    if (attacker_move == Move::Struggle) {
        return execute_struggle(
            policy_container,
            battle_state,
            attacker,
            defender,
            who_attacker_is
        );
    }

    const auto attacker_item = attacker.get_current_item_for_effect();
    if (attacker_move == Move::Hail) {
        uint8_t turns = 5;
        if (attacker_item == Item::IcyRock) {
            turns = 8;
        }
        battle_state.set_weather(Weather::Hail, turns);
    }

    if (attacker_move == Move::Rest) {
        const auto attacker_ability = attacker.get_current_ability();
        if (attacker.has_status_with_stage(StatusWithStage::HealBlocked)) {
            bool use_struggle = true;
            for (const auto move :
                 attacker.get_moves(
                     policy_container.can_use_less_accurate_moves(
                         who_attacker_is
                     )
                 )
            ) {
                if (move != Move::Rest &&
                    attacker.has_power_points(move)
                ) {
                    use_struggle = false;
                }
            }
            if (use_struggle) {
                return execute_struggle(
                    policy_container,
                    battle_state,
                    attacker,
                    defender,
                    who_attacker_is
                );
            }
            attacker.decrement_power_point(attacker_move, pressure_active);
            return 0;
        }

        if (attacker.get_current_stat(Stat::Health) ==
            attacker.get_original_stat(Stat::Health) ||
            attacker_ability == Ability::Insomnia ||
            attacker_ability == Ability::VitalSpirit ||
            (attacker_ability != Ability::Soundproof &&
                battle_state.has_field_status(FieldStatus::UproarActive))
        ) {
            attacker.decrement_power_point(attacker_move, pressure_active);
            return 0;
        }

        // Rest is usable
        attacker.add_hp(attacker.get_original_stat(Stat::Health));
        const StatusCondition status_condition =
            attacker.get_current_status_condition();
        if (status_condition == StatusCondition::PoisonStatus ||
            status_condition == StatusCondition::BadlyPoisoned ||
            status_condition == StatusCondition::Paralysis ||
            status_condition == StatusCondition::Burn
        ) {
            attacker.clear_status_condition();
        }

        if (attacker_ability == Ability::EarlyBird)
        [[unlikely]] {
            attacker.set_sleep(1);
        } else {
            attacker.set_sleep(2);
        }
        attacker.decrement_power_point(attacker_move, pressure_active);
        return 0;
    }


    const Weather weather = battle_state.get_weather();
    uint16_t damage = 0;
    if (attacker_move == Move::Moonlight) [[unlikely]] {
        execute_moonlight(attacker, weather);
    } else if (move_has_flag(attacker_move, MoveFlag::HAS_POWER)) {
        damage = execute_power_move(
            policy_container,
            battle_state,
            attacker_move_info,
            who_attacker_is
        );
    }

    const Who who_defender_is =
        who_attacker_is == Who::Player
            ? Who::Opponent
            : Who::Player;
    if (move_has_flag(attacker_move, MoveFlag::CONFUSES_DEFENDER_10)) [[unlikely
        ]
    ] {
        roll_confusion(
            policy_container,
            defender,
            who_defender_is,
            10
        );
    }
    if (move_has_flag(attacker_move, MoveFlag::FREEZES_DEFENDER_10)) [[unlikely]
    ] {
        roll_freeze(policy_container, weather, defender, 10);
    }

    if (move_has_flag(attacker_move, MoveFlag::PARALYZES_DEFENDER_10))
    [[unlikely]] {
        roll_paralysis(policy_container, defender, 10);
    }

    if (move_has_flag(attacker_move, MoveFlag::BURNS_DEFENDER_10)) [[unlikely]
    ] {
        roll_burn(policy_container, defender, 10, who_defender_is);
    }

    if (move_has_flag(
            attacker_move,
            MoveFlag::OMNI_BOOSTS_ATTACKER)
    )[[unlikely]] {
        if (policy_container.roll_stat_increase(10, who_attacker_is)) {
            attacker.increase_stat_stage<Stat::Attack>(1);
            attacker.increase_stat_stage<Stat::Defense>(1);
            attacker.increase_stat_stage<Stat::SpecialAttack>(1);
            attacker.increase_stat_stage<Stat::SpecialDefense>(1);
            attacker.increase_stat_stage<Stat::Speed>(1);
        }
    }

    if (move_has_flag(
            attacker_move,
            MoveFlag::BOOSTS_ATTACKERS_SPECIAL_ATTACK_ONE_STAGE_70)
    )[[unlikely]] {
        if (policy_container.roll_stat_increase(70, who_attacker_is)) {
            attacker.increase_stat_stage<Stat::SpecialAttack>(1);
        }
    }

    if (move_has_flag(
            attacker_move,
            MoveFlag::LOWERS_ATTACKERS_SPEED_ONE_STAGE)
    )[[unlikely]] {
        attacker.decrease_stat_stage<Stat::Speed>(1, StatDropSource::Self);
    }

    if (move_has_flag(
            attacker_move,
            MoveFlag::LOWERS_ATTACKERS_SPECIAL_ATTACK_TWO_STAGES)
    ) [[unlikely]] {
        attacker.decrease_stat_stage<Stat::SpecialAttack>(
            2, StatDropSource::Self);
    }

    if (move_has_flag(
        attacker_move,
        MoveFlag::LOWERS_DEFENDER_SPECIAL_ATTACK_ONE_STAGE_50)) [[unlikely]] {
        roll_stat_drop<Stat::SpecialAttack, Policies...>(
            policy_container,
            defender,
            who_defender_is,
            1,
            50,
            StatDropSource::OtherMove
        );
    }

    if (move_has_flag(
            attacker_move,
            MoveFlag::LOWERS_DEFENDER_SPECIAL_DEFENSE_ONE_STAGE_10)
    ) [[unlikely]] {
        roll_stat_drop<Stat::SpecialDefense, Policies...>(
            policy_container,
            defender,
            who_defender_is,
            1,
            10,
            StatDropSource::OtherMove
        );
    }

    if (move_has_flag(
            attacker_move,
            MoveFlag::LOWERS_DEFENDER_SPECIAL_DEFENSE_ONE_STAGE_20)
    ) [[unlikely]] {
        roll_stat_drop<Stat::SpecialDefense, Policies...>(
            policy_container,
            defender,
            who_defender_is,
            1,
            20,
            StatDropSource::OtherMove
        );
    }

    if (defender.get_current_ability() == Ability::FlashFire &&
        attacker_move_info->type == PokemonType::Fire
    ) [[unlikely]] {
        defender.set_status(Status::FlashFired);
    }

    if (damage > 0 &&
        attacker_move_info->type == PokemonType::Fire &&
        defender.get_current_status_condition() == StatusCondition::Freeze
    ) [[unlikely]] {
        defender.clear_status_condition();
    }

    // TODO see test_todo.txt for missing flinch related features
    if (move_has_flag(attacker_move, MoveFlag::FLINCHES_DEFENDER_20) &&
        (defender_ability != Ability::InnerFocus &&
            defender_ability != Ability::ShieldDust)
    ) [[unlikely]] {
        roll_flinch(policy_container, defender, 20);
    }

    attacker.decrement_power_point(attacker_move, pressure_active);
    return damage;
}

#endif //GEN_IV_BATTLE_FRONTIER_ANALYZER_MOVE_EXECUTION_H
