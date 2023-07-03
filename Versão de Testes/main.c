#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "RBT.c"

int main()
{
    int choice, item, novo;
    //int qtd;
    //char name[64];
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
            insertRb(root, item);
            fflush(stdin);
            /* item = insertRb(root, item);
            printf("Digite o nome do produto: ");
            fgets(name, 64, stdin);
            adicionarName(*root, name);
            printf("Digite a qtd do produto: ");
            scanf("%d", &qtd);
            
            adicionarInformacoes(*root, qtd); 
            imprimirString(*root); */
            prinTree(root);
            break;
        case 2:
            printf("Digite o produto a ser removido: ");
            scanf("%d", &item);
            removeElementRb(*root, item);
            prinTree(root);
            break;
        case 3:
            printf("Digite o produto a ser atualizado: ");
            scanf("%d", &item);

            if (item == 1)
            {
                printf("O produto %d existe!\n", item);
                
                printf("\nInforme o novo valor: ");
                scanf("%d", &novo);
               // trocarInfo(*root, item, novo);

                //prinTree(root);
            }
            else printf("O produto não existe!\n");
            
            break;  
        case 4:
            printf("Digite o elemento a ser inserido: ");
            scanf("%d", &item);
            //searchElement(*root, item);

            break;      
        case 5:
            //prinTree(root);
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
