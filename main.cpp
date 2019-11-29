// A C++ program for Dijkstra's single source shortest path algorithm.
// The program is for adjacency matrix representation of the graph
#include <iostream>
#include <climits>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <string>
#include <iomanip>
#include <mutex>



// Number of vertices in the graph
#define V 10
/* Define Infinite as a large enough
value.This value will be used for
vertices not connected to each other */
#define INF 99999

using namespace std;

mutex mtx;

// Fucntion to convert a string to
// integer array
int * convertStrtoArr(string str, int amount)
{
    // get length of string str
    int str_length;
    str_length =  str.length();
    //cout << "str.length(): " << str.length() << endl;

    // create an array with size as string
    // length and initialize with 0
    //int arr[str_length] = { 0 };

    int *arr;
    arr = (int *) calloc(amount, sizeof(int));

    int j = 0, i;

    mtx.lock();

    // Traverse the string
    for (i = 0; str[i] != '\r'; i++) {
        if(i < str_length - 1){
            // if str[i] is ' ' then split
            if (str[i] == ' ') {
                // Increment j to point to next
                // array location
                j++;
            }
            else {
                // subtract str[i] by 48 to convert it to int
                // Generate number by multiplying 10 and adding
                // (int)(str[i])
                arr[j] = arr[j] * 10 + (str[i] - 48);
                //cout << "arr[" << j << "] : " << arr[j] << endl;
            }
        }
    }
    mtx.unlock();
    return arr;
}
// A utility function to find the vertex with minimum distance value, from
// the set of vertices not yet included in shortest path tree
int minDistance(int dist[], bool sptSet[])
{
    // Initialize min value
    int min = INT_MAX, min_index = -1;

    for (int v = 0; v < V; v++)
        if (!sptSet[v] && dist[v] <= min)
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
    //printSolution(dist);
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
                cout << setfill('0') << setw(3) << dist[i][j] << "     ";
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
    //printSolutionFloyd(dist);
}


// driver program to test above function
int main()
{
    clock_t t;
    double time_taken;
    string line;
    int *actualLine;
    actualLine = (int *) calloc(V, sizeof(int));
    string Num = std::to_string(V);
    ifstream myfile ("/home/osama/CLionProjects/PAA04/Conjunto4/Entrada "+ Num + ".txt");
    ofstream output;
    output.open("/home/osama/Documents/Unioeste/2019/PAA/Trabalho04/Saida.csv", std::ios::app);
    int graph[V][V];
    if (myfile.is_open())
    {
        int count = 0;
        while(getline (myfile, line))
        {
            actualLine = convertStrtoArr(line, V);
            //cout << "ActualLine: " << actualLine << endl;
            for(int i = 0; i < V; i++)
            {
                graph[count][i] = actualLine[i];
                if(graph[count][i] == 0){
                    if(count != i) graph[count][i] = INF;
                }
                //cout << "Graph[" << count << "][" << i << "]: " << actualLine[i] << endl;
            }
            count++;
        }
    }
    else cout << "Unable to open file" << endl;
    myfile.clear();
    myfile.close();

    t = clock();
    if(V == 10) output << "Dijkstra" << "," << "Floyd-Warshall" << "," << "Conjunto de Entrada"  << endl;
    for(int i = 0; i < V; i++)
    {
        dijkstra(graph, i);
    }
    t = clock() - t;
    time_taken = ((double) t) / CLOCKS_PER_SEC;
    cout << "Time taken in dijkstra: " << time_taken << endl;
    output << time_taken << ",";

    t = clock();
    floydWarshall(graph);
    t = clock() - t;
    time_taken = ((double) t) / CLOCKS_PER_SEC;
    cout << "Time taken in Warshall: " << time_taken << endl;
    output << time_taken << "," << V  << endl;
    output.close();

    return 0;
}
