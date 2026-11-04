//
// Created by stguable on 2026/10/28.
//

#include "evaluator.h"

#include <stdlib.h>

#include "stack.h"

static const int pattern_scores[] = {
        0,  // 未找到
        (int)1e6,  // 活4
        (int)1e4,  // 跳3
        (int)1e8,  // 连5
        (int)1e5,  // 冲4
        (int)1e4,  // 活3
        (int)1e3   // 活2
};

static const int corr_multiplier = 10; // 如果落子一次同时出现了多个模式，则加分=多个模式分数之和*corr_multiplier

int is_sub_array(const int * big_array, const int big_len, const int * small_array, const int small_len) {
    for (int offset = 0; offset <= big_len - small_len; offset++) {
        for (int i = 0; i < small_len; i++) {
            if (big_array[offset + i] != small_array[i]) {
                return -1;
            }
        }
        return offset;
    }
    return -1;
}

FindBasicPatternResult find_basic_pattern(const int * board, const int stone_type, const int x, const int y, const int direction) {
    // 在给定方向，以给定中心，寻找基本模式
    // 模式类型:
    // 0: 未找到  1: 活4  2: 跳3  3: 连5  4: 冲4  5: 活3  6: 活2
    // stone_type: 1: 黑  -1: 白

    int dir_x;
    int dir_y;

    switch (direction) {
        case 1:  // 竖直
            dir_x = 0;
            dir_y = 1;
            break;
        case 2:  // 水平
            dir_x = 1;
            dir_y = 0;
            break;
        case 3:  // 主对角线
            dir_x = 1;
            dir_y = 1;
            break;
        case 4:  // 副对角线
            dir_x = -1;
            dir_y = 1;
            break;
        default:
            dir_x = 0;
            dir_y = 0;
            break;
    }

    // 生成待匹配的模式
    // 上半部分
    int curr_pattern[15] = {-1};  // -1: 未定义  0: 空格  1: 落子
    int curr_pattern_pos[15][2] = {{-1, -1}};  // 存储每个位置的坐标
    int curr_x = x;
    int curr_y = y;
    int blank_count = 0;
    int idx = curr_y * 15 + curr_x;
    Stack * half_pattern = create_stack(15);
    Stack * half_pattern_pos_x = create_stack(15);
    Stack * half_pattern_pos_y = create_stack(15);
    while (curr_x >= 0 && curr_x <= 14 && curr_y >= 0 && curr_y <= 14 && board[idx] != stone_type && blank_count < 2) {
        const int val = board[idx];
        if (val == 0) {
            push(half_pattern, 0);
            push(half_pattern_pos_x, curr_x);
            push(half_pattern_pos_y, curr_y);
            blank_count++;
        }else {
            push(half_pattern, 1);
            push(half_pattern_pos_x, curr_x);
            push(half_pattern_pos_y, curr_y);
            blank_count = 0;
        }
        curr_x -= dir_x;
        curr_y -= dir_y;
        idx = curr_y * 15 + curr_x;
    }
    int i = 0;
    while (1) {
        const int val = pop(half_pattern);
        const int pos_x = pop(half_pattern_pos_x);
        const int pos_y = pop(half_pattern_pos_y);
        if (val == -1) {
            break;
        }
        curr_pattern[i] = val;
        curr_pattern_pos[i][0] = pos_x;
        curr_pattern_pos[i][1] = pos_y;
        i++;
    }
    free(half_pattern);
    free(half_pattern_pos_x);
    free(half_pattern_pos_y);
    // 下半部分
    curr_x = x + dir_x;
    curr_y = y + dir_y;
    blank_count = 0;
    idx = curr_y * 15 + curr_x;
    while (curr_x >= 0 && curr_x <= 14 && curr_y >= 0 && curr_y <= 14 && board[idx] != stone_type && blank_count < 2) {
        const int val = board[idx];
        if (val == 0) {
            curr_pattern[i] = 0;
            blank_count++;
            curr_pattern_pos[i][0] = curr_x;
            curr_pattern_pos[i][1] = curr_y;
        }else {
            curr_pattern[i] = 1;
            curr_pattern_pos[i][0] = curr_x;
            curr_pattern_pos[i][1] = curr_y;
            blank_count = 0;
        }
        curr_x += dir_x;
        curr_y += dir_y;
        idx = curr_y * 15 + curr_x;
        i++;
    }

    // 进行匹配
    const int * patterns[] = {
        (int[]){0, 1, 1, 1, 1, 0},  // 活4
        (int[]){0, 1, 1, 0, 1, 0},  // 跳3正
        (int[]){0, 1, 0, 1, 1, 0},  // 跳3反
        (int[]){1, 1, 1, 1, 1},  // 连5
        (int[]){1, 1, 1, 1, 0},  // 冲4_1正
        (int[]){0, 1, 1, 1, 1},  // 冲4_1反
        (int[]){1, 1, 1, 0, 1},  // 冲4_2正
        (int[]){1, 0, 1, 1, 1},  // 冲4_2反
        (int[]){1, 1, 0, 1, 1},  // 冲4_3
        (int[]){0, 1, 1, 1, 0},  // 活3
        (int[]){0, 1, 1, 0, 0},   // 活2_正
        (int[]){0, 0, 1, 1, 0}   // 活2_反
    };
    const int patterns_len[] = {6, 6, 6, 5, 5, 5, 5, 5, 5, 5, 5, 5};
    const int patterns_type[] = {1, 2, 2, 3, 4, 4, 4, 4, 4, 5, 6, 6};
    for (int i = 0; i < 12; i++) {
        // 遍历所有模式
        const int * pattern = patterns[i];
        const int pattern_len = patterns_len[i];
        const int pattern_type = patterns_type[i];
        const int offset = is_sub_array(curr_pattern, 15, pattern, pattern_len);
        if (offset == -1) {
            continue;
        }
        FindBasicPatternResult result;
        result.pattern_type = pattern_type;
        for (int j = 0; j < pattern_len; j++) {
            result.stone_pos[j][0] = curr_pattern_pos[offset + j][0];
            result.stone_pos[j][1] = curr_pattern_pos[offset + j][1];
        }
        return result;
    }
    FindBasicPatternResult result;
    result.pattern_type = 0;
    return result;
}

State * create_state(int * board, PatternMap * pattern_map, const int basic_score, const int bonus_score) {
    State * state = malloc(sizeof(State));
    state->board = board;
    state->pattern_map = pattern_map;
    state->basic_score = basic_score;
    state->bonus_score = bonus_score;
    return state;
}

int reverse_color(const int color) {
    return color == 1 ? -1 : 1;
}

int calc_delta(const int * board, const int x, const int y) {
    int delta = 0;
    for (int i = 0; i < 2; i++) {
        const int target_colors[] = {-1, 1};
        const int target_color = target_colors[i];
        for (int direction = 1; direction <= 4; direction++) {
            const FindBasicPatternResult old_pattern = find_basic_pattern(board, target_color, x, y, direction);
            if (old_pattern.pattern_type == 0) {
                continue;
            }
            delta += target_color * pattern_scores[old_pattern.pattern_type];
        }
    }
    return delta;
}

int move_and_update_state(State * state, const int x, const int y, const int color) {
    if (state->board[y * 15 + x] != 0) {
        return -1;
    }
    state->basic_score -= calc_delta(state->board, x, y);
    move(state->board, x, y, color);
    state->basic_score += calc_delta(state->board, x, y);
    return 0;
}


// TODO: 实现更新棋盘状态功能：落子后寻找落子位置的基本模式，如果有，检查新模式中包含的棋子是否包含旧模式，如果是就删除旧模式，保留新模式
