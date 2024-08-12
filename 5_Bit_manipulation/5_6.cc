#include <iostream>

int countBitsToFlip(int A, int B) {
    // Perform XOR between A and B
    int xorResult = A ^ B;

    // Count the number of set bits (1s) in the XOR result
    int count = 0;
    while (xorResult != 0) {
        count += xorResult & 1;
        xorResult >>= 1;
    }

    return count;
}

int main() {
    int A = 29; // 11101 in binary
    int B = 15; // 01111 in binary

    int result = countBitsToFlip(A, B);
    std::cout << "Number of bits to flip to convert " << A << " to " << B << " is: " << result << std::endl;

    return 0;
}
