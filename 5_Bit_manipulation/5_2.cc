#include <iostream>
#include <string>

std::string printBinary(double num) {
    if (num >= 1 || num <= 0) {
        return "ERROR";
    }

    std::string binary = "0.";
    while (num > 0) {
        if (binary.length() >= 34) { // "0." + 32 bits
            return "ERROR";
        }
        
        double r = num * 2;
        if (r >= 1) {
            binary += "1";
            num = r - 1;
        } else {
            binary += "0";
            num = r;
        }
    }
    return binary;
}

int main() {
    double num = 0.72;
    std::string result = printBinary(num);
    std::cout << "Binary representation of " << num << " is: " << result << std::endl;

    num = 0.5;
    result = printBinary(num);
    std::cout << "Binary representation of " << num << " is: " << result << std::endl;

    return 0;
}
