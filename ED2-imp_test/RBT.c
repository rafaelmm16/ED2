// ED2_TrabPratico_Grupo5_[IasminMarquesPereira][RafaelMendesMerlo].zip,
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "RBT.h"

#define RED 1
#define BLACK 0

RbTree *createRbTree()
{ // Função auxiliar para criar um novo nó
	RbTree *root = (RbTree *)malloc(sizeof(RbTree));
	if (root != NULL)
	{
		*root = NULL;
	}
	return root;
}

void freeNode(struct NO *no)
{ // Liberar o No
	if (no == NULL)
		return;
	freeNode(no->left);
	freeNode(no->right);
	free(no);
	no = NULL;
}

void freeRbTree(RbTree *root)
{ // Liberar a árvore
	if (root == NULL)
		return;
	freeNode(*root);
	free(root);
}

// Encontrar Elemento - Busca
struct NO *searchElement(struct NO *raiz, int valor)
{
	if (raiz == NULL || raiz->info == valor)
	{
		return raiz; // retorna o valor encontrado ou a raiz (se for nula)
	}
	if (valor < raiz->info)
	{ // Se o valor for menor que o valor do nó atual, realiza a busca na subárvore esquerda
		return searchElement(raiz->left, valor);
	}
	else
	{
		// Se o valor for maior que o valor do nó atual, realiza a busca na subárvore direita
		return searchElement(raiz->right, valor);
	}
}

int returnQuant(struct NO *raiz, int valor, int qnt)
{ // retorna a quantidade atual do produto;
	if (raiz == NULL || raiz->info == valor)
	{
		qnt = raiz->qtd_prod;
		return qnt; // retorna a quantidade do produto atual se existir
	}

	if (valor < raiz->info)
	{ // Se o valor for menor que o valor do nó atual, realiza a busca na subárvore esquerda
		return returnQuant(raiz->left, valor, qnt);
	}
	else
	{
		// Se o valor for maior que o valor do nó atual, realiza a busca na subárvore direita
		return returnQuant(raiz->right, valor, qnt);
	}
}

// Rotações
struct NO *rotateLeftRb(struct NO *root)
{ // Rotação a esquerda
	struct NO *newRoot = root->right;
	struct NO *newRootLeft = newRoot != NULL ? newRoot->left : NULL;

	root->right = newRootLeft;
	newRoot->left = root;

	// Atualizar as cores corretamente
	newRoot->color = root->color;
	root->color = RED;

	// Atualizar as cores dos filhos
	if (newRootLeft)
	{
		newRootLeft->color = BLACK;
	}

	return newRoot;
}

struct NO *rotateRightRb(struct NO *root)
{ // Rotação a Direita
	struct NO *newRoot = root->left;
	struct NO *newRootRight = newRoot != NULL ? newRoot->right : NULL;

	root->left = newRootRight;
	newRoot->right = root;

	// Atualizar as cores corretamente
	newRoot->color = root->color;
	root->color = RED;

	// Atualizar as cores dos filhos
	if (newRootRight)
	{
		newRootRight->color = BLACK;
	}

	return newRoot;
}

// Informações do No
int getColor(struct NO *node)
{ // pegar o cor do NO
	if (node)
		return node->color;
	else
		return BLACK; // NULL
}

void changeColor(struct NO *node)
{ // Altera a cor de um nó e de seus filhos
	// Altera a cor de um nó e de seus filhos
	if ((node->left != NULL) || (node->right != NULL))
	{ // verifica se diferente de null se existem)
		node->color = !node->color;
	}

	if (node->left != NULL)
		node->left->color = !node->left->color;
	if (node->right != NULL)
		node->right->color = !node->right->color;
}

int BlackHeight(struct NO *node)
{ // altura negra
	if (node == NULL)
	{
		return 0;
	}

	int leftBlackHeight = BlackHeight(node->left);
	int rightBlackHeight = BlackHeight(node->right);

	int currentBlackHeight = getColor(node) == BLACK ? 1 : 0; // se no == BLACK, retorna 1, caso contrario 0;

	return leftBlackHeight - rightBlackHeight + currentBlackHeight;
}

