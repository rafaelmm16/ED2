#include <stdio.h>
#include <stdlib.h>

// Estrutura de um nó da árvore
typedef struct Node {
    int value;
    int color; // 0 para vermelho, 1 para preto
    struct Node* left;
    struct Node* right;
    struct Node* parent;
} Node;

// Função auxiliar para rotacionar a árvore à esquerda
Node* createNode(int value, int color, Node* parent);

Node* rotateLeft(Node* root, Node* node);

Node* rotateRight(Node* root, Node* node);

Node* fixTree(Node* root, Node* node);

Node* insertRecursively(Node* root, Node* parent, int value);

Node* insert(Node* root, int value);

void printInOrder(Node* root);

void freeTree(Node* root);