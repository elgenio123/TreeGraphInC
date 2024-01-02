
#ifndef tree_h
#define tree_h 
    #include <stdlib.h>
    #include <stdio.h>
    #define LEAF NULL

    typedef enum Color { RED, BLACK }Color;

    typedef struct Node {
        int key;
        Color color;
        struct Node *parent;
        struct Node *left;
        struct Node *right;
    }Node;

    Node* parent(Node* n);
    Node* grandparent(Node* n);
    Node* brother(Node* n);
    Node* uncle(Node* child);
    Node* createNode(int data);
    void left_rotation(Node* root, Node* x);
    void right_rotation(Node* root, Node* x);

    //insertion
    void recursive_insert(Node *root,  Node *n);
    void insertion_case1(Node *n);
    void insertion_case2(Node *root,Node *n);
    void insertion_case3(Node *root, Node *n);
    void insertion_case4(Node *root, Node *n);
    void repair_tree_insert(Node *root,Node *n);
    Node *insertion(Node *root, int val);

    int search(Node *root, int key);

    //deletion
    void transplant(Node** root, Node* u, Node* v);
    Node* find_min(Node* node);
    void delete_fixup(Node* root, Node* x);
    Node* delete_node(Node* root, int key);

    void displayTree(Node *root);
    void clear_tree(Node *root);
    
#endif