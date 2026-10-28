//
// Created by stguable on 2026/10/28.
//

#ifndef CCPP2026_GAME_ENGINE_H
#define CCPP2026_GAME_ENGINE_H

int count(const int * board, int x, int y, int dir_x, int dir_y);

int move(int * board, int x, int y, int color);

void print_board(const int * board);

#endif //CCPP2026_GAME_ENGINE_H