struct NO *insertNodeRb(struct NO *root, int key, int qtd, const char *name, int *ans)
{
	// int altura = BlackHeight(root);
	if (!root)
	{
		struct NO *insert = (struct NO *)malloc(sizeof(struct NO));
		if (!insert)
		{ // não foi inserido
			*ans = 0;
			return NULL;
		}
		insert->info = key;
		insert->color = RED;
		insert->left = insert->right = NULL;
		insert->qtd_prod = qtd;
		// Adicionar o nome do produto
		insert->name_prod = (char *)malloc((strlen(name) + 1) * sizeof(char));
		strcpy(insert->name_prod, name);

		// insert->qtd_prod = qtd;
		*ans = 1;
		return insert;
	}

	// If the key already exists in the tree, return NULL
	if (key == root->info)
	{
		*ans = 0;
		return NULL;
	}
	// casos de violação de inserção e o tratamento

	if (key < root->info)
	{
		root->left = insertNodeRb(root->left, key, qtd, name, ans);
	}
	else
	{
		root->right = insertNodeRb(root->right, key, qtd, name, ans);
	}

	if (*ans)
	{ // Check if the tree is balanced after the insertion.

		if (key < root->info)
		{
			// Navegue para a subárvore esquerda
			// root->left = insertNodeRb(root->left, key, qtd,name,ans);

			// Verifique as propriedades da árvore vermelho-preto e faça as rotações e alterações de cor necessárias
			if (root->left && getColor(root->left) == RED && getColor(root->left->left) == RED)
			{
				// Caso 2: nodo adicionado à esquerda e irmão com cor vermelha
				if (root->right && getColor(root->right) == RED)
				{
					root->color = RED;
					root->left->color = BLACK;
					root->right->color = BLACK;
				}
				else
				{
					root = rotateRightRb(root);
					root->right->color = RED;
					root->color = BLACK;
				}
			}
			else if (root->left && getColor(root->left) == RED && getColor(root->left->right) == RED)
			{
				// Caso 1: pai e tio vermelhos
				if (root->right && getColor(root->right) == RED)
				{
					root->color = RED;
					root->left->color = BLACK;
					root->right->color = BLACK;
				}
				else
				{
					root->left = rotateLeftRb(root->left);
					root = rotateRightRb(root);
					root->color = BLACK;
					root->right->color = RED;
				}
			}
		}
		else
		{
			// Navegue para a subárvore direita
			// root->right = insertNodeRb(root->left, key, qtd,name,ans);

			// Verifique as propriedades da árvore vermelho-preto e faça as rotações e alterações de cor necessárias
			if (root->right && getColor(root->right) == RED && getColor(root->right->right) == RED)
			{
				// Caso 2: nodo adicionado à direita e irmão com cor vermelha
				if (root->left && getColor(root->left) == RED)
				{
					root->color = RED;
					root->left->color = BLACK;
					root->right->color = BLACK;
				}
				else
				{
					root = rotateLeftRb(root);
					root->left->color = RED;
					root->color = BLACK;
				}
			}
			else if (root->right && getColor(root->right) == RED && getColor(root->right->left) == RED)
			{
				// Caso 1: pai e tio vermelhos
				if (root->left && getColor(root->left) == RED)
				{
					root->color = RED;
					root->left->color = BLACK;
					root->right->color = BLACK;
				}
				else
				{
					root->right = rotateRightRb(root->right);
					root = rotateLeftRb(root);
					root->color = BLACK;
					root->left->color = RED;
				}
			}
		}
	}
	return root;
}

int insertRb(RbTree *root, int valor, int qtd, const char *name, char **name_prod)
{
	int ans;

	free(*name_prod);												// Libera a memória anterior, se necessário
	*name_prod = (char *)malloc((strlen(name) + 1) * sizeof(char)); // Aloca memória suficiente para a nova string

	int i = 0;
	// tratamento de inserção de um tipo char/ string
	while (name[i] != '\0')
	{
		if (name[i] == ' ')
		{
			(*name_prod)[i] = '\0';
			// break;
		}
		(*name_prod)[i] = name[i];
		i++;
	}
	printf("%s", *name_prod);

	*root = insertNodeRb(*root, valor, qtd, *name_prod, &ans); // Faz o tratamento das possíveis violações da árvore rubro-negra

	if ((*root) != NULL) // Seta a cor da raiz para preta, se necessário
		(*root)->color = BLACK;

	return ans;
}

