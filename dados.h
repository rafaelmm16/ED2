#ifndef DADOS_H
#define DADOS_H

#include <stdio.h>
#include <stdlib.h>

void comparar(void *a, void *b, void *result);
void *criaNo(int v);

void imprime(void *node);
void deletaNo(void *node);

void copiaNo(void *origem, void *destino);
void *copiaDado(void *origem);

#endif
