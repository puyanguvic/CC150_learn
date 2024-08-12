#include <iostream>
#include <string>

class URLifier {
public:
    /**
     * @brief Replace all spaces in a string with '%20'
     * 
     * This method assumes that the string has sufficient space at the end
     * to accommodate the additional characters.
     * 
     * Time Complexity: O(n), where n is the true length of the string
     * Space Complexity: O(1), as we modify the string in-place
     * 
     * @param str The string to be URLified
     * @param trueLength The true length of the string (excluding extra space at the end)
     */
    static void urlify(std::string& str, int trueLength) {
        int spaceCount = 0;
        
        // First pass: count the number of spaces
        for (int i = 0; i < trueLength; i++) {
            if (str[i] == ' ') {
                spaceCount++;
            }
        }
        
        // Calculate the new length of the string
        int newLength = trueLength + spaceCount * 2;
        
        // Second pass: replace spaces from end to start
        for (int i = trueLength - 1; i >= 0; i--) {
            if (str[i] == ' ') {
                str[newLength - 1] = '0';
                str[newLength - 2] = '2';
                str[newLength - 3] = '%';
                newLength -= 3;
            } else {
                str[newLength - 1] = str[i];
                newLength--;
            }
        }
    }
};

// Test function
void runTests() {
    std::string test1 = "Mr John Smith    ";
    int trueLength1 = 13;
    
    std::string test2 = "Hello World  ";
    int trueLength2 = 11;
    
    std::string test3 = "NoSpaces";
    int trueLength3 = 8;
    
    std::cout << "Original: \"" << test1.substr(0, trueLength1) << "\"" << std::endl;
    URLifier::urlify(test1, trueLength1);
    std::cout << "URLified: \"" << test1 << "\"" << std::endl << std::endl;
    
    std::cout << "Original: \"" << test2.substr(0, trueLength2) << "\"" << std::endl;
    URLifier::urlify(test2, trueLength2);
    std::cout << "URLified: \"" << test2 << "\"" << std::endl << std::endl;
    
    std::cout << "Original: \"" << test3 << "\"" << std::endl;
    URLifier::urlify(test3, trueLength3);
    std::cout << "URLified: \"" << test3 << "\"" << std::endl;
}

int main() {
    runTests();
    return 0;
}