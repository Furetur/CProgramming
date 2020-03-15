//
// Created by furetur on 15.03.2020.
//

#ifndef HOMEWORK_MACHINE_H
#define HOMEWORK_MACHINE_H

#include "../../lib/linkedlist/linkedlist.h"


const int NULL_STATE;
const int NULL_TRANSITION;


struct NonDeterministicMachine
{
    LinkedList* currentStates;
    int startState;
    int endState;
    int numStates;

    const int** stateTable;
};

typedef struct NonDeterministicMachine NonDeterministicMachine;

NonDeterministicMachine* newMachine(int startState, int endState, const int** stateTable, int numStates);

void deleteMachine(NonDeterministicMachine* machine);

void resetMachine(NonDeterministicMachine* machine);

bool runMachine(NonDeterministicMachine* machine, const char* input);

#endif //HOMEWORK_MACHINE_H
