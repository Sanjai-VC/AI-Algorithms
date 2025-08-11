#include <bits/stdc++.h>
using namespace std;

// Graph structure
struct Graph {
    unordered_map<string, vector<pair<string, int>>> edges;
} graph;

// BFS Search
pair<vector<string>, int> BFS(const string &start, const string &goal) {
    queue<pair<string, vector<string>>> q;
    unordered_set<string> visited;
    q.push(make_pair(start, vector<string>{start}));
    visited.insert(start);

    while (!q.empty()) {
        pair<string, vector<string>> frontPair = q.front();
        q.pop();

        string node = frontPair.first;
        vector<string> path = frontPair.second;

        if (node == goal)
            return make_pair(path, (int)path.size() - 1); // cost = number of edges

        for (size_t i = 0; i < graph.edges[node].size(); i++) {
            string neighbor = graph.edges[node][i].first;
            if (!visited.count(neighbor)) {
                visited.insert(neighbor);
                vector<string> new_path = path;
                new_path.push_back(neighbor);
                q.push(make_pair(neighbor, new_path));
            }
        }
    }
    return make_pair(vector<string>{}, INT_MAX);
}

// DFS Search
pair<vector<string>, int> DFS(const string &start, const string &goal) {
    stack<pair<string, vector<string>>> st;
    unordered_set<string> visited;
    st.push(make_pair(start, vector<string>{start}));

    while (!st.empty()) {
        pair<string, vector<string>> topPair = st.top();
        st.pop();

        string node = topPair.first;
        vector<string> path = topPair.second;

        if (node == goal)
            return make_pair(path, (int)path.size() - 1);

        if (!visited.count(node)) {
            visited.insert(node);
            for (size_t i = 0; i < graph.edges[node].size(); i++) {
                string neighbor = graph.edges[node][i].first;
                vector<string> new_path = path;
                new_path.push_back(neighbor);
                st.push(make_pair(neighbor, new_path));
            }
        }
    }
    return make_pair(vector<string>{}, INT_MAX);
}

// Oracle Search (Rate Limiting)
pair<vector<string>, int> oracleSearch(const string &start, const string &goal, int OR) {
    vector<string> path{start};
    string current = start;
    int cost = 0;

    while (current != goal) {
        if (graph.edges[current].empty())
            return make_pair(vector<string>{}, INT_MAX);

        // pick the smallest edge cost neighbor
        auto next = min_element(graph.edges[current].begin(), graph.edges[current].end(),
                                [&](const pair<string, int> &a, const pair<string, int> &b) {
                                    return a.second < b.second;
                                });

        cost += next->second;
        if (cost > OR) // Oracle rate exceeded
            return make_pair(vector<string>{}, INT_MAX);

        path.push_back(next->first);
        current = next->first;

        // avoid infinite loop
        if (path.size() > graph.edges.size())
            return make_pair(vector<string>{}, INT_MAX);
    }

    return make_pair(path, cost);
}

int main() {
    int n, m;
    cout << "Enter number of nodes and edges: ";
    cin >> n >> m;

    vector<string> nodes(n);
    cout << "Enter node labels:\n";
    for (int i = 0; i < n; i++) cin >> nodes[i];

    cout << "Enter " << m << " edges (u v w):\n";
    for (int i = 0; i < m; i++) {
        string u, v;
        int w;
        cin >> u >> v >> w;
        graph.edges[u].push_back(make_pair(v, w));
        graph.edges[v].push_back(make_pair(u, w)); // undirected
    }

    string start, goal;
    cout << "Enter source and goal: ";
    cin >> start >> goal;

    cout << "\nGraph adjacency list:\n";
    for (auto &p : graph.edges) {
        cout << p.first << " -> ";
        for (auto &nbr : p.second) cout << "(" << nbr.first << "," << nbr.second << ") ";
        cout << "\n";
    }

    // BFS
    pair<vector<string>, int> bfs_result = BFS(start, goal);
    if (!bfs_result.first.empty()) {
        cout << "\nBFS Path: ";
        for (auto &x : bfs_result.first) cout << x << " ";
        cout << " | Cost: " << bfs_result.second << "\n";
    } else {
        cout << "\nNo BFS path found.\n";
    }

    // DFS
    pair<vector<string>, int> dfs_result = DFS(start, goal);
    if (!dfs_result.first.empty()) {
        cout << "DFS Path: ";
        for (auto &x : dfs_result.first) cout << x << " ";
        cout << " | Cost: " << dfs_result.second << "\n";
    } else {
        cout << "No DFS path found.\n";
    }

    // Oracle Search
    int OR;
    cout << "Enter Oracle Rate limit: ";
    cin >> OR;
    pair<vector<string>, int> oracle_result = oracleSearch(start, goal, OR);
    if (!oracle_result.first.empty()) {
        cout << "Oracle Search Path: ";
        for (auto &x : oracle_result.first) cout << x << " ";
        cout << " | Cost: " << oracle_result.second << "\n";
    } else {
        cout << "No Oracle Search path found within OR limit.\n";
    }

    return 0;
}
