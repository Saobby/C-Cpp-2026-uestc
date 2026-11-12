//
// Created by stguable on 2026/10/28.
//

#include "stack.h"

int init_stack(Stack * stack) {
    stack->size = 15;
    stack->count = 0;
    return 0;
}


int push(Stack * stack, const int val) {
    if (stack->count >= stack->size) {
        return 1;
    }
    stack->data[stack->count] = val;
    stack->count++;
    return 0;
}

int pop(Stack * stack) {
    if (stack->count <= 0) {
        return -1;
    }
    stack->count--;
    return stack->data[stack->count];
}


