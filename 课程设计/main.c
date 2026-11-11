//
// Created by stguable on 2026/10/28.
//

#include <stdio.h>
#include <stdlib.h>

#include "game_engine.h"
#include "evaluator.h"

static int board[15 * 15] = {0};
static State * state = NULL;

int main() {

    state = create_state(board, 0);

    move(board, 7, 7, 1);
    move(board, 7, 8, 1);
    move(board, 8, 7, 1);
    move(board, 8, 8, 1);
    printf("score: %d\n", evaluate(board));
    // move_and_update_state(state, 7, 7, 1);
    // printf("score: %d\n", state->score);
    // move_and_update_state(state, 7, 8, 1);
    // printf("score: %d\n", state->score);
    // move_and_update_state(state, 8, 7, 1);
    // printf("score: %d\n", state->score);
    // move_and_update_state(state, 8, 8, 1);
    // printf("score: %d\n", state->score);

    free(state);

    return 0;
}
