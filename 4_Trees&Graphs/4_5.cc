#include <iostream>
#include <climits>
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
    bool isValidBST(TreeNode* root) {
        return isValidBSTHelper(root, LONG_MIN, LONG_MAX);
    }

private:
    bool isValidBSTHelper(TreeNode* node, long min, long max) {
        if (node == NULL) {
            return true;
        }
        
        if (node->val <= min || node->val >= max) {
            return false;
        }
        
        return isValidBSTHelper(node->left, min, node->val) &&
               isValidBSTHelper(node->right, node->val, max);
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
        
        if (values[i] != INT_MIN) {
            current->left = new TreeNode(values[i]);
            q.push(current->left);
        }
        
        if (i + 1 < values.size() && values[i + 1] != INT_MIN) {
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
void testIsValidBST() {
    Solution solution;

    // Valid BST
    TreeNode* validBST = createTree({4, 2, 6, 1, 3, 5, 7});
    std::cout << "Valid BST is " 
              << (solution.isValidBST(validBST) ? "a valid BST" : "not a valid BST") 
              << std::endl;
    deleteTree(validBST);

    // Invalid BST
    TreeNode* invalidBST = createTree({5, 1, 4, INT_MIN, INT_MIN, 3, 6});
    std::cout << "Invalid BST is " 
              << (solution.isValidBST(invalidBST) ? "a valid BST" : "not a valid BST") 
              << std::endl;
    deleteTree(invalidBST);

    // Another invalid BST (to catch edge cases)
    TreeNode* invalidBST2 = createTree({10, 5, 15, INT_MIN, INT_MIN, 6, 20});
    std::cout << "Another invalid BST is " 
              << (solution.isValidBST(invalidBST2) ? "a valid BST" : "not a valid BST") 
              << std::endl;
    deleteTree(invalidBST2);
}

int main() {
    testIsValidBST();
    return 0;
}