/* void addName(struct NO *no, const char *name){ //adicionar informações sobre o produto: nome [verificar]
	if (no == NULL)	{// Nó inválido
		return;
	}

	free(no->name_prod); // Libera a memória anterior, se necessário
	no->name_prod = (char *)malloc((strlen(name) + 1) * sizeof(char)); // Aloca memória suficiente para a nova string

	// Copia a nova string para o campo infoString
	strcpy(no->name_prod, name);
} */

void changeInfo(struct NO *root, int valorAntigo, int novoValor)
{ // muda a quantidade do produto
	struct NO *no = searchElement(root, valorAntigo);
	if (no == NULL)
	{ // Nó não encontrado
		return;
	}
	no->qtd_prod = novoValor;
}

// Remoção
/* struct NO *balanceNodes(struct NO *node){

	if (getColor(node->right) == RED) // no Vermelho sempre filho a esquerda
		node = rotateLeftRb(node);

	// Filho da direita e neto da esquerda sao vermelhos
	// if(node->left != NULL && getColor(node->right) == RED && getColor(node->left->left) == RED)

	// Filho da esquerda e neto da esquerda s�o vermelhos
	if (node->left != NULL && getColor(node->left) == RED && getColor(node->left->left) == RED)
		node = rotateRightRb(node);

	// 2 filhos Vermelhos: troca cor!
	if (getColor(node->left) == RED && getColor(node->right) == RED)
		changeColor(node);

	return node;
}
 */

struct NO *dellBalanceNodes(struct NO *node)
{
	if (node->left == NULL && node->right != NULL && getColor(node->right) == BLACK)
	{
		printf("trocou a cor a direita %d\n", node->info);
		node->right->color = RED;
	}
	if (node->right == NULL && node->left != NULL && getColor(node->left) == BLACK)
	{
		printf("trocou a cor a esquerda %d\n", node->info);
		node->left->color = RED;
	}

	// O nó Vermelho sempre tem um filho à esquerda
	/* if (node->left != NULL && getColor(node->left) == RED)
	{
		//printf("Entrou na rotação a direita %d\n", node->info);
		//node = rotateRightRb(node);
		printf("ENTROU NESSE INFERNO\n");
		node->left->color = RED;
		//node->right->color = BLACK;
	}
 */
	// O filho direito e o neto à direita são vermelhos
	if (node->right != NULL && getColor(node->right) == RED && getColor(node->right->right) == RED)
	{
		printf("Entrou na rotação a esquerda %d\n", node->info);
		node = rotateLeftRb(node);
		node->color = RED;
	}

	// Nó Vermelho com dois filhos Vermelhos: trocar as cores
	if (node->left != NULL && node->right != NULL &&
		getColor(node) == RED && getColor(node->left) == RED && getColor(node->right) == RED && node->left->right != NULL)
	{
		printf("troca de cores pai e filhos %d\n", node->info);
		node->color = BLACK;		// Cor do nó atual é definida como preto
		node->left->color = BLACK;	// Cor do filho da esquerda é definida como preto
		node->right->color = BLACK; // Cor do filho da direita é definida como preto
		node->left->right->color = RED;
	}

	return node;
}

struct NO *moveRedToLeft(struct NO *node)
{
	changeColor(node);
	if (node->right != NULL && getColor(node->right->left) == RED)
	{
		node->right = rotateRightRb(node->right);
		node = rotateLeftRb(node);
		changeColor(node);
	}
	return node;
}

struct NO *moveRedToRight(struct NO *node)
{
	changeColor(node);
	if (node->left != NULL && getColor(node->left->left) == RED)
	{
		node = rotateRightRb(node);
		changeColor(node);
	}
	return node;
}

