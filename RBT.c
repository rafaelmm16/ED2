#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "RBT.h"

#define RED 1
#define BLACK 0

// Função auxiliar para criar um novo nó
RbTree *createRbTree(){
	RbTree *root = (RbTree *)malloc(sizeof(RbTree));
	if (root != NULL)
	{
		*root = NULL;
	}
	return root;
}

void freeNode(struct NO *no){
	if (no == NULL)
		return;
	freeNode(no->left);
	freeNode(no->right);
	free(no);
	no = NULL;
}

void freeRbTree(RbTree *root){
	if (root == NULL)
		return;
	freeNode(*root);
	free(root);
}

// CONSULTA ARVORE
// ************
struct NO *searchElement(struct NO *raiz, int valor){
	if (raiz == NULL || raiz->info == valor){
		// Retorna a raiz se for nula ou se o valor correspondente for encontrado
		return raiz;
	}

	if (valor < raiz->info){
		// Se o valor for menor que o valor do nó atual, realiza a busca na subárvore esquerda
		return searchElement(raiz->left, valor);
	}
	else{
		// Se o valor for maior que o valor do nó atual, realiza a busca na subárvore direita
		return searchElement(raiz->right, valor);
	}
}

// Rotações
struct NO *rotateLeftRb(struct NO *input){
	struct NO *aux;

	aux = input->right;
	input->right = aux->left;
	aux->left = input;
	aux->color = input->color;
	input->color = RED;
	return aux;
}

struct NO *rotateRightRb(struct NO *input){
	struct NO *aux = input->left;

	input->left = aux->right;
	aux->right = input;
	aux->color = input->color;
	input->color = RED;
	return aux;
}

// Informações do No
int getColor(struct NO *node){
	if (node)
		return node->color;
	else
		return BLACK;
}

void changeColor(struct NO *node){
	// Altera a cor de um nó e de seus filhos
	node->color = !node->color;
	if (node->left != NULL)
		node->left->color = !node->left->color;
	if (node->right != NULL)
		node->right->color = !node->right->color;
}

// INSERCAO
// ************
int BlackHeight(struct NO *node)
{
	if (node == NULL) {
        return 0;
    }
    
    int leftBlackHeight = BlackHeight(node->left);
    int rightBlackHeight = BlackHeight(node->right);

    int currentBlackHeight = getColor(node) == BLACK ? 1 : 0;
    
    return leftBlackHeight - rightBlackHeight + currentBlackHeight;
}

