#include <iostream>
#include <vector>
#include <queue>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    std::vector<std::vector<int>> BSTSequences(TreeNode* root) {
        std::vector<std::vector<int>> result;
        if (!root) {
            result.push_back(std::vector<int>());
            return result;
        }

        std::vector<int> prefix;
        prefix.push_back(root->val);

        // Get all sequences from left and right subtrees
        std::vector<std::vector<int>> leftSeq = BSTSequences(root->left);
        std::vector<std::vector<int>> rightSeq = BSTSequences(root->right);

        // Weave together each sequence from the left and right subtrees
        for (const auto& left : leftSeq) {
            for (const auto& right : rightSeq) {
                std::vector<std::vector<int>> weaved;
                weaveLists(left, right, weaved, prefix);
                result.insert(result.end(), weaved.begin(), weaved.end());
            }
        }

        return result;
    }

private:
    void weaveLists(const std::vector<int>& first, const std::vector<int>& second,
                    std::vector<std::vector<int>>& results, std::vector<int>& prefix) {
        // If one list is empty, add the remainder to a cloned prefix and store result
        if (first.empty() || second.empty()) {
            std::vector<int> result = prefix;
            result.insert(result.end(), first.begin(), first.end());
            result.insert(result.end(), second.begin(), second.end());
            results.push_back(result);
            return;
        }

        // Recurse with head of first added to the prefix
        prefix.push_back(first.front());
        weaveLists(std::vector<int>(first.begin() + 1, first.end()), second, results, prefix);
        prefix.pop_back();

        // Recurse with head of second added to the prefix
        prefix.push_back(second.front());
        weaveLists(first, std::vector<int>(second.begin() + 1, second.end()), results, prefix);
        prefix.pop_back();
    }
};

// Helper function to create a BST
TreeNode* createBST(std::vector<int>& nums) {
    if (nums.empty()) return nullptr;
    TreeNode* root = new TreeNode(nums[0]);
    for (int i = 1; i < nums.size(); i++) {
        TreeNode* node = root;
        while (true) {
            if (nums[i] < node->val) {
                if (!node->left) {
                    node->left = new TreeNode(nums[i]);
                    break;
                }
                node = node->left;
            } else {
                if (!node->right) {
                    node->right = new TreeNode(nums[i]);
                    break;
                }
                node = node->right;
            }
        }
    }
    return root;
}

// Helper function to delete the BST
void deleteBST(TreeNode* root) {
    if (root) {
        deleteBST(root->left);
        deleteBST(root->right);
        delete root;
    }
}

// Test function
void testBSTSequences() {
    Solution solution;

    std::vector<int> nums = {2, 1, 3};
    TreeNode* root = createBST(nums);

    std::vector<std::vector<int>> sequences = solution.BSTSequences(root);

    std::cout << "Possible sequences that could have led to the BST:" << std::endl;
    for (const auto& seq : sequences) {
        for (int num : seq) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }

    deleteBST(root);
}

int main() {
    testBSTSequences();
    return 0;
}