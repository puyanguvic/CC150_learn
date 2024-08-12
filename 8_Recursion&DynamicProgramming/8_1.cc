#include <iostream>
#include <vector>
#include <stdexcept>

class Solution {
public:
    // Optimized iterative approach using space-efficient dynamic programming
    int tripleStep(int n) {
        if (n < 0) return 0;
        if (n == 0) return 1;

        std::vector<int> dp(3, 0);
        dp[0] = 1;
        dp[1] = 1;
        dp[2] = 2;

        for (int i = 3; i <= n; i++) {
            dp[i % 3] = dp[(i - 1) % 3] + dp[(i - 2) % 3] + dp[(i - 3) % 3];
        }

        return dp[n % 3];
    }
};

// Test function
void runTests() {
    Solution solution;

    int n = 10;
    std::cout << "Number of ways to run up " << n << " steps: " << solution.tripleStep(n) << std::endl;
}

int main() {
    runTests();
    return 0;
}
