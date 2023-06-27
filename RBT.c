#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "RBT.h"

#define RED 1
#define BLACK 0

// Função auxiliar para criar um novo nó
RbTree *createRbTree()
{
	RbTree *root = (RbTree *)malloc(sizeof(RbTree));
	if (root != NULL)
	{
		*root = NULL;
	}
	return root;
}

// LIBERAR
// ************
void freeNode(struct NO *no)
{
	if (no == NULL)
		return;
	freeNode(no->left);
	freeNode(no->right);
	free(no);
	no = NULL;
}

void freeRbTree(RbTree *root)
{
	if (root == NULL)
		return;
	freeNode(*root);
	free(root);
}

// CONSULTA ARVORE
// ************
struct NO *searchElement(struct NO *raiz, int valor)
{
    if (raiz == NULL || raiz->info == valor)
    {
        // Retorna a raiz se for nula ou se o valor correspondente for encontrado
        return raiz;
    }

    if (valor < raiz->info)
    {
        // Se o valor for menor que o valor do nó atual, realiza a busca na subárvore esquerda
        return searchElement(raiz->left, valor);
    }
    else
    {
        // Se o valor for maior que o valor do nó atual, realiza a busca na subárvore direita
        return searchElement(raiz->right, valor);
    }
}

// ROTACAO
// ************
struct NO *rotateLeftRb(struct NO *No1)
{
	struct NO *No2 = No1->right;
	No1->right = No2->left;
	No2->left = No1;
	No2->color = No1->color;
	No1->color = RED;
	return No2;
}

struct NO *rotateRightRb(struct NO *No1)
{
	struct NO *No2 = No1->left;
	No1->left = No2->right;
	No2->right = No1;
	No2->color = No1->color;
	No1->color = RED;
	return No2;
}

// PROPRIEDADES
// ************
int getColor(struct NO* node)
{
	if (node)
		return node->color;
	else
		return BLACK;
}

void changeColor(struct NO* node)
{
	// Altera a cor de um nó e de seus filhos
	node->color = !node->color;
    if(node->left != NULL)
        node->left->color = !node->left->color;
    if(node->right != NULL)
        node->right->color = !node->right->color;
}

// INSERCAO
// ************

struct NO *insertNodeRb(struct NO *root, int key, int *ans)
{
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
		insert->name_prod = NULL;
		insert->cod_prod = 0;
		insert->qtd_prod = 0;
		*ans = 1;
		return insert;
	}

	if(key == root->info)
        *ans = 0;// Valor duplicado
    else{
        if(key < root->info)
            root->left = insertNodeRb(root->left,key,ans);
        else
            root->right = insertNodeRb(root->right,key,ans);
    }

	// Nó Vermelho é sempre filho à esquerda
	if ((root->right != NULL && getColor(root->right) == RED) && getColor(root->left) == BLACK)
		root = rotateLeftRb(root);

	// Filho e Neto são vermelhos
	// Filho vira pai de 2 nós vermelhos
	if ((root->left != NULL && getColor(root->left) == RED) && getColor(root->left->left) == RED)
		root = rotateRightRb(root);

	if ((getColor(root->right) == RED && getColor(root->right->right) == RED) && getColor(root->left) == RED
	/* || (getColor(root->right) == RED && getColor(root->right->left) == RED) */)
		changeColor(root);

	// 2 filhos Vermelhos: troca cor!
	 /* if(getColor(root->left) == RED && getColor(root->right) == RED)
        changeColor(root); */

	return root;
}

int insertRb(RbTree *root, int valor)
{
	int ans;

	*root = insertNodeRb(*root, valor, &ans);
	if ((*root) != NULL)
		(*root)->color = BLACK;

	return ans;
}

void adicionarInformacoes(struct NO* no, int cod, int qtd)
{
    if (no == NULL)
    {
        // Nó inválido
        return;
    }

	no->cod_prod = cod;
    no->qtd_prod = qtd;
}

void adicionarName(struct NO* no, const char* name)
{
    if (no == NULL)
    {
        // Nó inválido
        return;
    }
    
    // Libera a memória anterior, se necessário
    free(no->name_prod);

    // Aloca memória suficiente para a nova string
    no->name_prod = (char*)malloc((strlen(name) + 1) * sizeof(char));

    // Copia a nova string para o campo infoString
    strcpy(no->name_prod, name);
}

void trocarInfo(struct NO* root, int valorAntigo, int novoValor)
{
    struct NO* no = searchElement(root, valorAntigo);

    if (no == NULL)
    {
        // Nó não encontrado
        return;
    }

    no->info = novoValor;
}

// REMOCAOO
// ************
struct NO *balanceNodes(struct NO *node)
{
	// n� Vermelho � sempre filho � esquerda
	if (getColor(node->right) == RED)
		node = rotateLeftRb(node);

	// Filho da direita e neto da esquerda s�o vermelhos
	// if(node->left != NULL && getColor(node->right) == RED && getColor(node->left->left) == RED)

