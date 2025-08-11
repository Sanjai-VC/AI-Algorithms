#include <bits/stdc++.h>
using namespace std;

// Graph representation
struct Edge {
    string to;
    int cost;
};

struct Node {
    vector<Edge> edges;
};

map<string, Node> graph;

// Branch and Bound search
pair<vector<string>, int> branchAndBound(const string& start, const string& goal) {
    typedef pair<int, vector<string>> PathState; // cost, path
    priority_queue<PathState, vector<PathState>, greater<PathState>> pq;

    pq.push(make_pair(0, vector<string>{start}));
    int bestCost = numeric_limits<int>::max();
    vector<string> bestPath;

    while (!pq.empty()) {
        PathState state = pq.top();
        pq.pop();

        int cost = state.first;
        vector<string> path = state.second;
        string curr = path.back();

        if (curr == goal) {
            if (cost < bestCost) {
                bestCost = cost;
                bestPath = path;
            }
            continue;
        }

        for (size_t i = 0; i < graph[curr].edges.size(); i++) {
            string nb = graph[curr].edges[i].to;
            int nbCost = graph[curr].edges[i].cost;

            // avoid cycles
            if (find(path.begin(), path.end(), nb) == path.end()) {
                if (cost + nbCost < bestCost) {
                    vector<string> newPath = path;
                    newPath.push_back(nb);
                    pq.push(make_pair(cost + nbCost, newPath));
                }
            }
        }
    }

    return make_pair(bestPath, bestCost);
}

int main() {
    // Example graph
    graph["A"].edges = {{"B", 4}, {"C", 2}};
    graph["B"].edges = {{"D", 5}, {"E", 10}};
    graph["C"].edges = {{"D", 8}, {"F", 4}};
    graph["D"].edges = {{"E", 2}, {"F", 1}};
    graph["E"].edges = {{"G", 3}};
    graph["F"].edges = {{"G", 6}};
    graph["G"].edges = {};

    string start = "A";
    string goal = "G";

    pair<vector<string>, int> result = branchAndBound(start, goal);

    cout << "Best path: ";
    for (size_t i = 0; i < result.first.size(); i++) {
        cout << result.first[i];
        if (i + 1 < result.first.size()) cout << " -> ";
    }
    cout << "\nCost: " << result.second << endl;

    return 0;
}
