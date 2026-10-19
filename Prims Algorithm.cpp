#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

// Structure to represent an edge: (weight, neighbor_node)
typedef pair<int, int> Edge; 

void primMST(int V, const vector<vector<Edge>>& adj) {
    // Min-heap to store pairs of (weight, node)
    priority_queue<Edge, vector<Edge>, greater<Edge>> pq;

    // Vectors to track MST inclusion and edge configurations
    vector<int> key(V, 1e9);       // Minimum weight edge to include node in MST
    vector<int> parent(V, -1);     // Array to store constructed MST structure
    vector<bool> inMST(V, false);  // True if vertex is included in MST

    // Start with vertex 0
    int src = 0;
    pq.push({0, src});
    key[src] = 0;

    int mst_weight = 0;

    while (!pq.empty()) {
        // Extract the node with the minimum weight edge
        int u = pq.top().second;
        int weight = pq.top().first;
        pq.pop();

        // If the vertex is already part of the MST, skip it
        if (inMST[u]) continue;

        // Include vertex in MST
        inMST[u] = true;
        mst_weight += weight;

        // Traverse all adjacent vertices of u
        for (const auto& edge : adj[u]) {
            int v = edge.second;
            int weight_uv = edge.first;

            // If v is not in MST and weight of (u,v) is smaller than current key of v
            if (!inMST[v] && weight_uv < key[v]) {
                key[v] = weight_uv;
                pq.push({key[v], v});
                parent[v] = u;
            }
        }
    }

    // Print the constructed MST
    cout << "Edges in the Minimum Spanning Tree:\n";
    for (int i = 1; i < V; ++i) {
        if (parent[i] != -1) {
            cout << parent[i] << " - " << i << " \n";
        }
    }
    cout << "Total Weight of MST: " << mst_weight << "\n";
    cout << "Enrollment No:92460118181";
}

int main() {
    int V = 5; // Number of vertices
    vector<vector<Edge>> adj(V);

    // Graph composition: addEdge(u, v, weight)
    // Represented as adj[u].push_back({weight, v})
    adj[0].push_back({2, 1}); adj[1].push_back({2, 0});
    adj[0].push_back({3, 3}); adj[3].push_back({3, 0});
    adj[1].push_back({3, 2}); adj[2].push_back({3, 1});
    adj[1].push_back({8, 5}); // assuming a minor correction if needed, mapping properly to V=5 indices
    adj[1].push_back({5, 4}); adj[4].push_back({5, 1});
    adj[2].push_back({7, 4}); adj[4].push_back({7, 2});
    adj[3].push_back({6, 4}); adj[4].push_back({6, 3});

    primMST(V, adj);

    return 0;
}
