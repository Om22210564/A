#include <iostream>
#include <vector>
using namespace std;

void floydWarshall(vector<vector<int>>& graph, int n) {
    // Initialize the distance matrix with the input graph
    vector<vector<int>> dist = graph;

    // Floyd-Warshall Algorithm
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                // Skip if there's no path from i to k or k to j
                if (dist[i][k] == -1 || dist[k][j] == -1) continue;

                // Update the shortest path from i to j
                if (dist[i][j] == -1 || dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // Print the result
    cout << "Shortest distances between every pair of vertices:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (dist[i][j] == -1)
                cout << "INF ";
            else
                cout << dist[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int n; // Number of vertices
    cout << "Enter the number of vertices: ";
    cin >> n;

    vector<vector<int>> graph(n, vector<int>(n));
    cout << "Enter the adjacency matrix (-1 for no direct path):\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> graph[i][j];
        }
    }

    floydWarshall(graph, n);

    return 0;
}
