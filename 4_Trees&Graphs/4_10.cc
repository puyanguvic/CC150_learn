#include <iostream>
#include <vector>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    bool isSubtree(TreeNode* T1, TreeNode* T2) {
        if (!T1) return false;
        if (isIdentical(T1, T2)) return true;
        return isSubtree(T1->left, T2) || isSubtree(T1->right, T2);
    }

private:
    bool isIdentical(TreeNode* root1, TreeNode* root2) {
        if (!root1 && !root2) return true;
        if (!root1 || !root2) return false;
        return (root1->val == root2->val &&
                isIdentical(root1->left, root2->left) &&
                isIdentical(root1->right, root2->right));
    }
};

// Helper function to create a binary tree
TreeNode* createBinaryTree(std::vector<int>& nums, int index = 0) {
    if (index >= nums.size() || nums[index] == -1) return nullptr;
    TreeNode* root = new TreeNode(nums[index]);
    root->left = createBinaryTree(nums, 2 * index + 1);
    root->right = createBinaryTree(nums, 2 * index + 2);
    return root;
}

// Helper function to delete the binary tree
void deleteBinaryTree(TreeNode* root) {
    if (root) {
        deleteBinaryTree(root->left);
        deleteBinaryTree(root->right);
        delete root;
    }
}

// Test function
void testCheckSubtree() {
    Solution solution;

    // Create T1: [3,4,5,1,2,null,null,null,null,0]
    std::vector<int> nums1 = {3,4,5,1,2,-1,-1,-1,-1,0};
    TreeNode* T1 = createBinaryTree(nums1);

    // Create T2: [4,1,2]
    std::vector<int> nums2 = {4,1,2};
    TreeNode* T2 = createBinaryTree(nums2);

    bool result = solution.isSubtree(T1, T2);

    std::cout << "Is T2 a subtree of T1? " << (result ? "Yes" : "No") << std::endl;

    deleteBinaryTree(T1);
    deleteBinaryTree(T2);
}

int main() {
    testCheckSubtree();
    return 0;
}