#include <stdio.h>
#include <stdlib.h>

struct NO{
	int info;
	int color;
	struct NO *left;
	struct NO *right;

	char name_prod[100];
	int cod_prod;
	int qtd_prod;
};

typedef struct NO *RbTree;

RbTree *createRbTree();
void freeRbTree(RbTree* root);
int insertRb(RbTree* root, int valor);
int removeRb(RbTree  *root, int valor);
int searchElement(RbTree *root, int valor);
int isEmpty(RbTree *root);
int totalNodes(RbTree *root);
int heightRb(RbTree *root);
void inOrder(RbTree *root, int H);
void posOrder(RbTree *root, int H);
void preOrder(RbTree *root,int H);

void prinTree(RbTree *root);
void PrintTreeHelper(RbTree *node, int indentLevel);
