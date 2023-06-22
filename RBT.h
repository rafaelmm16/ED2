#include <stdio.h>
#include <stdlib.h>

typedef enum Color
{
    RED,
    BLACK
} Color;

// Estrutura de um nó da árvore
typedef struct Node
{
    Color color; // 0 para vermelho, 1 para preto
    struct Node *left;
    struct Node *right;
    int id;
} Node;

// Função auxiliar para rotacionar a árvore à esquerda
Node *createNode(int value);

Node *insert(Node *root, int value);

void insertNode(Node *currentNode, Node *node);

void print(Node *root);

Node *rotateLeft(Node **root, Node *node);

Node *rotateRight(Node **root, Node *node);

Node *grandparent(Node *node);

Node *uncle(Node *node);

void fixupAfterInsertion(Node **root, Node *newNode);