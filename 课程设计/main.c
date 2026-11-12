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
    move(board, 7, 6, 1);
    move(board, 6, 6, 1);
    move(board, 6, 7, 1);
    // const Pos pos = search(board, -1);
    // printf("pos = (%d, %d)", pos.x, pos.y);
    // Pos moves[15*15];
    // generate_moves(board, -1, moves);
    // Pattern pattern = find_basic_pattern(board, 1, 7, 7, 1);
    int score = evaluate(board);

    return 0;
}
