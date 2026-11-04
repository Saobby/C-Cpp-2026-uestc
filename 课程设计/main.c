//
// Created by stguable on 2026/10/28.
//

#include <stdio.h>

#include "game_engine.h"
#include "evaluator.h"

static int board[15 * 15] = {0};
static State * state = NULL;

int main() {

    state = create_state(board, 0);



    return 0;
}
