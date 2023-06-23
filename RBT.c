#include <stdio.h>
#include <stdlib.h>
#include "RBT.h"

// Função auxiliar para criar um novo nó
Node *createNode(int id){
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

Node *insert(Node *root, int id) { //cria a estrutura do no, caso a arvore esteja vazia ele cria um NO raiz
    Node *node = createNode(id); // chama a função de criar o NO

    if (root == NULL) {
        node->color = BLACK;
        return node;
    }

    insertNode(&root, node); 

    return root;
}

void prinTree(Node *root){
    printTreeHelper(root, 0);
}

void printTreeHelper(Node *node, int indentLevel){
    if (node != NULL){
        printTreeHelper(node->right, indentLevel + 1);

        for (int i = 0; i < indentLevel; i++)
            printf("     ");
        
        printf("%d - %d\n", node->id, node->color);

        printTreeHelper(node->left, indentLevel + 1);
    }
}


Node *rotateLeft(Node **root, Node *node){
    Node *rightChild = node->right;
    node->right = rightChild->left;
    rightChild->left = node;
    if (*root == node){
        *root = rightChild;
    }

    return rightChild;
}

Node *rotateRight(Node **root, Node *node){
    Node *leftChild = node->left;
    node->left = leftChild->right;
    leftChild->right = node;
    if (*root == node){
        *root = leftChild;
    }

    return leftChild;
}

void fixupAfterInsertion(Node **root, Node *node) {
    
}
