#include <stdio.h>
#include <stdlib.h>
#include "binary_tree.h"


int main() {
    
    /* Initialize array with values to insert them into the tree */
    int array[] = {5,3,8,1,4,9};
    int N = sizeof(array)/sizeof(int);
    Node *root = NULL;

    /* Run the functions on the tree */
    int i;
    for(i=0; i<N; ++i)
        insert(&root,array[i]);
    
    printTree(root);
    printf("\n");
    for(i=1; i<=10; ++i)
        if(isIn(root,i))
        printf("%d is in the tree.\n",i);
    printf("Tree Height: %d\n", treeHeight(root));
    printf("Number of nodes: %d \n", numOfNodes(root));
    freeTree(root);
    
    return 0;
}