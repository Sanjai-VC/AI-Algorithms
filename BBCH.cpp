#include <bits/stdc++.h>
using namespace std;

struct Node {
    unordered_map<string, int> edges; // neighbor -> cost
    int heuristic;
};

unordered_map<string, Node> graph;

// Branch and Bound with Cost + Heuristic
pair<vector<string>, int> bbCostHeuristic(const string& start, const string& goal) {
    typedef tuple<int, int, string, vector<string>> State;
    priority_queue<State, vector<State>, greater<State>> pq;

    pq.push(make_tuple(graph[start].heuristic, 0, start, vector<string>{start}));
    int bestCost = numeric_limits<int>::max();
    vector<string> bestPath;
    set<string> visited;

    while (!pq.empty()) {
        State top = pq.top();
        pq.pop();

        int f       = get<0>(top);
        int cost    = get<1>(top);
        string curr = get<2>(top);
        vector<string> path = get<3>(top);

        if (curr == goal) {
            if (cost < bestCost) {
                bestCost = cost;
                bestPath = path;
            }
            continue;
        }

        visited.insert(curr);

        for (auto it = graph[curr].edges.begin(); it != graph[curr].edges.end(); ++it) {
            string nb = it->first;
            int nbCost = it->second;
            if (!visited.count(nb)) {
                int g = cost + nbCost;
                int h = graph[nb].heuristic;
                int fg = g + h;
                if (fg < bestCost) {
                    vector<string> newPath = path;
                    newPath.push_back(nb);
                    pq.push(make_tuple(fg, g, nb, newPath));
                }
            }
        }
    }

    return make_pair(bestPath, bestCost);
}

int main() {
    int n;
    cout << "Enter number of nodes: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        string node;
        int heuristic;
        cout << "Enter node name and heuristic: ";
        cin >> node >> heuristic;
        graph[node].heuristic = heuristic;
    }

    int e;
    cout << "Enter number of edges: ";
    cin >> e;
    for (int i = 0; i < e; i++) {
        string u, v;
        int cost;
        cout << "Enter edge (u v cost): ";
        cin >> u >> v >> cost;
        graph[u].edges[v] = cost;
        graph[v].edges[u] = cost; // undirected
    }

    string start, goal;
    cout << "Enter start node: ";
    cin >> start;
    cout << "Enter goal node: ";
    cin >> goal;

    pair<vector<string>, int> result = bbCostHeuristic(start, goal);
    vector<string> path = result.first;
    int cost = result.second;

    if (!path.empty()) {
        cout << "Best Path: ";
        for (size_t i = 0; i < path.size(); i++) {
            cout << path[i] << " ";
        }
        cout << "\nCost: " << cost << "\n";
    } else {
        cout << "No path found.\n";
    }

    return 0;
}
