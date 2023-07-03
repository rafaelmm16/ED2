#include <stdio.h>
#include <stdlib.h>

struct NO{
	int info;
	int color;
	struct NO *left;
	struct NO *right;
	char* name_prod;
	int qtd_prod;
};

typedef struct NO *RbTree;

RbTree *createRbTree();
void freeRbTree(RbTree* root);
int insertRb(RbTree *root, int valor, int qtd, const char *name, char **name_prod);
int removeRb(RbTree  *root, int valor);
//int searchElement(RbTree *root, int valor);
int isEmpty(RbTree *root);
int totalNodes(RbTree *root);
int heightRb(RbTree *root);

void prinTree(RbTree *root);
void printTreeHelper(RbTree *node, int indentLevel);
void imprimirString(struct NO* no);
void printProd(RbTree *root);
void printProdHelper(RbTree *root, int indentLevel);