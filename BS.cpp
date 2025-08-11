#include <bits/stdc++.h>
using namespace std;

// Graph represented as adjacency list: node -> (neighbor, cost)
map<string, vector<pair<string, int>>> graphData;

// Function to add edge
void addEdge(string u, string v, int cost) {
    graphData[u].push_back(make_pair(v, cost));
}

// Function to print the graph
void printGraph() {
    for (map<string, vector<pair<string, int>>>::iterator it = graphData.begin(); it != graphData.end(); ++it) {
        cout << it->first << " -> ";
        for (size_t i = 0; i < it->second.size(); i++) {
            cout << "(" << it->second[i].first << ", " << it->second[i].second << ") ";
        }
        cout << "\n";
    }
}

// Beam Search implementation
void beamSearch(string start, string goal, int beamWidth) {
    queue<vector<string>> paths;
    paths.push(vector<string>(1, start));

    while (!paths.empty()) {
        vector<vector<string>> candidates;

        // Explore each path in the current queue
        while (!paths.empty()) {
            vector<string> path = paths.front();
            paths.pop();

            string lastNode = path.back();
            if (lastNode == goal) {
                cout << "Goal found! Path: ";
                for (size_t i = 0; i < path.size(); i++) {
                    cout << path[i];
                    if (i != path.size() - 1) cout << " -> ";
                }
                cout << "\n";
                return;
            }

            // Generate new paths by extending current path
            for (size_t i = 0; i < graphData[lastNode].size(); i++) {
                vector<string> newPath = path;
                newPath.push_back(graphData[lastNode][i].first);
                candidates.push_back(newPath);
            }
        }

        // Sort candidates by heuristic (cost from last node to goal)
        sort(candidates.begin(), candidates.end(), [](vector<string>& a, vector<string>& b) {
            return a.back() < b.back(); // Simple lexicographic heuristic
        });

        // Keep only top beamWidth paths
        for (int i = 0; i < beamWidth && i < (int)candidates.size(); i++) {
            paths.push(candidates[i]);
        }
    }

    cout << "Goal not found.\n";
}

int main() {
    // Graph creation
    addEdge("A", "B", 1);
    addEdge("A", "C", 2);
    addEdge("B", "D", 4);
    addEdge("B", "E", 5);
    addEdge("C", "F", 3);
    addEdge("C", "G", 6);

    cout << "Graph:\n";
    printGraph();

    string start = "A";
    string goal = "G";
    int beamWidth = 2;

    cout << "\nBeam Search from " << start << " to " << goal << " with beam width " << beamWidth << ":\n";
    beamSearch(start, goal, beamWidth);

    return 0;
}
