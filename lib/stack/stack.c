//
// Created by furetur on 06.03.2020.
//

#include "stack.h"

Stack* newStack()
{
    return newLinkedList();
}


void deleteStack(Stack* stack)
{
    deleteLinkedList(stack);
}


void stackPush(Stack* stack, const int val)
{
    linkedListPushBack(stack, val);
}


int stackPop(Stack* stack)
{
    return linkedListPopBack(stack);
}


int stackPeek(Stack* stack)
{
    return stack->tail->val;
}