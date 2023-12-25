#include <stdio.h>
#include "tree.h"


#include "graph.h"
#include "others.h"


int main() {

    // Node *root = NULL;
    // int a;
    // for(int i=0; i<=4; i++){
    //     printf("Enter the key of a node\n");
    //     scanf("%d", &a);
    //     root = insertion(root, a);
    // }
    // if(search(root, 2))
    //     printf("exists\n");
    // else
    //     printf("Does not exists\n");
    // displayTree(root);
    // free(root);
    unsigned long long a;
    printf("Enter an integer\n");
    scanf("%llu", &a);
    executeFunction(fib, a, fib_dynamic, a);
    printf("hello baby");
    return 0;
}