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

Node *insert(Node *root, int id)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->id = id;
    node->color = RED; // Novos nós sempre são vermelhos
    node->left = NULL;
    node->right = NULL;

    // Caso base: árvore vazia
    if (root == NULL)
    {
        root = node;
        root->color = BLACK; // Raiz sempre é preta
        return root;
    }

    insertNode(root, node);
    fixupAfterInsertion(&root, node);

    return root;
}

void insertNode(Node *currentNode, Node *node)
{
    if (node->id < currentNode->id)
    {
        if (currentNode->left == NULL)
        {
            currentNode->left = node;
        }
        else
        {
            insertNode(currentNode->left, node);
        }
    }
    else
    {
        if (currentNode->right == NULL)
        {
            currentNode->right = node;
        }
        else
        {
            insertNode(currentNode->right, node);
        }
    }
}

void print(Node *root)
{
    if (root != NULL)
    {
        print(root->left);
        printf("%d ", root->id);
        printf("%d ", root->color);
        print(root->right);
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

Node *grandparent(Node *node)
{
    if (node != NULL && node->left != NULL)
    {
        return node->left->left;
    }
    return NULL;
}

Node *uncle(Node *node)
{
    Node *g = grandparent(node);
    if (g == NULL)
    {
        return NULL;
    }
    if (node->left == g->right)
    {
        return g->left;
    }
    else
    {
        return g->right;
    }
}

void fixupAfterInsertion(Node **root, Node *node)
{
    node->color = RED;

    while (node != *root && node->left != NULL && node->left->color == RED)
    {
        Node *uncleNode = uncle(node);
        Node *grandparentNode = grandparent(node);

        if (uncleNode != NULL && uncleNode->color == RED)
        {
            node->color = BLACK;
            node->left->color = BLACK;
            grandparentNode->color = RED;
            node = grandparentNode;
        }
        else
        {
            if (node->left == grandparentNode->right)
            {
                node = node->left;
                rotateLeft(root, node);
            }
            node->left->color = BLACK;
            grandparentNode->color = RED;
            rotateRight(root, grandparentNode);
        }
    }
}