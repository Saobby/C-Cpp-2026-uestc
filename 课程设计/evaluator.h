//
// Created by stguable on 2026/10/28.
//

#ifndef CCPP2026_EVALUATOR_H
#define CCPP2026_EVALUATOR_H

typedef struct FindBasicPatternResult {
    int pattern_type;
    int stone_pos[5][2];
}FindBasicPatternResult;

int is_sub_array(const int * big_array, int big_len, const int * small_array, int small_len);

FindBasicPatternResult find_basic_pattern(const int * board, int x, int y, int direction);


#endif //CCPP2026_EVALUATOR_H
