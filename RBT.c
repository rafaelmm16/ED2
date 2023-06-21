#include <stdio.h>
#include <stdlib.h>
#include "RBT.h"

// Função auxiliar para criar um novo nó
Node *createNode(int value, int color, Node *parent)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->value = value;
    node->color = color;
    node->left = NULL;
    node->right = NULL;
    node->parent = parent;
    return node;
}

Node *rotateLeft(Node *root, Node *node)
{
    Node *right = node->right;
    node->right = right->left;

    if (node->right != NULL)
    {
        node->right->parent = node;
    }

    right->parent = node->parent;

    if (node->parent == NULL)
    {
        root = right;
    }
    else if (node == node->parent->left)
    {
        node->parent->left = right;
    }
    else
    {
        node->parent->right = right;
    }

    right->left = node;
    node->parent = right;

    return root;
}

// Função auxiliar para rotacionar a árvore à direita
Node *rotateRight(Node *root, Node *node)
{
    Node *left = node->left;
    node->left = left->right;

    if (node->left != NULL)
    {
        node->left->parent = node;
    }

    left->parent = node->parent;

    if (node->parent == NULL)
    {
        root = left;
    }
    else if (node == node->parent->left)
    {
        node->parent->left = left;
    }
    else
    {
        node->parent->right = left;
    }

    left->right = node;
    node->parent = left;

    return root;
}

// Função auxiliar para corrigir a árvore após a inserção de um novo nó
Node *fixTree(Node *root, Node *node)
{
    // Caso base: o nó é a raiz da árvore
    if (node->parent == NULL)
    {
        node->color = 1; // Pinte-o de preto
        return node;
    }

    // Caso base: o nó pai é preto
    if (node->parent->color == 1)
    {
        return root;
    }

    Node *parent = node->parent;
    Node *grandparent = node->parent->parent;
    Node *uncle = NULL;

    // Caso 1: O tio é vermelho
    if (grandparent->left == parent)
    {
        uncle = grandparent->right;

        if (uncle != NULL && uncle->color == 0)
        {
            parent->color = 1;
            uncle->color = 1;
            grandparent->color = 0;
            return fixTree(root, grandparent);
        }
    }
    else
    {
        uncle = grandparent->left;

        if (uncle != NULL && uncle->color == 0)
        {
            parent->color = 1;
            uncle->color = 1;
            grandparent->color = 0;
            return fixTree(root, grandparent);
        }
    }

    // Caso 2: O nó é filho direito de seu pai
    if (node == parent->right)
    {
        root = rotateLeft(root, parent);
        node = parent;
        parent = node->parent;
        grandparent = parent->parent;
    }
    else
    {
        // Caso 3: O nó é filho esquerdo de seu pai
        if (node == parent->left)
        {
            root = rotateRight(root, parent);
            node = parent;
            parent = node->parent;
            //grandparent = parent->parent;
        }
    }

    // Caso 4: O nó é filho à direita do seu pai após a rotação à esquerda
    parent->color = 1;
    grandparent->color = 0;

    if (node == parent->left)
    {
        root = rotateRight(root, grandparent);
    }
    else
    {
        // Caso 5: O nó é filho à esquerda do seu pai após a rotação à direita
        root = rotateLeft(root, grandparent);
    }

    return root;
}

// Função recursiva para inserir um valor na árvore
Node *insertRecursively(Node *root, Node *parent, int value)
{
    if (root == NULL)
    {
        return createNode(value, 0, parent);
    }

    if (value < root->value)
    {
        root->left = insertRecursively(root->left, root, value);
    }
     else if(value > root->value)
     {
        root->right = insertRecursively(root->right, root, value); 
     }
    return fixTree(root, root);
}

// Função para inserir um valor na árvore
Node *insert(Node *root, int value)
{
    return insertRecursively(root, NULL, value);
}

// Função auxiliar para imprimir a árvore em ordem
void printInOrder(Node *root)
{
    if (root != NULL)
    {
        printInOrder(root->left);
        printf("%d ", root->value);
        printInOrder(root->right);
    }
}

// Função auxiliar para liberar a memória da árvore
void freeTree(Node *root)
{
    if (root != NULL)
    {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}