//
// Created by stguable on 2026/11/11.
//

#include "decider.h"
#include "evaluator.h"

Pos * generate_moves(const int * board, const int color) {
    Pos moves[15 * 15] = {{.x = -1, .y = -1}};
    int count = 0;
    int added_pos[15 * 15] = {0};
    // 能直接胜利的点最优先
    const Pattern * patterns = find_basic_patterns(board, color);
    for (int i = 0; i < 15 * 15; i++) {
        const Pattern pattern = patterns[i];
        if (pattern.pattern_type == 1 || pattern.pattern_type == 4) {  // 活4️或冲4
            for (int j = 0; j < 6; j++) {
                const int pos_x = pattern.stone_pos[i][0];
                const int pos_y = pattern.stone_pos[i][1];
                const int idx = pos_y * 15 + pos_x;
                if (board[idx] == 0 && added_pos[idx] == 0) {
                    added_pos[idx] = 1;
                    moves[count].x = pos_x;
                    moves[count].y = pos_y;
                    count++;
                }
            }
        }
    }
    // 能防止对方立马获胜的点优先
    const Pattern * patterns2 = find_basic_patterns(board, -color);
    for (int i = 0; i < 15 * 15; i++) {
        const Pattern pattern = patterns2[i];
        if (pattern.pattern_type == 1 || pattern.pattern_type == 4) {  // 活4️或冲4
            for (int j = 0; j < 6; j++) {
                const int pos_x = pattern.stone_pos[i][0];
                const int pos_y = pattern.stone_pos[i][1];
                const int idx = pos_y * 15 + pos_x;
                if (board[idx] == 0 && added_pos[idx] == 0) {
                    added_pos[idx] = 1;
                    moves[count].x = pos_x;
                    moves[count].y = pos_y;
                    count++;
                }
            }
        }
    }
    // 能防止对方形成活4的点优先
    for (int i = 0; i < 15 * 15; i++) {
        const Pattern pattern = patterns2[i];
        if (pattern.pattern_type == 2 || pattern.pattern_type == 5) {  // 活4️或冲4
            for (int j = 0; j < 6; j++) {
                const int pos_x = pattern.stone_pos[i][0];
                const int pos_y = pattern.stone_pos[i][1];
                const int idx = pos_y * 15 + pos_x;
                if (board[idx] == 0 && added_pos[idx] == 0) {
                    added_pos[idx] = 1;
                    moves[count].x = pos_x;
                    moves[count].y = pos_y;
                    count++;
                }
            }
        }
    }
    // 添加剩余的点
    for (int y = 0; y < 15; y++) {
        for (int x = 0; x < 15; x++) {
            const int idx = y * 15 + x;
            if (board[idx] != 0) {
                //    .
                //   ...
                //  ..x..
                //   ...
                //    .
                const Pos dots[12] = {
                    {.x = 0, .y = -2},
                    {.x = -1, .y = -1},
                    {.x = 0, .y = -1},
                    {.x = 1, .y = -1},
                    {.x = -2, .y = 0},
                    {.x = -1, .y = 0},
                    {.x = 1, .y = 0},
                    {.x = 2, .y = 0},
                    {.x = -1, .y = 1},
                    {.x = 0, .y = 1},
                    {.x = 1, .y = 1},
                    {.x = 0, .y = 2}
                };
                for (int i = 0; i < 12; i++) {
                    const int dot_x = dots[i].x + x;
                    const int dot_y = dots[i].y + y;
                    const int pos_idx = dot_y * 15 + dot_x;
                    if (dot_x >= 0 && dot_x < 15 && dot_y >= 0 && dot_y < 15 && board[pos_idx] == 0 && added_pos[pos_idx] == 0) {
                        added_pos[pos_idx] = 1;
                        moves[count].x = dot_x;
                        moves[count].y = dot_y;
                        count++;
                    }
                }
            }
        }
    }
    return moves;
}
