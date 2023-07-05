#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rbt-name.c"

int main()
{
    int choice, novo;
    int qtd=0;
    int item =0;
    char name[100];
    char *name_prod = NULL;
    RbTree *root = createRbTree();
    int item_dois=0;
    int quant_atual=0;

    do
    {
        printf("\n --------------------------------------------- \n1. Cadastrar um novo produto\n");
        printf("2. Excluir um produto cadastrado\n");
        printf("3. Atualizar a quantidade de um produto no estoque\n");
        printf("4. Listar produtos cadastrados\n");
        printf("5. Listar produtos em estoque\n");
        printf("6. Imprimir a árvore Rubro-Negra\n");
        printf("0. Sair\n --------------------------------------------- \n");
        printf("\nEscolha uma opção: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1: //[ok]
            item =0;
            printf("Digite o codigo produto a ser inserido: ");
            scanf("%d", &item);
            if (item<=0){
                printf("\n Codigo invalido \n");
            }else if (searchElement(*root, item)){ //codigo inserido já existe
                printf("\n Já possui um produto cadastrado com essa chave, tente outra chave \n");
            }else{
                fflush(stdin);
                printf("Digite o nome do produto (sem espaços): ");
                scanf(" %99[^\n]", name);
                //printf("%s", name);
                printf("Digite a qtd do produto: ");
                scanf("%d", &qtd);
                if(item<0){
                    printf("\n - quantidade inválida - \n");
                }else{
                    item = insertRb(root, item, qtd, name, &name_prod);      
                    printf("\n");
                    printProd(root);
                }
                
            }
            
            break;
        case 2: //[verificar]
            printf("Digite o produto a ser removido: ");
            scanf("%d", &item);
            removeRb(root, item);
            prinTree(root);
            break;
        case 3: //[ok]
            printf("Digite o codigo do produto a ser atualizado: ");
            scanf("%d", &item_dois);
            if (searchElement(*root, item_dois)) { //item é o codigo do produto
                quant_atual = returnQuant(*root,item_dois,quant_atual);
                printf("\n> O produto %d existe! Quantidade Atual: %d \n", item_dois, quant_atual);
                printf("\nInforme o novo valor da quantidade: ");
                scanf("%d", &novo);
                if(novo<0){
                    printf("Numero inserido invalido;\n");                    
                }else{
                    changeInfo(*root, item_dois, novo);
                    printProd(root);
                }

            }else 
                printf("O produto não existe!\n");
            
            break;  
        case 4: //[ok];
            printf("\n");
            printProdCastrados(root);

            break;      
        case 5://[ok]
            printf("\n Produtos Disponiveis no Estoque Atualmente \n");
            printProdEstoqueAux(root);
            break;
        case 6: //[ok]
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