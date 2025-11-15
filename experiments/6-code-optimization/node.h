#ifndef NODE_H
#define NODE_H

// Simple node structure for expression tree
typedef struct Node {
    char op;
    int value;
    char id[32];
    struct Node *left, *right;
} Node;

// Function declarations
Node* makeNode(char op, Node* left, Node* right);
Node* makeLeaf(int value);
void optimize(Node* node);
void printOptimized(Node* node);
void freeTree(Node* node);

#endif