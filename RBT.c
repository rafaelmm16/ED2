// ED2_TrabPratico_Grupo5_[IasminMarquesPereira][RafaelMendesMerlo]
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

void freeNode(struct NO *no){ // Liberar o No
	if (no == NULL)
		return;
	freeNode(no->left);
	freeNode(no->right);
	free(no);
	no = NULL;
}

void freeRbTree(RbTree *root){ // Liberar a árvore
	if (root == NULL)
		return;
	freeNode(*root);
	free(root);
}

struct NO *searchElement(struct NO *root, int current){ // Encontrar Elemento - Busca
	if (root == NULL || root->info == current){
		return root; // retorna o valor encontrado ou a raiz (se for nula)
	}
	if (current < root->info)	{ // Se o valor for menor que o valor do nó atual, realiza a busca na subárvore esquerda
		return searchElement(root->left, current);
	}else{// Se o valor for maior que o valor do nó atual, realiza a busca na subárvore direita
		return searchElement(root->right, current);
	}
}

int returnQuant(struct NO *root, int current, int qnt){ // retorna a quantidade atual do produto;
	if (root == NULL || root->info == current){
		qnt = root->qtd_prod;
		return qnt; // retorna a quantidade do produto atual se existir
	}
	if (current < root->info){ // Se o valor for menor que o valor do nó atual, realiza a busca na subárvore esquerda
		return returnQuant(root->left, current, qnt);
	}else{ // Se o valor for maior que o valor do nó atual, realiza a busca na subárvore direita
		return returnQuant(root->right, current, qnt);
	}
}

// Rotações
struct NO *rotateLeftRb(struct NO *root){ // Rotação a esquerda
	struct NO *newRoot = root->right;
	struct NO *newRootLeft = newRoot != NULL ? newRoot->left : NULL;

	root->right = newRootLeft;
	newRoot->left = root;

	newRoot->color = root->color; // Atualizar as cores corretamente
	root->color = RED;
	
	if (newRootLeft){ // Atualizar as cores dos filhos
		newRootLeft->color = BLACK;
	}

	return newRoot;
}

struct NO *rotateRightRb(struct NO *root){ // Rotação a Direita
	struct NO *newRoot = root->left;
	struct NO *newRootRight = newRoot != NULL ? newRoot->right : NULL;

	root->left = newRootRight;
	newRoot->right = root;

	newRoot->color = root->color; // Atualizar as cores corretamente
	root->color = RED;

	if (newRootRight){ // Atualizar as cores dos filhos
		newRootRight->color = BLACK;
	}

	return newRoot;
}

int getColor(struct NO *node){ // pega a Cor do No
	if (node)
		return node->color;
	else
		return BLACK;
}

void changeColor(struct NO *node){ // Altera a cor de um nó e de seus filhos
	if ((node->left != NULL) || (node->right != NULL)){ // verifica se diferente de null - se existem
		node->color = !node->color;
	}
	if (node->left != NULL)
		node->left->color = !node->left->color;
	if (node->right != NULL)
		node->right->color = !node->right->color;
}


struct NO *insertNodeRb(struct NO *root, int key, int qtd, const char *name, int *ans){ //função responsavel pela verificação de violações e inserção do no na arvore
	if (!root){
		struct NO *insert = (struct NO *)malloc(sizeof(struct NO));
		if (!insert){ // No não foi inserido
			*ans = 0;
			return NULL;
		}
		insert->info = key; //info recebe o numero da chave do produto
		insert->color = RED; // no inicia com a cor Vermelha
		insert->left = insert->right = NULL; //filhos nulos
		insert->qtd_prod = qtd; //quantidade do produto recebe a quatidade inserida pelo usuário
		insert->name_prod = (char *)malloc((strlen(name) + 1) * sizeof(char)); // Adicionar o nome do produto
		strcpy(insert->name_prod, name);
		*ans = 1;
		return insert;
	}
	if (key == root->info){ // Se a chave já existir, retorna NULL
		*ans = 0;
		return NULL;
	}
	
	if (key < root->info){ //Chave do produto menor do que a atual, desce para esquerda
		root->left = insertNodeRb(root->left, key, qtd, name, ans);
	}
	else{  //Chave do produto maior do que a atual, desce para direita
		root->right = insertNodeRb(root->right, key, qtd, name, ans);
	}

