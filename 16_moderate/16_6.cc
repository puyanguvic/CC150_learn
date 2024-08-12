#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cmath>

class SmallestDifference {
public:
    static int findSmallestDifference(std::vector<int>& arr1, std::vector<int>& arr2) {
        // Sort both arrays
        std::sort(arr1.begin(), arr1.end());
        std::sort(arr2.begin(), arr2.end());

        int i = 0, j = 0;
        int minDiff = INT_MAX;
        int pair1 = 0, pair2 = 0;

        // Compare elements to find minimum difference
        while (i < arr1.size() && j < arr2.size()) {
            int diff = std::abs(arr1[i] - arr2[j]);
            
            if (diff < minDiff) {
                minDiff = diff;
                pair1 = arr1[i];
                pair2 = arr2[j];
            }
            
            if (arr1[i] < arr2[j]) {
                i++;
            } else {
                j++;
            }
        }

        std::cout << "The pair is (" << pair1 << ", " << pair2 << ")" << std::endl;
        return minDiff;
    }
};

int main() {
    std::vector<int> arr1 = {1, 3, 15, 11, 2};
    std::vector<int> arr2 = {23, 127, 235, 19, 8};

    int result = SmallestDifference::findSmallestDifference(arr1, arr2);
    std::cout << "The smallest difference is " << result << std::endl;

    return 0;
}