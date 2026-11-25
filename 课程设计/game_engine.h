//
// Created by stguable on 2026/10/28.
//

#ifndef CCPP2026_GAME_ENGINE_H
#define CCPP2026_GAME_ENGINE_H

static const char idx_char_table[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E'};

int count(const int * board, int x, int y, int dir_x, int dir_y);

int move(int * board, int x, int y, int color);

void print_board(const int * board);

int unmove(int * board, int x, int y);

int char2idx(char c);

#endif //CCPP2026_GAME_ENGINE_H
