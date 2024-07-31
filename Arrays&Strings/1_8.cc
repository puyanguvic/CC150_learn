#include <iostream>
#include <vector>

class MatrixZeroer {
public:
    /**
     * @brief Set entire row and column to 0 if an element is 0
     * 
     * This method modifies the input matrix such that if an element
     * is 0, its entire row and column are set to 0.
     * 
     * Time Complexity: O(M * N), where M and N are the dimensions of the matrix
     * Space Complexity: O(1), as we use the first row and column as markers
     * 
     * @param matrix The input MxN matrix to modify
     */
    static void setZeros(std::vector<std::vector<int>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) return;

        int M = matrix.size();
        int N = matrix[0].size();

        bool firstRowZero = false;
        bool firstColZero = false;

        // Check if first row contains zero
        for (int j = 0; j < N; j++) {
            if (matrix[0][j] == 0) {
                firstRowZero = true;
                break;
            }
        }

        // Check if first column contains zero
        for (int i = 0; i < M; i++) {
            if (matrix[i][0] == 0) {
                firstColZero = true;
                break;
            }
        }

        // Use first row and column as markers
        for (int i = 1; i < M; i++) {
            for (int j = 1; j < N; j++) {
                if (matrix[i][j] == 0) {
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }
            }
        }

        // Nullify rows based on markers in first column
        for (int i = 1; i < M; i++) {
            if (matrix[i][0] == 0) {
                for (int j = 1; j < N; j++) {
                    matrix[i][j] = 0;
                }
            }
        }

        // Nullify columns based on markers in first row
        for (int j = 1; j < N; j++) {
            if (matrix[0][j] == 0) {
                for (int i = 1; i < M; i++) {
                    matrix[i][j] = 0;
                }
            }
        }

        // Nullify first row if needed
        if (firstRowZero) {
            for (int j = 0; j < N; j++) {
                matrix[0][j] = 0;
            }
        }

        // Nullify first column if needed
        if (firstColZero) {
            for (int i = 0; i < M; i++) {
                matrix[i][0] = 0;
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
        {1, 2, 3, 4},
        {5, 0, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 0}
    };

    std::vector<std::vector<int>> matrix2 = {
        {1, 0, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    std::cout << "Original Matrix 1:" << std::endl;
    MatrixZeroer::printMatrix(matrix1);
    MatrixZeroer::setZeros(matrix1);
    std::cout << "Modified Matrix 1:" << std::endl;
    MatrixZeroer::printMatrix(matrix1);

    std::cout << "Original Matrix 2:" << std::endl;
    MatrixZeroer::printMatrix(matrix2);
    MatrixZeroer::setZeros(matrix2);
    std::cout << "Modified Matrix 2:" << std::endl;
    MatrixZeroer::printMatrix(matrix2);
}

int main() {
    runTests();
    return 0;
}