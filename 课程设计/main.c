//
// Created by stguable on 2026/10/28.
//

#include <stdio.h>
#include "decider.h"
#include "game_engine.h"
#include "evaluator.h"

static int board[15 * 15] = {0};

int main() {

    move(board, 7, 7, 1);
    move(board, 7, 5, -1);
    // move(board, 7, 3, 1);
    // move(board, 7, 1, -1);
    // move(board, 6, 0, 1);
    const Pos pos = search(board, 1);
    printf("pos = (%d, %d)\n", pos.x, pos.y);

    return 0;
}
