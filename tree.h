
#ifndef tree_h
#define tree_h 
    #include <stdlib.h>
    #include <stdio.h>
    #define LEAF NULL

    typedef struct Node {
        int key;
        enum { RED, BLACK } color;
        struct Node *parent;
        struct Node *left;
        struct Node *right;
    }Node;

    typedef struct RedBlackTree{
        Node *root;
    }RedBlackTree;

    Node* parent(Node* n);
    Node* grandparent(Node* n);
    Node* brother(Node* n);
    Node* uncle(Node* child);
    Node* createNode(int data);
    void left_rotation(Node* x);
    void right_rotation(Node* x);

    void recursive_insert(Node *root,  Node *n);

    void insertion_cas1(Node *n);
    void insertion_cas2(Node *n);
    void insertion_cas3(Node *n);
    void insertion_cas4(Node *n);
    void insertion_cas5(Node *n);

    void repair_tree_insert(Node *n);
    Node *insertion(Node *root, int val);

    int search(Node *root, int key);

    void displayTree(Node *root);
    
#endif