	// tratamento de casos de violação da inserção
	if (*ans){ //checa o balanceamento da arvore
		if (key < root->info){ //Chave do produto menor do que a atual, desce para esquerda
			if (root->left && getColor(root->left) == RED && getColor(root->left->left) == RED)	{
				if (root->right && getColor(root->right) == RED){ // no adicionado à esquerda e irmão com cor vermelha
					root->color = RED;
					root->left->color = BLACK;
					root->right->color = BLACK;
				}else{
					root = rotateRightRb(root);
					root->right->color = RED;
					root->color = BLACK;
				}
			}else if (root->left && getColor(root->left) == RED && getColor(root->left->right) == RED){
				if (root->right && getColor(root->right) == RED){// pai e tio vermelhos
					root->color = RED;
					root->left->color = BLACK;
					root->right->color = BLACK;
				}else{
					root->left = rotateLeftRb(root->left);
					root = rotateRightRb(root);
					root->color = BLACK;
					root->right->color = RED;
				}
			}
		}else{ //Chave do produto maior do que a atual, desce para direita
			if (root->right && getColor(root->right) == RED && getColor(root->right->right) == RED)	{
				if (root->left && getColor(root->left) == RED){//no adicionado à direita e irmão com cor vermelha
					root->color = RED;
					root->left->color = BLACK;
					root->right->color = BLACK;
				}else{
					root = rotateLeftRb(root);
					root->left->color = RED;
					root->color = BLACK;
				}
			}else if (root->right && getColor(root->right) == RED && getColor(root->right->left) == RED){
				if (root->left && getColor(root->left) == RED){//pai e tio vermelhos
					root->color = RED;
					root->left->color = BLACK;
					root->right->color = BLACK;
				}else{
					root->right = rotateRightRb(root->right);
					root = rotateLeftRb(root);
					root->color = BLACK;
					root->left->color = RED;
				}
			}
		}
	}
	return root;
}

int insertRb(RbTree *root, int current, int qtd, const char *name, char **name_prod){//função auxiliar a inserção do produto na árvore
	int ans;
	free(*name_prod);// Libera a memória anterior, se necessário
	*name_prod = (char *)malloc((strlen(name) + 1) * sizeof(char)); // Aloca memória suficiente para a nova string
	int i = 0;
	
	while (name[i] != '\0'){ // tratamento de inserção de um tipo char/ string
		if (name[i] == ' '){
			(*name_prod)[i] = '\0';
		}
		(*name_prod)[i] = name[i];
		i++;
	}
	printf("%s", *name_prod);

	*root = insertNodeRb(*root, current, qtd, *name_prod, &ans); // Faz o tratamento das possíveis violações da árvore rubro-negra

	if ((*root) != NULL) // Seta a cor da raiz para preta, se necessário
		(*root)->color = BLACK;

	return ans;
}


void changeInfo(struct NO *root, int oldValue, int newValue){ // muda a quantidade do produto
	struct NO *no = searchElement(root, oldValue);//verifica se o elemento existe
	if (no == NULL){ // Nó não encontrado
		return;
	}
	no->qtd_prod = newValue;
}


struct NO *dellBalanceNodes(struct NO *node){ //ultima verificação de balanceamento apos a remoção
	if (node->left == NULL && node->right != NULL && getColor(node->right) == BLACK){//trocou a cor direita
		node->right->color = RED;
	}
	if (node->right == NULL && node->left != NULL && getColor(node->left) == BLACK){ //trocou a cor esquerda
		node->left->color = RED;
	}
	if (node->right != NULL && getColor(node->right) == RED && getColor(node->right->right) == RED){ // O filho direito e o neto à direita são vermelhos
		node = rotateLeftRb(node);
		node->color = RED;
	}

	// Nó Vermelho com dois filhos Vermelhos: trocar as cores
	if (node->left != NULL && node->right != NULL && getColor(node) == RED && getColor(node->left) == RED && getColor(node->right) == RED && node->left->right != NULL){
		node->color = BLACK;		// Cor do nó atual é definida como preto
		node->left->color = BLACK;	// Cor do filho da esquerda é definida como preto
		node->right->color = BLACK; // Cor do filho da direita é definida como preto
		node->left->right->color = RED;
	}
	return node;
}

struct NO *moveRedToLeft(struct NO *node){ //move o no vermelho para esquerda
	changeColor(node);
	if (node->right != NULL && getColor(node->right->left) == RED){
		node->right = rotateRightRb(node->right);
		node = rotateLeftRb(node);
		changeColor(node);
	}
	return node;
}

struct NO *moveRedToRight(struct NO *node){ //move o no vermelho para direita
	changeColor(node);
	if (node->left != NULL && getColor(node->left->left) == RED){
		node = rotateRightRb(node);
		changeColor(node);
	}
	return node;
}


struct NO *searchSmallest(struct NO *node){ //pesquisa o menor elemento (subarvore esquerda)
	if (node == NULL)
		return NULL;

	if (node->left == NULL)
		return node;

	return searchSmallest(node->left);
}

struct NO *searchLargest(struct NO *node){ //pesquisa o maior elemento (subarvore direita)
	if (node == NULL)
		return NULL;

	if (node->right == NULL)
		return node;

	return searchLargest(node->right);
}

struct NO *removeElementRb(struct NO *node, int current){ //função que faz a exclusão do No e faz as verificações de violação da árvore

