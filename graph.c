#include "graph.h"

NodeGraph* createGraphNode(int dest, int weight) {
    NodeGraph* newNode = (NodeGraph*)malloc(sizeof(NodeGraph));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}
Graph* createGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;

    graph->array = (NodeGraph**)malloc(V * sizeof(NodeGraph*));

    for (int i = 0; i < V; ++i)
        graph->array[i] = NULL;

    return graph;
}