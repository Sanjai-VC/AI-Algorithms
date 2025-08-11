#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<int>> adj;
unordered_map<char, int> charToId;
vector<char> idToChar;
set<pair<int,int>> usedEdges;

void dfs_layer(int u, vector<int>& path, int goal) {
    cout << "Visiting: " << idToChar[u] << " | Current path: ";
    for (int node : path) cout << idToChar[node] << " ";
    cout << "\n";

    if (u == goal) {
        cout << "Goal found! Path: ";
        for (size_t i = 0; i < path.size(); ++i) {
            if (i) cout << " ";
            cout << idToChar[path[i]];
        }
        cout << "\n";
    }

    for (int v : adj[u]) {
        pair<int,int> e1 = {u, v}, e2 = {v, u};
        if (!usedEdges.count(e1) && !usedEdges.count(e2)) {
            usedEdges.insert(e1);
            usedEdges.insert(e2);

            path.push_back(v);
            dfs_layer(v, path, goal);
            path.pop_back();
        }
    }
}

void bfs_dfs_mix(int source, int goal) {
    queue<int> q;
    vector<bool> inQueue(n, false);
    q.push(source);
    inQueue[source] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        vector<int> path = {u};
        dfs_layer(u, path, goal);

        for (int v : adj[u]) {
            if (!inQueue[v]) {
                q.push(v);
                inQueue[v] = true;
            }
        }
    }

    cout << "\nAll edges explored once or BFS queue empty. Search complete.\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "Enter number of nodes and edges: " << flush;
    cin >> n >> m;
    adj.assign(n, {});
    idToChar.resize(n);

    cout << "Enter node labels:\n" << flush;
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
    cout << "\n";

    bfs_dfs_mix(source, goal);

    return 0;
}