	if (current < node->info){//O valor é menor do que o valor do nó atual
		if (getColor(node->left) == BLACK && getColor(node->left->left) == BLACK)
			node = moveRedToLeft(node);

		node->left = removeElementRb(node->left, current);
	}else if (current > node->info){ //O valor é maior do que o valor do nó atual
		if (getColor(node->left) == RED)
			node = rotateRightRb(node);

		if (getColor(node->right) == BLACK && getColor(node->right->left) == BLACK)
			node = moveRedToRight(node);

		node->right = removeElementRb(node->right, current);
	}else{ // valor == atual
		if (current == node->info && node->left == NULL && node->right == NULL){ // Verifica se é uma folha, remove o no
			free(node);
			return NULL;
		}

		if (node->right != NULL && getColor(node->right) == BLACK && node->right->left != NULL && getColor(node->right->left) == BLACK)
			node = moveRedToRight(node);

		if (current == node->info){
			if (node->left != NULL){ //Substituindo o valor do nó atual pelo maior elemento da subárvore esquerda
				struct NO *x = searchLargest(node->left);
				node->info = x->info;
				node->left = removeElementRb(node->left, x->info);
			}else if (node->right != NULL){ //O nó atual não tem filho esquerdo, substituindo o valor pelo menor elemento da subárvore direita
				struct NO *x = searchSmallest(node->right);
				node->info = x->info;
				node->right = removeElementRb(node->right, x->info);
			}else{ //O nó atual não tem filhos, removendo o nó
				free(node);
				return NULL;
			}
		}
	}

	if (node == NULL){ // Verifica se o nó atual é NULL
		return NULL;
	}

	node = dellBalanceNodes(node); // Ajusta o balanceamento do nó após a remoção (função auxiliar de verificação de violações apos remoção)
	return node;
}

int removeRb(RbTree *root, int current){ //função auxiliar da remoção de elementos da árvore
	if (searchElement(*root, current)){ //elemento encontrado
		*root = removeElementRb(*root, current); // Atualiza o ponteiro raiz após a remoção
		
		if (*root != NULL) // Define a cor da nova raiz como preta
			(*root)->color = BLACK; 
		return 1;
	}else{ //elemento não foi encontrado
		return 0;
	}
}


void prinTree(RbTree *root){ // auxiliar da impressao da arvore rubro negra
	if (root == NULL){
		printf("Árvore vazia.\n");
		return;
	}
	printTreeHelper(root, 0);
}

void printTreeHelper(RbTree *root, int indentLevel){ // impressao arvore rubro negra

	if (root == NULL){
		printf("Árvore vazia.\n");
	}
	if (*root == NULL){
		return;
	}

	RbTree currentNode = *root;
	printTreeHelper(&(currentNode->right), indentLevel + 1);
	for (int i = 0; i < indentLevel; i++){
		printf("    ");
	}
	if (currentNode != NULL){
		printf("%d - %d\n", currentNode->info, getColor(currentNode)); // Acessar cor do nó por getColor(currentNode)

		printTreeHelper(&(currentNode->left), indentLevel + 1);
	}
}

void printProd(RbTree *root){ // auxiliar na impressao do produto
	if (root == NULL){
		printf("Árvore vazia.\n");
		return;
	}
	printProdHelper(root, 0);
}

void printProdHelper(RbTree *root, int indentLevel){ // impressao produto
	if (root == NULL){
		printf("Árvore vazia.\n");
	}
	if (*root == NULL){
		return;
	}
	
	if (*root != NULL){
		printProdHelper(&((*root)->right), indentLevel + 1);

		for (int i = 0; i < indentLevel; i++)
			printf("    ");

		printf("%d (%d) - [ %s: %d ] \n", (*root)->info, (*root)->color, (*root)->name_prod, (*root)->qtd_prod);
		printProdHelper(&((*root)->left), indentLevel + 1);
	}
}

void printProdEstoqueAux(RbTree *root){ // auxiliar na impressao do produto em estoque
	if (root == NULL){
		printf("Árvore vazia.\n");
		return;
	}
	printProdEstoque(root, 0);
}

void printProdEstoque(RbTree *root, int indentLevel){ // impressao produto em estoque	
	if (root == NULL){
		printf("Árvore vazia.\n");
	}
	if (*root == NULL){
		return;
	}
	
	if (*root != NULL){
		if ((*root)->qtd_prod != 0 && (*root)->qtd_prod > 0){
			printf("%s : %d \n", (*root)->name_prod, (*root)->qtd_prod);
		}
		printProdEstoque(&((*root)->right), indentLevel + 1);
		printProdEstoque(&((*root)->left), indentLevel + 1);
	}
}

void printProdCastrados(RbTree *root){ // auxiliar na impressao do produtos cadastrados
	if (root == NULL){
		printf("Árvore vazia.\n");
		return;
	}
	printProdCastradosHelper(root, 0);
}

void printProdCastradosHelper(RbTree *root, int indentLevel){ // impressao produtos cadastrados	
	if (root == NULL){
		printf("Árvore vazia.\n");
	}
	if (*root == NULL){
		return;
	}	
	if (*root != NULL){
		printf("%d : %s  \n", (*root)->qtd_prod, (*root)->name_prod);
		printProdCastradosHelper(&((*root)->right), indentLevel + 1);
		printProdCastradosHelper(&((*root)->left), indentLevel + 1);
	}
}
