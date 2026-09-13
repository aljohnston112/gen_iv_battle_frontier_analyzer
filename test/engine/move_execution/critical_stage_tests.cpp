#include "move_execution.h"
#include "../mocks.h"

#include "gtest/gtest.h"

TEST(MoveExecution, StoneEdgeHasIncreasedCriticalHitChance) {
    EXPECT_EQ(
        1u,
        get_crit_stage_for_attacker(PokemonState{&Regirock_7_3}, Move::StoneEdge)
    );
}