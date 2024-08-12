#include <iostream>
#include <vector>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    TreeNode* sortedArrayToBST(std::vector<int>& nums) {
        return sortedArrayToBSTHelper(nums, 0, nums.size() - 1);
    }

private:
    TreeNode* sortedArrayToBSTHelper(std::vector<int>& nums, int left, int right) {
        if (left > right) {
            return NULL;
        }

        // Always choose the middle element as the root
        int mid = left + (right - left) / 2;
        TreeNode* root = new TreeNode(nums[mid]);

        // Recursively construct the left subtree
        root->left = sortedArrayToBSTHelper(nums, left, mid - 1);

        // Recursively construct the right subtree
        root->right = sortedArrayToBSTHelper(nums, mid + 1, right);

        return root;
    }
};

// Helper function to print the tree in-order
void inorderTraversal(TreeNode* root) {
    if (root == NULL) return;
    inorderTraversal(root->left);
    std::cout << root->val << " ";
    inorderTraversal(root->right);
}

// Test function
void testSortedArrayToBST() {
    Solution solution;
    std::vector<int> nums = {1, 2, 3, 4, 5, 6, 7};

    TreeNode* root = solution.sortedArrayToBST(nums);

    std::cout << "In-order traversal of the constructed BST: ";
    inorderTraversal(root);
    std::cout << std::endl;
}

int main() {
    testSortedArrayToBST();
    return 0;
}