#include "tree.h"

Node* parent(Node* n) {
  return n->parent;
}

Node* grandparent(Node* n) {
  Node* p = parent(n);
  if (p == NULL)
    return NULL; 
  return parent(p);
}

Node* brother(Node* n) {
  Node* p = parent(n);
  if (p == NULL)
    return NULL; 
  if (n == p->left)
    return p->right;
  else
    return p->left;
}

Node* uncle(Node* child) {
  Node* p = parent(child);
  Node* g = grandparent(child);
  if (g == NULL)
    return NULL; 
  return brother(p);
}

void left_rotation(Node* x) {
  Node* y = x->right;
  //x's right son becomes y's left son
  x->right = y->left;
  if (y->left != LEAF)
    y->left->parent = x;
 
  y->parent = x->parent;
  //if x is the root, y becomes the root
  if (x->parent == NULL)
    x = y;

  //else; replace x by y
  else if (x == x->parent->left)
    x->parent->left = y;
  else
    x->parent->right = y;

  //we attache x at left of y
  y->left = x;
  x->parent = y;
}

void right_rotation(Node* x) {
  Node* y = x->left;
  //x's left son becomes y's right son
  x->left = y->right;
  if (y->right != LEAF)
    y->right->parent = x;
 
  y->parent = x->parent;
  //if x is the root, y becomes the root
  if (x->parent == NULL)
    x = y;

  //else; replace x by y
  else if (x == x->parent->right)
    x->parent->right = y;
  else
    x->parent->left = y;

  //we attache x at the right of y
  y->right = x;
  x->parent = y;
}

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    newNode->key = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;
    
    return newNode;
}

void recursive_insert(Node *root,  Node *n){
  if (root != NULL && n->key < root->key) {
    if (root->left != LEAF) {
      recursive_insert(root->left, n);
      return;
    }
    else
      root->left = n;
  } 
  else if (root != NULL) {
    if (root->right != LEAF) {
      recursive_insert(root->right, n);
      return;
	}
    else
      root->right = n;
  }

  n->parent = root;
  n->left = LEAF; 
  n->right = LEAF; 
  n->color = 0;
}


void insertion_cas1(Node *n) {
  printf("case1\n");
   if (parent(n) == NULL)
      n->color = 1;
}

void insertion_cas2(Node *n) {
   printf("case2\n");
   return; // The tree is already a RBT
}

void insertion_cas3(Node *n) {
   printf("case3\n");
   parent(n)->color = 1;
   uncle(n)->color = 1;
   
   Node *g = grandparent(n);
   g->color = 0;
   repair_tree_insert(g);
}

void insertion_cas4(Node *n) {
   
   Node *p = parent(n);
   Node *g = grandparent(n);
   printf("case4st\n");
   if (n == g->left->right) {
      printf("case4if\n");
      left_rotation(p);
      n = n->left;
   } else if (n == g->right->left) {
      printf("case4else\n");
      right_rotation(p);
      n = n->right; 
   }
  printf("case4\n");
   insertion_cas5(n);
}

void insertion_cas5(Node *n) {
   printf("case5\n");
   Node *p = parent(n);
   Node *g = grandparent(n);

   if (n == p->left)
      right_rotation(g);
   else
      left_rotation(g);
  
   p->color = 1;
   g->color = 0;
}


void repair_tree_insert(Node *n) {
   printf("beginning\n");
   if (parent(n) == NULL){
      insertion_cas1(n);
      printf("insertcase1\n");}
   else if (parent(n)->color == 1){
      insertion_cas2(n);
      printf("insertcase2\n");}
   else if (uncle(n) != NULL && uncle(n)->color == 0){
      insertion_cas3(n);
      printf("insertcase3\n");}
   else{
      insertion_cas4(n);
      printf("insertcase4\n");}
}

//Takes a tree and a node n and returns the new root after insertion
Node *insertion(Node *root, int val) {

    Node *n = createNode(val);
    printf("insert\n");
    recursive_insert(root, n);
    printf("insertrec\n");
    // Repair tree in case rules are violated
    repair_tree_insert(n);
    printf("insertrep\n");
    // search for new root
    root = n;
    
    while (parent(root) != NULL)
        root = parent(root);
       
    return root;
}

int search(Node *root, int key){
    if(root == NULL)
        return 0;
    if (root->key == key)
        return 1;
    if(root->key < key)
        search(root->right, key);
    else
        search(root->left, key);
}


void displayTree(Node *root){
    if(root!=NULL){
        displayTree(root->left);
        printf(" %d ", root->key);
        displayTree(root->right);
    }
}