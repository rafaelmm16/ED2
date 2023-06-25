#include "RBT.c"
#include "dados.c"
#include "orderedSet.c"

#include <stdio.h>
#include <stdlib.h>

int main() {
    int choice, item;
    orderedSet *root;
    root = createRbTree();

    do {
        printf("1. Inserir elemento na árvore\n");
        printf("2. Exibir árvore em ordem\n");
        printf("3. Procurar um id\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Digite o elemento a ser inserido: ");
                scanf("%d", &item);
                if (isOnSet(root, criaNo(item), &comparar) == 1)
					printf("O elemento ja pertence ao conjunto A!\n");
				else
					insertElement(root, criaNo(item), &comparar);
                break;
            case 2:
                if (isEmpty(root))
					printf("A arvore esta vazio!\n");
				else
				{
					printf("Conjunto A:\n");
					printRb(root, &imprime);
				}
                break;
            case 3:
                printf("Digite o elemento a ser inserido: ");
                scanf("%d", &item);
                //searchInfoRBTree(root, item);
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