/* struct NO *removeSmaller(struct NO *node){
	if (node->left == NULL){
		free(node);
		return NULL;
	}
	if (getColor(node->left) == BLACK && getColor(node->left->left) == BLACK)
		node = moveRedToLeft(node);

	node->left = removeSmaller(node->left);
	return balanceNodes(node);
} */

/* struct NO *searchSmaller(struct NO *atual){
	struct NO *no1 = atual;
	struct NO *no2 = atual->left;
	while (no2 != NULL){
		no1 = no2;
		no2 = no2->left;
	}
	return no1;
} */

struct NO *searchSmallest(struct NO *node)
{
	if (node == NULL)
		return NULL;

	if (node->left == NULL)
		return node;

	return searchSmallest(node->left);
}

struct NO *searchLargest(struct NO *node)
{
	if (node == NULL)
		return NULL;

	if (node->right == NULL)
		return node;

	return searchLargest(node->right);
}

struct NO *removeElementRb(struct NO *node, int valor)
{
	// printf("Entrou na função removeElementRb\n");

	if (valor < node->info)
	{
		// printf("O valor %d é menor do que o valor do nó atual\n", valor);

		if (getColor(node->left) == BLACK && getColor(node->left->left) == BLACK)
			node = moveRedToLeft(node);

		node->left = removeElementRb(node->left, valor);
	}
	else if (valor > node->info)
	{
		// printf("O valor %d é maior do que o valor do nó atual\n", valor);

		if (getColor(node->left) == RED)
			node = rotateRightRb(node);

		if (getColor(node->right) == BLACK && getColor(node->right->left) == BLACK)
			node = moveRedToRight(node);

		node->right = removeElementRb(node->right, valor);
	}
	else
	{ // valor == node->info
		// printf("O valor %d é igual ao valor do nó atual\n", valor);

		if (valor == node->info && node->left == NULL && node->right == NULL)
		{ // Verifica se é uma folha
			// printf("O nó atual é uma folha, removendo o nó\n");
			free(node);
			return NULL;
		}

		if (node->right != NULL && getColor(node->right) == BLACK && node->right->left != NULL && getColor(node->right->left) == BLACK)
			node = moveRedToRight(node);

		if (valor == node->info)
		{
			// printf("Substituindo o valor %d do nó atual pelo maior elemento da subárvore esquerda\n", valor);
			if (node->left != NULL)
			{
				struct NO *x = searchLargest(node->left);
				node->info = x->info;
				node->left = removeElementRb(node->left, x->info);
			}
			else if (node->right != NULL)
			{
				// printf("O nó atual não tem filho esquerdo, substituindo o valor %d pelo menor elemento da subárvore direita\n", valor);

				struct NO *x = searchSmallest(node->right);
				node->info = x->info;
				node->right = removeElementRb(node->right, x->info);
			}
			else
			{
				// printf("O nó atual não tem filhos, removendo o nó\n");

				free(node);
				return NULL;
			}
		}
	}

	if (node == NULL)
	{ // Verifica se o nó atual é NULL
		// printf("O nó atual é NULL\n");
		return NULL;
	}

	// printf("Executando dellBalanceNodes para ajustar o balanceamento do nó\n");

	node = dellBalanceNodes(node); // Ajusta o balanceamento do nó após a remoção

	return node;
}

int removeRb(RbTree *root, int valor)
{
	/* if (searchElement(*root, valor)){
		struct NO *h = *root;
		*root = removeElementRb(h, valor);
		if (*root != NULL)
			(*root)->color = BLACK;
		return 1;
	}else
		return 0; */

	// printf("Chamando searchElement\n"); // Verifica se a função é chamada
	if (searchElement(*root, valor))
	{
		// printf("Entrou no if\n"); // Verifica se entra no if
		*root = removeElementRb(*root, valor); // Atualiza o ponteiro raiz após a remoção
											   // printf("\n\nEntrou.\n");
		if (*root != NULL)
			(*root)->color = BLACK; // Define a cor da nova raiz como preta
		return 1;
	}
	else
	{
		// printf("Entrou no else\n"); // Verifica se entra no else
		return 0;
	}
}

