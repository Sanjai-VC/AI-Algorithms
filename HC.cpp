#include <bits/stdc++.h>
using namespace std;

struct Node {
    vector<pair<string, int>> edges; // neighbor, cost (not really used in pure HC)
    int heuristic{};
};

map<string, Node> graph;

// Hill Climbing Search (as per your given implementation)
vector<string> hillClimbing(const string& start, const string& goal) {
    vector<string> path{start};
    string current = start;
    while (current != goal) {
        const auto& neighbors = graph[current].edges;
        if (neighbors.empty()) return {};
        auto next = min_element(neighbors.begin(), neighbors.end(),
                                [](auto& a, auto& b) {
                                    return graph[a.first].heuristic < graph[b.first].heuristic;
                                });
        if (graph[next->first].heuristic >= graph[current].heuristic) return {};
        path.push_back(next->first);
        current = next->first;
    }
    return path;
}

int main() {
    int n, m;
    cout << "Enter number of nodes and edges: ";
    cin >> n >> m;

    cout << "Enter node labels (e.g., A B C ...):\n";
    vector<string> labels(n);
    for (int i = 0; i < n; i++) cin >> labels[i];

    cout << "Enter " << m << " edges (u v):\n";
    for (int i = 0; i < m; i++) {
        string u, v;
        cin >> u >> v;
        graph[u].edges.push_back({v, 1});
        graph[v].edges.push_back({u, 1});
    }

    cout << "Enter heuristic values for each node:\n";
    for (auto& label : labels) {
        int h;
        cout << label << ": ";
        cin >> h;
        graph[label].heuristic = h;
    }

    string start, goal;
    cout << "Enter source and goal: ";
    cin >> start >> goal;

    // Print adjacency list
    cout << "\nGraph adjacency list:\n";
    for (auto& entry : graph) {
    string node = entry.first;
    auto& data = entry.second;
    // use node, data
}


    cout << "\nStarting Hill Climbing...\n";
    auto path = hillClimbing(start, goal);
    if (path.empty()) {
        cout << "No path found from " << start << " to " << goal << "\n";
    } else {
        cout << "Path found: ";
        for (auto& p : path) cout << p << " ";
        cout << "\n";
    }
}
