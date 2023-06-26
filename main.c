#include <stdio.h>
#include <stdlib.h>

#include "RBT.c"

int main()
{
    int choice, item;
    RbTree *root = createRbTree();

    do
    {
        printf("1. Cadastrar um novo produto\n");
        printf("2. Excluir um produto cadastrado\n");
        printf("3. Atualizar a quantidade de um produto no estoque\n");
        printf("4. Listar produtos cadastrados\n");
        printf("5. Listar produtos em estoque\n");
        printf("6. Imprimir a árvore Rubro-Negra\n");
        printf("0. Sair\n");
        printf("\nEscolha uma opção: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Digite o elemento a ser inserido: ");
            scanf("%d", &item);
            item = insertRb(root, item);
            break;
        case 2:
            printf("Digite o elemento a ser removido: ");
            scanf("%d", &item);
            removeRb(root, item);
            prinTree(root);
            break;
        case 3:
            prinTree(root);
            break;  
        case 4:
            printf("Digite o elemento a ser inserido: ");
            scanf("%d", &item);
            searchElement(root, item);

            break;      
        case 5:
            prinTree(root);
            break;
        case 6:
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
