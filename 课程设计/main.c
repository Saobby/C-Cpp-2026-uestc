//
// Created by stguable on 2026/10/28.
//

#include <stdio.h>
#include "decider.h"
#include "game_engine.h"
#include "patterns_table_mgr.h"

static int board[15 * 15] = {0};

int main() {
    // save_patterns_table();
    Table table;
    load_patterns_table(&table);

    move(board, 7, 7, 1);
    print_board(board);
    while (1) {
        int x;
        int y;
        while (1) {
            printf("请输入落子位置，比如1,2:");
            char x_idx;
            char y_idx;
            scanf(" %c,%c", &x_idx, &y_idx);
            x = char2idx(x_idx);
            y = char2idx(y_idx);
            if (x != -1 && y != -1) {
                break;
            }
            printf("请输入有效的位置!\n");
        }
        const int rsp = move(board, x, y, -1);
        if (rsp == 2) {
            printf("你赢了!你赢了!你赢了!你赢了!你赢了!你赢了!你赢了!\n");
            return 0;
        }
        const Pos pos = search(&table, board, 1);
        const int rsp2 = move(board, pos.x, pos.y, 1);
        print_board(board);
        printf("AI落子在了%c,%c!\n", idx_char_table[pos.x], idx_char_table[pos.y]);
        if (rsp2 == 1) {
            printf("哦不!你输了!\n");
            return 0;
        }
    }
}
