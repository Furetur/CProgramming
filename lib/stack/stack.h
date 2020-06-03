//
// Created by furetur on 06.03.2020.
//

#ifndef HOMEWORK_STACK_H
#define HOMEWORK_STACK_H


#include "../linkedlist/linkedlist.h"

typedef LinkedList Stack;

Stack* newStack();

void deleteStack(Stack* stack);

void stackPush(Stack* stack, int val);

int stackPop(Stack* stack);

int stackPeek(Stack* stack);

#endif //HOMEWORK_STACK_H
