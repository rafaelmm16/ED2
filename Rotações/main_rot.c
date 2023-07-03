#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "RBT_rot.c"

int main()
{
    int choice, item;
    int quant=0;
    char name[100];
    char *name_prod = NULL;
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
            printf("Quantidade: ");
            scanf("%d", &quant);
            fflush(stdin);
            printf("Nome do produto (sem espaços): ");
            scanf(" %99[^\n]", name);
            insertRb(root, item, quant, name, &name_prod);
            prinTree(root);
            break;
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