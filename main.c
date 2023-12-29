#include <stdio.h>
#include "queue.h"
#include "tree.h"
#include "graph.h"
#include "others.h"


int main() {

    Node *root = NULL;
    int a;
    for(int i=0; i<=2; i++){
        printf("Enter the key of a node\n");
        scanf("%d", &a);
        root = insertion(root, a);
    }
    breadthFirstSearch(root);
    displayTree(root);

    
    free(root);
    printf("hello baby");
    return 0;
}