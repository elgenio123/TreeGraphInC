
#ifndef graph_h
#define graph_h

    #include <stdio.h>
    #include <stdlib.h>
    typedef struct NodeGraph {
        int dest;
        int weight;
        struct NodeGraph  *next;
    }NodeGraph;

    typedef struct Graph {
        int V; 
        struct NodeGraph** array;    
    }Graph;
    NodeGraph* createGraphNode(int dest, int weight);
    Graph* createGraph(int V);
#endif