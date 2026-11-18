//
// Created by stguable on 2026/10/28.
//

#ifndef CCPP2026_EVALUATOR_H
#define CCPP2026_EVALUATOR_H
#include "patterns_table_mgr.h"

typedef struct Pattern {
    int pattern_type;
    int stone_pos[6][2];
}Pattern;

Pattern find_basic_pattern(const Table * table, const int * board, int stone_type, int x, int y, int direction);

int evaluate(const Table * table, const int * board);

int find_basic_patterns(const Table * table, const int * board, int target_color, Pattern * results);

#endif //CCPP2026_EVALUATOR_H
