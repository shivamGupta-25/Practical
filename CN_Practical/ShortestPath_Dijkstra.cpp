#include <bits/stdc++.h>
using namespace std;

const int N = 1e3 + 10;
const int INF = 1e9 + 10;

vector<pair<int, int>> g[N]; // graph {node, weight}

vector<int> dijkstra(int source, int n)
{
    vector<int> vis(N, 0);
    vector<int> dist(N, INF);

    set<pair<int, int>> st; // {weight, node}
    st.insert({0, source});
    dist[source] = 0;

    while (!st.empty())
    {
        auto node = *st.begin();
        int v = node.second;
        int v_dist = node.first;
        st.erase(st.begin());
        
        if (vis[v])
        {
            continue;
        }
        vis[v] = 1;
        
        for (auto child : g[v])
        {
            int child_v = child.first;
            int wt = child.second;

            if (dist[v] + wt < dist[child_v])
            {
                dist[child_v] = dist[v] + wt;
                st.insert({dist[child_v], child_v});
            }
        }
    }
    
    return dist;
}

int main()
{
    cout << "Enter number of nodes and edges (n m): ";
    int n, m;
    cin >> n >> m;
    
    // Clear the graph
    for (int i = 0; i < N; i++) {
        g[i].clear();
    }
    
    cout << "Enter " << m << " edges (source, destination, weight) Example: 1 2 50:" << endl;
    for (int i = 0; i < m; ++i)
    {
        int x, y, wt;
        cin >> x >> y >> wt;
        g[x].push_back({y, wt});
        // For undirected graph, uncomment the following line
        // g[y].push_back({x, wt});
    }
    
    cout << "Enter source node: ";
    int source;
    cin >> source;
    
    vector<int> distances = dijkstra(source, n);
    
    // Print distances from source to all nodes
    cout << "\nShortest Path Results:" << endl;
    cout << "=======================" << endl;
    for (int i = 1; i <= n; ++i)
    {
        cout << "Node " << i << ": ";
        if (distances[i] == INF)
            cout << "Not reachable" << endl;
        else
            cout << distances[i] << endl;
    }

    return 0;
}

/* Sample Input:
    Enter number of nodes and edges (n m): 6 11
    Enter 11 edges (source, destination, weight) Example: 1 2 50:
    1 2 50
    1 3 45
    1 4 10
    2 3 10
    2 4 15
    3 5 30
    4 1 10
    4 5 15
    5 2 20
    5 3 35
    6 5 3

    Enter source node: 1
*/