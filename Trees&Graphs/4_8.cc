#include <iostream>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    TreeNode* findFirstCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        // Base case: if root is null or equal to either p or q
        if (!root || root == p || root == q) {
            return root;
        }

        // Recursively search in left and right subtrees
        TreeNode* left = findFirstCommonAncestor(root->left, p, q);
        TreeNode* right = findFirstCommonAncestor(root->right, p, q);

        // If both left and right are non-null, root is the LCA
        if (left && right) {
            return root;
        }

        // If one side is null, return the non-null side
        return left ? left : right;
    }
};

// Helper function to create a binary tree
TreeNode* createBinaryTree() {
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(5);
    root->right = new TreeNode(1);
    root->left->left = new TreeNode(6);
    root->left->right = new TreeNode(2);
    root->right->left = new TreeNode(0);
    root->right->right = new TreeNode(8);
    root->left->right->left = new TreeNode(7);
    root->left->right->right = new TreeNode(4);
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
void testFirstCommonAncestor() {
    Solution solution;
    TreeNode* root = createBinaryTree();

    // Test cases
    TreeNode* p = root->left->left;  // Node with value 6
    TreeNode* q = root->left->right->right;  // Node with value 4
    TreeNode* ancestor = solution.findFirstCommonAncestor(root, p, q);
    std::cout << "First common ancestor of 6 and 4: " << ancestor->val << std::endl;

    p = root->left;  // Node with value 5
    q = root->right;  // Node with value 1
    ancestor = solution.findFirstCommonAncestor(root, p, q);
    std::cout << "First common ancestor of 5 and 1: " << ancestor->val << std::endl;

    p = root->left->right;  // Node with value 2
    q = root->left;  // Node with value 5
    ancestor = solution.findFirstCommonAncestor(root, p, q);
    std::cout << "First common ancestor of 2 and 5: " << ancestor->val << std::endl;

    deleteBinaryTree(root);
}

int main() {
    testFirstCommonAncestor();
    return 0;
}