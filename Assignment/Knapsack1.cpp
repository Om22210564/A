#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int knapsackDP(vector<int>& weights, vector<int>& values, int capacity) {
    int n = values.size();
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));
    for (int i = 1; i <= n; i++)
        for (int w = 1; w <= capacity; w++)
            dp[i][w] = weights[i - 1] <= w ? max(dp[i - 1][w], values[i - 1] + dp[i - 1][w - weights[i - 1]]) : dp[i - 1][w];
    return dp[n][capacity];
}
int knapsackBacktrack(vector<int>& weights, vector<int>& values, int capacity, int n, int currWeight = 0, int currValue = 0, int idx = 0) {
    if (idx == n || currWeight > capacity) return currValue;
    int exclude = knapsackBacktrack(weights, values, capacity, n, currWeight, currValue, idx + 1);
    int include = currWeight + weights[idx] <= capacity ? knapsackBacktrack(weights, values, capacity, n, currWeight + weights[idx], currValue + values[idx], idx + 1) : 0;
    return max(include, exclude);
}
struct Node {
    int level, profit, weight;
    float bound;
    Node(int l, int p, int w, float b) : level(l), profit(p), weight(w), bound(b) {}
};
bool operator<(const Node& a, const Node& b) { return a.bound < b.bound; }
float bound(Node u, int n, int capacity, vector<int>& weights, vector<int>& values) {
    if (u.weight >= capacity) return 0;
    float profit_bound = u.profit;
    int j = u.level + 1, totweight = u.weight;
    while (j < n && totweight + weights[j] <= capacity) {
        totweight += weights[j];
        profit_bound += values[j++];
    }
    if (j < n) profit_bound += (capacity - totweight) * (float)values[j] / weights[j];
    return profit_bound;
}
int knapsackBranchAndBound(vector<int>& weights, vector<int>& values, int capacity) {
    int n = values.size(), maxProfit = 0;
    priority_queue<Node> pq;
    pq.push(Node(-1, 0, 0, 0));
    while (!pq.empty()) {
        Node u = pq.top(); pq.pop();
        if (u.level == n - 1) continue;
        Node v(u.level + 1, u.profit, u.weight, 0);
        v.weight += weights[v.level]; v.profit += values[v.level];
        if (v.weight <= capacity && v.profit > maxProfit) maxProfit = v.profit;
        v.bound = bound(v, n, capacity, weights, values);
        if (v.bound > maxProfit) pq.push(v);
        v.weight = u.weight; v.profit = u.profit; v.bound = bound(v, n, capacity, weights, values);
        if (v.bound > maxProfit) pq.push(v);
    }
    return maxProfit;
}
int main() {
    vector<int> weights = {2, 3, 4, 5}, values = {3, 4, 5, 6};
    int capacity = 5;
    cout << "Dynamic Programming: " << knapsackDP(weights, values, capacity) << endl;
    cout << "Backtracking: " << knapsackBacktrack(weights, values, capacity, values.size()) << endl;
    cout << "Branch and Bound: " << knapsackBranchAndBound(weights, values, capacity) << endl;
    return 0;
}
