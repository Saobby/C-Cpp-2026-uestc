//
// Created by stguable on 2026/11/11.
//

#include "decider.h"
#include "evaluator.h"

int generate_moves(const int * board, const int color, Pos * moves) {
    for (int i = 0; i < 15 * 15; i++) {
        moves[i] = (Pos){.x = -1, .y = -1};
    }
    int count = 0;
    int added_pos[15 * 15] = {0};
    // 能直接胜利的点最优先
    Pattern patterns[15 * 15];
    find_basic_patterns(board, color, patterns);
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
    Pattern patterns2[15 * 15];
    find_basic_patterns(board, -color, patterns2);
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
    return 0;
}


int negamax(int * board, const int depth, int alpha, const int beta, const int color) {
    if (depth == 0) {
        return color * evaluate(board);
    }
    int best_score = -2147483648;
    Pos moves[15 * 15];
    generate_moves(board, color, moves);
    for (int i = 0; i < 15 * 15; i++) {
        const Pos pos = moves[i];
        if (pos.x == -1 || pos.y == -1) {
            continue;
        }
        int score;
        const int rsp = move(board, pos.x, pos.y, color);
        if (rsp == 1 || rsp == 2) {
            score = color * evaluate(board);
        }else {
            score = -negamax(board, depth - 1, -beta, -alpha, -color);
        }
        unmove(board, pos.x, pos.y);
        if (score > best_score) {
            best_score = score;
        }
        if (score > alpha) {
            alpha = score;
        }
        if (alpha >= beta) {
            break;
        }
    }
    return best_score;
}


Pos search(int * board, const int color) {
    int best_score = -2147483648;
    Pos best_pos;
    best_pos.x = -1;
    best_pos.y = -1;
    Pos moves[15 * 15];
    generate_moves(board, color, moves);
    if (moves[0].x == -1 || moves[0].y == -1) {
        return moves[0];  // 错误，没有可落子点。
    }
    // 检查能否立马胜利
    const int rsp = move(board, moves[0].x, moves[0].y, color);
    unmove(board, moves[0].x, moves[0].y);
    if ((color == 1 && rsp == 1) || (color == -1 && rsp == 2)) {
        return moves[0];
    }
    for (int i = 0; i < 15 * 15; i++) {
        const Pos pos = moves[i];
        if (pos.x == -1 || pos.y == -1) {
            continue;
        }
        const int score = negamax(board, SEARCH_DEPTH, -2147483648, 2147483647, color);
        unmove(board, pos.x, pos.y);
        if (score > best_score) {
            best_score = score;
            best_pos = pos;
        }
    }
    return best_pos;
}
