#include <stdio.h>
#include <stdlib.h>
#include "binary_tree.h"


/* Create new node */
Node* newNode(int data)
{
    Node *p = (Node*) malloc (sizeof(Node));
    p->data = data;
    p->ls = p->rs = NULL;
    return p;
}

/* Print the data of a specific node */
void printTreeRec(Node *root)
{
    printf("%d, ", root->data);
}

/********* All the next functions work recursively *********/

/* Create a new node with value data and insert it to the tree */
void insert(Node **root, int data)
{
    if (!*root)
    {
        *root = newNode(data);
        return;
    }
    
    if ((*root)->data > data)
        insert(&(*root)->ls, data);
    else
        insert(&(*root)->rs, data);
}

/* Calculate and return the height of the tree */
int treeHeight(Node *root)
{
    if (!root)
        return 0;
    
    int height_rs = treeHeight(root->rs);
    int height_ls = treeHeight(root->ls);

    return 1 + max(height_ls, height_rs);
}

/* Calculate and return the sum nodes of the tree */
int numOfNodes(Node *root)
{
    if (!root)
        return 0;
    
    return 1 + numOfNodes(root->ls) + numOfNodes(root->rs);
}

/* Printing all the data in the tree in the 'in order' algorithm way */
void printTree(Node *root)
{
    if (!root)
        return;

    printTree(root->ls);
    printTreeRec(root);
    printTree(root->rs);
}

/* Clean and free all the tree nodes */
void freeTree(Node *root)
{
    if (!root)
        return;

    freeTree(root->ls);
    freeTree(root->rs);
    
    free(root);
}

/* Check if the data exis in the tree */
int isIn(Node *root, int data)
{
    if (!root)
        return 0;

    if (root->data == data)
        return 1;
    
    else if (root->data < data)
        return isIn(root->rs, data);
    
    return isIn(root->ls, data);
}

/* Auxalry function to calulate max value between two elements */
int max(int num1, int num2)
{
    if (num1 > num2)
        return num1;
    return num2;
}