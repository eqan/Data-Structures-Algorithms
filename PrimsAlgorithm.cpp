#include <vector>
#include <iostream>

using namespace std;

class MinimumSpanningTreeAlgorithms
{
    int N, E; // ? Total Nodes & Edges
    bool *visited;
public:
    // ?       Weight, Start & End Vertex
    vector<pair<int, pair<int, int>>> graph, mst;
    MinimumSpanningTreeAlgorithms(const int &N, const int &E) : N(N), E(E){
        visited = new bool[N];
        for (int i = 0; i < N; i++)
            visited[i] = false;
    };
    int prim(const int &start)
    {
        int total = 0;
        int n = start;
        while (!visited[n])
        {
            visited[n] = true;
            int w = INT32_MAX, min = INT32_MIN, minNext;
            for (int i = 0; i < graph.size(); i++)
            {
                if (graph[i].second.first == n || graph[i].second.second == n)
                {
                    int next;
                    if (graph[i].second.first == n)
                        next = graph[i].second.second;
                    else
                        next = graph[i].second.first;

                    if (!visited[next] && graph[i].first < w)
                    {
                        w = graph[i].first;
                        min = i;
                        minNext = next;
                    }
                }
            }

            if (min != INT32_MIN)
            {
                n = minNext;
                mst.push_back(graph[min]);
                total += graph[min].first;
            }
        }

        return total;
    }
};

// NOTE You will see glimpses of me using C style statements, I have become fond of regular expressions
// thats why i like to implement C Style statements as they have a similar Look & feel
int main()
{
    char startVertex, endVertex;
    int weight, E, N, opt, total;
    cout << "Enter Total Edges: ";
    cin >> E;
    MinimumSpanningTreeAlgorithms obj(E - 1, E);
Loop:
    cout << "0. Add Edges\n1. Print Prim's Minimum Span\n2. Exit\n";
    cout << "Option > ";
    cin >> opt;
    switch (opt)
    {
    case 0:
        system("clear");
        for (int i = 0; i < E; i++)
        {
            printf("Input for %d edge of %d edges: ", i, E - 1);
            cin >> startVertex >> endVertex >> weight;
            obj.graph.push_back(make_pair(weight, make_pair(startVertex - 'A', endVertex - 'A')));
        }
        break;
    case 1:
        system("clear");
        {
            total = obj.prim(0);
            for (int i = 0; i < obj.mst.size(); i++)
                printf("%c -> %c %d\n", obj.mst[i].second.first + 'A', obj.mst[i].second.second + 'A', obj.mst[i].first);

            printf("Total with Prim: %d\n", total);
            obj.mst.clear();
        }
        break;
    case 2:
        exit(0);
        break;
    default:
        cout << "[-] The Option is out of bounds, Please try again\n";
        break;
    }
    goto Loop;
    return 0;
}
