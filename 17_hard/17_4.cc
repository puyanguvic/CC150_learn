#include <iostream>
#include <vector>

// Helper function to fetch the jth bit of number
int fetchBit(int num, int j) {
    return (num >> j) & 1;
}

int findMissingNumber(const std::vector<int>& A, int n) {
    int missingNumber = 0;
    
    // Number of bits required to represent n
    int totalBits = 0;
    while ((1 << totalBits) <= n) {
        totalBits++;
    }

    for (int j = 0; j < totalBits; ++j) {
        int expectedOnes = 0;
        int actualOnes = 0;

        for (int i = 0; i < n; ++i) {
            expectedOnes += (i >> j) & 1;
        }

        for (int num : A) {
            actualOnes += fetchBit(num, j);
        }

        if (actualOnes != expectedOnes) {
            missingNumber |= (1 << j);
        }
    }

    return missingNumber;
}

int main() {
    std::vector<int> A = {0, 1, 2, 4, 5, 6};  // n = 6, missing number is 3
    int n = 6;

    int missingNumber = findMissingNumber(A, n);
    std::cout << "Missing number is: " << missingNumber << std::endl;

    return 0;
}
