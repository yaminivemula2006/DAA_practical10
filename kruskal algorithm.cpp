#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent an edge in the graph
struct Edge {
    int src, dest, weight;

    // Comparator operator to sort edges based on their weight
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

// Class to represent the Disjoint Set (Union-Find) data structure
class DisjointSet {
private:
    vector<int> parent;
    vector<int> rank;

public:
    // Constructor to initialize DSU for V vertices
    DisjointSet(int V) {
        parent.resize(V);
        rank.resize(V, 0);
        // Initially, every vertex is its own parent (representative)
        for (int i = 0; i < V; i++) {
            parent[i] = i;
        }
    }

    // Find operation with Path Compression
    int find(int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]); // Path compression
    }

    // Union operation by Rank
    void unite(int u, int v) {
        int root_u = find(u);
        int root_v = find(v);

        if (root_u != root_v) {
            // Attach smaller rank tree under root of higher rank tree
            if (rank[root_u] < rank[root_v]) {
                parent[root_u] = root_v;
            } else if (rank[root_u] > rank[root_v]) {
                parent[root_v] = root_u;
            } else {
                parent[root_v] = root_u;
                rank[root_u]++;
            }
        }
    }
};

// Function to find the Minimum Spanning Tree (MST) using Kruskal's Algorithm
void kruskalMST(vector<Edge>& edges, int V) {
    // 1. Sort all edges in non-decreasing order of their weight
    sort(edges.begin(), edges.end());

    DisjointSet dsu(V);
    vector<Edge> mst; // To store the resulting MST edges
    int mst_weight = 0;

    // 2. Iterate through all sorted edges
    for (const auto& edge : edges) {
        int root_src = dsu.find(edge.src);
        int root_dest = dsu.find(edge.dest);

        // If including this edge does not cause a cycle
        if (root_src != root_dest) {
            mst.push_back(edge);          // Add edge to result
            mst_weight += edge.weight;   // Accumulate total weight
            dsu.unite(root_src, root_dest); // Merge components
        }

        // Optimization: Stop early if we have found V - 1 edges
        if (mst.size() == V - 1) {
            break;
        }
    }

    // Print the constructed MST
    cout << "\nEdges in the Minimum Spanning Tree:\n";
    cout << "Source -- Destination == Weight\n";
    for (const auto& edge : mst) {
        cout << edge.src << " -- " << edge.dest << " == " << edge.weight << "\n";
    }
    cout << "\nTotal Weight of MST: " << mst_weight << endl;
}

int main() {
    int V, E;
    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;

    vector<Edge> edges(E);
    cout << "Enter edges in format (source destination weight):\n";
    for (int i = 0; i < E; i++) {
        cin >> edges[i].src >> edges[i].dest >> edges[i].weight;
    }

    kruskalMST(edges, V);

    return 0;
}
