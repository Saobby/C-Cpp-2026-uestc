//
// Created by stguable on 2026/10/28.
//

#include <stdio.h>
#include "decider.h"
#include "game_engine.h"

static int board[15 * 15] = {0};

int main() {

    move(board, 7, 7, 1);
    const Pos pos = search(board, -1);
    printf("pos = (%d, %d)", pos.x, pos.y);

    return 0;
}
