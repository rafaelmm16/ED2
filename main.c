#include"RBT.c"
#include <stdio.h>
#include <stdlib.h>

int main() {
    Node *root = NULL;
    int choice, item;

    do {
        printf("1. Inserir elemento na árvore\n");
        printf("2. Exibir árvore em ordem\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Digite o elemento a ser inserido: ");
                scanf("%d", &item);
                root = insert(root, item);
                break;
            case 2:
                printf("Árvore em ordem: ");
                print(root);
                printf("\n");
                break;
            case 0:
                printf("Encerrando...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
        printf("\n");
    } while (choice != 0);

    
    return 0;
}