// árvore
/* int isEmpty(RbTree *root){ // verifica se esta vazia
	if (root == NULL)
		return 1;
	if (*root == NULL)
		return 1;
	return 0;
} */

/* int totalNodes(RbTree *root){ //total de nos da arvore
	if (root == NULL)
		return 0;
	if (*root == NULL)
		return 0;

	int alt_esq = totalNodes(&((*root)->left));
	int alt_dir = totalNodes(&((*root)->right));
	return (alt_esq + alt_dir + 1);
} */

/* int heightRb(RbTree *root){ //altura da arvore rubro negra
	if (root == NULL)
		return 0;
	if (*root == NULL)
		return 0;
	int alt_esq = heightRb(&((*root)->left));
	int alt_dir = heightRb(&((*root)->right));
	if (alt_esq > alt_dir)
		return (alt_esq + 1);
	else
		return (alt_dir + 1);
} */

void prinTree(RbTree *root)
{ // auxiliar da impressao da arvore rubro negra

	if (root == NULL)
	{
		printf("Árvore vazia.\n");
		return;
	}
	printTreeHelper(root, 0);
}

void printTreeHelper(RbTree *root, int indentLevel)
{ // impressao arvore rubro negra

	if (root == NULL)
	{
		// Árvore vazia, não há nada para imprimir
		printf("Árvore vazia.\n");
		// return;
	}
	if (*root == NULL)
	{
		return;
	}

	RbTree currentNode = *root;
	printTreeHelper(&(currentNode->right), indentLevel + 1);
	for (int i = 0; i < indentLevel; i++)
	{
		printf("    ");
	}
	if (currentNode != NULL)
	{
		printf("%d - %d\n", currentNode->info, getColor(currentNode)); // Acessar cor do nó por getColor(currentNode)

		printTreeHelper(&(currentNode->left), indentLevel + 1);
	}
}

void printProd(RbTree *root)
{ // auxiliar na impressao do produto
	printProdHelper(root, 0);
}

void printProdHelper(RbTree *root, int indentLevel)
{ // impressao produto
	if (*root != NULL)
	{
		printProdHelper(&((*root)->right), indentLevel + 1);

		for (int i = 0; i < indentLevel; i++)
			printf("    ");

		printf("%d (%d) - [ %s: %d ] \n", (*root)->info, (*root)->color, (*root)->name_prod, (*root)->qtd_prod); /* , (*root)->cod_prod, (*root)->qtd_prod) */
		printProdHelper(&((*root)->left), indentLevel + 1);
	}
}

void printProdEstoqueAux(RbTree *root)
{ // auxiliar na impressao do produto em estoque
	printProdEstoque(root, 0);
}

void printProdEstoque(RbTree *root, int indentLevel)
{ // impressao produto em estoque
	if (*root != NULL)
	{
		if ((*root)->qtd_prod != 0 && (*root)->qtd_prod > 0)
		{
			printf("%s : %d \n", (*root)->name_prod, (*root)->qtd_prod);
			// printf("%d : %s  \n",(*root)->qtd_prod, (*root)->name_prod);
		}
		printProdEstoque(&((*root)->right), indentLevel + 1);
		printProdEstoque(&((*root)->left), indentLevel + 1);
	}
}

void printProdCastrados(RbTree *root)
{ // auxiliar na impressao do produtos cadastrados
	printProdCastradosHelper(root, 0);
}

void printProdCastradosHelper(RbTree *root, int indentLevel)
{ // impressao produtos cadastrados
	if (*root != NULL)
	{
		printf("%d : %s  \n", (*root)->qtd_prod, (*root)->name_prod);
		printProdCastradosHelper(&((*root)->right), indentLevel + 1);
		printProdCastradosHelper(&((*root)->left), indentLevel + 1);
		// for (int i = 0; i < indentLevel; i++){}
	}
}

void imprimirString(struct NO *no)
{
	if (no == NULL || no->name_prod == NULL)
	{ // Nó inválido ou string não definida
		return;
	}
	printf("Nome do Produto: %s\n", no->name_prod);
}