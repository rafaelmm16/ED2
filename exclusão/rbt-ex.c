#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rbt-ex.h"

#define RED 1
#define BLACK 0

// Função auxiliar para criar um novo nó
RbTree *createRbTree()
{
    RbTree *root = (RbTree *)malloc(sizeof(RbTree));
    if (root != NULL)
    {
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
    if ((node->left != NULL) || (node->right != NULL))
    {
        node->color = !node->color;
    }

    if (node->left != NULL)
        node->left->color = !node->left->color;
    if (node->right != NULL)
        node->right->color = !node->right->color;
}

struct NO *rotateRightRb(struct NO *root)
{
    struct NO *newRoot = root->left;
    struct NO *newRootRight = newRoot != NULL ? newRoot->right : NULL;

    root->left = newRootRight;
    newRoot->right = root;

    // Atualizar as cores corretamente
    newRoot->color = root->color;
    root->color = RED;

    // Atualizar as cores dos filhos
    if (newRootRight)
    {
        newRootRight->color = BLACK;
    }

    return newRoot;
}

struct NO *rotateLeftRb(struct NO *root)
{
    struct NO *newRoot = root->right;
    struct NO *newRootLeft = newRoot != NULL ? newRoot->left : NULL;

    root->right = newRootLeft;
    newRoot->left = root;

    // Atualizar as cores corretamente
    newRoot->color = root->color;
    root->color = RED;

    // Atualizar as cores dos filhos
    if (newRootLeft)
    {
        newRootLeft->color = BLACK;
    }

    return newRoot;
}

// INSERÇÃO
// ************
struct NO *insertNodeRb(struct NO *root, int key, int *ans)
{
    if (!root)
    {
        struct NO *insert = (struct NO *)malloc(sizeof(struct NO));
        if (!insert)
        {
            *ans = 0;
            return NULL;
        }

        insert->info = key;
        insert->color = RED;
        insert->left = insert->right = NULL;
        insert->name_prod = NULL;
        insert->cod_prod = 0;
        insert->qtd_prod = 0;

        *ans = 1;
        return insert;
    }

    if (key == root->info)
    {
        *ans = 0;
        return root;
    }

    if (key < root->info)
    {
        // Navegue para a subárvore esquerda
        root->left = insertNodeRb(root->left, key, ans);

        // Verifique as propriedades da árvore vermelho-preto e faça as rotações e alterações de cor necessárias
        if (root->left && getColor(root->left) == RED && getColor(root->left->left) == RED)
        {
            // Caso 2: nodo adicionado à esquerda e irmão com cor vermelha
            if (root->right && getColor(root->right) == RED)
            {
                root->color = RED;
                root->left->color = BLACK;
                root->right->color = BLACK;
            }
            else
            {
                root = rotateRightRb(root);
                root->right->color = RED;
                root->color = BLACK;
            }
        }
        else if (root->left && getColor(root->left) == RED && getColor(root->left->right) == RED)
        {
            // Caso 1: pai e tio vermelhos
            if (root->right && getColor(root->right) == RED)
            {
                root->color = RED;
                root->left->color = BLACK;
                root->right->color = BLACK;
            }
            else
            {
                root->left = rotateLeftRb(root->left);
                root = rotateRightRb(root);
                root->color = BLACK;
                root->right->color = RED;
            }
        }
    }
    else
    {
        // Navegue para a subárvore direita
        root->right = insertNodeRb(root->right, key, ans);

        // Verifique as propriedades da árvore vermelho-preto e faça as rotações e alterações de cor necessárias
        if (root->right && getColor(root->right) == RED && getColor(root->right->right) == RED)
        {
            // Caso 2: nodo adicionado à direita e irmão com cor vermelha
            if (root->left && getColor(root->left) == RED)
            {
                root->color = RED;
                root->left->color = BLACK;
                root->right->color = BLACK;
            }
            else
            {
                root = rotateLeftRb(root);
                root->left->color = RED;
                root->color = BLACK;
            }
        }
        else if (root->right && getColor(root->right) == RED && getColor(root->right->left) == RED)
        {
            // Caso 1: pai e tio vermelhos
            if (root->left && getColor(root->left) == RED)
            {
                root->color = RED;
                root->left->color = BLACK;
                root->right->color = BLACK;
            }
            else
            {
                root->right = rotateRightRb(root->right);
                root = rotateLeftRb(root);
                root->color = BLACK;
                root->left->color = RED;
            }
        }
    }

    return root;
}

int insertRb(RbTree *root, int valor)
{
    int ans;

    *root = insertNodeRb(*root, valor, &ans);
    if ((*root) != NULL)
        (*root)->color = BLACK;

    return ans;
}

void adicionarInformacoes(struct NO *no, int cod, int qtd)
{
    if (no == NULL)
    {
        // Nó inválido
        return;
    }

    no->cod_prod = cod;
    no->qtd_prod = qtd;
}

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
    // O nó Vermelho sempre tem um filho à esquerda
    if (getColor(node->right) == RED)
        node = rotateLeftRb(node);

    // O filho direito e o neto à esquerda são vermelhos
    if (node->left != NULL && getColor(node->left->left) == RED)
        node = rotateRightRb(node);

    // 2 filhos Vermelhos: troca cor!
    if (getColor(node->left) == RED && getColor(node->right) == RED)
        changeColor(node);

    return node;
}

