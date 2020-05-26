//
// Created by furetur on 12.03.2020.
//

#include "avltree.h"
#include "stdlib.h"
#include "../commonutils/commonutils.h"
#include "../arrayutils/arrayutils.h"
#include "stdio.h"
#include "string.h"


const int MAX_DEBUG_STRING_LENGTH = 500;

const int MAX_SORTED_STRING_LENGTH = 500;


AVLNode* newAVLNode(const int key)
{
    AVLNode* node = malloc(sizeof(AVLNode));
    node->key = key;
    node->height = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}


void deleteAVLNode(AVLNode* node)
{
    node->left = NULL;
    node->right = NULL;
    free(node);
}


void deleteTree(AVLNode* root)
{
    if (root == NULL)
    {
        return;
    }
    AVLNode* leftSubtree = root->left;
    AVLNode* rightSubtree = root->right;

    deleteAVLNode(root);

    deleteTree(leftSubtree);
    deleteTree(rightSubtree);
}

int getHeight(AVLNode* node)
{
    if (node == NULL)
    {
        return 0;
    }
    return node->height;
}

int getBalanceFactor(AVLNode* node)
{
    return getHeight(node->right) - getHeight(node->left);
}

void recalculateHeight(AVLNode* node)
{
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    node->height = max(leftHeight, rightHeight) + 1;
}


AVLNode* rotateRight(AVLNode* pivot)
{
    AVLNode* newRoot = pivot->left;
    AVLNode* nodeToRelocate = newRoot->right;

    newRoot->right = pivot;
    pivot->left = nodeToRelocate;

    recalculateHeight(pivot);
    recalculateHeight(newRoot);

    return newRoot;
}


AVLNode* rotateLeft(AVLNode* pivot)
{
    AVLNode* newRoot = pivot->right;
    AVLNode* nodeToRelocate = newRoot->left;

    newRoot->left = pivot;
    pivot->right = nodeToRelocate;

    recalculateHeight(pivot);
    recalculateHeight(newRoot);

    return newRoot;
}


AVLNode* balanceNode(AVLNode* node)
{
    recalculateHeight(node);
    if (getBalanceFactor(node) == 2)
    {
        if (getBalanceFactor(node->right) < 0)
        {
            node->right = rotateRight(node->right);
        }
        return rotateLeft(node);
    }
    else if (getBalanceFactor(node) == -2)
    {
        if (getBalanceFactor(node->left) > 0)
        {
            node->left = rotateLeft(node->left);
        }
        return rotateRight(node);
    }
    return node;
}


bool includesKey(AVLNode* node, const int key)
{
    if (node == NULL)
    {
        return false;
    }
    if (node->key == key)
    {
        return true;
    }
    if (key < node->key)
    {
        return includesKey(node->left, key);
    }
    return includesKey(node->right, key);
}


AVLNode* insertKey(AVLNode* node, const int key)
{
    if (node == NULL)
    {
        return newAVLNode(key);
    }
    if (key < node->key)
    {
        node->left = insertKey(node->left, key);
    }
    else
    {
        node->right = insertKey(node->right, key);
    }
    return balanceNode(node);
}


AVLNode* findNodeWithMinKey(AVLNode* node)
{
    if (node->left == NULL)
    {
        return node;
    }
    return findNodeWithMinKey(node->left);
}

AVLNode* removeNodeWithMinKey(AVLNode* node)
{
    if (node->left == NULL)
    {
        AVLNode* rightNode = node->right;
        return rightNode;
    }
    node->left = removeNodeWithMinKey(node->left);
    return balanceNode(node);
}


AVLNode* removeKey(AVLNode* node, const int key)
{
    if (node == NULL)
    {
        return NULL;
    }
    if (key < node->key)
    {
        node->left = removeKey(node->left, key);
    }
    if (key > node->key)
    {
        node->right = removeKey(node->right, key);
    }
    if (key == node->key)
    {
        if (node->right == NULL)
        {
            AVLNode* leftNode = node->left;
            deleteAVLNode(node);
            return leftNode;
        }
        AVLNode* leftSubtree = node->left;
        AVLNode* rightSubtree = node->right;
        AVLNode* nodeWithMinKey = findNodeWithMinKey(rightSubtree);

        nodeWithMinKey->right = removeNodeWithMinKey(rightSubtree);
        nodeWithMinKey->left = leftSubtree;

        deleteAVLNode(node);

        return balanceNode(nodeWithMinKey);
    }

    return balanceNode(node);
}





char* toDebugString(AVLNode* node)
{
    if (node == NULL)
    {
        return "null";
    }

    char* debugString = createCharArray(MAX_DEBUG_STRING_LENGTH);

    char* leftDebugString = toDebugString(node->left);
    char* rightDebugString = toDebugString(node->right);

    snprintf(debugString, MAX_DEBUG_STRING_LENGTH, "(%d %s %s)", node->key, leftDebugString, rightDebugString);

    if (strcmp(leftDebugString, "null") != 0)
    {
        free(leftDebugString);
    }
    if (strcmp(rightDebugString, "null") != 0)
    {
        free(rightDebugString);
    }

    return debugString;
}


char* toSortedString(AVLNode* node, bool reversed)
{
    if (node == NULL)
    {
        char* emptyString = createCharArray(1);
        return emptyString;
    }
    char* sortedString = createCharArray(MAX_SORTED_STRING_LENGTH);

    char* leftSortedString = toSortedString(node->left, reversed);
    char* rightSortedString = toSortedString(node->right, reversed);

    if (!reversed)
    {
        snprintf(sortedString, MAX_DEBUG_STRING_LENGTH,
                 "%s %d %s", leftSortedString, node->key, rightSortedString);
    }
    else
    {
        snprintf(sortedString, MAX_DEBUG_STRING_LENGTH,
                 "%s %d %s", rightSortedString, node->key, leftSortedString);
    }

    free(leftSortedString);
    free(rightSortedString);

    return sortedString;
}


AVLTree* newAVLTree()
{
    AVLTree* tree = malloc(sizeof(AVLTree));
    tree->root = NULL;
    return tree;
}


void deleteAVLTree(AVLTree* tree)
{
    deleteTree(tree->root);
    free(tree);
}

void AVLTreeInsert(AVLTree* tree, const int key)
{
    tree->root = insertKey(tree->root, key);
}


void AVLTreeRemove(AVLTree* tree, const int key)
{
    tree->root = removeKey(tree->root, key);
}


bool AVLTreeIncludes(AVLTree* tree, const int key)
{
    return includesKey(tree->root, key);
}


char* AVLTreeToDebugString(AVLTree* tree)
{
    return toDebugString(tree->root);
}


char* AVLTreeToSortedString(AVLTree* tree, bool reversed)
{
    return toSortedString(tree->root, reversed);
}


