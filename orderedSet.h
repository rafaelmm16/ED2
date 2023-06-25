#ifndef ORDEREDSET_H
#define ORDEREDSET_H

#include<stdio.h>
#include<stdlib.h>

#include "dados.h"
#include "RBT.h"

typedef RbTree orderedSet;

void printSet(orderedSet *set, void (*cb)(void *));
int setCardinality(orderedSet *set);
int isEmpty(orderedSet *set);
void emptySet(orderedSet *S, void (*cb)(void *));

int insertElement(orderedSet *S, void *key, void(*cb)(void*, void *, void *));
int removeElement(orderedSet *S, void *key, void(*cb)(void*, void *, void *), void(*funcDelete)(void *), void(*funcCopy)(void *, void *));
int isOnSet(orderedSet *S, void *key, void(*cb)(void *, void *, void *));

void preOrderIntersection(orderedSet *root, orderedSet *destination, orderedSet *check, void(*cb)(void*, void *, void *), void *(*copia)(void*));
orderedSet *intersectionSets(orderedSet *S1, orderedSet *S2, void(*cb)(void*, void *, void *), void *(*copia)(void*));

void preOrderDifference(orderedSet *root, orderedSet *destination, orderedSet *check, void(*cb)(void*, void *, void *), void *(*copia)(void*));
orderedSet *differenceSets(orderedSet *S1, orderedSet *S2, void(*cb)(void*, void *, void *), void *(*copia)(void*));

void preOrderUnion(orderedSet *root, orderedSet *destination, void(*cb)(void*, void *, void *), void *(*copia)(void*));
orderedSet *unionSets(orderedSet *S1, orderedSet *S2, void(*cb)(void*, void *, void *), void *(*copia)(void*));

#endif
