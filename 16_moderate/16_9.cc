#include <iostream>
#include <climits>

class Operations {
private:
    static int negate(int a) {
        int neg = 0;
        int d = a < 0 ? 1 : -1;
        while (a != 0) {
            neg += d;
            a += d;
        }
        return neg;
    }

    static int abs(int a) {
        return a < 0 ? negate(a) : a;
    }

public:
    static int multiply(int a, int b) {
        if (a == 0 || b == 0) return 0;
        
        int absA = abs(a);
        int absB = abs(b);
        
        int result = 0;
        for (int i = 0; i < absB; ++i) {
            result += absA;
        }
        
        if ((a < 0 && b > 0) || (a > 0 && b < 0)) {
            result = negate(result);
        }
        
        return result;
    }

    static int subtract(int a, int b) {
        return a + negate(b);
    }

    static int divide(int a, int b) {
        if (b == 0) {
            throw std::runtime_error("Division by zero");
        }

        int absA = abs(a);
        int absB = abs(b);

        int quotient = 0;
        int sum = 0;

        while (sum + absB <= absA) {
            sum += absB;
            ++quotient;
        }

        if ((a < 0 && b > 0) || (a > 0 && b < 0)) {
            quotient = negate(quotient);
        }

        return quotient;
    }
};

int main() {
    std::cout << "10 * 5 = " << Operations::multiply(10, 5) << std::endl;
    std::cout << "10 - 5 = " << Operations::subtract(10, 5) << std::endl;
    std::cout << "10 / 5 = " << Operations::divide(10, 5) << std::endl;

    std::cout << "-10 * 5 = " << Operations::multiply(-10, 5) << std::endl;
    std::cout << "10 - (-5) = " << Operations::subtract(10, -5) << std::endl;
    std::cout << "-10 / 5 = " << Operations::divide(-10, 5) << std::endl;

    return 0;
}