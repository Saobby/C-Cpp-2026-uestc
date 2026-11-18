//
// Created by stguable on 2026/11/11.
//

#ifndef CCPP2026_DECIDER_H
#define CCPP2026_DECIDER_H

#define SEARCH_DEPTH 4
#include "patterns_table_mgr.h"

typedef struct Pos {
    int x;
    int y;
}Pos;

int generate_moves(const Table * table, const int * board, int color, Pos * moves);

int negamax(const Table * table, int * board, int depth, int alpha, int beta, int color);

Pos search(const Table * table, int * board, int color);

#endif //CCPP2026_DECIDER_H
