#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// A structure to represent a weighted edge
struct Edge {
    int src, dest, weight;
};

// A class to represent a disjoint set (Union-Find)
class DisjointSet {
public:
    vector<int> parent, rank;

    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    // Find the representative of the set containing 'x'
    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]); // Path compression
        return parent[x];
    }

    // Union the two sets containing 'x' and 'y'
    void unionSets(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        // Union by rank
        if (rootX != rootY) {
            if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
};

// Function to compare two edges based on their weight (for sorting)
bool compareEdges(Edge a, Edge b) {
    return a.weight < b.weight;
}

// Function to find the MST using Kruskal's algorithm
void kruskal(int V, vector<Edge>& edges) {
    // Sort edges by weight
    sort(edges.begin(), edges.end(), compareEdges);

    DisjointSet ds(V); // Initialize disjoint-set

    vector<Edge> mst; // To store the result MST
    int mstWeight = 0; // To store the total weight of MST

    // Process each edge in sorted order
    for (auto& edge : edges) {
        int u = edge.src, v = edge.dest;

        // If including this edge does not form a cycle
        if (ds.find(u) != ds.find(v)) {
            ds.unionSets(u, v); // Include the edge in MST
            mst.push_back(edge); // Add to the MST
            mstWeight += edge.weight; // Add to the total weight
        }
    }

    // Print the MST
    cout << "Edges in the Minimum Spanning Tree (MST):\n";
    for (auto& edge : mst) {
        cout << edge.src << " - " << edge.dest << " : " << edge.weight << endl;
    }
    cout << "Total weight of the MST: " << mstWeight << endl;
}

int main() {
    int V, E;

    // Read number of vertices and edges
    cout << "Enter number of vertices: ";
    cin >> V;
    cout << "Enter number of edges: ";
    cin >> E;

    vector<Edge> edges(E);

    // Read edges
    cout << "Enter the edges (source, destination, weight):\n";
    for (int i = 0; i < E; i++) {
        cin >> edges[i].src >> edges[i].dest >> edges[i].weight;
    }

    // Run Kruskal's algorithm
    kruskal(V, edges);

    return 0;
}
