//
// Created by stguable on 2026/10/28.
//

#ifndef CCPP2026_STACK_H
#define CCPP2026_STACK_H

typedef struct {
    int *data;
    int size;
    int count;
}Stack;

Stack * create_stack(int size);

int push(Stack * stack, int val);

int pop(Stack * stack);

#endif //CCPP2026_STACK_H
