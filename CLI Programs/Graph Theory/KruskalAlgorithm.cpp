#include <vector>
#include <iostream>

using namespace std;

class MinimumSpanningTreeAlgorithms
{
    int N, E; // ? Total Nodes & Edges
    int root(int n, int *parent)
    {
        while (n != parent[n])
            n = parent[n];
        return n;
    }
    template <typename ForwardIterator>
    void sort(ForwardIterator first, ForwardIterator last)
    {
        for (ForwardIterator sorted = first; first != last; last = sorted)
        {
            sorted = first;
            for (ForwardIterator current = first, prev = first; ++current != last; ++prev)
            {
                if (*current < *prev)
                {
                    iter_swap(current, prev);
                    sorted = current;
                }
            }
        }
    }

public:
    // ?       Weight, Start & End Vertex
    vector<pair<int, pair<int, int>>> graph, mst;
    MinimumSpanningTreeAlgorithms(const int &N, const int &E) : N(N), E(E){};
    int kruskal()
    {
        int total = 0, parent[N];
        for (int i = 0; i < N; i++)
            parent[i] = i;

        sort(graph.begin(), graph.end());

        for (int i = 0; i < graph.size(); i++)
        {
            int rootStartVertex = root(graph[i].second.first, parent), rootEndVertex = root(graph[i].second.second, parent);
            if (rootStartVertex != rootEndVertex)
            {
                mst.push_back(graph[i]);
                parent[rootStartVertex] = parent[rootEndVertex];
                total += graph[i].first;
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
    cout << "0. Add Edges\n1. Print Kruskal's Minimum Span\n2. Exit\n";
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
            total = obj.kruskal();
            for (int i = 0; i < obj.mst.size(); i++)
                printf("%c -> %c %d\n", obj.mst[i].second.first + 'A', obj.mst[i].second.second + 'A', obj.mst[i].first);

            printf("Total with Kruskal: %d\n\n", total);
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