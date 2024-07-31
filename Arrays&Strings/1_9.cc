#include <iostream>
#include <string>

class StringRotationChecker {
public:
    /**
     * @brief Check if s2 is a rotation of s1
     * 
     * This method checks if s2 is a rotation of s1 using only one call
     * to the isSubstring method.
     * 
     * Time Complexity: O(N), where N is the length of the strings
     * Space Complexity: O(N) to create the doubled string
     * 
     * @param s1 The first string
     * @param s2 The second string
     * @return true if s2 is a rotation of s1, false otherwise
     */
    static bool isRotation(const std::string& s1, const std::string& s2) {
        if (s1.length() != s2.length() || s1.empty()) {
            return false;
        }

        std::string s1s1 = s1 + s1;
        return isSubstring(s1s1, s2);
    }

private:
    // This is a mock implementation of isSubstring
    // In a real scenario, this would be provided or implemented differently
    static bool isSubstring(const std::string& s1, const std::string& s2) {
        return s1.find(s2) != std::string::npos;
    }
};

// Test function
void runTests() {
    std::pair<std::string, std::string> testCases[] = {
        {"waterbottle", "erbottlewat"},
        {"hello", "llohe"},
        {"rotation", "tationro"},
        {"abc", "cab"},
        {"", ""},
        {"a", "a"},
        {"ab", "ba"},
        {"abc", "bca"},
        {"abc", "cab"},
        {"abc", "abc"},
        {"abcde", "deabc"},
        {"abcde", "cdeba"}
    };

    for (const auto& test : testCases) {
        std::cout << "\"" << test.first << "\" and \"" << test.second << "\": " 
                  << (StringRotationChecker::isRotation(test.first, test.second) ? "Is a rotation" : "Not a rotation")
                  << std::endl;
    }
}

int main() {
    runTests();
    return 0;
}