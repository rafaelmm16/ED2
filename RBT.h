// ED2_TrabPratico_Grupo5_[IasminMarquesPereira][RafaelMendesMerlo]
#include <stdio.h>
#include <stdlib.h>

struct NO{ //estrutura do NO
	int info; //chave do produto = chave da arvore
	int color;//cor do no (red or black)
	struct NO *left; //no filho esquerdo
	struct NO *right; //no filho direito
	char* name_prod; //nome do produto
	int qtd_prod; //quantidade do produto
};

typedef struct NO *RbTree;

//funções utilizadas no codigo;
RbTree *createRbTree();
void freeNode(struct NO *no);
void freeRbTree(RbTree *root);
struct NO *searchElement(struct NO *root, int current);
int returnQuant(struct NO *root, int current, int qnt);
struct NO *rotateLeftRb(struct NO *root);
struct NO *rotateRightRb(struct NO *root);
int getColor(struct NO *node);
void changeColor(struct NO *node);
int insertRb(RbTree *root, int current, int qtd, const char *name, char **name_prod);
void changeInfo(struct NO *root, int oldValue, int newValue);
struct NO *dellBalanceNodes(struct NO *node);
struct NO *moveRedToLeft(struct NO *node);
struct NO *moveRedToRight(struct NO *node);
struct NO *searchSmallest(struct NO *node);
struct NO *searchLargest(struct NO *node);
struct NO *removeElementRb(struct NO *node, int current);
int removeRb(RbTree *root, int current);
void prinTree(RbTree *root);
void printTreeHelper(RbTree *root, int indentLevel);
void printProd(RbTree *root);
void printProdHelper(RbTree *root, int indentLevel);
void printProdEstoqueAux(RbTree *root);
void printProdEstoque(RbTree *root, int indentLevel);
void printProdCastrados(RbTree *root);
void printProdCastradosHelper(RbTree *root, int indentLevel);
