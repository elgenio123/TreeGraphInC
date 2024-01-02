#include <stdio.h>
#include <stdlib.h>
#include "includes/queue.h"
#include "includes/tree.h"
#include "includes/graph.h"
#include "includes/others.h"


int main() {

    Graph myGraph;
    int numVertices,src;

    int globalChoice, *quit= malloc(sizeof(int));
    *quit = 1;

    while(*quit){
        system("cls");
        printf("\n");
        printf("*************WELCOME TO MY PROJECT ON ALGORITHM*************\n\n");
        printf("PLEASE CHOOSE WHICH OPERATION YOU WANT TO PERFORM\n\n");
        printf("1.  Parallelized version of DIjkstra's Algorithm\n\n");
        printf("2.  Non-Parallelized version of DIjkstra's Algorithm\n\n");
        printf("3.  Prim's Algorithm\n\n");
        printf("4.  Kruskall's Algorithm\n\n");
        printf("5.  Operations in RED-BLACK trees\n\n");
        printf("6.  Dynamic and sequential Fibonacci series\n\n");
        printf("Press any other key to quit\n\n");
        scanf("%d", &globalChoice);
        switch(globalChoice){
            case 1: 
                printf("1 chosen\n");
                endProgram(quit);
                break;
            case 2:
                system("cls");
                printf("Enter the number of vertices\n");
                scanf("%d", &numVertices);
                printf("Enter the source node\n");
                scanf("%d", &src);
                initGraph(&myGraph, numVertices);
                printf("Enter the Adjacent matrix of the graph\n");
                for(int i = 0; i<numVertices; i++){
                    for(int j = i; j<numVertices; j++){
                        if(i!=j){
                            printf("Enter the weight between %d and %d ", i, j);
                            scanf("%d", &((&myGraph)->adjacencyMatrix[i][j]));
                        }
                    }
                }
                for(int i = 0; i<numVertices; i++)
                    for(int j = i; j<numVertices; j++)
                       (&myGraph)->adjacencyMatrix[j][i] = (&myGraph)->adjacencyMatrix[i][j];
                dijkstra(&myGraph, src);
                endProgram(quit);
                break;
            case 3: 
                system("cls");
                printf("Enter the number of vertices\n");
                scanf("%d", &numVertices);
                initGraph(&myGraph, numVertices);
                printf("Enter the Adjacent matrix of the graph\n");
                for(int i = 0; i<numVertices; i++){
                    for(int j = i; j<numVertices; j++){
                        if(i!=j){
                            printf("Enter the weight between %d and %d ", i, j);
                            scanf("%d", &((&myGraph)->adjacencyMatrix[i][j]));
                        }
                    }
                }
                for(int i = 0; i<numVertices; i++)
                    for(int j = i; j<numVertices; j++)
                       (&myGraph)->adjacencyMatrix[j][i] = (&myGraph)->adjacencyMatrix[i][j];
                primMST(&myGraph);
                endProgram(quit);
                break;
            case 4:
                system("cls");
                printf("Enter the number of vertices\n");
                scanf("%d", &numVertices);
                initGraph(&myGraph, numVertices);
                printf("Enter the Adjacent matrix of the graph\n");
                for(int i = 0; i<numVertices; i++){
                    for(int j = i; j<numVertices; j++){
                        if(i!=j){
                            printf("Enter the weight between %d and %d ", i, j);
                            scanf("%d", &((&myGraph)->adjacencyMatrix[i][j]));
                        }
                    }
                }
                for(int i = 0; i<numVertices; i++)
                    for(int j = i; j<numVertices; j++)
                       (&myGraph)->adjacencyMatrix[j][i] = (&myGraph)->adjacencyMatrix[i][j];
                kruskalMST(&myGraph);
                endProgram(quit);
                break; 
            case 5: 
                int numberNodes, a, nodeValue, choice, *leave = malloc(sizeof(int));
                *leave = 1;
                Node *root = NULL;
                system("cls");
                printf("Enter the number of nodes of the tree\n");
                scanf("%d", &numberNodes);
                for(int i=0; i<numberNodes; i++){
                    printf("Enter the key of a node\n");
                    scanf("%d", &a);
                    root = insertion(root, a);
                }
                while(*leave){
                    system("cls");
                    printf("Choose the operation you wanna perform\n(any other key will exit this menu)\n");
                    printf("        1. Insert new node \n");
                    printf("        2. Delete a node \n");
                    printf("        3. Search a node \n");
                    printf("        4. Display tree \n");
                    scanf("%d", &choice);
                    switch(choice){
                        case 1:
                            printf("Enter key of new node\n");
                            scanf("%d", &nodeValue);
                            insertion(root, nodeValue);
                            exitMenuTree(leave);
                            break;
                        case 2:
                            printf("Enter key of node to delete\n");
                            scanf("%d", &nodeValue);
                            Node* r = delete_node(root, nodeValue);
                            free(r);
                            exitMenuTree(leave);
                            break;
                        
                        case 3:
                            printf("Enter key of node to search\n");
                            scanf("%d", &nodeValue);
                            if(search(root, nodeValue))
                                printf("Node exists\n");
                            else  
                                printf("Node does not exists\n");  
                            exitMenuTree(leave);
                            break;
                        case 4:
                            printf("Breadth First Search\n");
                            breadthFirstSearch(root);
                            printf("\n");
                            printf("Depth First Search\n");
                            displayTree(root);
                            printf("\n");
                            exitMenuTree(leave);
                            break;
                        default:
                            clear_tree(root);
                            *leave = 0;
                    }
                }
                endProgram(quit);
                break;
            case 6: 
                unsigned long long n;
                system("cls");
                printf("Enter the value of n\n");
                scanf("%llu", &n);
                executeFunction(fib, fib_dynamic, n);
                endProgram(quit);
                break;
            default:
                *quit=0;
        }
    }


    printf("End...");
    getchar();
    return 0;
}