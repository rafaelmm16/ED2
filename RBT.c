#include <stdio.h>
#include <stdlib.h>
#include "RBT.h"

// Função auxiliar para criar um novo nó
Node *createNode(int id)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->id = id;
    node->color = RED;
    node->left = NULL;
    node->right = NULL;

    return node;
}

void insertNode(Node **root, Node *node) {
    if (*root == NULL) {
        node->color = BLACK;
        *root = node;
        return;
    }

    Node *parent = NULL;
    Node *current = *root;

    while (current != NULL) {
        parent = current;

        if (node->id < current->id) {
            current = current->left;
        } else if (node->id > current->id) {
            current = current->right;
        } else {
            // Se o valor já existe na árvore, não faz nada
            free(node);
            return;
        }
    }

    if (node->id < parent->id) {
        parent->left = node;
    } else {
        parent->right = node;
    }

    fixupAfterInsertion(root, node);
}

Node *insert(Node *root, int id) {
    Node *node = createNode(id);

    if (root == NULL) {
        node->color = BLACK;
        return node;
    }

    insertNode(&root, node);

    return root;
}

void prinTree(Node *root)
{
    printTreeHelper(root, 0);
}

void printTreeHelper(Node *node, int indentLevel)
{
    if (node != NULL)
    {
        printTreeHelper(node->right, indentLevel + 1);

        for (int i = 0; i < indentLevel; i++)
            printf("     ");
        
        printf("%d - %d\n", node->id, node->color);

        printTreeHelper(node->left, indentLevel + 1);
    }
}


Node *rotateLeft(Node **root, Node *node)
{
    Node *rightChild = node->right;
    node->right = rightChild->left;
    rightChild->left = node;
    if (*root == node)
    {
        *root = rightChild;
    }

    return rightChild;
}

Node *rotateRight(Node **root, Node *node)
{
    Node *leftChild = node->left;
    node->left = leftChild->right;
    leftChild->right = node;
    if (*root == node)
    {
        *root = leftChild;
    }

    return leftChild;
}

void fixupAfterInsertion(Node **root, Node *node) {
    node->color = RED;

    while (node != *root && node->left != NULL && node->left->color == RED) {
        Node* sibling = NULL;
        Node* uncle = NULL;
        Node* grandparent = *root;

        while (grandparent->left != NULL && grandparent->left->left != node->left) {
            grandparent = grandparent->left;
        }

        if (grandparent->left != NULL) {
            uncle = grandparent->left->right;
            sibling = grandparent->left;
        } else {
            uncle = grandparent->right->left;
            sibling = grandparent->right;
        }

        if (uncle != NULL && uncle->color == RED) {
            grandparent->color = RED;
            sibling->color = BLACK;
            uncle->color = BLACK;
            node = grandparent;
        } else {
            if (node == sibling->right) {
                node = sibling->left;
                rotateRight(root, sibling);
            }

            node->left->color = BLACK;
            grandparent->color = RED;
            rotateLeft(root, grandparent);
        }
    }

    (*root)->color = BLACK;
}
