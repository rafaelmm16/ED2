#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "RBT.h"

#define RED 1
#define BLACK 0


RbTree *createRbTree(){ // Função auxiliar para criar um novo nó
	RbTree *root = (RbTree *)malloc(sizeof(RbTree));
	if (root != NULL){
		*root = NULL;
	}
	return root;
}

void freeNode(struct NO *no){ //Liberar o No
	if (no == NULL)
		return;
	freeNode(no->left);
	freeNode(no->right);
	free(no);
	no = NULL;
}

void freeRbTree(RbTree *root){ //Liberar a árvore
	if (root == NULL)
		return;
	freeNode(*root);
	free(root);
}


// Encontrar Elemento - Busca
struct NO *searchElement(struct NO *raiz, int valor){
	if (raiz == NULL || raiz->info == valor){
		return raiz; // retorna o valor encontrado ou a raiz (se for nula)
	}

	if (valor < raiz->info){ // Se o valor for menor que o valor do nó atual, realiza a busca na subárvore esquerda
		return searchElement(raiz->left, valor);
	}else{
		// Se o valor for maior que o valor do nó atual, realiza a busca na subárvore direita
		return searchElement(raiz->right, valor);
	}
}


// Rotações
struct NO *rotateLeftRb(struct NO *No1){ // Rotação a esquerda
	struct NO *No2 = No1->right;
	No1->right = No2->left;
	No2->left = No1;
	No2->color = No1->color;
	No1->color = RED;
	return No2;
}

struct NO *rotateRightRb(struct NO *No1){ // Rotação a Direita
	struct NO *No2 = No1->left;
	No1->left = No2->right;
	No2->right = No1;
	No2->color = No1->color;
	No1->color = RED;
	return No2;
}

// Informações do No
int getColor(struct NO *node){ //pegar o cor do NO
	if (node)
		return node->color;
	else
		return BLACK; // NULL
}

void changeNodeColor (struct NO *node){ //Altera a cor de um nó
	if(node!=NULL)
		node->color = !node->color;
}

void changeColor(struct NO *node){ // Altera a cor de um nó e de seus filhos	
	node->color = !node->color;
	if (node->left != NULL)
		node->left->color = !node->left->color;
	if (node->right != NULL)
		node->right->color = !node->right->color;
}

int BlackHeight(struct NO *node){ //altura negra
	if (node == NULL) {
        return 0;
    }
    
    int leftBlackHeight = BlackHeight(node->left);
    int rightBlackHeight = BlackHeight(node->right);

    int currentBlackHeight = getColor(node) == BLACK ? 1 : 0; //se no == BLACK, retorna 1, caso contrario 0;
    
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
		insert->name_prod = name;
		//insert->cod_prod = 0;
		insert->qtd_prod = qtd;
		*ans = 1;
		return insert;
	}
	
	if (key == root->info){  // Valor duplicado inserido
		printf("Valor inserido Inválido.\n");
		*ans = 0;
	}else{
		if (key < root->info)
			root->left = insertNodeRb(root->left, key, qtd,name, ans);
		else
			root->right = insertNodeRb(root->right, key, qtd,name, ans);
	}

	//printf("\n Altura Preta %d \n", altura);
	
