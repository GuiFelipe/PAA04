// A C++ program for Dijkstra's single source shortest path algorithm.
// The program is for adjacency matrix representation of the graph
#include <iostream>
#include <limits.h>
#include <stdio.h>
#include <time.h>

// Number of vertices in the graph
#define V 10
/* Define Infinite as a large enough
value.This value will be used for
vertices not connected to each other */
#define INF 99999

using namespace std;

// A utility function to find the vertex with minimum distance value, from
// the set of vertices not yet included in shortest path tree
int minDistance(int dist[], bool sptSet[])
{
    // Initialize min value
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

// A utility function to print the constructed distance array
int printSolution(int dist[])
{
    printf("Vertex \t\t Distance from Source\n");
    for (int i = 0; i < V; i++)
        printf("%d \t\t %d\n", i, dist[i]);
}

// Function that implements Dijkstra's single source shortest path algorithm
// for a graph represented using adjacency matrix representation
void dijkstra(int graph[V][V], int src)
{
    int dist[V]; // The output array.  dist[i] will hold the shortest
    // distance from src to i

    bool sptSet[V]; // sptSet[i] will be true if vertex i is included in shortest
    // path tree or shortest distance from src to i is finalized

    // Initialize all distances as INFINITE and stpSet[] as false
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices not
        // yet processed. u is always equal to src in the first iteration.
        int u = minDistance(dist, sptSet);

        // Mark the picked vertex as processed
        sptSet[u] = true;

        // Update dist value of the adjacent vertices of the picked vertex.
        for (int v = 0; v < V; v++)

            // Update dist[v] only if is not in sptSet, there is an edge from
            // u to v, and total weight of path from src to  v through u is
            // smaller than current value of dist[v]
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    // print the constructed distance array
    printSolution(dist);
}
/* A utility function to print solution */
void printSolutionFloyd(int dist[][V])
{
    cout<<"The following matrix shows the shortest distances"
          " between every pair of vertices \n";
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (dist[i][j] == INF)
                cout<<"INF"<<"     ";
            else
                cout<<dist[i][j]<<"     ";
        }
        cout<<endl;
    }
}

// Solves the all-pairs shortest path
// problem using Floyd Warshall algorithm
void floydWarshall (int graph[][V])
{
    /* dist[][] will be the output matrix
    that will finally have the shortest
    distances between every pair of vertices */
    int dist[V][V], i, j, k;

    /* Initialize the solution matrix same
    as input graph matrix. Or we can say
    the initial values of shortest distances
    are based on shortest paths considering
    no intermediate vertex. */
    for (i = 0; i < V; i++)
        for (j = 0; j < V; j++)
            dist[i][j] = graph[i][j];

    /* Add all vertices one by one to
    the set of intermediate vertices.
    ---> Before start of an iteration,
    we have shortest distances between all
    pairs of vertices such that the
    shortest distances consider only the
    vertices in set {0, 1, 2, .. k-1} as
    intermediate vertices.
    ----> After the end of an iteration,
    vertex no. k is added to the set of
    intermediate vertices and the set becomes {0, 1, 2, .. k} */
    for (k = 0; k < V; k++)
    {
        // Pick all vertices as source one by one
        for (i = 0; i < V; i++)
        {
            // Pick all vertices as destination for the
            // above picked source
            for (j = 0; j < V; j++)
            {
                // If vertex k is on the shortest path from
                // i to j, then update the value of dist[i][j]
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }

    // Print the shortest distance matrix
    printSolutionFloyd(dist);
}


// driver program to test above function
int main()
{
    clock_t t;
    double time_taken;
    /* Let us create the example graph discussed above */
    int graph[V][V] = { {0, INF, 8, 3, 3, 6, INF, 1, 0, 5 },
                        {8, 0, 1, 2, INF, INF, 4, INF, 4, 6 },
                        {4, 6, 0, 9, 1, 9, 6, INF, 3, INF },
                        {INF, INF, 6, 0, 5, 4 ,INF, INF ,4, 4 },
                        {6, 9, 8, INF, INF, 0, INF, INF, 3, INF },
                        {3, INF, 2, 8, 7, 0, 6, 4, INF, INF },
                        {7, 5, 4, INF, 1, INF, 0, INF, INF, 6 },
                        {1, 7, 0, 8, 1, 2, INF, 0, 8, 7 },
                        {2, INF, 9, INF, 9, 3, INF, 3, 0, 7 },
                        {0, INF, 1, INF, INF, 5, INF, 3, 8, 0 }
    };

    t = clock();
    for(int i = 0; i < V; i++)
    {
        dijkstra(graph, i);
    }
    t = clock() - t;
    time_taken = ((double) t) / CLOCKS_PER_SEC;
    cout << "Time taken in dijkstra: " << time_taken << endl;

    t = clock();
    floydWarshall(graph);
    t = clock() - t;
    time_taken = ((double) t) / CLOCKS_PER_SEC;
    cout << "Time taken in Warshall: " << time_taken << endl;
    
    return 0;
}
