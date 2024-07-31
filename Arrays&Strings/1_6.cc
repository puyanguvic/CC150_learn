#include <iostream>
#include <string>
#include <sstream>

class StringCompressor {
public:
    /**
     * @brief Compress a string using counts of repeated characters
     * 
     * This method compresses the input string by replacing sequences of
     * repeated characters with the character followed by its count.
     * If the compressed string is not shorter than the original string,
     * it returns the original string.
     * 
     * Time Complexity: O(n), where n is the length of the input string
     * Space Complexity: O(n) in the worst case, for the compressed string
     * 
     * @param str The input string to compress
     * @return std::string The compressed string if shorter, otherwise the original string
     */
    static std::string compress(const std::string& str) {
        if (str.length() <= 2) {
            return str;  // No compression possible for strings of length 1 or 2
        }

        std::ostringstream compressed;
        int count = 1;
        char current = str[0];

        for (size_t i = 1; i < str.length(); ++i) {
            if (str[i] == current) {
                count++;
            } else {
                compressed << current << count;
                current = str[i];
                count = 1;
            }
        }
        compressed << current << count;  // Handle the last sequence

        std::string result = compressed.str();
        return (result.length() < str.length()) ? result : str;
    }
};

// Test function
void runTests() {
    std::string testCases[] = {
        "aabcccccaaa",
        "abcdef",
        "aabb",
        "aaa",
        "a",
        "",
        "AABBBCCCC"
    };

    for (const auto& test : testCases) {
        std::cout << "Original: \"" << test << "\"" << std::endl;
        std::cout << "Compressed: \"" << StringCompressor::compress(test) << "\"" << std::endl << std::endl;
    }
}

int main() {
    runTests();
    return 0;
}