#include <iostream>
#include <vector>
#include <list>
#include <queue>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    // DFS approach
    std::vector<std::list<TreeNode*>> createLevelLinkedListDFS(TreeNode* root) {
        std::vector<std::list<TreeNode*>> levelLists;
        createLevelLinkedListDFSHelper(root, 0, levelLists);
        return levelLists;
    }

    // BFS approach
    std::vector<std::list<TreeNode*>> createLevelLinkedListBFS(TreeNode* root) {
        std::vector<std::list<TreeNode*>> levelLists;
        if (!root) return levelLists;

        std::queue<TreeNode*> queue;
        queue.push(root);

        while (!queue.empty()) {
            int levelSize = queue.size();
            std::list<TreeNode*> currentLevel;

            for (int i = 0; i < levelSize; i++) {
                TreeNode* node = queue.front();
                queue.pop();
                currentLevel.push_back(node);

                if (node->left) queue.push(node->left);
                if (node->right) queue.push(node->right);
            }

            levelLists.push_back(currentLevel);
        }

        return levelLists;
    }

private:
    void createLevelLinkedListDFSHelper(TreeNode* node, int level, std::vector<std::list<TreeNode*>>& levelLists) {
        if (!node) return;

        if (levelLists.size() == level) {
            levelLists.push_back(std::list<TreeNode*>());
        }

        levelLists[level].push_back(node);
        createLevelLinkedListDFSHelper(node->left, level + 1, levelLists);
        createLevelLinkedListDFSHelper(node->right, level + 1, levelLists);
    }
};

// Helper function to create a sample binary tree
TreeNode* createSampleTree() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->right = new TreeNode(6);
    return root;
}

// Helper function to print the result
void printResult(const std::vector<std::list<TreeNode*>>& levelLists) {
    for (int i = 0; i < levelLists.size(); i++) {
        std::cout << "Level " << i << ": ";
        for (TreeNode* node : levelLists[i]) {
            std::cout << node->val << " ";
        }
        std::cout << std::endl;
    }
}

// Test function
void testListOfDepths() {
    Solution solution;
    TreeNode* root = createSampleTree();

    std::cout << "DFS approach result:" << std::endl;
    auto dfsLists = solution.createLevelLinkedListDFS(root);
    printResult(dfsLists);

    std::cout << "\nBFS approach result:" << std::endl;
    auto bfsLists = solution.createLevelLinkedListBFS(root);
    printResult(bfsLists);
}

int main() {
    testListOfDepths();
    return 0;
}