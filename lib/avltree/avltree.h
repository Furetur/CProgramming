//
// Created by furetur on 12.03.2020.
//

#ifndef HOMEWORK_AVLTREE_H
#define HOMEWORK_AVLTREE_H

#include <stdbool.h>

typedef struct Node {
    int key;
    unsigned char height;
    // connections
    struct Node* parent;
    struct Node* left;
    struct Node* right;
} AVLNode;


typedef struct AVLTree {
    AVLNode* root;
} AVLTree;


AVLTree* newAVLTree();

void deleteAVLTree(AVLTree* tree);

void AVLTreeInsert(AVLTree* tree, int key);

void AVLTreeRemove(AVLTree* tree, int key);

bool AVLTreeIncludes(AVLTree* tree, int key);

char* AVLTreeToDebugString(AVLTree* tree);

char* AVLTreeToSortedString(AVLTree* tree, bool reversed);


#endif //HOMEWORK_AVLTREE_H
