
#ifndef graph_h
#define graph_h

    #include <stdio.h>
    #include <stdlib.h>
    #include <limits.h>
    #include <stdint.h>
    #include <omp.h>

    #define MAX_VERTICES 100

    typedef struct Vertex {
        int64_t distance;
        int inCluster;
    }Vertex;

    typedef struct Edge{
        int src, dest, weight;
    } Edge;

    typedef struct Graph{
        int numVertices;
        int adjacencyMatrix[MAX_VERTICES][MAX_VERTICES];
    }Graph;

    // Subset structure for Disjoint Set
    typedef struct Subset{
        int parent;
        int rank;
    } Subset;



    void initGraph(Graph* graph, int numVertices);
    void addEdge(Graph* graph, int startVertex, int endVertex, int weight);
    void printGraph(Graph* graph);

    int minDistance(int dist[], int sptSet[], int);
    void dijkstra(Graph *graph, int src);
    void printSolution(int dist[], int);
    void dijkstra_parallel(Graph *graph, int src);

    int minKey(int key[], int mstSet[],int n);
    void printMST(int parent[], Graph *graph, int n);
    void primMST(Graph *graph);

    int compareEdges(const void* a, const void* b);
    int find(Subset subsets[], int i);
    void Union(Subset subsets[], int x, int y);
    Edge* getEdges(Graph *graph);
    void kruskalMST(Graph *graph);
    #endif