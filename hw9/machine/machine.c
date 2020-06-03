//
// Created by furetur on 15.03.2020.
//

#include <stdlib.h>
#include "machine.h"
#include "string.h"

const int NULL_STATE = -1;
const int NULL_TRANSITION = 0;


void resetMachine(NonDeterministicMachine* machine)
{
    LinkedList* startStates = newLinkedList();
    linkedListPushBack(startStates, machine->startState);

    LinkedList* oldStates = machine->currentStates;

    machine->currentStates = startStates;

    if (oldStates != NULL)
    {
        deleteLinkedList(oldStates);
    }
}


NonDeterministicMachine* newMachine(const int startState, const int endState, const int** stateTable, const int numStates)
{
    NonDeterministicMachine* machine = malloc(sizeof(NonDeterministicMachine));
    machine->startState = startState;
    machine->endState = endState;
    machine->stateTable = stateTable;
    machine->numStates = numStates;
    machine->currentStates = NULL;

    resetMachine(machine);
    return machine;
}


void deleteMachine(NonDeterministicMachine* machine)
{
    deleteLinkedList(machine->currentStates);
    free(machine);
}


void performNullTransitions(NonDeterministicMachine* machine, const int state)
{
    const int nextState = machine->stateTable[state][NULL_TRANSITION];
    if (nextState != NULL_STATE)
    {
        linkedListPushBack(machine->currentStates, nextState);
        performNullTransitions(machine, nextState);
    }
}


void performAllNullTransitions(NonDeterministicMachine* machine)
{

    LinkedListIterator* currentStatesIterator = getLinkedListIterator(machine->currentStates);

    while (linkedListIteratorHasNext(currentStatesIterator))
    {
        const int state = linkedListIteratorGetNext(currentStatesIterator);
        performNullTransitions(machine, state);
    }

    deleteLinkedListIterator(currentStatesIterator);
}

void moveMachine(NonDeterministicMachine* machine, char token)
{
    LinkedList* newStates = newLinkedList();

    LinkedListIterator* statesIterator = getLinkedListIterator(machine->currentStates);

    while (linkedListIteratorHasNext(statesIterator))
    {
        const int currentStateId = linkedListIteratorGetNext(statesIterator);
        const int nextState = machine->stateTable[currentStateId][token];

        if (nextState != NULL_STATE)
        {
            linkedListPushBack(newStates, nextState);
        }
    }

    LinkedList* oldStates = machine->currentStates;
    machine->currentStates = newStates;

    deleteLinkedList(oldStates);
    deleteLinkedListIterator(statesIterator);

    // perform all available null transitions
    performAllNullTransitions(machine);
}


bool isMachineFinishedNow(NonDeterministicMachine* machine)
{
    LinkedList* currentStates = machine->currentStates;
    return linkedListContains(currentStates, machine->endState);
}


bool runMachine(NonDeterministicMachine* machine, const char* input)
{
    const int inputLength = strlen(input);

    performAllNullTransitions(machine);

    for (int i = 0; i < inputLength; ++i)
    {
        moveMachine(machine, input[i]);
        if (machine->currentStates->size == 0)
        {
            return false;
        }
    }
    return isMachineFinishedNow(machine);
}