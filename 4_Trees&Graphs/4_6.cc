#include <iostream>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode *parent;
    TreeNode(int x) : val(x), left(NULL), right(NULL), parent(NULL) {}
};

class Solution {
public:
    TreeNode* inorderSuccessor(TreeNode* node) {
        if (node == NULL) return NULL;

        // Case 1: Node has a right subtree
        if (node->right != NULL) {
            return leftmostChild(node->right);
        }

        // Case 2: Node doesn't have a right subtree
        // We need to move up until we're on left instead of right
        TreeNode* parent = node->parent;
        while (parent != NULL && parent->left != node) {
            node = parent;
            parent = parent->parent;
        }
        return parent;
    }

private:
    TreeNode* leftmostChild(TreeNode* node) {
        if (node == NULL) return NULL;
        while (node->left != NULL) {
            node = node->left;
        }
        return node;
    }
};

// Helper function to insert a node into the BST
TreeNode* insert(TreeNode* root, int val) {
    if (root == NULL) return new TreeNode(val);

    TreeNode* cur;
    if (val <= root->val) {
        cur = insert(root->left, val);
        root->left = cur;
        cur->parent = root;
    } else {
        cur = insert(root->right, val);
        root->right = cur;
        cur->parent = root;
    }

    return root;
}

// Helper function to find a node with a given value
TreeNode* findNode(TreeNode* root, int val) {
    if (root == NULL || root->val == val) return root;
    if (val < root->val) return findNode(root->left, val);
    return findNode(root->right, val);
}

// Test function
void testInorderSuccessor() {
    Solution solution;

    // Create a BST
    TreeNode* root = NULL;
    int values[] = {20, 8, 22, 4, 12, 10, 14};
    for (int val : values) {
        root = insert(root, val);
    }

    // Test cases
    int testValues[] = {8, 10, 14, 22};
    for (int val : testValues) {
        TreeNode* node = findNode(root, val);
        TreeNode* successor = solution.inorderSuccessor(node);
        std::cout << "Inorder successor of " << val << " is: ";
        if (successor) {
            std::cout << successor->val << std::endl;
        } else {
            std::cout << "NULL" << std::endl;
        }
    }
}

int main() {
    testInorderSuccessor();
    return 0;
}