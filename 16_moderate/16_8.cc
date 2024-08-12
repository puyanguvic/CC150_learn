#include <iostream>
#include <string>
#include <vector>

class EnglishInt {
private:
    static const std::vector<std::string> ones;
    static const std::vector<std::string> teens;
    static const std::vector<std::string> tens;
    static const std::vector<std::string> thousands;

    static std::string convertThreeDigits(int num) {
        std::string result;
        if (num >= 100) {
            result += ones[num / 100] + " Hundred";
            num %= 100;
            if (num > 0) result += " ";
        }
        if (num >= 20) {
            result += tens[num / 10 - 2];
            if (num % 10 > 0) {
                result += " " + ones[num % 10];
            }
        } else if (num >= 10) {
            result += teens[num - 10];
        } else if (num > 0) {
            result += ones[num];
        }
        return result;
    }

public:
    static std::string convert(long long num) {
        if (num == 0) return "Zero";
        if (num < 0) return "Negative " + convert(-num);

        std::string result;
        int index = 0;

        while (num > 0) {
            if (num % 1000 != 0) {
                std::string temp = convertThreeDigits(num % 1000);
                if (index > 0) temp += " " + thousands[index];
                if (!result.empty()) temp += ", ";
                result = temp + result;
            }
            num /= 1000;
            index++;
        }

        return result;
    }
};

const std::vector<std::string> EnglishInt::ones = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"};
const std::vector<std::string> EnglishInt::teens = {"Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
const std::vector<std::string> EnglishInt::tens = {"Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
const std::vector<std::string> EnglishInt::thousands = {"", "Thousand", "Million", "Billion", "Trillion"};

int main() {
    std::vector<long long> tests = {0, 5, 10, 15, 20, 50, 100, 123, 1000, 1234, 10000, 12345, 100000, 123456, 1000000, 1234567, 1000000000, 1234567890};
    
    for (long long num : tests) {
        std::cout << num << ": " << EnglishInt::convert(num) << std::endl;
    }

    return 0;
}