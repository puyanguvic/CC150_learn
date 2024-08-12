#include <iostream>
#include <vector>
#include <unordered_set>

class Solution {
public:
    using Grid = std::vector<std::vector<bool>>;
    using Path = std::vector<std::pair<int, int>>;

    bool getPath(const Grid& grid, int row, int col, Path& path, std::unordered_set<std::string>& failedPoints) {
        // If out of bounds or not accessible, return false
        if (row < 0 || col < 0 || !grid[row][col]) {
            return false;
        }

        std::string point = std::to_string(row) + "," + std::to_string(col);

        // If we've already visited this cell and found it to be a dead end, return false
        if (failedPoints.find(point) != failedPoints.end()) {
            return false;
        }

        bool isAtOrigin = (row == 0 && col == 0);

        // If there's a path from the start to my current location, add my location.
        if (isAtOrigin || getPath(grid, row - 1, col, path, failedPoints) || getPath(grid, row, col - 1, path, failedPoints)) {
            path.emplace_back(row, col);
            return true;
        }

        failedPoints.insert(point); // Cache the result
        return false;
    }

    Path findPath(const Grid& grid) {
        Path path;
        std::unordered_set<std::string> failedPoints;
        if (getPath(grid, grid.size() - 1, grid[0].size() - 1, path, failedPoints)) {
            return path;
        }
        return {}; // Return empty path if no path is found
    }
};

// Test function
void runTests() {
    Solution solution;

    Solution::Grid grid = {
        {true,  true,  true,  true},
        {true,  false, true,  true},
        {true,  true,  true,  false},
        {false, true,  true,  true}
    };

    Solution::Path path = solution.findPath(grid);
    if (!path.empty()) {
        std::cout << "Path found: ";
        for (auto& p : path) {
            std::cout << "(" << p.first << "," << p.second << ") ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "No path found" << std::endl;
    }
}

int main() {
    runTests();
    return 0;
}
