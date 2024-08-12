#include <random>
#include <ctime>
#include <iostream>
#include <unordered_map>

class TreeNode {
public:
    int data;
    TreeNode* left;
    TreeNode* right;
    int size;  // Number of nodes in this subtree (including this node)

    TreeNode(int d) : data(d), left(nullptr), right(nullptr), size(1) {}
};

class BinaryTree {
private:
    TreeNode* root;
    std::mt19937 gen;

public:
    BinaryTree() : root(nullptr) {
        gen.seed(std::time(0));  // Seed the random number generator
    }

    void insert(int data) {
        root = insertHelper(root, data);
    }

    TreeNode* find(int data) {
        return findHelper(root, data);
    }

    void remove(int data) {
        root = removeHelper(root, data);
    }

    TreeNode* getRandomNode() {
        if (!root) return nullptr;
        int index = std::uniform_int_distribution<>(0, root->size - 1)(gen);
        return getRandomNodeHelper(root, index);
    }

private:
    TreeNode* insertHelper(TreeNode* node, int data) {
        if (!node) return new TreeNode(data);

        if (data <= node->data)
            node->left = insertHelper(node->left, data);
        else
            node->right = insertHelper(node->right, data);

        node->size++;
        return node;
    }

    TreeNode* findHelper(TreeNode* node, int data) {
        if (!node || node->data == data) return node;
        if (data < node->data)
            return findHelper(node->left, data);
        return findHelper(node->right, data);
    }

    TreeNode* removeHelper(TreeNode* node, int data) {
        if (!node) return nullptr;

        if (data < node->data)
            node->left = removeHelper(node->left, data);
        else if (data > node->data)
            node->right = removeHelper(node->right, data);
        else {
            if (!node->left) {
                TreeNode* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                TreeNode* temp = node->left;
                delete node;
                return temp;
            }

            TreeNode* temp = minValueNode(node->right);
            node->data = temp->data;
            node->right = removeHelper(node->right, temp->data);
        }

        node->size--;
        return node;
    }

    TreeNode* minValueNode(TreeNode* node) {
        TreeNode* current = node;
        while (current && current->left)
            current = current->left;
        return current;
    }

    TreeNode* getRandomNodeHelper(TreeNode* node, int& index) {
        if (!node) return nullptr;

        int leftSize = node->left ? node->left->size : 0;

        if (index < leftSize)
            return getRandomNodeHelper(node->left, index);
        if (index == leftSize)
            return node;

        index = index - leftSize - 1;
        return getRandomNodeHelper(node->right, index);
    }
};


void testBinaryTree() {
    BinaryTree tree;
    
    // insert node
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);

    // test find
    std::cout << "find 40: " << (tree.find(40) ? "found" : "not found") << std::endl;
    std::cout << "find 90: " << (tree.find(90) ? "found" : "not found") << std::endl;

    // test delete
    tree.remove(20);
    std::cout << "delete 20, then find 20: " << (tree.find(20) ? "found" : "not found") << std::endl;

    // test random node
    std::unordered_map<int, int> count;
    int iterations = 100000;
    for (int i = 0; i < iterations; i++) {
        TreeNode* node = tree.getRandomNode();
        if (node) {
            count[node->data]++;
        }
    }

    std::cout << "random reslut (" << iterations << " iteration count):" << std::endl;
    for (const auto& pair : count) {
        std::cout << "node " << pair.first << ": " 
                  << pair.second << " times (" 
                  << (float)pair.second / iterations * 100 << "%)" << std::endl;
    }
}

int main() {
    testBinaryTree();
    return 0;
}