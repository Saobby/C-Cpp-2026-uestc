//
// Created by stguable on 2026/10/28.
//

#include "stack.h"
#include <stdlib.h>

Stack * create_stack(const int size) {
    Stack *stack = malloc(sizeof(Stack));
    stack->data = (int *)malloc(sizeof(int) * size);
    stack->size = size;
    stack->count = 0;
    return stack;
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


