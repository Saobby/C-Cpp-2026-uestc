//
// Created by stguable on 2026/10/28.
//

#ifndef CCPP2026_EVALUATOR_H
#define CCPP2026_EVALUATOR_H
#include "game_engine.h"

typedef struct FindBasicPatternResult {
    int pattern_type;
    int stone_pos[6][2];
}FindBasicPatternResult;

typedef struct State {
    int * board;
    int score;  // 正数表示黑棋优势，负数表示白棋优势
}State;

int is_sub_array(const int * big_array, int big_len, const int * small_array, int small_len);

FindBasicPatternResult find_basic_pattern(const int * board, int stone_type, int x, int y, int direction);

State * create_state(int * board, int score);

int move_and_update_state(State * state, int x, int y, int color);

int evaluate(const int * board);

#endif //CCPP2026_EVALUATOR_H
