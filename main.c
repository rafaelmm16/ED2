// ED2_TrabPratico_Grupo5_[IasminMarquesPereira][RafaelMendesMerlo]
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "RBT.h"

int main(){
    //variaveis de controle e armazenamento de informações para exibição
    int choice, novo; //controle do menu
    int qtd=0;//quantidade do produto
    int item =0; // controle de codigo do item a ser inserido
    char name[100]; // nome produto - string
    char *name_prod = NULL; //controle nome do produto - string
    RbTree *root = createRbTree();//arvore rubro negra
    int item_dois=0; // controle - atualização de quantidade de produto
    int quant_atual=0; // quantidade atual do produto

    do{
        printf("\n --------------------------------------------- \n1. Cadastrar um novo produto\n");
        printf("2. Excluir um produto cadastrado\n");
        printf("3. Atualizar a quantidade de um produto no estoque\n");
        printf("4. Listar produtos cadastrados\n");
        printf("5. Listar produtos em estoque\n");
        printf("6. Imprimir a árvore Rubro-Negra\n");
        printf("0. Sair\n --------------------------------------------- \n");
        printf("\nEscolha uma opção: ");
        scanf("%d", &choice);

        switch (choice){
        case 1: //inserir um produto
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
        case 2: //remover um produto
            printf("Digite o produto a ser removido: ");
            scanf("%d", &item);
            if (searchElement(*root, item)){//se o produto existir: remove 
                removeRb(root, item);//remove o produto
                prinTree(root);//printa a arvore
            }else{ //produto nao existe
                printf("Produto não Existe! \n");
            }
            break;
        case 3: //atualizar quantidade do produto
            printf("Digite o codigo do produto a ser atualizado: ");
            scanf("%d", &item_dois);
            if (searchElement(*root, item_dois)) { //verifica se o produto existe
                quant_atual = returnQuant(*root,item_dois,quant_atual);
                printf("\n> O produto %d existe! Quantidade Atual: %d \n", item_dois, quant_atual);
                printf("\nInforme o novo valor da quantidade: ");
                scanf("%d", &novo);
                if(novo<0){ //se o valor da quantidade menor que zero, INVALIDO
                    printf("Numero inserido invalido;\n");                    
                }else{
                    changeInfo(*root, item_dois, novo);
                    printProd(root);
                }
            }else 
                printf("O produto não existe!\n");
            break;  
        case 4: //Exibe os produtos cadastrados

            if (*root == NULL){ // caso a árvore esteja vazia, não possui produtos cadastrados
                printf("\n [Sem produtos Cadastrados] \n");
            }else{ // se a arvore possuir produtos cadastrados
                printf("\n --- Produtos Cadastrados --- \n");
                printProdCastrados(root);
            }

            break;      
        case 5://Exibe os produtos disponiveis em estoque
            if (*root == NULL){ // caso a árvore esteja vazia, não possui produtos cadastrados
                printf("\n [Sem produtos Cadastrados] \n"); 
            }else{ //caso não possua produtos: não tera informações, se possuir disponivel em estoque: exibira 
                printf("\n --- Produtos Disponiveis no Estoque Atualmente --- \n");
                printProdEstoqueAux(root);  
            }            
            break;
        case 6: //impressao da arvore
            if (*root == NULL){  // caso a árvore esteja vazia
                printf("\n [Árvore Vazia] \n");
            }else{//exibe os elementos cadastrados na arvore
                prinTree(root);
            } 
            break;
        case 0://encerra o programa
            printf("Encerrando...\n");
            break;
        default: //lida com as opções invalidas
            printf("Opção inválida! Tente novamente.\n");
        }
        printf("\n");
    } while (choice != 0);

    return 0;
}