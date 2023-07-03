#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "RBT.c"

int main()
{
    int choice, item, novo;
    int qtd=0;
    char name[100];
    char *name_prod = NULL;
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
            printf("Digite o produto a ser inserido: ");
            scanf("%d", &item);
            fflush(stdin);
            printf("Digite o nome do produto: ");
            scanf(" %99[^\n]", name);
            printf("Digite a qtd do produto: ");
            scanf("%d", &qtd);
            
            item = insertRb(root, item, qtd, name, &name_prod);
            
            printProd(root);
            break;
        case 2:
            printf("Digite o produto a ser removido: ");
            scanf("%d", &item);
            removeRb(root, item);
            prinTree(root);
            break;
        case 3:
            printf("Digite o cod do produto a ser atualizado: ");
            scanf("%d", &item);

            if (searchElement(*root, item))
            {
                printf("O produto %d existe!\n", item);
                
                printf("\nInforme o novo valor: ");
                scanf("%d", &novo);
                changeInfo(*root, item, novo);

                printProd(root);
            }
            else printf("O produto não existe!\n");
            
            break;  
        case 4:
            
            //searchElement(*root, item);

            break;      
        case 5:
            printf("Produtos em est: ");
            break;
        case 6:
            prinTree(root);
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
