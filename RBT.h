#ifndef RBT_H
#define RBT_H

#include <stdio.h>
#include <stdlib.h>

#include "dados.h"

struct NO{
	void *info;
	int color;
	struct NO *left;
	struct NO *right;
};

typedef struct NO *RbTree;

RbTree *createRbTree();
void freeNode(struct NO *node, void (*cb)(void *));
void freeRbTree(RbTree *root, void (*cb)(void *));

// Pesquisa e remoção de nós específicos
struct NO *searchSmaller(struct NO *node);
struct NO *removeSmaller(struct NO *node, void (*cb)(void *));
int isInTreeRb(RbTree *node, void *key, void (*cb)(void *, void *, void *));
struct NO *searchElement(RbTree *node, void *key, void (*cb)(void *, void *, void *));

int getColor(struct NO *node);
void changeColor(struct NO *node);

// Funções para rotação
struct NO *rotateLeftRb(struct NO *input);
struct NO *rotateRightRb(struct NO *input);

// Funções para correção de cor dos nós
struct NO *moveRedToLeft(struct NO *input);
struct NO *moveRedToRight(struct NO *input);
struct NO *balanceNodes(struct NO *input);

// Funções para inserção
int insertRb(RbTree *T, void *key, void (*cb)(void *, void *, void *));
struct NO *insertNodeRb(struct NO *root, void *key, int *ans, void (*cb)(void *, void *, void *));

// Funções para remoção
int removeRb(RbTree *root, void *key, void (*cb)(void *, void *, void *), void (*funcDeleta)(void *), void (*funcCopy)(void *, void *));
struct NO *removeElementRb(struct NO *root, void *key, void (*cb)(void *, void *, void *), void (*funcDeleta)(void *), void (*funcCopy)(void *, void *));

//Impressão da árvore pedida
void printRb(RbTree *root, void (*cb)(void *));

#endif
