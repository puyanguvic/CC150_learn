#include <iostream>
#include <cstdint>

class NumberMax {
public:
    static int findMax(int a, int b) {
        int64_t diff = static_cast<int64_t>(a) - static_cast<int64_t>(b);
        int sign = (diff >> 63) & 1;
        return a * (1 - sign) + b * sign;
    }
};

int main() {
    std::cout << "Max of 5 and 3: " << NumberMax::findMax(5, 3) << std::endl;
    std::cout << "Max of -2 and 10: " << NumberMax::findMax(-2, 10) << std::endl;
    std::cout << "Max of -5 and -10: " << NumberMax::findMax(-5, -10) << std::endl;
    return 0;
}