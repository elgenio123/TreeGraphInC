#include "../includes/tree.h"
#include "../includes/queue.h"

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

Node* createNode(int key) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    newNode->key = key;
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
  //printf("casee1\n");
   if (parent(n) == NULL)
      n->color = 1;
}

void insertion_case2(Node *root, Node *n) {
   //printf("casee2\n");
   parent(n)->color = 1;
   uncle(n)->color = 1;
   
   Node *g = grandparent(n);
   g->color = 0;
   repair_tree_insert(root, g);
}

void insertion_case3(Node *root, Node *n) {
   
   Node *p = parent(n);
   Node *g = grandparent(n);
//    printf("casee3st\n");
   if (g->left !=LEAF && n == g->left->right) {
      //printf("casee3if\n");
      left_rotation(root, p);
      n = n->left;
   } else if (g->right !=LEAF && n == g->right->left) {
      //printf("casee3else\n");
      right_rotation(root, p);
      n = n->right; 
   }
 // printf("casee3end\n");
   insertion_case4(root, n);
}

void insertion_case4(Node *root, Node *n) {
//    printf("casee4st\n");
   Node *p = parent(n);
   Node *g = grandparent(n);

   if (n == p->left)
      right_rotation(root, g);
   else
      left_rotation(root, g);
   p->color = 1;
   g->color = 0;
    //printf("casee4end\n");
}


void repair_tree_insert(Node *root, Node *n) {
//    printf("beginning\n");
   if (parent(n) == NULL){
      insertion_case1(n);
    //   printf("insertcasee1\n");
    }
   else if (parent(n)->color == 1)
      return;
   else if (uncle(n) != NULL && uncle(n)->color == 0){
      insertion_case2(root, n);
    //   printf("insertcasee2\n");
    }
   else{
      insertion_case3(root, n);
    //   printf("insertcasee3\n");
    }
}

//Takes a tree and a node n and returns the new root after insertion
Node *insertion(Node *root, int val) {

    Node *n = createNode(val);
    // printf("insert\n");
    recursive_insert(root, n);
    // printf("insertrec\n");

    repair_tree_insert(root, n);
    // printf("insertrep\n");
   
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

void transplant(Node** root, Node* u, Node* v) {
       if (u->parent == NULL)
        *root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;

    if (v != NULL)
        v->parent = u->parent;
}

Node* find_min(Node* node) {
    while (node->left != NULL)
        node = node->left;
    return node;
}


void delete_fixup(Node* root, Node* x) {
    // Fix the tree after deletion
    //printf("Start delete fixUp\n");
    while (x != root && (x == NULL || x->color == BLACK)) {
        if (x == x->parent->left) {
            Node* sibling = x->parent->right;

            if (sibling->color == RED) {
                sibling->color = BLACK;
                x->parent->color = RED;
                left_rotation(root, x->parent);
                sibling = x->parent->right;
            }

            if ((sibling->left == NULL || sibling->left->color == BLACK) &&
                (sibling->right == NULL || sibling->right->color == BLACK)) {
                sibling->color = RED;
                x = x->parent;
            } else {
                if (sibling->right == NULL || sibling->right->color == BLACK) {
                    sibling->left->color = BLACK;
                    sibling->color = RED;
                    right_rotation(root, sibling);
                    sibling = x->parent->right;
                }

                sibling->color = x->parent->color;
                x->parent->color = BLACK;
                sibling->right->color = BLACK;
                left_rotation(root, x->parent);
                x = root;
            }
        } else {
            // Symmetric case (right child)
            struct Node* sibling = x->parent->left;

            if (sibling->color == RED) {
                sibling->color = BLACK;
                x->parent->color = RED;
                right_rotation(root, x->parent);
                sibling = x->parent->left;
            }

            if ((sibling->right == NULL || sibling->right->color == BLACK) &&
                (sibling->left == NULL || sibling->left->color == BLACK)) {
                sibling->color = RED;
                x = x->parent;
            } else {
                if (sibling->left == NULL || sibling->left->color == BLACK) {
                    sibling->right->color = BLACK;
                    sibling->color = RED;
                    left_rotation(root, sibling);
                    sibling = x->parent->left;
                }

                sibling->color = x->parent->color;
                x->parent->color = BLACK;
                sibling->left->color = BLACK;
                right_rotation(root, x->parent);
                x = root;
            }
        }
    }
    if(x == root  || x->color == RED){
        x->color = BLACK;
    }
    
    //printf("end delete fixUp\n");
}


Node* delete_node(Node* root, int key) {
    //printf("Start delete node helper\n");
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left=delete_node(root->left, key);
    else if (key > root->key)
         root->right=delete_node(root->right, key);
    else {
        if (root->left == NULL) {
            Node* temp = root->right;
            transplant(&root, root, root->right);
            if(root->color != RED){
               delete_fixup(root, temp);
               free(root);
            }
            else
                free(root);
            //printf("end delete node helper\n");
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            transplant(&root, root, root->left);
            if(root->color != RED){
               delete_fixup(root, temp);
               free(root);
            }
            else
                free(root);
            //printf("end delete node helper\n");
            return temp;
        }

        Node* temp = find_min(root->right);
        root->key = temp->key;
        root->right = delete_node(root->right, temp->key);
    }

    return root;
}


void displayTree(Node *root){
    if(root!=NULL){
        displayTree(root->left);
        printf(" %d ", root->key);
        displayTree(root->right);
    }
}
void clear_tree(Node *root){
  if(root!=NULL){
        clear_tree(root->left);
        clear_tree(root->right);
        free(root);
    }
}
