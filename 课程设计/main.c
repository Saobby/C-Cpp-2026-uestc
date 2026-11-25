//
// Created by stguable on 2026/10/28.
//

#include <stdio.h>
#include "decider.h"
#include "game_engine.h"
#include "input.h"
#include "patterns_table_mgr.h"

static int board[15 * 15] = {0};

int main() {
    // save_patterns_table();
    Table table;
    if (load_patterns_table(&table) != 0) {
        gen_patterns_table(&table);  // 没有表文件就现场生成
    }

    move(board, 7, 7, 1);
    print_board(board);
    while (1) {
        int x = -1;
        int y = -1;
        const InputResult in = input_ask_move(&x, &y, board);
        if (in == INPUT_QUIT) {
            printf("程序正在退出!\n");
            return 0;
        }
        if (in == INPUT_EOF) {
            printf("\n输入结束了,程序正在退出!\n");
            return 0;
        }
        const int rsp = move(board, x, y, -1);
        if (rsp == 2) {
            print_board(board);
            printf("你赢了!你赢了!你赢了!你赢了!你赢了!你赢了!你赢了!\n");
            return 0;
        }
        const Pos pos = search(&table, board, 1);
        if (pos.x == -1 || pos.y == -1) {
            printf("棋盘满了!平局!平局!\n");
            return 0;
        }
        const int rsp2 = move(board, pos.x, pos.y, 1);
        print_board(board);
        printf("AI落子在了%c,%c!\n", idx_char_table[pos.x], idx_char_table[pos.y]);
        if (rsp2 == 1) {
            printf("哦不!你输了!\n");
            return 0;
        }
    }
}

