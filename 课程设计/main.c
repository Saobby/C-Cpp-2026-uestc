//
// Created by stguable on 2026/10/28.
//

#include <stdio.h>

#include "game_engine.h"

int board[15 * 15] = {0};

int main() {
    print_board(board);
    printf("Result: %d\n", move(board, 7, 7, 1));
    print_board(board);
    printf("Result: %d\n", move(board, 8, 8, -1));
    print_board(board);

    printf("Result: %d\n", move(board, 7, 8, 1));
    print_board(board);
    printf("Result: %d\n", move(board, 9, 9, -1));
    print_board(board);

    printf("Result: %d\n", move(board, 7, 9, 1));
    print_board(board);
    printf("Result: %d\n", move(board, 10, 10, -1));
    print_board(board);

    printf("Result: %d\n", move(board, 7, 10, 1));
    print_board(board);
    printf("Result: %d\n", move(board, 11, 11, -1));
    print_board(board);

    printf("Result: %d\n", move(board, 7, 11, 1));
    print_board(board);
    printf("Result: %d\n", move(board, 11, 10, -1));
    print_board(board);
    return 0;
}
