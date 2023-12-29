#ifndef queue_h
#define queue_h
    #include "tree.h"
    typedef struct QueueNode {
        struct Node* data;
        struct QueueNode* next;
    }QueueNode;

    // Structure de la file
    typedef struct Queue {
        QueueNode* front;
        QueueNode* rear;
    }Queue;

    Queue* createQueue();
    void enqueue(Queue* queue, Node* data);
    Node* dequeue(Queue* queue);
    const char* colorToString(enum Color color);
    void breadthFirstSearch(Node* root);
#endif