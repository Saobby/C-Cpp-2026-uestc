//
// Created by stguable on 2026/11/25.
//

#include "input.h"

#include <stdio.h>
#include <string.h>

#include "game_engine.h"

// 跳过空白字符
static const char * skip_space(const char * p) {
    while (*p == ' ' || *p == '\t' || *p == '\r') {
        p++;
    }
    return p;
}

int input_read_line(char * buf, const int size) {
    if (fgets(buf, size, stdin) == NULL) {
        return INPUT_LINE_EOF;
    }
    if (strchr(buf, '\n') == NULL) {
        // 行太长，丢掉剩余字符
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
        }
    }
    buf[strcspn(buf, "\r\n")] = '\0';  // 兼容 \r\n
    return INPUT_LINE_OK;
}

int input_parse_pos(const char * line, int * x, int * y) {
    const char * p = skip_space(line);
    const char x_ch = *p;
    if (x_ch == '\0') {
        return -1;
    }
    p = skip_space(p + 1);
    if (*p != ',') {
        return -1;
    }
    p = skip_space(p + 1);
    const char y_ch = *p;
    if (y_ch == '\0') {
        return -1;
    }
    p = skip_space(p + 1);
    if (*p != '\0') {
        return -1;
    }
    const int x_idx = char2idx(x_ch);
    const int y_idx = char2idx(y_ch);
    if (x_idx == -1 || y_idx == -1) {
        return -1;
    }
    *x = x_idx;
    *y = y_idx;
    return 0;
}

InputResult input_ask_move(int * x, int * y, const int * board) {
    while (1) {
        printf("请输入落子位置，比如1,2(A-E表示10-14,q退出):");
        fflush(stdout);
        char line[32];
        if (input_read_line(line, sizeof(line)) != INPUT_LINE_OK) {
            return INPUT_EOF;
        }
        const char * p = skip_space(line);
        if (*p == 'q' || *p == 'Q') {
            return INPUT_QUIT;
        }
        if (input_parse_pos(line, x, y) != 0) {
            printf("请输入有效的位置!\n");
            continue;
        }
        if (is_occupied(board, *x, *y)) {
            printf("这个位置已经有棋子了!\n");
            continue;
        }
        return INPUT_OK;
    }
}
