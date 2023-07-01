#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "RBT_rot.c"

int main()
{
    int choice, item;
    //int qtd;
    //char name[64];
    RbTree *root = createRbTree();

    do
    {
        printf("1. Cadastrar um novo produto\n");
        printf("2. Imprimir Arvore\n");
        printf("0. Sair\n");
        printf("\nEscolha uma opcao: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Chave: ");
            scanf("%d", &item);
            insertRb(root, item);
            prinTree(root);
            break;;
        case 2:
            prinTree(root);
            //printf("%d", root->info);
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