#include <stdio.h>
#include <stdlib.h>
#include "RBT.h"

#define RED 1
#define BLACK 0

// Função auxiliar para criar um novo nó
RbTree *createRbTree()
{
	RbTree *root = (RbTree *)malloc(sizeof(RbTree));
	if (root != NULL)
		*root = NULL;
	return root;
}

void freeRbTree(RbTree *root, void (*cb)(void *))
{
	if (root == NULL)
		return;
	freeNode(*root, cb);
	free(root);
	root = NULL;
}

struct NO *searchSmaller(struct NO *node)
{
	/*
		Vai ao menor elemento da árvore (nó mais à esquerda)
	*/
	struct NO *n1 = node;
	struct NO *n2 = node->left;
	while (n2)
	{
		n1 = n2;
		n2 = n2->left;
	}
	return n1;
}

struct NO *removeSmaller(struct NO *node, void (*cb)(void *))
{ // ESSA DEVE LIBERAR A INFORMAÇÃO QUANDO FOR GENERICA
	if (node->left == NULL)
	{ // Caso o nó atual já seja o menor
		cb(node->info);
		free(node);
		return NULL;
	}
	if (getColor(node->left) == BLACK && getColor(node->left->left) == BLACK)
		node = moveRedToLeft(node);

	node->left = removeSmaller(node->left, cb);
	return balanceNodes(node);
}

int getColor(struct NO *node)
{
	if (node)
		return node->color;
	else
		return BLACK;
}

void changeColor(struct NO *node)
{
	// Altera a cor de um nó e de seus filhos
	if (node)
	{
		node->color = !node->color;
		if (node->right)
			node->right->color = !node->right->color;
		if (node->left)
			node->left->color = !node->left->color;
	}
}

struct NO *rotateLeftRb(struct NO *input)
{
	/*  a rotação pode criar uma violação nas regras da rb,
		outras funções são responsáveis por corrigir isso
	*/
	struct NO *aux = input->right;
	input->right = aux->left;
	aux->left = input;
	aux->color = input->color;
	input->color = RED;
	return aux; // retorna quem tomou o lugar de input na árvore
}

struct NO *rotateRightRb(struct NO *input)
{
	struct NO *aux = input->left;
	input->left = aux->right;
	aux->right = input;
	aux->color = input->color;
	input->color = RED;
	return aux;
}

struct NO *moveRedToLeft(struct NO *input)
{
	changeColor(input);
	if (getColor(input->right->left) == RED)
	{
		input->right = rotateRightRb(input->right);
		input = rotateLeftRb(input);
		changeColor(input);
	}
	return input;
}

struct NO *moveRedToRight(struct NO *input)
{
	changeColor(input);
	if (getColor(input->left->left) == RED)
	{
		input = rotateRightRb(input);
		changeColor(input);
	}
	return input;
}

struct NO *balanceNodes(struct NO *input)
{
	if (getColor(input->right) == RED)
		input = rotateLeftRb(input);
	if (input->left != NULL && getColor(input->right) == RED && getColor(input->left->left) == RED)
		input = rotateRightRb(input);
	if (getColor(input->left) == RED && getColor(input->right) == RED)
		changeColor(input);
	return input;
}

/*
		********************************
		********************************
		FUNÇÕES QUE PRECISAM DE CALLBACK
		********************************
		********************************
*/

void freeNode(struct NO *node, void (*cb)(void *))
{
	if (node == NULL)
		return;
	freeNode(node->left, cb);
	freeNode(node->right, cb);
	cb(node->info);
	free(node);
	node = NULL;
}

// o callback passado tem 2 args pois a função a ser usada deve comparar 2 elementos
int insertRb(RbTree *T, void *key, void (*cb)(void *, void *, void *))
{
	// Usa da função auxiliar para inserir e balancear a árvore
	int ans;

	*T = insertNodeRb(*T, key, &ans, cb);
	if ((*T) != NULL)
		(*T)->color = BLACK;

	return ans;
}

