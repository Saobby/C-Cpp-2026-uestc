//
// Created by stguable on 2026/10/28.
//

#include "game_engine.h"

#include <stdio.h>

// 棋盘数组: int[15*15], 0: 空  1: 黑  -1: 白


int count(const int * board, const int x, const int y, const int dir_x, const int dir_y) {
    int count = 0;
    int curr_x = x + dir_x;
    int curr_y = y + dir_y;
    int idx = curr_y * 15 + curr_x;
    while (curr_x >= 0 && curr_x <= 14 && curr_y >= 0 && curr_y <= 14 && board[idx] == board[y * 15 + x]) {
        count++;
        curr_x += dir_x;
        curr_y += dir_y;
        idx = curr_y * 15 + curr_x;
    }
    return count;
}


int move(int * board, const int x, const int y, const int color) {
    // 返回值: -1: 非法落子  0: 成功,游戏继续  1: 黑胜  2: 白胜
    const int win_val = color == 1 ? 1: 2;
    const int idx = y * 15 + x;
    if (board[idx] != 0) {
        return -1;
    }
    board[idx] = color;
    // 检查胜利
    // 纵向
    const int up_count = count(board, x, y, 0, -1);
    const int down_count = count(board, x, y, 0, 1);
    const int total1 = up_count + down_count + 1;
    if (total1 >= 5) {
        return win_val;
    }
    // 横向
    const int left_count = count(board, x, y, -1, 0);
    const int right_count = count(board, x, y, 1, 0);
    const int total2 = left_count + right_count + 1;
    if (total2 >= 5) {
        return win_val;
    }
    // 主对角线
    const int left_up_count = count(board, x, y, -1, -1);
    const int right_down_count = count(board, x, y, 1, 1);
    const int total3 = left_up_count + right_down_count + 1;
    if (total3 >= 5) {
        return win_val;
    }
    // 副对角线
    const int right_up_count = count(board, x, y, 1, -1);
    const int left_down_count = count(board, x, y, -1, 1);
    const int total4 = right_up_count + left_down_count + 1;
    if (total4 >= 5) {
        return win_val;
    }
    return 0;
}

void print_board(const int * board) {
    for (int y = 0; y < 15; y++) {
        for (int x = 0; x < 15; x++) {
            const int idx = y * 15 + x;
            if (board[idx] == 1) {
                printf("X ");
            } else if (board[idx] == -1) {
                printf("O ");
            } else {
                printf("+ ");
            }
        }
        printf("\n");
    }
    printf("\n");
}
