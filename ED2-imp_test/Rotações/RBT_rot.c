#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "RBT_rot.h"

#define RED 1
#define BLACK 0

// Função auxiliar para criar um novo nó
RbTree *createRbTree(){
	RbTree *root = (RbTree *)malloc(sizeof(RbTree));
	if (root != NULL){
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

// PROPRIEDADES
// ************
int getColor(struct NO *node)
{
    if (node)
        return node->color;
    else
        return BLACK;
}

// ROTACAO
// ************
void changeColor(struct NO *node)
{
	// Altera a cor de um nó e de seus filhos
	if ((node->left != NULL) || (node->right != NULL) ){
		node->color = !node->color;
	}
	
	if (node->left != NULL)
		node->left->color = !node->left->color;
	if (node->right != NULL)
		node->right->color = !node->right->color;
}
struct NO* rotateRightRb(struct NO* root) {
    struct NO* newRoot = root->left;
    struct NO* newRootRight = newRoot->right;

    root->left = newRootRight;
    newRoot->right = root;

    // Atualizar as cores corretamente
    newRoot->color = root->color;
    root->color = RED;

    // Atualizar as cores dos filhos
    if (newRootRight) {
        newRootRight->color = BLACK;
    }

    return newRoot;
}

struct NO* rotateLeftRb(struct NO* root) {
    struct NO* newRoot = root->right;
    struct NO* newRootLeft = newRoot->left;

    root->right = newRootLeft;
    newRoot->left = root;

    // Atualizar as cores corretamente
    newRoot->color = root->color;
    root->color = RED;

    // Atualizar as cores dos filhos
    if (newRootLeft) {
        newRootLeft->color = BLACK;
    }

    return newRoot;
}

// INSERÇÃO
// ************
struct NO* insertNodeRb(struct NO* root, int key, int quant, const char *name, int* ans) {
    if (!root) {
        struct NO* insert = (struct NO*)malloc(sizeof(struct NO));
        if (!insert) { // não foi inserido
            *ans = 0;
            return NULL;
        }

        insert->info = key;
        insert->color = RED;
        insert->left = insert->right = NULL;
        //insert->name_prod = name;
        //insert->cod_prod = 0;
        insert->qtd_prod = quant;

		// Adicionar o nome do produto
        insert->name_prod = (char *)malloc((strlen(name) + 1) * sizeof(char));
        strcpy(insert->name_prod, name);

        *ans = 1;
        return insert;
    }

    if (key == root->info) {
        *ans = 0;
        return NULL;
    }

    if (key < root->info) {
        // Navegue para a subárvore esquerda
        root->left = insertNodeRb(root->left, key,quant, name, ans);

        // Verifique as propriedades da árvore vermelho-preto e faça as rotações e alterações de cor necessárias
        if (root->left && getColor(root->left) == RED && getColor(root->left->left) == RED) {
            // Caso 2: nodo adicionado à esquerda e irmão com cor vermelha
            if (root->right && getColor(root->right) == RED) {
                root->color = RED;
                root->left->color = BLACK;
                root->right->color = BLACK;
            }
            else {
                root = rotateRightRb(root);
                root->right->color = RED;
                root->color = BLACK;
            }
        }
        else if (root->left && getColor(root->left) == RED && getColor(root->left->right) == RED) {
            // Caso 1: pai e tio vermelhos
            if (root->right && getColor(root->right) == RED) {
                root->color = RED;
                root->left->color = BLACK;
                root->right->color = BLACK;
            }
            else {
                root->left = rotateLeftRb(root->left);
                root = rotateRightRb(root);
                root->color = BLACK;
                root->right->color = RED;
            }
        }
    } else {
        // Navegue para a subárvore direita
        root->right = insertNodeRb(root->right, key, quant, name, ans);

        // Verifique as propriedades da árvore vermelho-preto e faça as rotações e alterações de cor necessárias
        if (root->right && getColor(root->right) == RED && getColor(root->right->right) == RED) {
            // Caso 2: nodo adicionado à direita e irmão com cor vermelha
            if (root->left && getColor(root->left) == RED) {
                root->color = RED;
                root->left->color = BLACK;
                root->right->color = BLACK;
            }
            else {
                root = rotateLeftRb(root);
                root->left->color = RED;
                root->color = BLACK;
            }
        }
        else if (root->right && getColor(root->right) == RED && getColor(root->right->left) == RED) {
            // Caso 1: pai e tio vermelhos
            if (root->left && getColor(root->left) == RED) {
                root->color = RED;
                root->left->color = BLACK;
                root->right->color = BLACK;
            }
            else {
                root->right = rotateRightRb(root->right);
                root = rotateLeftRb(root);
                root->color = BLACK;
                root->left->color = RED;
            }
        }
    }

    return root;
}

int insertRb(RbTree* root, int valor, int quant, const char *name, char **name_prod) {
    int ans;

	free(*name_prod); // Libera a memória anterior, se necessário
    *name_prod = (char *)malloc((strlen(name) + 1) * sizeof(char)); // Aloca memória suficiente para a nova string

	int i = 0;
	//tratamento de inserção de um tipo char/ string
    while (name[i] != '\0') {
        if (name[i] == ' ') {
            (*name_prod)[i] = '\0';
            break;
        }
        (*name_prod)[i] = name[i];
        i++;
    }


    *root = insertNodeRb(*root, valor, quant, *name_prod, &ans);
	//free(*name);
    if ((*root) != NULL)
        (*root)->color = BLACK;

    return ans;
}
/* 
void adicionarInformacoes(struct NO *no, int cod, int qtd)
{
	if (no == NULL)
	{
		// Nó inválido
		return;
	}

	//no->cod_prod = cod;
	no->qtd_prod = qtd;
} */

void adicionarName(struct NO *no, const char *name)
{
	if (no == NULL)
	{
		// Nó inválido
		return;
	}

	// Libera a memória anterior, se necessário
	free(no->name_prod);

	// Aloca memória suficiente para a nova string
	no->name_prod = (char *)malloc((strlen(name) + 1) * sizeof(char));

	// Copia a nova string para o campo infoString
	strcpy(no->name_prod, name);
}

void trocarInfo(struct NO *root, int valorAntigo, int novoValor)
{
	struct NO *no = searchElement(root, valorAntigo);

	if (no == NULL)
	{
		// Nó não encontrado
		return;
	}

	no->info = novoValor;
}

// REMOCAOO
// ************
struct NO *dellBalanceNodes(struct NO *node)
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
	return dellBalanceNodes(node);
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
	return dellBalanceNodes(node);
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
	printTreeHelper(root, 0);
}

void printTreeHelper(RbTree *root, int indentLevel)
{
	if (*root != NULL)
	{
		printTreeHelper(&((*root)->right), indentLevel + 1);

		for (int i = 0; i < indentLevel; i++)
			printf("    ");

		printf("%d(%d) - [%d: %s]\n", (*root)->info, (*root)->color, (*root)->qtd_prod, (*root)->name_prod); // , (*root)->cod_prod, (*root)->qtd_prod)
		printTreeHelper(&((*root)->left), indentLevel + 1);
	}
} 

void imprimirString(struct NO *no)
{
	if (no == NULL)
	{
		// Nó inválido
		return;
	}

	if (no->name_prod == NULL)
	{
		// String não definida
		return;
	}

	printf("Nome do Produto: %s\n", no->name_prod);
}