struct NO *insertNodeRb(struct NO *root, int key, int qtd, const char *name, int *ans){
	//int altura = BlackHeight(root);
	if (!root){
		struct NO *insert = (struct NO *)malloc(sizeof(struct NO));
		if (!insert){ // não foi inserido
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
        
        insert->qtd_prod = qtd;
        *ans = 1;
        return insert;
	}
	
	// If the key already exists in the tree, return NULL.
	if (key == root->info)
	{
		*ans = 0;
		return NULL;
	}

	// If the key is less than the root's key, recursively insert the node into the left subtree.
	if (key < root->info)
	{
		root->left = insertNodeRb(root->left, key, qtd,name, ans);
	}
	// Otherwise, recursively insert the node into the right subtree.
	else
	{
		root->right = insertNodeRb(root->right, key, qtd,name, ans);
	}

	// Check if the tree is balanced after the insertion.
	if (*ans)
	{
		// If the right child of the root is red, perform a left rotation.
		if (root->right != NULL && root->right->color == RED)
		{
			root = rotateLeftRb(root);
		}

		// If the left child of the root is red and its left child is also red, perform a right rotation.
		if (root->left != NULL && root->left->color == RED && root->left->left != NULL && root->left->left->color == RED)
		{
			root = rotateRightRb(root);
		}

		// If the root is red and both of its children are black, change the color of the root to black.
		if ((root != NULL && root->color == RED 
		&& root->left != NULL && root->left->color == BLACK 
		&& root->right != NULL && root->right->color == BLACK))
		{
			root->color = BLACK;
		}
	}

	return root;
}

int insertRb(RbTree *root, int valor, int qtd, const char *name, char **name_prod) {
    int ans;

    free(*name_prod); // Libera a memória anterior, se necessário
    *name_prod = (char *)malloc((strlen(name) + 1) * sizeof(char)); // Aloca memória suficiente para a nova string
    
    int i = 0;
    while (name[i] != '\0') {
        if (name[i] == ' ') {
            (*name_prod)[i] = '\0';
            break;
        }
        (*name_prod)[i] = name[i];
        i++;
    }
    
    *root = insertNodeRb(*root, valor, qtd, *name_prod, &ans); // Faz o tratamento das possíveis violações da árvore rubro-negra

    if ((*root) != NULL) // Seta a cor da raiz para preta, se necessário
        (*root)->color = BLACK;

    return ans;
}



void adicionarQuantidade(struct NO *no, int key, int quantidade)
{
	if (no == NULL)
	{
		// Nó inválido
		return;
	}

	// Procura o nó com a chave especificada
	while (no != NULL && key != no->info)
	{
		if (key < no->info)
		{
			no = no->left;
		}
		else
		{
			no = no->right;
		}
	}

	// Se o nó existir, adiciona a quantidade ao nó correspondente
	if (no != NULL && key == no->info)
	{
		no->qtd_prod += quantidade;
	}
}

void addInfo(struct NO *no,int qtd) { //adicionar informações sobre o produto: quantidade
	if (no == NULL)	{ // Nó inválido
		return;
	}
	//no->cod_prod = cod;
	no->qtd_prod = qtd;
}

void addName(struct NO *no, const char *name){ //adicionar informações sobre o produto: nome
	if (no == NULL)	{// Nó inválido
		return;
	}
	
	free(no->name_prod); // Libera a memória anterior, se necessário
	no->name_prod = (char *)malloc((strlen(name) + 1) * sizeof(char)); // Aloca memória suficiente para a nova string

	// Copia a nova string para o campo infoString
	strcpy(no->name_prod, name);
}

void changeInfo(struct NO *root, int valorAntigo, int novoValor){
	struct NO *no = searchElement(root, valorAntigo);

	if (no == NULL)	{
		// Nó não encontrado
		return;
	}
	no->qtd_prod = novoValor;
}


// Remoção
struct NO *balanceNodes(struct NO *node){
	
	if (getColor(node->right) == RED) // no Vermelho sempre filho a esquerda
		node = rotateLeftRb(node);

	// Filho da esquerda e neto da esquerda s�o vermelhos
	if (node->left != NULL && getColor(node->left) == RED && getColor(node->left->left) == RED)
		node = rotateRightRb(node);

	// 2 filhos Vermelhos: troca cor!
	if (getColor(node->left) == RED && getColor(node->right) == RED)
		changeColor(node);

	return node;
}

struct NO *moveRedToLeft(struct NO *node){
	changeColor(node);
	if (getColor(node->right->left) == RED){
		node->right = rotateRightRb(node->right);
		node = rotateLeftRb(node);
		changeColor(node);
	}
	return node;
}

struct NO *moveRedToRight(struct NO *node){
	changeColor(node);
	if (getColor(node->left->left) == RED){
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
//impressao arvore rubro negra
void prinTree(RbTree *root)
{
	printTreeHelper(root, 0);
}

void printTreeHelper(RbTree *root, int indentLevel)
{
	if (*root != NULL)
	{
		printTreeHelper(&((*root)->right), indentLevel + 1);

		for (int i = 0; i < indentLevel; i++)
			printf("    ");

		printf("%d (%d)\n", (*root)->info, (*root)->color); /* , (*root)->cod_prod, (*root)->qtd_prod) */
		printTreeHelper(&((*root)->left), indentLevel + 1);
	}
}

//impressao produto
void printProd(RbTree *root)
{
	printProdHelper(root, 0);
}

void printProdHelper(RbTree *root, int indentLevel)
{
	if (*root != NULL)
	{
		printProdHelper(&((*root)->right), indentLevel + 1);

		for (int i = 0; i < indentLevel; i++)
			printf("    ");

		printf("%d (%d) - [ %s: %d ] \n", (*root)->info, (*root)->color, (*root)->name_prod,(*root)->qtd_prod); /* , (*root)->cod_prod, (*root)->qtd_prod) */
		printProdHelper(&((*root)->left), indentLevel + 1);
	}
}

void imprimirString(struct NO *no)
{
	if (no == NULL || no->name_prod == NULL)
	{
		// Nó inválido ou string não definida
		return;
	}

	printf("Nome do Produto: %s\n", no->name_prod);
}