//
// Created by stguable on 2026/10/28.
//

#ifndef CCPP2026_STACK_H
#define CCPP2026_STACK_H

typedef struct {
    int data[15];
    int size;
    int count;
}Stack;

int init_stack(Stack * stack);

int push(Stack * stack, int val);

int pop(Stack * stack);

#endif //CCPP2026_STACK_H