	// Filho da esquerda e neto da esquerda s�o vermelhos
	if (node->left != NULL && getColor(node->left) == RED && getColor(node->left->left) == RED)
		node = rotateRightRb(node);

	// 2 filhos Vermelhos: troca cor!
	if (getColor(node->left) == RED && getColor(node->right) == RED)
		changeColor(node);

	return node;
}

struct NO *moveRedToLeft(struct NO *node)
{
	changeColor(node);
	if (getColor(node->right->left) == RED)
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
	if (getColor(node->left->left) == RED)
	{
		node = rotateRightRb(node);
		changeColor(node);
	}
	return node;
}

struct NO *removeSmaller(struct NO *node)
{
	if (node->left == NULL)
	{
		free(node);
		return NULL;
	}
	if (getColor(node->left) == BLACK && getColor(node->left->left) == BLACK)
		node = moveRedToLeft(node);

	node->left = removeSmaller(node->left);
	return balanceNodes(node);
}

struct NO *searchSmaller(struct NO *atual)
{
	struct NO *no1 = atual;
	struct NO *no2 = atual->left;
	while (no2 != NULL)
	{
		no1 = no2;
		no2 = no2->left;
	}
	return no1;
}

struct NO *removeElementRb(struct NO *node, int valor)
{
	if (valor < node->info)
	{
		if (getColor(node->left) == BLACK && getColor(node->left->left) == BLACK)
			node = moveRedToLeft(node);

		node->left = removeElementRb(node->left, valor);
	}
	else
	{
		if (getColor(node->left) == RED)
			node = rotateRightRb(node);

		if (valor == node->info && (node->left == NULL))
		{
			free(node);
			return NULL;
		}

		if (getColor(node->right) == BLACK && getColor(node->right->left) == BLACK)
			node = moveRedToRight(node);

		if (valor == node->info)
		{
			struct NO *x = searchSmaller(node->right);
			node->info = x->info;
			node->right = removeSmaller(node->right);
		}
		else
			node->right = removeElementRb(node->right, valor);
	}
	return balanceNodes(node);
}

int removeRb(RbTree *root, int valor)
{
	if (searchElement(*root, valor))
	{
		struct NO *h = *root;
		*root = removeElementRb(h, valor);
		if (*root != NULL)
			(*root)->color = BLACK;
		return 1;
	}
	else
		return 0;
}

// PROPRIEDADES ARVORE
// ************
int isEmpty(RbTree *root)
{
	if (root == NULL)
		return 1;
	if (*root == NULL)
		return 1;
	return 0;
}

int totalNodes(RbTree *root)
{
	if (root == NULL)
		return 0;
	if (*root == NULL)
		return 0;

	int alt_esq = totalNodes(&((*root)->left));
	int alt_dir = totalNodes(&((*root)->right));
	return (alt_esq + alt_dir + 1);
}

int heightRb(RbTree *root)
{
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
}

// PERCURSO
// ************
void posOrder(RbTree *root, int H)
{
	if (root == NULL)
		return;

	if (*root != NULL)
	{
		posOrder(&((*root)->left), H + 1);
		posOrder(&((*root)->right), H + 1);

		if ((*root)->color == RED)
			printf("%d  Vermelho: H(%d) \n", (*root)->info, H);
		else
			printf("%d  Preto: H(%d) \n", (*root)->info, H);
	}
}

void inOrder(RbTree *root, int H)
{
	if (root == NULL)
		return;

	if (*root != NULL)
	{
		inOrder(&((*root)->left), H + 1);

		if ((*root)->color == RED)
			printf("%dR: H(%d) \n", (*root)->info, H);
		else
			printf("%dB: H(%d) \n", (*root)->info, H);

		inOrder(&((*root)->right), H + 1);
	}
}

void preOrder(RbTree *root, int H)
{
	if (root == NULL)
		return;

	if (*root != NULL)
	{
		if ((*root)->color == RED)
			printf("%d  Vermelho: H(%d) \n", (*root)->info, H);
		else
			printf("%d  Preto: H(%d) \n", (*root)->info, H);

		preOrder(&((*root)->left), H + 1);
		preOrder(&((*root)->right), H + 1);
	}
}

void prinTree(RbTree *root)
{
	PrintTreeHelper(root, 0);
}

void PrintTreeHelper(RbTree *root, int indentLevel)
{
	if (*root != NULL)
	{
		PrintTreeHelper(&((*root)->right), indentLevel + 1);

		for (int i = 0; i < indentLevel; i++)
			printf("    ");

		printf("%d - %d - %d - %d\n", (*root)->info, (*root)->color, (*root)->cod_prod, (*root)->qtd_prod);
		PrintTreeHelper(&((*root)->left), indentLevel + 1);
	}
}

void imprimirString(struct NO* no)
{
    if (no == NULL || no->name_prod == NULL)
    {
        // Nó inválido ou string não definida
        return;
    }
    
    printf("Nome do Produto: %s\n", no->name_prod);
}