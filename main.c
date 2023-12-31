#include <stdio.h>
#include "includes/queue.h"
#include "includes/tree.h"
#include "includes/graph.h"
#include "includes/others.h"


int main() {

    // Node *root = NULL;
    // int a, nodeValue;
    // // char quitValue;
    // // enum {FALSE, TRUE} quit = TRUE;
    // for(int i=0; i<=5; i++){
    //     printf("Enter the key of a node\n");
    //     scanf("%d", &a);
    //     root = insertion(root, a);
    // }
    // breadthFirstSearch(root);
    // printf("\n");
    // displayTree(root);
    // printf("\n");
    // printf("Enter the node to be deleted\n");
    // scanf("%d", &nodeValue);
    // Node * v = delete_node_helper(root, nodeValue);
    // printf("After deletion\n");
    // breadthFirstSearch(root);
    // printf("\n");
    // displayTree(root);
    // printf("\n");
    // // while(quit){
    // //     breadthFirstSearch(root);
    // //     printf("\n");
    // //     displayTree(root);
    // //     printf("\n");
    // //     printf("Would you like to quit(y or n or d to delete a node)?\n");
    // //     scanf("%c", quitValue);
    // //     switch(quitValue){
    // //         case 'y':
    // //             quit = FALSE;
    // //             break;
    // //         case 'n':
    // //             quit = TRUE;
    // //             break;
    // //         case 'd':
    // //             printf("Enter the key of the node\n");
    // //             scanf("%d", &nodeValue);
    // //             delete_node(root, nodeValue);
    // //         default:
    // //             printf("Choose either 'y' or 'n'\n");
    // //             scanf("%c", quitValue);
    // //             break;
    // //     }
    // // }


    // clear_tree(root);
    //

    // Graph myGraph;
    // int numVertices = 4;
    // initGraph(&myGraph, numVertices);

    // addEdge(&myGraph, 0, 1, 2);
    // addEdge(&myGraph, 0, 3, 1);
    // addEdge(&myGraph, 1, 2, 4);
    // addEdge(&myGraph, 1, 4, 3);
    // addEdge(&myGraph, 2, 3, 5);
    // addEdge(&myGraph, 2, 4, 0);
    // addEdge(&myGraph, 3, 4, 6);
    // addEdge(&myGraph, 3, 5, 2);
    // addEdge(&myGraph, 4, 5, 0);

    // printGraph(&myGraph);
    //dijkstra(&myGraph, 1);
    //dijkstra_parallel(&myGraph, 0);
    //primMST(&myGraph);

    int numVertices = 4;
    int numEdges = 5;

    Edge edges[] = {
        {0, 1, 10},
        {0, 2, 6},
        {0, 3, 5},
        {1, 3, 15},
        {2, 3, 4}
    };

    kruskalMST(edges, numVertices, numEdges);

    printf("End...");
    return 0;
}