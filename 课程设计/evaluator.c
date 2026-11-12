//
// Created by stguable on 2026/10/28.
//

#include "evaluator.h"

#include <stdlib.h>
#include <math.h>

#include "stack.h"

static const int pattern_scores[] = {
        0,  // 未找到
        (int)1e6,  // 活4
        (int)1e4,  // 跳3
        (int)1e9,  // 连5
        (int)1e5,  // 冲4
        (int)1e4,  // 活3
        (int)1e3   // 活2
};

static const int corr_multiplier = 10; // 如果落子一次同时出现了多个模式，则加分=多个模式分数之和*corr_multiplier^(模式数-1)

int is_sub_array(const int * big_array, const int big_len, const int * small_array, const int small_len) {
    for (int offset = 0; offset <= big_len - small_len; offset++) {
        int ok = 1;
        for (int i = 0; i < small_len; i++) {
            if (big_array[offset + i] != small_array[i]) {
                ok = 0;
                break;
            }
        }
        if (ok == 1) {
            return offset;
        }
    }
    return -1;
}

Pattern find_basic_pattern(const int * board, const int stone_type, const int x, const int y, const int direction) {
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
    int curr_pattern[15]; // -1: 未定义  0: 空格  1: 落子
    for (int i = 0; i < 15; i++) {
        curr_pattern[i] = -1;
    }
    int curr_pattern_pos[15][2];  // 存储每个位置的坐标
    for (int i = 0; i < 15; i++) {
        curr_pattern_pos[i][0] = -1;
        curr_pattern_pos[i][1] = -1;
    }
    int curr_x = x;
    int curr_y = y;
    int blank_count = 0;
    int idx = curr_y * 15 + curr_x;
    Stack * half_pattern = create_stack(15);
    Stack * half_pattern_pos_x = create_stack(15);
    Stack * half_pattern_pos_y = create_stack(15);
    while (curr_x >= 0 && curr_x <= 14 && curr_y >= 0 && curr_y <= 14 && board[idx] != -stone_type && blank_count < 2) {
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
    while (curr_x >= 0 && curr_x <= 14 && curr_y >= 0 && curr_y <= 14 && board[idx] != -stone_type && blank_count < 2) {
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
        Pattern result;
        result.pattern_type = pattern_type;
        for (int j = 0; j < 6; j++) {
            result.stone_pos[j][0] = -1;
            result.stone_pos[j][1] = -1;
        }
        for (int j = 0; j < pattern_len; j++) {
            result.stone_pos[j][0] = curr_pattern_pos[offset + j][0];
            result.stone_pos[j][1] = curr_pattern_pos[offset + j][1];
        }
        return result;
    }
    Pattern result;
    result.pattern_type = 0;
    return result;
}

int evaluate(const int * board) {
    const int target_colors[] = {-1, 1};
    int checked_pos[2][15 * 15][4] = {0};  // 结构: [颜色][坐标索引][方向]，用于记录每个点在每个方向上是否已经检查过
    int checked_pos2[2][15 * 15] = {0};  // 同上
    int crossing_points[2][15 * 15][2];  // 结构: [颜色][交叉点索引][坐标]
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 15 * 15; j++) {
            crossing_points[i][j][0] = -1;
            crossing_points[i][j][1] = -1;
        }
    }
    int crossing_points_count[2] = {0};  // 结构: [颜色][交叉点数量]
    int score = 0;
    // 计算基础分并找出交叉点
    for (int i = 0; i < 2; i++) {
        const int target_color = target_colors[i];
        for (int y = 0; y < 15; y++) {
            for (int x = 0; x < 15; x++) {
                const int idx = y * 15 + x;
                if (board[idx] != target_color) {
                    continue;
                }
                for (int direction = 1; direction <= 4; direction++) {
                    if (checked_pos[i][idx][direction - 1]) {
                        continue;
                    }
                    const Pattern pattern = find_basic_pattern(board, target_color, x, y, direction);
                    if (pattern.pattern_type == 0) {
                        continue;
                    }
                    score += target_color * pattern_scores[pattern.pattern_type];  // 基础分
                    // 记录已检查过的方向和交叉点
                    for (int j = 0; j < 6; j++) {
                        const int pos_x = pattern.stone_pos[j][0];
                        const int pos_y = pattern.stone_pos[j][1];
                        if (pos_x == -1 || pos_y == -1) {
                            continue;
                        }
                        const int pos_idx = pos_y * 15 + pos_x;
                        // 记录已检查过的点的方向
                        checked_pos[i][pos_idx][direction - 1] = 1;
                        // 记录交叉点
                        if (checked_pos2[i][pos_idx]) {
                            // 交叉点
                            crossing_points[i][crossing_points_count[i]][0] = pos_x;
                            crossing_points[i][crossing_points_count[i]][1] = pos_y;
                            crossing_points_count[i]++;
                        } else {
                            checked_pos2[i][pos_idx] = 1;
                        }
                    }
                }
            }
        }
    }
    for (int i = 0; i < 2; i++) {
        const int target_color = target_colors[i];
        for (int j = 0; j < crossing_points_count[i]; j++) {
            int tmp_sum = 0;
            int pattern_count = 0;
            const int x = crossing_points[i][j][0];
            const int y = crossing_points[i][j][1];
            for (int direction = 1; direction <= 4; direction++) {
                const Pattern pattern = find_basic_pattern(board, target_color, x, y, direction);
                if (pattern.pattern_type == 0) {
                    continue;
                }
                tmp_sum += pattern_scores[pattern.pattern_type];
                pattern_count++;
            }
            score += target_color * tmp_sum * (int)pow(corr_multiplier, pattern_count-1);
        }
    }
    return score;
}


int find_basic_patterns(const int * board, const int target_color, Pattern * results) {
    for (int i = 0; i < 15 * 15; i++) {
        results[i] = (Pattern){.pattern_type = 0, .stone_pos = {{-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}}};
    }
    int count = 0;
    int checked_pos[15 * 15][4] = {0};  // 结构: [坐标索引][方向]，用于记录每个点在每个方向上是否已经检查过
    for (int y = 0; y < 15; y++) {
        for (int x = 0; x < 15; x++) {
            const int idx = y * 15 + x;
            if (board[idx] != target_color) {
                continue;
            }
            for (int direction = 1; direction <= 4; direction++) {
                if (checked_pos[idx][direction - 1]) {
                    continue;
                }
                const Pattern pattern = find_basic_pattern(board, target_color, x, y, direction);
                if (pattern.pattern_type == 0) {
                    continue;
                }
                results[count] = pattern;
                count++;
                // 记录已检查过的方向
                for (int j = 0; j < 6; j++) {
                    const int pos_x = pattern.stone_pos[j][0];
                    const int pos_y = pattern.stone_pos[j][1];
                    if (pos_x == -1 || pos_y == -1) {
                        continue;
                    }
                    const int pos_idx = pos_y * 15 + pos_x;
                    // 记录已检查过的点的方向
                    checked_pos[pos_idx][direction - 1] = 1;
                }
            }
        }
    }
    return 0;
}
