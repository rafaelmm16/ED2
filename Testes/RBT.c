#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "RBT.h"

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
    if (node->left == NULL && node->right != NULL && getColor(node->right) == BLACK)
    {
        printf("trocou a cor a direita %d\n", node->info);
        node->right->color = RED;
    }
    if (node->right == NULL && node->left != NULL && getColor(node->left) == BLACK)
    {
        printf("trocou a cor a esquerda %d\n", node->info);
        node->left->color = RED;
    }

    // O nó Vermelho sempre tem um filho à esquerda
    if (node->left != NULL && getColor(node->left) == RED)
    {
        //printf("Entrou na rotação a direita %d\n", node->info);
        //node = rotateRightRb(node);
        printf("ENTROU NESSE INFERNO\n");
        node->left->color = RED;
    }

    // O filho direito e o neto à direita são vermelhos
    if (node->right != NULL && getColor(node->right) == RED && getColor(node->right->right) == RED)
    {
        printf("Entrou na rotação a esquerda %d\n", node->info);
        node = rotateLeftRb(node);
    }

    // Nó Vermelho com dois filhos Vermelhos: trocar as cores
    if (node->left != NULL && node->right != NULL &&
        getColor(node) == RED && getColor(node->left) == RED && getColor(node->right) == RED)
    {
        printf("troca de cores pai e filhos %d\n", node->info);
        changeColor(node);
        changeColor(node->left);
        changeColor(node->right);
    }

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

struct NO *searchSmallest(struct NO *node)
{
    if (node == NULL)
        return NULL;

    if (node->left == NULL)
        return node;

    return searchSmallest(node->left);
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

struct NO *searchLargest(struct NO *node)
{
    if (node == NULL)
        return NULL;

    if (node->right == NULL)
        return node;

    return searchLargest(node->right);
}

struct NO *removeElementRb(struct NO *node, int valor)
{
    printf("Entrou na função removeElementRb\n");

    if (valor < node->info)
    {
        printf("O valor %d é menor do que o valor do nó atual\n", valor);

        if (getColor(node->left) == BLACK && getColor(node->left->left) == BLACK)
            node = moveRedToLeft(node);

        node->left = removeElementRb(node->left, valor);
    }
    else if (valor > node->info)
    {
        printf("O valor %d é maior do que o valor do nó atual\n", valor);

        if (getColor(node->left) == RED)
            node = rotateRightRb(node);

        if (getColor(node->right) == BLACK && getColor(node->right->left) == BLACK)
            node = moveRedToRight(node);

        node->right = removeElementRb(node->right, valor);
    }
    else // valor == node->info
    {
        printf("O valor %d é igual ao valor do nó atual\n", valor);

        if (valor == node->info && node->left == NULL && node->right == NULL) // Verifica se é uma folha
        {
            printf("O nó atual é uma folha, removendo o nó\n");

            free(node);
            return NULL;
        }

        if (node->right != NULL && getColor(node->right) == BLACK && node->right->left != NULL && getColor(node->right->left) == BLACK)
            node = moveRedToRight(node);

        if (valor == node->info)
        {
            printf("Substituindo o valor %d do nó atual pelo maior elemento da subárvore esquerda\n", valor);
            if (node->left != NULL)
            {
                struct NO *x = searchLargest(node->left);
                node->info = x->info;
                node->left = removeElementRb(node->left, x->info);
            }
            else if (node->right != NULL)
            {
                printf("O nó atual não tem filho esquerdo, substituindo o valor %d pelo menor elemento da subárvore direita\n", valor);

                struct NO *x = searchSmallest(node->right);
                node->info = x->info;
                node->right = removeElementRb(node->right, x->info);
            }
            else
            {
                printf("O nó atual não tem filhos, removendo o nó\n");

                free(node);
                return NULL;
            }
        }
    }

    if (node == NULL) // Verifica se o nó atual é NULL
    {
        printf("O nó atual é NULL\n");
        return NULL;
    }

    printf("Executando dellBalanceNodes para ajustar o balanceamento do nó\n");

    node = dellBalanceNodes(node); // Ajusta o balanceamento do nó após a remoção

    return node;
}

int removeRb(RbTree *root, int valor)
{
    // printf("Chamando searchElement\n"); // Verifica se a função é chamada
    if (searchElement(*root, valor))
    {
        // printf("Entrou no if\n");              // Verifica se entra no if
        *root = removeElementRb(*root, valor); // Atualiza o ponteiro raiz após a remoção
        // printf("Entrou.\n");
        if (*root != NULL)
            (*root)->color = BLACK; // Define a cor da nova raiz como preta
        return 1;
    }
    else
    {
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
        // return;
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