//
// Created by furetur on 15.03.2020.
//


#include <stdlib.h>
#include "machine/machine.h"
#include "stdio.h"
#include "../lib/arrayutils/arrayutils.h"


const int MAX_INPUT_LENGTH = 500;

void addOptionalSignsTransition(int** stateTable, const int from, const int to)
{
    stateTable[from]['+'] = to;
    stateTable[from]['-'] = to;
    stateTable[from][NULL_TRANSITION] = to;
}


void addOneOrMoreDigitsTransition(int** stateTable, const int from, const int to)
{
    for (int i = 0; i < 10; ++i)
    {
        stateTable[from]['0' + i] = to;
        stateTable[to]['0' + i] = to;
    }
}


void addShortcut(int** stateTable, const int from, const int to)
{
    stateTable[from][NULL_TRANSITION] = to;
}

NonDeterministicMachine* getRealNumberMachine()
{
    const int numStates = 8;
    int** stateTable = createInt2dArrayWithVal(numStates, 256, NULL_STATE);

    addOptionalSignsTransition(stateTable, 0, 1);
    addOneOrMoreDigitsTransition(stateTable, 1, 2);

    stateTable[2]['.'] = 3;

    addOneOrMoreDigitsTransition(stateTable, 3, 4);
    addShortcut(stateTable, 2, 4);

    stateTable[4]['E'] = 5;
    addOptionalSignsTransition(stateTable, 5, 6);

    addOneOrMoreDigitsTransition(stateTable, 6, 7);

    addShortcut(stateTable, 4, 7);

    return newMachine(0, 7, (const int **) stateTable, numStates);
}


void deleteRealNumbersMachine(NonDeterministicMachine* machine)
{
    freeInt2dArray(machine->stateTable, 8);
    deleteMachine(machine);
}

int main()
{
    char* inputString = createCharArray(MAX_INPUT_LENGTH);

    printf("Enter something and we will tell you whether it's a number or not:\n");
    scanf("%s", inputString);

    NonDeterministicMachine* realNumbersMachine = getRealNumberMachine();

    if (runMachine(realNumbersMachine, inputString))
    {
        printf("Your string represents a number");
    }
    else
    {
        printf("It is not a number");
    }

    free(inputString);
    deleteRealNumbersMachine(realNumbersMachine);

    return 0;
}