struct NO *moveRedToLeft(struct NO *node)
{
    changeColor(node);
    if (node->right != NULL && getColor(node->right->left) == RED)
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
    if (node->left != NULL && getColor(node->left->left) == RED)
    {
        node = rotateRightRb(node);
        changeColor(node);
    }
    return node;
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

struct NO *removeElementRb(struct NO *root, int valor)
{
    if (root == NULL){
         printf("Removi.\n");
        return NULL;
    }
   

    if (valor < root->info)
    {
        if (root->left != NULL && getColor(root->left) == BLACK && root->left->left != NULL && getColor(root->left->left) == BLACK)
        {
            printf("Movendo vermelho para a esquerda.\n");
            root = moveRedToLeft(root);
        }

        printf("Descendo para a subárvore esquerda.\n");
        root->left = removeElementRb(root->left, valor);
    }
    else if (valor > root->info)
    {
        if (root->left != NULL && getColor(root->left) == RED)
        {
            printf("Rotacionando à direita.\n");
            root = rotateRightRb(root);
        }

        if (root->right != NULL && getColor(root->right) == BLACK && root->right->left != NULL && getColor(root->right->left) == BLACK)
        {
            printf("Movendo vermelho para a direita.\n");
            root = moveRedToRight(root);
        }

        printf("Descendo para a subárvore direita.\n");
        root->right = removeElementRb(root->right, valor);
    }
    else // Caso em que o valor é igual ao valor do nó atual
    {
        if (root != NULL && root->left == NULL && root->right == NULL) // Nó folha
        {
            printf("Removendo nó folha.\n");
            free(root);
            return NULL; // Retorna NULL para indicar que a árvore está vazia
        }
        else if (root->left == NULL) // Nó com apenas filho à direita
        {
            printf("Removendo nó com apenas filho à direita.\n");
            struct NO *temp = root->right;
            free(root);
            return temp; // Retorna o filho à direita como nova raiz
        }
        else if (root->right == NULL) // Nó com apenas filho à esquerda
        {
            printf("Removendo nó com apenas filho à esquerda.\n");
            struct NO *temp = root->left;
            free(root);
            return temp; // Retorna o filho à esquerda como nova raiz
        }
        else // Nó com dois filhos
        {
            printf("Removendo nó com dois filhos.\n");
            struct NO *minValueNode = searchSmaller(root->right); // Encontra o menor valor na subárvore direita
            root->info = minValueNode->info;                    // Copia o valor do menor nó para o nó atual
            root->right = removeElementRb(root->right, minValueNode->info); // Remove o menor nó recursivamente da subárvore direita
        }
    }

    if (root->left != NULL && getColor(root->left) == RED && root->left->left != NULL && getColor(root->left->left) == RED)
    {
        printf("Rotacionando à direita.\n");
        root = rotateRightRb(root);
    }

    if (root->right != NULL && getColor(root->right) == RED && root->right->right != NULL && getColor(root->right->right) == RED)
    {
        printf("Rotacionando à esquerda.\n");
        root = rotateLeftRb(root);
    }

    return root;
}

int removeRb(RbTree *root, int valor)
{
    printf("Chamando searchElement\n"); // Verifica se a função é chamada
    if (searchElement(*root, valor))
    {
        printf("Entrou no if\n"); // Verifica se entra no if
        *root = removeElementRb(*root, valor); // Atualiza o ponteiro raiz após a remoção
        printf("\n\nEntrou.\n");
        if (*root != NULL)
            (*root)->color = BLACK; // Define a cor da nova raiz como preta
        return 1;
    }
    else{
        printf("Entrou no else\n"); // Verifica se entra no else
        return 0;
    }
}

// PROPRIEDADES ARVORE
// ************

void prinTree(RbTree *root)
{
    if (root == NULL)
    {
        //
        printf("Árvore vazia.\n");
        return;
    }

    PrintTreeHelper(root, 0);
}

void PrintTreeHelper(RbTree *root, int indentLevel)
{
    if (root == NULL)
    {
        // Árvore vazia, não há nada para imprimir
        printf("Árvore vazia.\n");
        //return;
    }
    if (*root == NULL)
    {
        return;
    }
    

    RbTree currentNode = *root;

    PrintTreeHelper(&(currentNode->right), indentLevel + 1);

    for (int i = 0; i < indentLevel; i++)
    {
        printf("    ");
    }

    if (currentNode != NULL)
    {
        printf("%d - %d\n", currentNode->info, getColor(currentNode)); // Acessar cor do nó por getColor(currentNode)
        
        PrintTreeHelper(&(currentNode->left), indentLevel + 1);
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