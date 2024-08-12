#include <iostream>
#include <bitset>

// leetcode 437 Path Sum III

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    int insertBits(int N, int M, int i, int j) {
        // Create a mask to clear bits i through j in N
        int allOnes = ~0; // All 1s

        // 1s before position j, then 0s
        int left = allOnes << (j + 1);

        // 1s after position i
        int right = (1 << i) - 1;

        // All 1s, except for 0s between i and j
        int mask = left | right;

        // Clear bits j through i then put M in there
        int n_cleared = N & mask; // Clear bits j through i.
        int m_shifted = M << i; // Move M into the correct position.

        return n_cleared | m_shifted; // OR them, and we're done!
    }
};

// Test function
void testInsertBits() {
    Solution solution;

    // Test case
    int N = 0b10000000000;
    int M = 0b10011;
    int i = 2;
    int j = 6;

    int result = solution.insertBits(N, M, i, j);
    std::cout << "Result: " << std::bitset<11>(result) << std::endl; // Output in binary
}

int main() {
    testInsertBits();
    return 0;
}
