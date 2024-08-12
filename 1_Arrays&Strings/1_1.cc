#include <iostream>
#include <unordered_set>
#include <string>
#include <vector>

/**
 * @brief Determines if a string has all unique characters using an unordered_set.
 * 
 * This function iterates through each character in the input string and uses
 * an unordered_set to check for duplicates. It has a time complexity of O(n)
 * and a space complexity of O(min(n, c)), where n is the length of the string
 * and c is the size of the character set.
 * 
 * @param str The input string to check for unique characters.
 * @return true If all characters in the string are unique.
 * @return false If there are any duplicate characters in the string.
 */
bool isUnique(const std::string& str) {
    std::unordered_set<char> char_set;
    for (char c : str) {
        if (char_set.find(c) != char_set.end()) {
            return false;
        }
        char_set.insert(c);
    }
    return true;
}

/**
 * @brief Determines if a string has all unique characters without using additional data structures.
 * 
 * This function uses nested loops to compare each character with every other character
 * in the string. It has a time complexity of O(n^2) and a space complexity of O(1).
 * It assumes an ASCII character set and returns false for strings longer than 128 characters.
 * 
 * @param str The input string to check for unique characters.
 * @return true If all characters in the string are unique.
 * @return false If there are any duplicate characters in the string or if the string length exceeds 128.
 */
bool isUniqueNoExtraDS(const std::string& str) {
    if (str.length() > 128) {  // Assuming ASCII character set
        return false;
    }

    for (size_t i = 0; i < str.length() - 1; ++i) {
        for (size_t j = i + 1; j < str.length(); ++j) {
            if (str[i] == str[j]) {
                return false;
            }
        }
    }
    return true;
}

/**
 * @brief Test function to run both isUnique and isUniqueNoExtraDS on a set of test strings.
 * 
 * @param test_strings Vector of strings to test.
 */
void runTests(const std::vector<std::string>& test_strings) {
    std::cout << "Testing isUnique function:\n";
    for (const auto& str : test_strings) {
        std::cout << "\"" << str << "\" is " 
                  << (isUnique(str) ? "unique" : "not unique") << std::endl;
    }
    
    std::cout << "\nTesting isUniqueNoExtraDS function:\n";
    for (const auto& str : test_strings) {
        std::cout << "\"" << str << "\" is " 
                  << (isUniqueNoExtraDS(str) ? "unique" : "not unique") << std::endl;
    }
}

int main() {
    std::vector<std::string> test_strings = {"abcdefg", "hello", "unique", "test", ""};
    runTests(test_strings);
    return 0;
}