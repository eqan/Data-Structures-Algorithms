#include <iostream>
#include <time.h>
using namespace std;

class Graph
{
    int numberOfVertices;

public:
    Graph(const int &numberOfVertices) : numberOfVertices(numberOfVertices) {}

    void dijkstra(int **graph, int src)
    {
        int dist[numberOfVertices];
        bool visited[numberOfVertices];
        // ? Arrays Initalizing Setup
        for (int i = 0; i < numberOfVertices; i++)
            dist[i] = INT32_MAX, visited[i] = false;
        dist[src] = 0; // ? Initial Source Index
        for (int count = 0; count < numberOfVertices; count++)
        {
            int minimumDistance = minDistance(dist, visited);
            visited[minimumDistance] = true;
            for (int v = 0; v < numberOfVertices; v++)
                if (!visited[v] && graph[minimumDistance][v] && dist[minimumDistance] != INT32_MAX && dist[minimumDistance] + graph[minimumDistance][v] < dist[v])
                    dist[v] = dist[minimumDistance] + graph[minimumDistance][v];
        }
        printSolution(dist);
    }

private:
    // ? Calculating The Minimum Distance
    int minDistance(const int dist[], const bool visited[])
    {
        int min = INT32_MAX, minIndex;
        for (int v = 0; v < numberOfVertices; v++)
            if (visited[v] == false && dist[v] <= min)
                min = dist[v], minIndex = v;
        return minIndex;
    }
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
    int numberOfVertices;
    cout << "Enter Number Of Vertices: ";
    cin >> numberOfVertices;
    int **graph = new int *[numberOfVertices];
    srand(time(0));
    printf("Random Generated Matrix: \n");
    for (int i = 0; i < numberOfVertices; i++)
    {
        graph[i] = new int[numberOfVertices];
        for (int j = 0; j < numberOfVertices; j++)
        {
            graph[i][j] = rand() % 2;
            cout << graph[i][j] << ' ';
        }
        cout << '\n';
    }
    Graph obj(numberOfVertices);
    obj.dijkstra(graph, 0);
    return 0;
}