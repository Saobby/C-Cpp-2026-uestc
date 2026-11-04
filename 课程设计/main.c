//
// Created by stguable on 2026/10/28.
//

#include <stdio.h>

#include "game_engine.h"
#include "pattern_map.h"
#include "evaluator.h"

static int board[15 * 15] = {0};
static PatternMap * pattern_map = NULL;
static State * state = NULL;

int main() {
    pattern_map = create_pattern_map();

    state = create_state(board, pattern_map, 0, 0);


    return 0;
}