/* 	//dois Rubros seguidos/ sequencia
	if(root->right=!NULL){
		if ((getColor(root->right) == RED && getColor(root->right->right) == RED) || (getColor(root->right) == RED && getColor(root->right->left) == RED){
			changeColor(root);
		}
			
	}

	if(root->left!=NULL){
		if((getColor(root->left) == RED && getColor(root->left->right) == RED) || (getColor(root->left) == RED && getColor(root->left->left) == RED))){
			changeColor(root);
		}
	}
	
	if(root!=NULL && root->color==RED){
		if(root->right!=NULL){
			if ((getColor(root->right) == RED && getColor(root->right->right) == RED) || (getColor(root->right) == RED && getColor(root->right->left) == RED)){
				changeColor(root);
			}
				
		}

		if(root->left!=NULL){
			if((getColor(root->left) == RED && getColor(root->left->right) == RED) || (getColor(root->left) == RED && getColor(root->left->left) == RED)){
				changeColor(root);
			}
		}
	}

	// If the root is red and both of its children are black, change the color of the root to black.
	
	if (root != NULL && root->color == RED){
		if(root->left != NULL && root->left->color == BLACK && root->right != NULL && root->right->color == BLACK){
			root->color=BLACK;
		}

	}

	//dois vermelhos seguidos 
	if (root != NULL && root->color == RED){
		if(root->left != NULL && root->left->color == RED || root->right != NULL && root->right->color == RED){
			root->color==BLACK;
			//changeColor(root);

		}
	}





	if (root != NULL && root->color == BLACK){
		if(root->left != NULL && root->left->color == RED && root->right != NULL && root->right->color == RED){
			changeColor(root);
		}
	}  */

	//dois Rubros seguidos/ sequencia
	if ((getColor(root->right) == RED && getColor(root->right->right) == RED && (root->right)!=NULL && (root->right->right)!=NULL) 
	|| (getColor(root->right) == RED && getColor(root->right->left) == RED && (root->right)!=NULL && (root->right->left)!=NULL)
	|| (getColor(root->left) == RED && getColor(root->left->right) == RED && (root->left)!=NULL && (root->left->right) !=NULL)
	|| (getColor(root->left) == RED && getColor(root->left->left) == RED && (root->left)!=NULL && (root->left->left) !=NULL))
		changeColor(root);


	//o tio de 1 é rubro
	if (getColor(root->left) == RED && getColor(root->right) == RED && getColor(root->left->left) == RED && getColor(root) == BLACK){
		changeColor(root); // muda a cor da root e de seus filhos;
		root->color = RED;
		//changeColor(root->left);
		//changeColor(root->right);	
	}
	
	//Condições para as rotações
	if ((root->left != NULL && getColor(root) == BLACK && getColor(root->left) == RED &&  root->left->right!=NULL && getColor(root->left->right) == RED)
		|| (root->right != NULL && getColor(root) == BLACK && getColor(root->right) == RED && root->right->left!=NULL && getColor(root->right->left) == RED))
		{
			printf("rodou direita");
			root = rotateRightRb(root);
		}
		if ((root->left != NULL && getColor(root) == BLACK && getColor(root->left) == RED && root->left->left!=NULL && getColor(root->left->left) == RED)
		|| (root->right != NULL && getColor(root) == BLACK && getColor(root->right) == RED && root->right->left!=NULL && getColor(root->right->left) == RED))
		{
			printf("rodou esquerda");
			root = rotateLeftRb(root);
			//roda pra esquerda e troca as cores
	}
	
	//inserir o no e ir verificando os casos 

	/*

																root (AVO)
						root->left (PAI)														root->right (TIO)
root->left->left (Filho Esq)		root->left->right (Filho Dir)		root->right->left (sobrinho Esq)		root->right->right (sobrinho Dir)


															root (AVO)
						root->left (TIO)														root->right (PAI)
root->left->left (sobrinho Esq)		root->left->right (sobrinho Dir)		root->right->left (Filho Esq)		root->right->right (Filho Dir)


	*/
	//Caso 1: o tio de q é Rubro. 
	/*if (getColor(root->right) == RED){ //tio da direita RED
		changeColor(root);
		//changeNodeColor(root->right); //muda cor do tio e do pai
		//changeNodeColor(root->left); 
	}
	if (getColor(root->left) == RED){ //tio da esquerda RED **
		changeColor(root);
		//changeNodeColor(root->right); //muda cor do tio e do pai
		//changeNodeColor(root->left); 
	} 

	//caso 2: O tio de q é Negro e q é filho a direita de seu pai //tio: root->right // q: root->left->right
	if(getColor(root->right) ==BLACK && (root->left->right)!=NULL ){ //tio da direita é BLACK
		if((root->left->right->right ==NULL) && (root->left->right->left ==NULL)){ //verificando de (root->left->right) é uma folha
			root->left->right = rotateRightRb(root->left->right); //rotação para esquerda no novo no
		}
		//se nao: nao roda
	}
	//caso 2: O tio de q é Negro e q é filho a direita de seu pai //tio: root->left  // q: root->right->right
	if(getColor(root->left) ==BLACK && (root->right->right)!=NULL ){ //tio da esquerda é BLACK ** //tio: root->left // q: root->right->right
		if((root->right->right->right ==NULL) && (root->right->right->left ==NULL)){ //verificando de (root->right->right) é uma folha
			root->right->right = rotateRightRb(root->right->right); //rotação para esquerda no novo no
		}
	} 


	//Caso 3: o tio de q é Negro e q é é filho a esquerda de seu pai. //tio: root->right e Q:root->left->left
	if(getColor(root->right) ==BLACK && (root->left->left)!=NULL){ //tio da direita é BLACK
		if((root->left->left->right ==NULL) && (root->left->left->left ==NULL)){ 
			root->left->left = rotateLeftRb(root->left->left); 
		}
	}
	//Caso 3: o tio de q é Negro e q é é filho a esquerda de seu pai. //tio: root->left e Q: root->right->left 
	if(getColor(root->left ) ==BLACK && (root->right->left)!=NULL){ //tio da esquerda é BLACK
		if((root->right->left->right ==NULL) && (root->right->left->left ==NULL)){ 
			root->right->left = rotateLeftRb(root->right->left); 
		}
	}


	if(getColor(root)==BLACK && getColor(root->left)==RED && getColor(root->left->left)==RED){
		changeColor(root->left);
		changeColor(root->right);
	}
	if(getColor(root)==BLACK && getColor(root->left)==RED && getColor(root->left->right)==RED){
		changeColor(root->left);
		changeColor(root->right);
	}
	if (getColor(root)==BLACK && getColor(root->right)==RED && getColor(root->right->left)==RED){
		changeColor(root->left);
		changeColor(root->right);
	}
	if (getColor(root)==BLACK && getColor(root->right)==RED && getColor(root->right->right)==RED){
		changeColor(root->left);
		changeColor(root->right);
	}*/


	/*

	if (altura != 0){


		printf("entrou aq ----");
		//printf("entrou aq");
		//root = rotateRightRb(root);
		//printf("entrou na direita");

		//caso 2
		if( getColor(root->right)==BLACK && root->left->right!=NULL){
			
			//root = rotateRightRb(root);
		}
		//CASO 3
		if(getColor(root->right)==BLACK && root->right->left!=NULL){
			//root=rotateLeftRb(root);
		}

		if ((root->left != NULL && getColor(root) == BLACK && getColor(root->left) == RED && getColor(root->left->right) == RED)
		|| (root->right != NULL && getColor(root) == BLACK && getColor(root->right) == RED && getColor(root->right->left) == RED))
		{
			printf("Rodou esquerda");
			root = rotateLeftRb(root);
			//root = rotateRightRb(root);
		}
		if ((root->left != NULL && getColor(root) == BLACK && getColor(root->left) == RED && getColor(root->left->left) == RED)
		|| (root->right != NULL && getColor(root) == BLACK && getColor(root->right) == RED && getColor(root->right->left) == RED))
		{
			printf("Rodou Direita");
			root = rotateRightRb(root);
			//root = rotateLeftRb(root);
		}
		
		// Nó Vermelho é sempre filho à esquerda
		// if ((root->right != NULL && getColor(root->right) == RED) && getColor(root->left) == BLACK)
			//root = rotateLeftRb(root); 

		// Filho e Neto são vermelhos
		// Filho vira pai de 2 nós vermelhos
		// if ((root->left != NULL && getColor(root->left) == RED) && getColor(root->left->left) == RED)
			//root = rotateRightRb(root); 
	}*/

	//altura do no atual = filho;
	//altura do no pai = altura - 2;

	return root;
}
/*
int insertRb(RbTree *root, int valor){ //insere o no na arvore
	int ans;
	*root = insertNodeRb(*root, valor, &ans);//faz o tratamento das possiveis violações da árvore rubro negra
	if ((*root) != NULL) //seta a cor da raiz para preta se diferente;
		(*root)->color = BLACK;
	return ans;

}

*/

int insertRb(RbTree *root, int valor, int qtd, const char *name){ //insere o no na arvore
	//valor = chave da arvore = codigo do produto
	//qtd = quantidade do produto
	int ans;

	//free(root->name_prod); // Libera a memória anterior, se necessário
	//root->name_prod = (char *)malloc((strlen(name) + 1) * sizeof(char)); // Aloca memória suficiente para a nova string


	*root = insertNodeRb(*root, valor, qtd, name, &ans);//faz o tratamento das possiveis violações da árvore rubro negra
	//valor =0;
	qtd =0;
	free(name);
	name = (char *)malloc((strlen(name) + 1) * sizeof(char)); // Aloca memória suficiente para a nova string
	
	
	if ((*root) != NULL) //seta a cor da raiz para preta se diferente;
		(*root)->color = BLACK;
	return ans;

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
	no->info = novoValor;
}


// Remoção
struct NO *balanceNodes(struct NO *node){
	
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