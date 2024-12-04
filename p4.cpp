#include <iostream>
#include <vector>
#include <climits>  // For INT_MAX

using namespace std;

// A structure to represent a weighted edge
struct Edge {
    int src, dest, weight;
};

// Bellman-Ford algorithm to find the shortest path from the source node to all other nodes
void bellmanFord(int V, int E, vector<Edge>& edges, int src) {
    // Step 1: Initialize distances from source to all other vertices as INFINITE
    vector<int> dist(V, INT_MAX);
    dist[src] = 0;

    // Step 2: Relax all edges V-1 times
    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = edges[j].src;
            int v = edges[j].dest;
            int weight = edges[j].weight;

            // Relaxation: If the distance to v through u is shorter, update it
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }

    // Step 3: Check for negative weight cycles
    for (int i = 0; i < E; i++) {
        int u = edges[i].src;
        int v = edges[i].dest;
        int weight = edges[i].weight;

        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            cout << "Graph contains negative weight cycle!" << endl;
            return;
        }
    }

    // Step 4: Print the shortest distances from the source to all other vertices
    cout << "Vertex \t Distance from Source" << endl;
    for (int i = 0; i < V; i++) {
        if (dist[i] == INT_MAX) {
            cout << i << " \t INF" << endl;  // If no path exists
        } else {
            cout << i << " \t " << dist[i] << endl;
        }
    }
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

    int source;
    cout << "Enter the source vertex: ";
    cin >> source;

    // Run the Bellman-Ford algorithm
    bellmanFord(V, E, edges, source);

    return 0;
}
