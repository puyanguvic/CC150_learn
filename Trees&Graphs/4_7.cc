#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

class Solution {
public:
    std::vector<char> findBuildOrder(std::vector<char>& projects,
                                     std::vector<std::pair<char, char>>& dependencies) {
        std::unordered_map<char, std::vector<char>> graph;
        std::unordered_map<char, int> inDegree;

        // Initialize graph and in-degree
        for (char project : projects) {
            graph[project] = std::vector<char>();
            inDegree[project] = 0;
        }

        // Build graph and calculate in-degree
        for (const auto& dep : dependencies) {
            graph[dep.first].push_back(dep.second);
            inDegree[dep.second]++;
        }

        // Queue to store nodes with in-degree 0
        std::queue<char> queue;
        for (char project : projects) {
            if (inDegree[project] == 0) {
                queue.push(project);
            }
        }

        std::vector<char> buildOrder;
        while (!queue.empty()) {
            char current = queue.front();
            queue.pop();
            buildOrder.push_back(current);

            for (char neighbor : graph[current]) {
                inDegree[neighbor]--;
                if (inDegree[neighbor] == 0) {
                    queue.push(neighbor);
                }
            }
        }

        // Check if all projects are included in the build order
        if (buildOrder.size() != projects.size()) {
            return {};  // Cycle detected, return empty vector
        }

        return buildOrder;
    }
};

// Test function
void testBuildOrder() {
    Solution solution;

    std::vector<char> projects = {'a', 'b', 'c', 'd', 'e', 'f'};
    std::vector<std::pair<char, char>> dependencies = {
        {'a', 'd'}, {'f', 'b'}, {'b', 'd'}, {'f', 'a'}, {'d', 'c'}
    };

    std::vector<char> buildOrder = solution.findBuildOrder(projects, dependencies);

    if (buildOrder.empty()) {
        std::cout << "No valid build order exists (cycle detected)" << std::endl;
    } else {
        std::cout << "Build Order: ";
        for (char project : buildOrder) {
            std::cout << project << " ";
        }
        std::cout << std::endl;
    }

    // Test with cycle
    std::vector<std::pair<char, char>> dependenciesWithCycle = {
        {'a', 'b'}, {'b', 'c'}, {'c', 'a'}
    };

    buildOrder = solution.findBuildOrder(projects, dependenciesWithCycle);

    if (buildOrder.empty()) {
        std::cout << "No valid build order exists (cycle detected)" << std::endl;
    } else {
        std::cout << "Build Order: ";
        for (char project : buildOrder) {
            std::cout << project << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    testBuildOrder();
    return 0;
}