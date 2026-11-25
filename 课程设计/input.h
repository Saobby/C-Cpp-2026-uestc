//
// Created by stguable on 2026/11/25.
//

#ifndef CCPP2026_INPUT_H
#define CCPP2026_INPUT_H

// input_read_line 返回值
#define INPUT_LINE_OK  0
#define INPUT_LINE_EOF (-1)

typedef enum InputResult {
    INPUT_OK = 0,   // 成功
    INPUT_QUIT,     // 用户退出
    INPUT_EOF,      // 输入结束
} InputResult;

int input_read_line(char * buf, int size);

int input_parse_pos(const char * line, int * x, int * y);

InputResult input_ask_move(int * x, int * y, const int * board);

#endif //CCPP2026_INPUT_H
