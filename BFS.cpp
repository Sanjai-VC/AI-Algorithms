#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<int>> adj;
unordered_map<char, int> charToId;
vector<char> idToChar;

void bfs(int source, int goal) {
    vector<bool> visited(n, false);
    vector<int> parent(n, -1);
    queue<vector<int>> q; // store full path to each node

    visited[source] = true;
    q.push({source});

    cout << "\nStarting BFS with Lexicographical Order...\n\n";

    while (!q.empty()) {
        vector<int> path = q.front();
        q.pop();
        int u = path.back();

        // Visiting print
        cout << "Visiting: " << idToChar[u] << " | Current path: ";
        for (int node : path) cout << idToChar[node] << " ";
        cout << "\n";

        if (u == goal) {
            cout << "\nGoal found! Path: ";
            for (size_t i = 0; i < path.size(); ++i) {
                if (i) cout << " ";
                cout << idToChar[path[i]];
            }
            cout << "\n";
            return;
        }

        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                vector<int> newPath = path;
                newPath.push_back(v);
                q.push(newPath);
            }
        }

        if (!path.empty() && parent[u] != -1) {
            cout << "Traceback from: " << idToChar[u] << " to " << idToChar[parent[u]] << "\n";
        }

        if (path.size() >= 2)
            parent[u] = path[path.size() - 2];
    }

    cout << "\nNo path found from " << idToChar[source] << " to " << idToChar[goal] << "\n";
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

    // Sort adjacency for lexicographical BFS
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

    bfs(source, goal);

    return 0;
}

