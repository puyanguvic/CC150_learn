#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    bool isBalanced(TreeNode* root) {
        return checkHeight(root) != -1;
    }

private:
    int checkHeight(TreeNode* node) {
        if (node == NULL) return 0;

        int leftHeight = checkHeight(node->left);
        if (leftHeight == -1) return -1; // Left subtree is unbalanced

        int rightHeight = checkHeight(node->right);
        if (rightHeight == -1) return -1; // Right subtree is unbalanced

        if (std::abs(leftHeight - rightHeight) > 1) {
            return -1; // Current node is unbalanced
        }

        return std::max(leftHeight, rightHeight) + 1;
    }
};

// Improved helper function to create a binary tree
TreeNode* createTree(const std::vector<int>& values) {
    if (values.empty()) return nullptr;
    
    TreeNode* root = new TreeNode(values[0]);
    std::queue<TreeNode*> q;
    q.push(root);
    
    for (int i = 1; i < values.size(); i += 2) {
        TreeNode* current = q.front();
        q.pop();
        
        if (values[i] != -1) {
            current->left = new TreeNode(values[i]);
            q.push(current->left);
        }
        
        if (i + 1 < values.size() && values[i + 1] != -1) {
            current->right = new TreeNode(values[i + 1]);
            q.push(current->right);
        }
    }
    
    return root;
}

// Helper function to delete the tree
void deleteTree(TreeNode* root) {
    if (root == nullptr) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

// Test function
void testIsBalanced() {
    Solution solution;

    // Balanced tree
    TreeNode* balancedTree = createTree({1, 2, 3, 4, 5, 6, 7});
    std::cout << "Balanced tree is " 
              << (solution.isBalanced(balancedTree) ? "balanced" : "not balanced") 
              << std::endl;
    deleteTree(balancedTree);

    // Unbalanced tree
    TreeNode* unbalancedTree = createTree({1, 2, 2, 3, 3, -1, -1, 4, 4});
    std::cout << "Unbalanced tree is " 
              << (solution.isBalanced(unbalancedTree) ? "balanced" : "not balanced") 
              << std::endl;
    deleteTree(unbalancedTree);
}

int main() {
    testIsBalanced();
    return 0;
}