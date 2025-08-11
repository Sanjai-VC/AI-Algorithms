#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<int>> adj;
vector<int> path;
vector<char> visited;
unordered_map<char, int> charToId;
vector<char> idToChar;
bool goalFound = false;

void dfs(int u, int goal) {
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
        goalFound = true;
        return;
    }

    for (int v : adj[u]) {
        if (!visited[v]) {
            visited[v] = 1;
            path.push_back(v);
            dfs(v, goal);
            if (goalFound) return; // stop after first goal
            path.pop_back();
            visited[v] = 0;
            cout << "Traceback from: " << idToChar[v] << " to " << idToChar[u] << "\n";
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

    // Sort neighbors for lexicographical order
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

    cout << "\nStarting DFS with Lexicographical Order, No Biting Tail, Traceback...\n\n";

    visited.assign(n, 0);
    path.clear();
    path.push_back(source);
    visited[source] = 1;

    dfs(source, goal);

    if (!goalFound) {
        cout << "\nNo path found from " << sLabel << " to " << gLabel << "\n";
    }

    return 0;
}
