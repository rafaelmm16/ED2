#include <stdio.h>
#include <stdlib.h>

struct NO{
	int info;
	int color;
	struct NO *left;
	struct NO *right;
	
	char* name_prod;
	int cod_prod;
	int qtd_prod;
};

typedef struct NO *RbTree;

RbTree *createRbTree();
void freeRbTree(RbTree* root);
int insertRb(RbTree* root, int valor);
int removeRb(RbTree  *root, int valor);
//int searchElement(RbTree *root, int valor);
int isEmpty(RbTree *root);
int totalNodes(RbTree *root);
int heightRb(RbTree *root);

void prinTree(RbTree *root);
void PrintTreeHelper(RbTree *root, int indentLevel);
void imprimirString(struct NO* no);