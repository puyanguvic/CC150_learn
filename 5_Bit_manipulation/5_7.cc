#include <iostream>

unsigned int swapOddEvenBits(unsigned int x) {
    // Mask all odd bits and shift them right by 1
    unsigned int oddBits = (x & 0xAAAAAAAA) >> 1;
    
    // Mask all even bits and shift them left by 1
    unsigned int evenBits = (x & 0x55555555) << 1;
    
    // Combine the shifted odd and even bits
    return (oddBits | evenBits);
}

int main() {
    unsigned int x = 23; // Example number: 23 (00010111 in binary)
    unsigned int result = swapOddEvenBits(x);
    
    std::cout << "Original number: " << x << " (" << std::bitset<32>(x) << ")" << std::endl;
    std::cout << "Swapped number: " << result << " (" << std::bitset<32>(result) << ")" << std::endl;
    
    return 0;
}
