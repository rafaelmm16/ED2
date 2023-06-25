#include <stdio.h>
#include <stdlib.h>

#include "dados.h"

void comparar(void *a, void *b, void *result)
{
	// a função considera que o ponteiro para resultado da comparação
	// já está devidamente alocado
	int *e1 = (int *)a;
	int *e2 = (int *)b;
	int *res = (int *)result; // faz o casting da var generica recebida

	if ((*e1) == (*e2))
		*res = 0;
	else if (((*e1) > (*e2)))
		*res = 1;
	else
		*res = 2;
}

void *criaNo(int v)
{
	int *novo = (int *)malloc(sizeof(int));
	if (novo != NULL)
		*novo = v;
	return novo;
}

void imprime(void *node)
{
	int *aux = (int *)node;
	printf("%d\n", *aux);
}

void deletaNo(void *node)
{
	free(node);
	node = NULL;
}

void copiaNo(void *origem, void *destino)
{
	*((int *)destino) = *((int *)origem);
}

void *copiaDado(void *origem)
{
	int *res = (int *)malloc(sizeof(int));
	*res = *((int *)origem);
	return res;
}
