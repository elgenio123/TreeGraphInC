#include "tree.h"
#include "queue.h"

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

void left_rotation(Node* root, Node* x) {
    if (x == NULL || x->right == NULL)
        return;

    Node* y = x->right;
    x->right = y->left;

    if (y->left != NULL)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == NULL)
        root = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;

    y->left = x;
    x->parent = y;
}

void right_rotation(Node* root, Node* x) {
    if (x == NULL || x->left == NULL)
        return;

    Node* y = x->left;
    x->left = y->right;

    if (y->right != NULL)
        y->right->parent = x;

    y->parent = x->parent;

    if (x->parent == NULL)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

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


void insertion_case1(Node *n) {
  printf("casee1\n");
   if (parent(n) == NULL)
      n->color = 1;
}

void insertion_case2(Node *root, Node *n) {
   printf("casee2\n");
   parent(n)->color = 1;
   uncle(n)->color = 1;
   
   Node *g = grandparent(n);
   g->color = 0;
   repair_tree_insert(root, g);
}

void insertion_case3(Node *root, Node *n) {
   
   Node *p = parent(n);
   Node *g = grandparent(n);
   printf("casee3st\n");
   if (g->left !=LEAF && n == g->left->right) {
      printf("casee3if\n");
      left_rotation(root, p);
      n = n->left;
   } else if (g->right !=LEAF && n == g->right->left) {
      printf("casee3else\n");
      right_rotation(root, p);
      n = n->right; 
   }
  printf("casee3end\n");
   insertion_case4(root, n);
}

void insertion_case4(Node *root, Node *n) {
   printf("casee4st\n");
   Node *p = parent(n);
   Node *g = grandparent(n);

   if (n == p->left)
      right_rotation(root, g);
   else
      left_rotation(root, g);
   p->color = 1;
   g->color = 0;
    printf("casee4end\n");
}


void repair_tree_insert(Node *root, Node *n) {
   printf("beginning\n");
   if (parent(n) == NULL){
      insertion_case1(n);
      printf("insertcasee1\n");}
   else if (parent(n)->color == 1)
      return;
   else if (uncle(n) != NULL && uncle(n)->color == 0){
      insertion_case2(root, n);
      printf("insertcasee2\n");}
   else{
      insertion_case3(root, n);
      printf("insertcasee3\n");}
}

//Takes a tree and a node n and returns the new root after insertion
Node *insertion(Node *root, int val) {

    Node *n = createNode(val);
    printf("insert\n");
    recursive_insert(root, n);
    printf("insertrec\n");
    // Repair tree in casee rules are violated
    repair_tree_insert(root, n);
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
