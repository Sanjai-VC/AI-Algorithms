#include <bits/stdc++.h>
using namespace std;

struct Node {
    vector<pair<string,int>> edges;
    int heuristic;
};
map<string, Node> graph;

pair<vector<string>, int> aStar(string start, string goal) {
    typedef tuple<int,int,string,vector<string>> State;
    priority_queue<State, vector<State>, greater<State>> pq;

    pq.push(State(graph[start].heuristic, 0, start, {start}));
    set<string> vis;

    while (!pq.empty()) {
        State topState = pq.top();
        pq.pop();

        int f = get<0>(topState);
        int gCost = get<1>(topState);
        string node = get<2>(topState);
        vector<string> path = get<3>(topState);

        if (node == goal) return {path, gCost};
        if (vis.count(node)) continue;
        vis.insert(node);

        for (size_t i = 0; i < graph[node].edges.size(); i++) {
            string nb = graph[node].edges[i].first;
            int w = graph[node].edges[i].second;
            if (!vis.count(nb)) {
                vector<string> np = path;
                np.push_back(nb);
                pq.push(State(gCost + w + graph[nb].heuristic, gCost + w, nb, np));
            }
        }
    }
    return {{}, INT_MAX};
}

int main() {
    graph["A"] = {{{"B", 1}, {"C", 3}}, 4};
    graph["B"] = {{{"D", 2}, {"E", 5}}, 2};
    graph["C"] = {{{"F", 4}}, 3};
    graph["D"] = {{{"G", 6}}, 0};
    graph["E"] = {{{"G", 2}}, 0};
    graph["F"] = {{{"G", 1}}, 0};
    graph["G"] = {{}, 0};

    pair<vector<string>, int> result = aStar("A", "G");
    vector<string> path = result.first;
    int cost = result.second;

    cout << "Path: ";
    for (size_t i = 0; i < path.size(); i++) {
        cout << path[i] << " ";
    }
    cout << "\nCost: " << cost << "\n";
}
