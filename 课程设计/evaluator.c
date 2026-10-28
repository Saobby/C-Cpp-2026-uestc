//
// Created by stguable on 2026/10/28.
//

#include "evaluator.h"

#include <stdlib.h>

#include "stack.h"

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

FindBasicPatternResult find_basic_pattern(const int * board, const int x, const int y, const int direction) {
    // 在给定方向，以给定中心，寻找基本模式
    // 模式类型:
    // 0: 未找到  1: 活4  2: 跳3  3: 连5  4: 冲4  5: 活3  6: 活2

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
    while (curr_x >= 0 && curr_x <= 14 && curr_y >= 0 && curr_y <= 14 && board[idx] != board[y * 15 + x] && blank_count < 2) {
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
    while (curr_x >= 0 && curr_x <= 14 && curr_y >= 0 && curr_y <= 14 && board[idx] != board[y * 15 + x] && blank_count < 2) {
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

// TODO: 实现更新棋盘状态功能：落子后寻找落子位置的基本模式，如果有，检查新模式中包含的棋子是否包含旧模式，如果是就删除旧模式，保留新模式
// TODO: 实现一个可以根据模式中索引最小的棋子O(1)查询出整个模式的数据结构