struct NO *insertNodeRb(struct NO *root, void *key, int *ans, void (*cb)(void *, void *, void *))
{
	if (!root)
	{ // a árvore tá vazia/chegou num nó folha
		struct NO *insert = (struct NO *)malloc(sizeof(struct NO));
		if (!insert)
		{ // não foi inserido
			*ans = 0;
			return NULL;
		}
		insert->info = key;
		insert->color = RED;
		insert->left = insert->right = NULL;
		*ans = 1;
		return insert;
	}
	// navegando até a posição onde o novo nó será inserido
	int *verify = (int *)malloc(sizeof(int));
	cb(key, root->info, verify);
	if (*verify == 0) // Se a chave for igual ao nó
		*ans = 0;
	else if (*verify == 2) // Se a chave for menor que o nó
		root->left = insertNodeRb(root->left, key, ans, cb);
	else
		root->right = insertNodeRb(root->right, key, ans, cb);
	// corrigindo questões de erros na coloração dos nós
	if (getColor(root->right) == RED && getColor(root->left) == BLACK)
		root = rotateLeftRb(root);
	if (getColor(root->left) == RED && getColor(root->left->left) == RED)
		root = rotateRightRb(root);
	if (getColor(root->left) == RED && getColor(root->right) == RED)
		changeColor(root);
	return root;
}

int removeRb(RbTree *root, void *key, void (*cb)(void *, void *, void *), void (*funcDeleta)(void *), void (*funcCopy)(void *, void *))
{
	if (isInTreeRb(root, key, cb))
	{
		struct NO *x = *root;
		*root = removeElementRb(x, key, cb, funcDeleta, funcCopy);
		if (*root != NULL)
			(*root)->color = BLACK;
		return 1; // remoção concluída
	}
	else
		return 0; // remoção não concluída
}

struct NO *removeElementRb(struct NO *root, void *key, void (*cb)(void *, void *, void *), void (*funcDeleta)(void *), void (*funcCopy)(void *, void *))
{
	int *verify = (int *)malloc(sizeof(int));
	cb(key, root->info, verify);
	if (*verify == 2)
	{ // Se o elemento a ser removido for menor que o elemento da raiz
		if (getColor(root->left) == BLACK && getColor(root->left->left) == BLACK)
			root = moveRedToLeft(root);
		root->left = removeElementRb(root->left, key, cb, funcDeleta, funcCopy);
	}
	else
	{ // Se ele for maior ou igual
		if (getColor(root->left) == RED)
		{
			root = rotateRightRb(root);
		}
		if ((*verify == 0) && root->right == NULL)
		{

			funcDeleta(root->info); // Deleta a informação do nó
			free(root);				// libera o nó
			return NULL;
		}
		if (getColor(root->right) == BLACK && getColor(root->right->left) == BLACK)
			root = moveRedToLeft(root);
		if (*verify == 0)
		{ // se ele for igual
			struct NO *x = searchSmaller(root->right);
			funcCopy(x->info, root->info);
			root->right = removeSmaller(root->right, funcDeleta);
		}
		else
			root->right = removeElementRb(root->right, key, cb, funcDeleta, funcCopy);
	}
	return balanceNodes(root);
}

int isInTreeRb(RbTree *node, void *key, void (*cb)(void *, void *, void *))
{ // testar essa função depois que conseguir testar a inserção
	if (node == NULL)
		return 0;
	struct NO *aux = *node;
	while (aux != NULL)
	{
		int *verify = (int *)malloc(sizeof(int));
		cb(key, aux->info, verify);
		if (*verify == 0)
		{
			return 1;
		}
		if (*verify == 1)
			aux = aux->right;
		else
			aux = aux->left;
	}
	return 0;
}

struct NO *searchElement(RbTree *node, void *key, void (*cb)(void *, void *, void *))
{
	if (node == NULL)
		return NULL;
	struct NO *aux = *node;
	while (aux != NULL)
	{
		int *verify = (int *)malloc(sizeof(int));
		cb(key, aux->info, verify);
		if (*verify == 0)
		{
			return aux;
		}
		if (*verify == 1)
			aux = aux->right;
		else
			aux = aux->left;
	}
	return NULL;
}

void printRb(RbTree *root, void (*cb)(void *))
{
	if (root == NULL)
		return;
	if (*root != NULL && (*root)->info != NULL)
	{
		printf("Endereco: %p | ", (void *)*root);
		if ((*root)->right != NULL)
			printf("Filho direito: %p | ", (void *)(*root)->right);
		else
			printf("Filho direito: NAO TEM | ");
		if ((*root)->left != NULL)
			printf("Filho esquerdo: %p | ", (void *)(*root)->left);
		else
			printf("Filho esquerdo: NAO TEM | ");
		if ((*root)->color == RED)
			printf("Cor: Vermelho | Valor: ");
		else
			printf("Cor: Preto | Valor: ");
		cb((*root)->info);
		printRb(&((*root)->left), cb);
		printRb(&((*root)->right), cb);
	}
}
