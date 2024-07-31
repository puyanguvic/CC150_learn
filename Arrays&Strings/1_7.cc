#include <iostream>
#include <vector>

class MatrixRotator {
public:
    /**
     * @brief Rotate a square matrix 90 degrees clockwise in place
     * 
     * This method rotates the input matrix 90 degrees clockwise without 
     * using any extra space.
     * 
     * Time Complexity: O(N^2), where N is the number of rows/columns in the matrix
     * Space Complexity: O(1), as we rotate in place
     * 
     * @param matrix The input NxN matrix to rotate
     */
    static void rotateMatrix(std::vector<std::vector<int>>& matrix) {
        int n = matrix.size();
        if (n == 0 || n != matrix[0].size()) return; // Not a square matrix

        for (int layer = 0; layer < n / 2; layer++) {
            int first = layer;
            int last = n - 1 - layer;
            for (int i = first; i < last; i++) {
                int offset = i - first;
                int top = matrix[first][i]; // Save top

                // Left -> Top
                matrix[first][i] = matrix[last-offset][first];

                // Bottom -> Left
                matrix[last-offset][first] = matrix[last][last-offset];

                // Right -> Bottom
                matrix[last][last-offset] = matrix[i][last];

                // Top -> Right
                matrix[i][last] = top; // Right <- saved top
            }
        }
    }

    // Helper function to print the matrix
    static void printMatrix(const std::vector<std::vector<int>>& matrix) {
        for (const auto& row : matrix) {
            for (int val : row) {
                std::cout << val << "\t";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
};

// Test function
void runTests() {
    std::vector<std::vector<int>> matrix1 = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    std::vector<std::vector<int>> matrix2 = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };

    std::cout << "Original Matrix 1:" << std::endl;
    MatrixRotator::printMatrix(matrix1);
    MatrixRotator::rotateMatrix(matrix1);
    std::cout << "Rotated Matrix 1:" << std::endl;
    MatrixRotator::printMatrix(matrix1);

    std::cout << "Original Matrix 2:" << std::endl;
    MatrixRotator::printMatrix(matrix2);
    MatrixRotator::rotateMatrix(matrix2);
    std::cout << "Rotated Matrix 2:" << std::endl;
    MatrixRotator::printMatrix(matrix2);
}

int main() {
    runTests();
    return 0;
}