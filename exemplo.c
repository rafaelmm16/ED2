#include <stdio.h>
#include <stdlib.h>

enum Color {RED, BLACK};

typedef struct Node {
    int data;
    enum Color color;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
} Node;

typedef struct RedBlackTree {
    Node *root;
} RedBlackTree;

Node* createNode(int data) {
    Node* node = (Node*) malloc(sizeof(Node));
    node->data = data;
    node->color = RED;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    return node;
}

void rotateLeft(RedBlackTree* tree, Node* node) {
    Node* rightChild = node->right;
    node->right = rightChild->left;

    if (rightChild->left != NULL) {
        rightChild->left->parent = node;
    }

    rightChild->parent = node->parent;

    if (node->parent == NULL) {
        tree->root = rightChild;
    } else if (node == node->parent->left) {
        node->parent->left = rightChild;
    } else {
        node->parent->right = rightChild;
    }

    rightChild->left = node;
    node->parent = rightChild;
}

void rotateRight(RedBlackTree* tree, Node* node) {
    Node* leftChild = node->left;
    node->left = leftChild->right;

    if (leftChild->right != NULL) {
        leftChild->right->parent = node;
    }

    leftChild->parent = node->parent;

    if (node->parent == NULL) {
        tree->root = leftChild;
    } else if (node == node->parent->left) {
        node->parent->left = leftChild;
    } else {
        node->parent->right = leftChild;
    }

    leftChild->right = node;
    node->parent = leftChild;
}

void fixViolations(RedBlackTree* tree, Node* node) {
    while (node != tree->root && node->color != BLACK && node->parent->color == RED) {
        Node* parent = node->parent;
        Node* grandparent = parent->parent;

        if (parent == grandparent->left) {
            Node* uncle = grandparent->right;

            if (uncle != NULL && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                node = grandparent;
            } else {
                if (node == parent->right) {
                    rotateLeft(tree, parent);
                    node = parent;
                    parent = node->parent;
                }

                rotateRight(tree, grandparent);
                parent->color = BLACK;
                grandparent->color = RED;
                node = parent;
            }
        } else {
            Node* uncle = grandparent->left;

            if (uncle != NULL && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                node = grandparent;
            } else {
                if (node == parent->left) {
                    rotateRight(tree, parent);
                    node = parent;
                    parent = node->parent;
                }

                rotateLeft(tree, grandparent);
                parent->color = BLACK;
                grandparent->color = RED;
                node = parent;
            }
        }
    }

    tree->root->color = BLACK;
}

void insert(RedBlackTree* tree, int data) {
    Node* node = createNode(data);

    Node* parent = NULL;
    Node* current = tree->root;

    while (current != NULL) {
        parent = current;

        if (data < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    node->parent = parent;

    if (parent == NULL) {
        tree->root = node;
    } else if (data < parent->data) {
        parent->left = node;
    } else {
        parent->right = node;
    }

    fixViolations(tree, node);
}

int main() {
    RedBlackTree tree;
    tree.root = NULL;

    insert(&tree, 10);
    insert(&tree, 20);
    insert(&tree, 30);

    // Test the tree structure

    return 0;
}
