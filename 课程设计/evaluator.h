//
// Created by stguable on 2026/10/28.
//

#ifndef CCPP2026_EVALUATOR_H
#define CCPP2026_EVALUATOR_H
#include "pattern_map.h"
#include "game_engine.h"

typedef struct FindBasicPatternResult {
    int pattern_type;
    int stone_pos[5][2];
}FindBasicPatternResult;

typedef struct State {
    int * board;
    PatternMap * pattern_map;
    // score: 正数表示黑棋优势，负数表示白棋优势
    int basic_score;
    int bonus_score;
}State;

int is_sub_array(const int * big_array, int big_len, const int * small_array, int small_len);

FindBasicPatternResult find_basic_pattern(const int * board, int stone_type, int x, int y, int direction);

State * create_state(int * board, PatternMap * pattern_map, int basic_score, int bonus_score);

int calc_delta(const int * board, int x, int y);

int move_and_update_state(State * state, int x, int y, int color);

int reverse_color(int color);

#endif //CCPP2026_EVALUATOR_H
