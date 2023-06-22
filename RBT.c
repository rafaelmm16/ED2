#include <stdio.h>
#include <stdlib.h>
#include "RBT.h"

// Função auxiliar para criar um novo nó
Node* createNode(int value)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->value = value;
    node->color = 0;
    node->left = NULL;
    node->right = NULL;
    node->id = 0;

    return node;
}

Node *insert(Node *root, int value)
{
    if (root == NULL)
        return createNode(value);

    if (value < root->value)
        root->left = insert(root->left, value);
    else if (value > root->value)
        root->right = insert(root->right, value);

    return root;
}

void print(Node *root) {
    if (root != NULL) {
        print(root->left);
        printf("%d ", root->value);
        print(root->right);
    }
}