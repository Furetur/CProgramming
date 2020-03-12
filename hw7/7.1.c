//
// Created by furetur on 12.03.2020.
//

#include <stdbool.h>
#include "stdlib.h"
#include "stdio.h"
#include "../lib/arrayutils/arrayutils.h"
#include "../lib/commonutils/commonutils.h"
#include "../lib/avltree/avltree.h"
#include "string.h";


int main()
{
    AVLTree* tree = newAVLTree();

    printf("Available commands:\n");
    printf("add n     ---- this adds a number n to the AVLTree\n");
    printf("remove n  ---- this removes a number n from the AVLTree:\n");
    printf("has n     ---- this checks whether n is present in the AVLTree\n");
    printf("sort      ---- this prints the elements of the tree in the ascending order\n");
    printf("sort_r    ---- this prints the elements of the tree in the descending order\n");
    printf("debug     ---- this prints the tree for debugging\n");
    printf("exit      ---- exits program\n");
    printf("===========================================================================\n");
    printf("Now enter your commands\n");

    char* command = createCharArray(10);

    scanf("%s", command);

    while (strcmp(command, "exit") != 0)
    {
        if (strcmp(command,"add") == 0)
        {
            int number = 0;
            scanf("%d", &number);
            AVLTreeInsert(tree, number);
            printf("> added %d\n", number);
        } else if (strcmp(command,"remove") == 0)
        {
            int number = 0;
            scanf("%d", &number);
            AVLTreeRemove(tree, number);
            printf("> removed %d\n", number);
        } else if (strcmp(command,"has") == 0)
        {
            int number = 0;
            scanf("%d", &number);
            if (AVLTreeIncludes(tree, number))
            {
                printf("> (TRUE) the tree includes the key %d\n", number);
            } else {
                printf("> (FALSE) the tree does not include the key %d\n", number);
            }
        } else if (strcmp(command,"sort") == 0)
        {
            char* outputString = AVLTreeToSortedString(tree, false);
            printf("> %s\n", outputString);
            free(outputString);
        } else if (strcmp(command,"sort_r") == 0)
        {
            char* outputString = AVLTreeToSortedString(tree, true);
            printf("> %s\n", outputString);
            free(outputString);
        } else if (strcmp(command,"debug") == 0)
        {
            char* outputString = AVLTreeToDebugString(tree);
            printf("> %s\n", outputString);
            free(outputString);
        } else {
            printf("> Unknown command\n");
        }
        scanf("%s", command);
    }

    free(command);
    deleteAVLTree(tree);

    return 0;
}