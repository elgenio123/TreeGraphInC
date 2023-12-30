#include <stdio.h>
#include "includes/queue.h"
#include "includes/tree.h"
#include "includes/graph.h"
#include "includes/others.h"


int main() {

    Node *root = NULL;
    int a, nodeValue;
    // char quitValue;
    // enum {FALSE, TRUE} quit = TRUE;
    for(int i=0; i<=5; i++){
        printf("Enter the key of a node\n");
        scanf("%d", &a);
        root = insertion(root, a);
    }
    breadthFirstSearch(root);
    printf("\n");
    displayTree(root);
    printf("\n");
    printf("Enter the node to be deleted\n");
    scanf("%d", &nodeValue);
    Node * v = delete_node_helper(root, nodeValue);
    printf("After deletion\n");
    breadthFirstSearch(root);
    printf("\n");
    displayTree(root);
    printf("\n");
    // while(quit){
    //     breadthFirstSearch(root);
    //     printf("\n");
    //     displayTree(root);
    //     printf("\n");
    //     printf("Would you like to quit(y or n or d to delete a node)?\n");
    //     scanf("%c", quitValue);
    //     switch(quitValue){
    //         case 'y':
    //             quit = FALSE;
    //             break;
    //         case 'n':
    //             quit = TRUE;
    //             break;
    //         case 'd':
    //             printf("Enter the key of the node\n");
    //             scanf("%d", &nodeValue);
    //             delete_node(root, nodeValue);
    //         default:
    //             printf("Choose either 'y' or 'n'\n");
    //             scanf("%c", quitValue);
    //             break;
    //     }
    // }


    clear_tree(root);
    printf("End...");
    return 0;
}