#include <iostream>
#include <string>
#include <unordered_map>
#include <cctype>

class PalindromePermutationChecker {
public:
    /**
     * @brief Check if a string is a permutation of a palindrome
     * 
     * This method ignores non-letter characters and is case-insensitive.
     * A string is a permutation of a palindrome if it has at most one character
     * with an odd count.
     * 
     * Time Complexity: O(n), where n is the length of the string
     * Space Complexity: O(1), as we use a fixed-size hash map (max 26 entries for lowercase letters)
     * 
     * @param str The input string to check
     * @return true if the string is a permutation of a palindrome
     * @return false otherwise
     */
    static bool isPalindromePermutation(const std::string& str) {
        std::unordered_map<char, int> charCount;
        int letterCount = 0;

        // Count the occurrence of each letter
        for (char c : str) {
            if (std::isalpha(c)) {
                char lowerC = std::tolower(c);
                charCount[lowerC]++;
                letterCount++;
            }
        }

        // Check if at most one character has an odd count
        int oddCount = 0;
        for (const auto& pair : charCount) {
            if (pair.second % 2 != 0) {
                oddCount++;
            }
        }

        // If string length is even, all characters should have even counts
        // If string length is odd, at most one character can have an odd count
        return oddCount <= 1;
    }
};

// Test function
void runTests() {
    std::string test1 = "Tact Coa";
    std::string test2 = "Race a car";
    std::string test3 = "A man a plan a canal panama";
    std::string test4 = "Hello World";

    std::cout << "\"" << test1 << "\": " 
              << (PalindromePermutationChecker::isPalindromePermutation(test1) ? "True" : "False") << std::endl;

    std::cout << "\"" << test2 << "\": " 
              << (PalindromePermutationChecker::isPalindromePermutation(test2) ? "True" : "False") << std::endl;

    std::cout << "\"" << test3 << "\": " 
              << (PalindromePermutationChecker::isPalindromePermutation(test3) ? "True" : "False") << std::endl;

    std::cout << "\"" << test4 << "\": " 
              << (PalindromePermutationChecker::isPalindromePermutation(test4) ? "True" : "False") << std::endl;
}

int main() {
    runTests();
    return 0;
}