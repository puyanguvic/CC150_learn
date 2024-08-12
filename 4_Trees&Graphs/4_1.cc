#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

class Graph {

public:
    Graph(int v) : V(v), adj(v) {}

    void addEdge(int v, int w) {
        adj[v].push_back(w);
    }

    bool isRouteBFS(int start, int end) {
        if (start == end) return true;

        std::queue<int> queue;
        std::unordered_set<int> visited;

        queue.push(start);
        visited.insert(start);

        while (!queue.empty()) {
            int v = queue.front();
            queue.pop();

            for (int neighbor : adj[v]) {
                if (neighbor == end) {
                    return true;
                }
                if (visited.find(neighbor) == visited.end()) {
                    visited.insert(neighbor);
                    queue.push(neighbor);
                }
            }
        }

        return false;
    }

    bool isRouteDFS(int start, int end) {
        std::unordered_set<int> visited;
        return dfsUtil(start, end, visited);
    }

private:
    int V; // Number of vertices
    std::vector<std::vector<int>> adj; // Adjacency list
    bool dfsUtil(int v, int end, std::unordered_set<int>& visited) {
        if (v == end) return true;

        visited.insert(v);

        for (int neighbor : adj[v]) {
            if (visited.find(neighbor) == visited.end()) {
                if (dfsUtil(neighbor, end, visited)) {
                    return true;
                }
            }
        }

        return false;
    }
};

// Test function
void testGraph() {
    Graph g(6);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 5);

    std::cout << "Route from 0 to 5: " << (g.isRouteBFS(0, 5) ? "Exists" : "Does not exist") << std::endl;
    std::cout << "Route from 2 to 5: " << (g.isRouteBFS(2, 5) ? "Exists" : "Does not exist") << std::endl;
    std::cout << "Route from 5 to 0: " << (g.isRouteBFS(5, 0) ? "Exists" : "Does not exist") << std::endl;
}

int main() {
    testGraph();
    return 0;
}