#include <stdio.h>
#include <stdlib.h>

// Estrutura de um nó da árvore
typedef struct Node {
    int value;
    int color; // 0 para vermelho, 1 para preto
    struct Node *left;
    struct Node *right;
    int id;
} Node;

// Função auxiliar para rotacionar a árvore à esquerda
Node* createNode(int value);

Node *insert(Node *root, int value);

void print(Node *root);