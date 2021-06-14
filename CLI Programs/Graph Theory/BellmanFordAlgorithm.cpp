#include <iostream>
#include <time.h>
using namespace std;

class Graph
{
    int numberOfVertices, numberOfEdges;

public:
    Graph(const int &numberOfVertices, const int &numberOfEdges) : numberOfVertices(numberOfVertices), numberOfEdges(numberOfEdges) {}

    void BellmanFord(int **graph, const int &src)
    {
        int dest = 1, weight = 2;
        int dis[numberOfVertices];
        // ? Arrays Initalizing Setup
        for (int i = 0; i < numberOfVertices; i++)
            dis[i] = INT32_MAX;
        dis[src] = 0; // ? Initial Source Index
        for (int v = 0; v < numberOfVertices - 1; v++)
        {
            for (int E = 0; E < numberOfEdges; E++)
            {
                if (dis[graph[E][src]] != INT32_MAX && dis[graph[E][src]] + graph[E][weight] < dis[graph[E][dest]])
                    dis[graph[E][dest]] = dis[graph[E][src]] + graph[E][weight];
            }
        }
        // ? Checking For A Negative Weight Cycle
        for (int E = 0; E < numberOfEdges; E++)
        {
            int src = graph[E][src], dest = graph[E][dest], weight = graph[E][weight];
            if (dis[src] != INT32_MAX && dis[src] + weight < dis[dest])
                cout << "Graph contains negative weight cycle\n";
        }
        printSolution(dis);
    }

private:
    void printSolution(int dist[])
    {
        printf("Vertex \t\t Distance from Source\n");
        for (int i = 0; i < numberOfVertices; i++)
            if (dist[i] != INT32_MAX)
                printf("%d \t\t %d\n", i, dist[i]);
    }
};

int main()
{
    int numberOfVertices, numberOfEdges;
    cout << "Enter Number Of Vertices: ";
    cin >> numberOfVertices;
    cout << "Enter Number Of Edges: ";
    cin >> numberOfEdges;
    int **graph = new int *[numberOfEdges];
    srand(time(0));
    printf("Random Generated Matrix: \n");
    printf("u v w\n");
    // ? Every edge will contanin 3 values (u,v,w)
    for (int i = 0; i < numberOfEdges; i++)
    {
        graph[i] = new int[numberOfVertices];
        for (int j = 0; j < 3; j++)
        {
            graph[i][j] = rand() % numberOfVertices;
            cout << graph[i][j] << ' ';
        }
        cout << '\n';
    }
    Graph obj(numberOfVertices, numberOfEdges);
    obj.BellmanFord(graph, 0);
    return 0;
}