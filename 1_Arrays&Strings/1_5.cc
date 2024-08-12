#include <iostream>
#include <string>
#include <cmath>

class OneAwayChecker {
public:
    /**
     * @brief Check if two strings are one edit (or zero edits) away
     * 
     * This method checks if the two input strings are one edit away from each other.
     * An edit can be an insertion, removal, or replacement of a single character.
     * 
     * Time Complexity: O(min(n, m)), where n and m are the lengths of the two strings
     * Space Complexity: O(1)
     * 
     * @param str1 The first string
     * @param str2 The second string
     * @return true if the strings are one edit (or zero edits) away
     * @return false otherwise
     */
    static bool isOneAway(const std::string& str1, const std::string& str2) {
        // If the difference in lengths is more than 1, they can't be one edit away
        if (std::abs(int(str1.length()) - int(str2.length())) > 1) {
            return false;
        }
        int i = 0;
        while(str1[i] == str2[i]) i ++;
        if (i == str1.length() || i == str2.length()) return true;
        return str1.substr(i) == str2.substr(i + 1) || 
               str1.substr(i + 1) == str2.substr(i + 1) ||
               str1.substr(i+1) == str2.substr(i);
    }
};

// Test function
void runTests() {
    std::pair<std::string, std::string> testCases[] = {
        {"pale", "ple"},
        {"pales", "pale"},
        {"pale", "bale"},
        {"pale", "bake"},
        {"apple", "aple"},
        {"apple", "appl"},
        {"apple", "apply"},
        {"apple", "aple"},
        {"apple", "applee"},
        {"a", ""},
        {"", "a"},
        {"abc", "abc"}
    };

    for (const auto& test : testCases) {
        std::cout << "\"" << test.first << "\" and \"" << test.second << "\": " 
                  << (OneAwayChecker::isOneAway(test.first, test.second) ? "true" : "false")
                  << std::endl;
    }
}

int main() {
    runTests();
    return 0;
}