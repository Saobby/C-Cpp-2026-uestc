//
// Created by stguable on 2026/10/28.
//

#include <stdio.h>
#include "decider.h"
#include "game_engine.h"
#include "patterns_table_mgr.h"

static int board[15 * 15] = {0};

int main() {

    save_patterns_table();

    move(board, 7, 7, 1);
    move(board, 7, 5, -1);
    const Pos pos = search(board, 1);
    printf("pos = (%d, %d)\n", pos.x, pos.y);

    return 0;
}
