//
// Created by stguable on 2026/10/28.
//

#ifndef CCPP2026_EVALUATOR_H
#define CCPP2026_EVALUATOR_H
#include "game_engine.h"

typedef struct Pattern {
    int pattern_type;
    int stone_pos[6][2];
}Pattern;

int is_sub_array(const int * big_array, int big_len, const int * small_array, int small_len);

Pattern find_basic_pattern(const int * board, int stone_type, int x, int y, int direction);

int evaluate(const int * board);

int find_basic_patterns(const int * board, int target_color, Pattern * results);

#endif //CCPP2026_EVALUATOR_H
