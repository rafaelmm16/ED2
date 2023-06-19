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

// Função auxiliar para criar um novo nó
Node* createNode(int value, int color, Node* parent) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->value = value;
    node->color = color;
    node->left = NULL;
    node->right = NULL;
    node->parent = parent;
    return node;
}