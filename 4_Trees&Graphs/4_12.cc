// leetcode 437 Path Sum III

#include <iostream>
#include <unordered_map>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    int pathSum(TreeNode* root, int targetSum) {
        int result = 0;
        std::unordered_map<long long, int> prefixSum;
        prefixSum[0] = 1;  // 初始化前缀和为0的情况
        backtrack(root, targetSum, 0, prefixSum, result);
        return result;
    }

private:
    void backtrack(TreeNode* node, 
                   long long targetSum, 
                   long long currentSum, 
                   std::unordered_map<long long, int>& prefixSum, 
                   int& result)
    {
        if (node == nullptr) {
            return;
        }

        currentSum += node->val;

        // count the paths
        if (prefixSum.find(currentSum - targetSum) != prefixSum.end()) {
            result += prefixSum[currentSum - targetSum];
        }

        // update prefix and hash
        prefixSum[currentSum]++;

        // process left and right subtree
        backtrack(node->left, targetSum, currentSum, prefixSum, result);
        backtrack(node->right, targetSum, currentSum, prefixSum, result);

        // remove current path
        prefixSum[currentSum]--;
    }
};

// Test function
void testPathSum() {
    Solution solution;

    // Create a sample binary tree
    TreeNode* root = new TreeNode(10);
    root->left = new TreeNode(5);
    root->right = new TreeNode(-3);
    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(2);
    root->right->right = new TreeNode(11);
    root->left->left->left = new TreeNode(3);
    root->left->left->right = new TreeNode(-2);
    root->left->right->right = new TreeNode(1);

    int targetSum = 8;
    int result = solution.pathSum(root, targetSum);

    std::cout << "Number of paths that sum to " << targetSum << ": " << result << std::endl;

    // Clean up the tree (in practice, use a proper tree deletion function)
    // This is a simplistic cleanup and may cause memory leaks in a real scenario
    delete root->left->right->right;
    delete root->left->left->right;
    delete root->left->left->left;
    delete root->right->right;
    delete root->left->right;
    delete root->left->left;
    delete root->right;
    delete root->left;
    delete root;
}

int main() {
    testPathSum();
    return 0;
}