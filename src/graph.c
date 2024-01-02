#include "../includes/graph.h"

void initGraph(Graph* graph, int numVertices) {
    graph->numVertices = numVertices;

    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            graph->adjacencyMatrix[i][j] = 0;
        }
    }
}

void addEdge(Graph* graph, int startVertex, int endVertex, int weight) {
    if (startVertex >= 0 && startVertex < graph->numVertices &&
        endVertex >= 0 && endVertex < graph->numVertices) {
        // Add the weighted edge to the adjacency matrix
        graph->adjacencyMatrix[startVertex][endVertex] = weight;
        graph->adjacencyMatrix[endVertex][startVertex] = weight; // Assuming an undirected graph
    } else {
        printf("Invalid vertices\n");
    }
}
void printGraph(Graph* graph) {
    printf("Adjacency Matrix:\n");
    for (int i = 0; i < graph->numVertices; i++) {
        for (int j = 0; j < graph->numVertices; j++) {
            printf("%d\t", graph->adjacencyMatrix[i][j]);
        }
        printf("\n");
    }
}
int minDistance(int dist[], int sptSet[], int n) {
    int min = INT_MAX, min_index;

    #pragma omp for
    for (int v = 0; v < n; v++) {
        if (sptSet[v] == 0 && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}
void printSolution(int dist[], int n) {
    printf("Vertex \t Distance from Source\n");
    for (int i = 0; i < n; i++)
        printf("%d \t %d\n", i, dist[i]);
}
void dijkstra(Graph *graph, int src) {
    int dist[graph->numVertices]; // The output array dist[i] holds the shortest distance from src to i
    int sptSet[graph->numVertices]; // sptSet[i] will be true if vertex i is included in the shortest
                   // path tree or the shortest distance from src to i is finalized

    // Initialize all distances as INFINITE and sptSet[] as false
    for (int i = 0; i < graph->numVertices; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = 0;
    }

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < graph->numVertices - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices not yet
        // processed. u is always equal to src in the first iteration.
        int u = minDistance(dist, sptSet, graph->numVertices);

        // Mark the picked vertex as processed
        sptSet[u] = 1;

        // Update dist value of the adjacent vertices of the picked vertex.
        for (int v = 0; v < graph->numVertices; v++) {
            // Update dist[v] only if it's not in the sptSet, there is an edge from
            // u to v, and the total weight of path from src to v through u is
            // smaller than the current value of dist[v]
            if (!sptSet[v] && graph->adjacencyMatrix[u][v] && dist[u] != INT_MAX &&
                dist[u] + graph->adjacencyMatrix[u][v] < dist[v]) {
                dist[v] = dist[u] + graph->adjacencyMatrix[u][v];
            }
        }
    }

    printSolution(dist, graph->numVertices);
}
int findMinDistance(int dist[], int sptSet[], int n) {
     int min = INT_MAX, min_index;

    #pragma omp parallel for
    for (int v = 0; v < n; v++) {
        if (sptSet[v] == 0 && dist[v] < min) {
            #pragma omp critical
            {
                min = dist[v];
                min_index = v;
            }
        }
    }

    return min_index;
}

// Parallel Dijkstra's algorithm
void dijkstra_parallel(Graph *graph, int src) {
    int V = graph->numVertices; //P = omp_get_num_procs()

      int dist[V];     // tTable to store shortest distances from the source
    int sptSet[V];   // Table to follow the nodes included in the tree of minimum weights

    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = 0;
    }

    // DIstance from source to itself is 0
    dist[src] = 0;

    printf("Number of threads %d\n", omp_get_num_procs());

    // Find the shortest way for every node
    for (int count = 0; count < V - 1; count++) {
        int u = findMinDistance(dist, sptSet, V);

        // Mark chosen node as treated
        sptSet[u] = 1;

        // Update the distance of the chosen node
        #pragma omp parallel for
        for (int v = 0; v < V; v++) {
            printf("Thread %d is processing iteration %d\n",omp_get_thread_num(), v);
            if (!sptSet[v] && graph->adjacencyMatrix[u][v] && dist[u] != INT_MAX && dist[u] + graph->adjacencyMatrix[u][v] < dist[v]) {
                #pragma omp critical
                {
                    printf("Thread %d is updating the table of distances\n", omp_get_thread_num());
                    dist[v] = dist[u] + graph->adjacencyMatrix[u][v];
                }
            }
        }
    }
    printSolution(dist, V);
}

