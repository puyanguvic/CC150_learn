#include <iostream>

int add(int a, int b) {
    while (b != 0) {
        // Calculate the carry
        int carry = a & b;

        // Calculate the sum without the carry
        a = a ^ b;

        // Move the carry to the next higher bit
        b = carry << 1;
    }
    return a;
}

int main() {
    int num1 = 15;
    int num2 = 32;
    
    std::cout << "Sum: " << add(num1, num2) << std::endl;
    
    return 0;
}
