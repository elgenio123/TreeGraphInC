#include "queue.h"

Queue* createQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = queue->rear = NULL;
    return queue;
}

void enqueue(Queue* queue, Node* data) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->data = data;
    newNode->next = NULL;

    if (queue->rear == NULL) {
        queue->front = queue->rear = newNode;
        return;
    }

    queue->rear->next = newNode;
    queue->rear = newNode;
}
Node* dequeue(Queue* queue) {
    if (queue->front == NULL)
        return NULL;

    Node* data = queue->front->data;
    QueueNode* temp = queue->front;

    queue->front = queue->front->next;

    if (queue->front == NULL)
        queue->rear = NULL;

    free(temp);

    return data;
}

const char* colorToString(enum Color color) {
    switch (color) {
        case RED:
            return "RED";
        case BLACK:
            return "BLACK";
        default:
            return "UNKNOWN_COLOR"; 
    }
}

void breadthFirstSearch(struct Node* root) {
    if (root == NULL)
        return;

    struct Queue* queue = createQueue();

    enqueue(queue, root);
    enqueue(queue, NULL);

    while (queue->front != NULL) {
        struct Node* current = dequeue(queue);

        if (current == NULL) {
            printf("\n");

            if (queue->front != NULL)
                enqueue(queue, NULL);
        } else {
            printf("%d %s ", current->key, colorToString(current->color));

            if (current->left != NULL)
                enqueue(queue, current->left);

            if (current->right != NULL)
                enqueue(queue, current->right);
        }
    }
    printf("\n");
    free(queue);
}
