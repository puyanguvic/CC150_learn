#include <iostream>
#include <vector>

class Solution {
public:
    int findMagicIndex(const std::vector<int>& A) {
        return binarySearchMagicIndex(A, 0, A.size() - 1);
    }

private:
    int binarySearchMagicIndex(const std::vector<int>& A, int start, int end) {
        if (start > end) {
            return -1;
        }

        int mid = start + (end - start) / 2;

        if (A[mid] == mid) {
            return mid;
        } else if (A[mid] > mid) {
            return binarySearchMagicIndex(A, start, mid - 1);
        } else {
            return binarySearchMagicIndex(A, mid + 1, end);
        }
    }
};

// Test function
void runTests() {
    Solution solution;

    std::vector<int> A = {-10, -5, 0, 3, 7};
    int magicIndex = solution.findMagicIndex(A);

    if (magicIndex != -1) {
        std::cout << "Magic index found: " << magicIndex << std::endl;
    } else {
        std::cout << "No magic index found" << std::endl;
    }
}

int main() {
    runTests();
    return 0;
}
