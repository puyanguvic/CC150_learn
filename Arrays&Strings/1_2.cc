#include <iostream>
#include <string>
#include <algorithm>
#include <array>

class PermutationChecker {
public:
    /**
     * @brief Check if two strings are permutations of each other using sorting method
     * 
     * Time Complexity: O(n log n), where n is the length of the strings (dominated by sorting)
     * Space Complexity: O(1), assuming in-place sorting
     * 
     * @param str1 The first string
     * @param str2 The second string
     * @return true if str1 is a permutation of str2
     * @return false if str1 is not a permutation of str2
     */
    static bool isPermutationSort(std::string str1, std::string str2) {
        if (str1.length() != str2.length()) {
            return false;
        }
        std::sort(str1.begin(), str1.end());
        std::sort(str2.begin(), str2.end());
        return str1 == str2;
    }

    /**
     * @brief Check if two strings are permutations of each other using character counting method
     * 
     * Time Complexity: O(n), where n is the length of the strings
     * Space Complexity: O(1), as we use a fixed-size array
     * 
     * @param str1 The first string
     * @param str2 The second string
     * @return true if str1 is a permutation of str2
     * @return false if str1 is not a permutation of str2
     */
    static bool isPermutationCount(const std::string& str1, const std::string& str2) {
        if (str1.length() != str2.length()) {
            return false;
        }

        std::array<int, 128> char_count = {0}; // Assuming ASCII character set

        for (char c : str1) {
            char_count[c]++;
        }

        for (char c : str2) {
            if (--char_count[c] < 0) {
                return false;
            }
        }

        return true;
    }
};

// Test function
void runTests() {
    std::pair<std::string, std::string> test_cases[] = {
        {"abc", "cba"},
        {"hello", "olleh"},
        {"permutation", "mutationper"},
        {"abc", "def"},
        {"aab", "aba"},
        {"", ""}
    };

    for (const auto& test : test_cases) {
        std::cout << "Testing \"" << test.first << "\" and \"" << test.second << "\":\n";
        std::cout << "Sort method: " 
                  << (PermutationChecker::isPermutationSort(test.first, test.second) ? "Is a permutation" : "Not a permutation")
                  << std::endl;
        std::cout << "Count method: " 
                  << (PermutationChecker::isPermutationCount(test.first, test.second) ? "Is a permutation" : "Not a permutation")
                  << std::endl << std::endl;
    }
}

int main() {
    runTests();
    return 0;
}