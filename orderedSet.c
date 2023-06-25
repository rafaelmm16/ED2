#include <stdio.h>
#include <stdlib.h>

#include "orderedSet.h"

// INFORMAÇÕES SOBRE CONJUNTOS
void printSet(orderedSet *set, void (*cb)(void *)){
	if(set && *set){
        printSet(&(*set)->left, cb);
        cb((*set)->info);
        printSet(&(*set)->right, cb);
    }
}

int setCardinality(orderedSet *set)
{
	if (set == NULL || (*set) == NULL)
		return 0;
	int leftHeight = setCardinality(&((*set)->left));
	int rightHeight = setCardinality(&((*set)->right));
	return (leftHeight + rightHeight + 1);
}

int isEmpty(orderedSet *set)
{
	if (set == NULL || *set == NULL)
		return 1;
	return 0;
}

void emptySet(orderedSet *S, void (*cb)(void *))
{
	freeRbTree(S, cb);
}

// OPERAÇÕES SOBRE UM ELEMENTO E UM CONJUNTO
int insertElement(orderedSet *S, void *key, void (*cb)(void *, void *, void *))
{
	return insertRb(S, key, cb);
}

int removeElement(orderedSet *S, void *key, void (*cb)(void *, void *, void *), void (*funcDelete)(void *), void (*funcCopy)(void *, void *))
{
	return removeRb(S, key, cb, funcDelete, funcCopy);
}

int isOnSet(orderedSet *S, void *key, void (*cb)(void *, void *, void *))
{
	return isInTreeRb(S, key, cb);
}

// OPERAÇÕES ENTRE DOIS CONJUNTOS
void preOrderIntersection(orderedSet *root, orderedSet *destination, orderedSet *check, void (*cb)(void *, void *, void *), void *(*copia)(void *))
{
	if (root == NULL)
		return;
	if (*root != NULL && (*root)->info != NULL)
	{
		if (isOnSet(check, (*root)->info, cb))
		{
			insertElement(destination, copia((*root)->info), cb);
		}
		preOrderIntersection(&((*root)->left), destination, check, cb, copia);
		preOrderIntersection(&((*root)->right), destination, check, cb, copia);
	}
}

orderedSet *intersectionSets(orderedSet *S1, orderedSet *S2, void (*cb)(void *, void *, void *), void *(*copia)(void *))
{
	// pega o que eles tem em comum: S1 e S2
	orderedSet *aux = createRbTree();
	if (S1 == NULL || S2 == NULL || aux == NULL)
		return NULL;
	preOrderIntersection(S1, aux, S2, cb, copia);
	return aux;
}

void preOrderUnion(orderedSet *root, orderedSet *destination, void (*cb)(void *, void *, void *), void *(*copia)(void *))
{
	if (root == NULL)
		return;
	if (*root != NULL && (*root)->info != NULL)
	{
		insertElement(destination, copia((*root)->info), cb);
		preOrderUnion(&((*root)->left), destination, cb, copia);
		preOrderUnion(&((*root)->right), destination, cb, copia);
	}
}

orderedSet *unionSets(orderedSet *S1, orderedSet *S2, void (*cb)(void *, void *, void *), void *(*copia)(void *))
{
	// juntar sem repetir
	orderedSet *aux = createRbTree();
	if (aux == NULL) // SE NÃO FOR CRIADO CORRETAMENTE
		return NULL;
	if (S1 != NULL)
		preOrderUnion(S1, aux, cb, copia);
	if (S2 != NULL)
		preOrderUnion(S2, aux, cb, copia);
	return aux;
}

void preOrderDifference(orderedSet *root, orderedSet *destination, orderedSet *check, void (*cb)(void *, void *, void *), void *(*copia)(void *))
{
	if (root == NULL)
		return;
	if (*root != NULL && (*root)->info != NULL)
	{
		if (isOnSet(check, (*root)->info, cb) == 0)
		{
			insertElement(destination, copia((*root)->info), cb);
		}
		preOrderDifference(&((*root)->left), destination, check, cb, copia);
		preOrderDifference(&((*root)->right), destination, check, cb, copia);
	}
}

orderedSet *differenceSets(orderedSet *S1, orderedSet *S2, void (*cb)(void *, void *, void *), void *(*copia)(void *))
{
	// todos o do primeiro que não estão no segundo
	orderedSet *aux = createRbTree();
	if (S1 == NULL || S2 == NULL || aux == NULL)
		return NULL;
	preOrderDifference(S1, aux, S2, cb, copia);
	return aux;
}
