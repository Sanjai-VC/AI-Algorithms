#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<int>> adj;
vector<int> path;
vector<char> visited;
unordered_map<char, int> charToId;
vector<char> idToChar;
int pathCount = 0;

void dfs(int u, int goal) {
    // Debug print
    cout << "Visiting: " << idToChar[u] << " | Current path: ";
    for (int node : path) cout << idToChar[node] << " ";
    cout << "\n";

    if (u == goal) {
        pathCount++;
        cout << "Path " << pathCount << ": ";
        for (size_t i = 0; i < path.size(); ++i) {
            if (i) cout << " ";
            cout << idToChar[path[i]];
        }
        cout << "\n\n";
        return;
    }

    for (int v : adj[u]) {
        if (!visited[v]) {
            visited[v] = 1;
            path.push_back(v);
            dfs(v, goal);
            path.pop_back();
            visited[v] = 0;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "Enter number of nodes and edges: " << flush;
    cin >> n >> m;
    adj.assign(n, {});

    idToChar.resize(n);

    cout << "Enter node labels (e.g., A B C ...):\n" << flush;
    for (int i = 0; i < n; i++) {
        char label;
        cin >> label;
        charToId[label] = i;
        idToChar[i] = label;
    }

    cout << "Enter " << m << " edges (u v):\n" << flush;
    for (int i = 0; i < m; i++) {
        char cu, cv;
        cin >> cu >> cv;
        int u = charToId[cu];
        int v = charToId[cv];
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    char sLabel, gLabel;
    cout << "Enter source and goal: " << flush;
    cin >> sLabel >> gLabel;
    int source = charToId[sLabel];
    int goal = charToId[gLabel];

    for (int i = 0; i < n; i++) {
        sort(adj[i].begin(), adj[i].end(), [&](int a, int b) {
            return idToChar[a] < idToChar[b];
        });
    }

    cout << "\nGraph adjacency list:\n";
    for (int i = 0; i < n; i++) {
        cout << idToChar[i] << ": ";
        for (int v : adj[i]) cout << idToChar[v] << " ";
        cout << "\n";
    }
    cout << "\nStarting British Museum Search...\n\n";

    visited.assign(n, 0);
    path.clear();
    path.push_back(source);
    visited[source] = 1;

    dfs(source, goal);

    if (pathCount == 0) {
        cout << "No path found from " << sLabel << " to " << gLabel << "\n";
    } else {
        cout << "\nTotal paths found: " << pathCount << "\n";
    }

    return 0;
}
