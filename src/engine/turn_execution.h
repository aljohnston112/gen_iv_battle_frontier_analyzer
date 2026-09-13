#ifndef GEN_IV_BATTLE_FRONTIER_ANALYZER_TURN_EXECUTER_H
#define GEN_IV_BATTLE_FRONTIER_ANALYZER_TURN_EXECUTER_H

#include "end_of_turn_effects.h"
#include "move.h"
#include "policies.h"
#include "thread_pool.h"

template <typename... Policies>
Who who_goes_first(
    const PolicyContainer<Policies...>& policy_container,
    const BattleState& battle_state,
    [[maybe_unused]] const Move player_move,
    [[maybe_unused]] const Move opponent_move
) {
    const bool player_faster =
        policy_container.is_player_faster(battle_state);
    if (player_faster) {
        return Who::Player;
    } else {
        return Who::Opponent;
    }
}

template <typename... Policies, typename State>
TurnResult execute_turn(
    const PolicyContainer<Policies...>& policy_container,
    State&& battle_state,
    const Move player_move,
    const Move opponent_move
) {
    const bool player_goes_first =
        who_goes_first(
            policy_container,
            battle_state,
            player_move,
            opponent_move
        ) == Who::Player;
    const Who first = player_goes_first ? Who::Player : Who::Opponent;
    const Who second = player_goes_first ? Who::Opponent : Who::Player;
    const Move first_move =
        player_goes_first ? player_move : opponent_move;
    const Move second_move = player_goes_first
                                 ? opponent_move
                                 : player_move;

    const uint16_t first_move_damage =
        execute_move(
            policy_container,
            battle_state,
            first,
            first_move
        );

    uint16_t second_move_damage = 0;
    if (!battle_state.is_battle_over()) {
        second_move_damage =
            execute_move(
                policy_container,
                battle_state,
                second,
                second_move
            );
    }
    apply_end_of_turn(policy_container, battle_state);

    return TurnResult{
        .battle_state= std::forward<State>(battle_state),
        .player_move_used = player_move,
        .player_move_damage =
        player_goes_first ? first_move_damage : second_move_damage,
        .opponent_move_used = opponent_move,
        .opponent_move_damage =
        player_goes_first ? second_move_damage : first_move_damage,
    };
}


#endif //GEN_IV_BATTLE_FRONTIER_ANALYZER_TURN_EXECUTER_H
