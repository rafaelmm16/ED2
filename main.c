#include"RBT.c"
#include <stdio.h>
#include <stdlib.h>

int main() {
    Node* root = NULL;

    root = insert(root, 100);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 60);
    root = insert(root, 70);

    printf("Árvore Rubro-Negra em Ordem: ");
    printInOrder(root);
    printf("\n");

    freeTree(root);
    
    return 0;
}
