#include <stdio.h>
#include <stdlib.h>

enum Color {Red = 0, Black};
typedef struct Node
{
    void* info;
    enum Color color;
    struct Node* Left;
    struct Node* Right;
}Node;
