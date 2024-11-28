#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <queue>
#include <numeric> // Include for std::iota
using namespace std;
const int INF = numeric_limits<int>::max();
const int MAXN = 20;
// Brute Force TSP
int tspBruteForce(vector<vector<int>>& dist, vector<int>& path) {
    int n = dist.size(), minCost = INF;
    vector<int> cities(n - 1);
    iota(cities.begin(), cities.end(), 1); // Fill cities with 1 to n-1
    do {
        int currentCost = dist[0][cities[0]];
        for (size_t i = 0; i < cities.size() - 1; i++)
            currentCost += dist[cities[i]][cities[i + 1]];
        currentCost += dist[cities.back()][0];
        if (currentCost < minCost) {
            minCost = currentCost;
            path = {0}; // Start from city 0
            path.insert(path.end(), cities.begin(), cities.end());
            path.push_back(0); // Return to starting city
        }
    } while (next_permutation(cities.begin(), cities.end()));
    return minCost;
}
// Dynamic Programming TSP
int tspDP(int pos, int visited, vector<vector<int>>& dist, vector<vector<int>>& dp, vector<vector<int>>& parent) {
    if (visited == (1 << dist.size()) - 1) return dist[pos][0];
    if (dp[pos][visited] != -1) return dp[pos][visited];
    int minCost = INF;
    for (int city = 0; city < dist.size(); city++) {
        if (!(visited & (1 << city))) {
            int newCost = dist[pos][city] + tspDP(city, visited | (1 << city), dist, dp, parent);
            if (newCost < minCost) {
                minCost = newCost;
                parent[pos][visited] = city;
            }
        }
    }
    return dp[pos][visited] = minCost;
}
// Branch and Bound TSP
struct Node {
    int cost, level, visited;
    vector<int> path;
    Node(int c, int l, int v, const vector<int>& p) : cost(c), level(l), visited(v), path(p) {}
    bool operator>(const Node& other) const { return cost > other.cost; }
};
int tspBranchAndBound(vector<vector<int>>& dist, vector<int>& bestPath) {
    int n = dist.size(), minCost = INF;
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    pq.push(Node(0, 0, 1, {0}));
    while (!pq.empty()) {
        Node node = pq.top(); pq.pop();
        if (node.level == n - 1) {
            int totalCost = node.cost + dist[node.level][0];
            if (totalCost < minCost) {
                minCost = totalCost;
                bestPath = node.path; bestPath.push_back(0);
            }
            continue;
        }
        for (int city = 0; city < n; city++) {
            if (city != node.level && !(node.visited & (1 << city))) {
                vector<int> newPath = node.path; newPath.push_back(city);
                pq.push(Node(node.cost + dist[node.level][city], city, node.visited | (1 << city), newPath));
            }
        }
    }
    return minCost;
}
int main() {
    vector<vector<int>> dist = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };
    // Brute Force
    vector<int> path;
    cout << "Brute Force - Minimum cost: " << tspBruteForce(dist, path) << "\nPath: ";
    for (int city : path) cout << city << " ";
    cout << "\n\n";
    // Dynamic Programming
    vector<vector<int>> dp(MAXN, vector<int>(1 << MAXN, -1)), parent(MAXN, vector<int>(1 << MAXN, -1));
    int minCost1 = tspDP(0, 1, dist, dp, parent);
    vector<int> dpPath;
    for (int currentCity = 0, visited = 1; ; ) {
        dpPath.push_back(currentCity);
        if (visited == (1 << dist.size()) - 1) break;
        currentCity = parent[currentCity][visited]; visited |= (1 << currentCity);
    }
    dpPath.push_back(0);
    cout << "Dynamic Programming - Minimum cost: " << minCost1 << "\nPath: ";
    for (int city : dpPath) cout << city << " ";
    cout << "\n\n";
    // Branch and Bound
    vector<int> bestPath;
    cout << "Branch and Bound - Minimum cost: " << tspBranchAndBound(dist, bestPath) << "\nPath: ";
    for (int city : bestPath) cout << city << " ";
    cout << "\n";
    return 0;
}