int minKey(int key[], int mstSet[],int n) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < n; v++) {
        if (mstSet[v] == 0 && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }

    return min_index;
}

void printMST(int parent[], Graph *graph, int n) {
    int totalWeight = 0;
    printf("Edge \tWeight\n");
    for (int i = 1; i < n; i++){
        printf("%d - %d \t%d \n", parent[i], i, graph->adjacencyMatrix[i][parent[i]]);
        totalWeight += graph->adjacencyMatrix[i][parent[i]];
    }
    printf("\nTotal weight = %d \n", totalWeight);
}

void primMST(Graph *graph) {
    int parent[graph->numVertices];
    int key[graph->numVertices];
    int mstSet[graph->numVertices];

    for (int i = 0; i < graph->numVertices; i++) {
        key[i] = INT_MAX;
        mstSet[i] = 0;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < graph->numVertices - 1; count++) {
        int u = minKey(key, mstSet, graph->numVertices);

        mstSet[u] = 1;

        for (int v = 0; v < graph->numVertices; v++) {
            if (graph->adjacencyMatrix[u][v] && mstSet[v] == 0 && graph->adjacencyMatrix[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph->adjacencyMatrix[u][v];
            }
        }
    }

    printMST(parent, graph, graph->numVertices);
}
// Compare function for qsort
int compareEdges(const void* a, const void* b) {
    return ((Edge*)a)->weight - ((Edge*)b)->weight;
}   

// Find operation for Disjoint Set
int find(Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

// Union operation for Disjoint Set
void Union(Subset subsets[], int x, int y) {
    int rootX = find(subsets, x);
    int rootY = find(subsets, y);

    if (subsets[rootX].rank < subsets[rootY].rank) {
        subsets[rootX].parent = rootY;
    } else if (subsets[rootX].rank > subsets[rootY].rank) {
        subsets[rootY].parent = rootX;
    } else {
        subsets[rootY].parent = rootX;
        subsets[rootX].rank++;
    }       
}

int getEdgeNumber(Graph *graph){
    int numEdges = 0;
    for (int i = 0; i < graph->numVertices; ++i) {
        for (int j = 0; j < graph->numVertices; ++j) {
            if (graph->adjacencyMatrix[i][j] != 0) {
                numEdges++;
            }
        }
    }
    return numEdges;
}

Edge* getEdges(Graph *graph){
    int numVertices = graph->numVertices;
    
    int numEdges = getEdgeNumber(graph);

    Edge* edges = (Edge*)malloc((numEdges) * sizeof(Edge));

    int edgeIndex = 0;
    for (int i = 0; i < numVertices; ++i) {
        for (int j = i + 1; j < numVertices; ++j) {
            if (graph->adjacencyMatrix[i][j] != 0) {
                edges[edgeIndex].src = i;
                edges[edgeIndex].dest = j;
                edges[edgeIndex].weight = graph->adjacencyMatrix[i][j];
                edgeIndex++;
            }
        }
    }
    return edges;
}

// Kruskal's Algorithm
void kruskalMST(Graph *graph) {

    Edge *edges = getEdges(graph);
    int numVertices = graph->numVertices;

    int numEdges = getEdgeNumber(graph);;
    
    qsort(edges, numEdges, sizeof(Edge), compareEdges);

    Subset subsets[MAX_VERTICES];
    for (int i = 0; i < numVertices; i++) {
        subsets[i].parent = i;
        subsets[i].rank = 0;
    }

    printf("Selected edges in the MST:\n");

    int totalWeight = 0;

    for (int i = 0, e = 0; e < numVertices - 1; i++) {
        int rootSrc = find(subsets, edges[i].src);
        int rootDest = find(subsets, edges[i].dest);

        if (rootSrc != rootDest) {
            printf("%d -- %d\n", edges[i].src, edges[i].dest);
            totalWeight += edges[i].weight;
            Union(subsets, rootSrc, rootDest);
            e++;
        }
    }
    printf("Total Weight of MST: %d\n", totalWeight);
}





