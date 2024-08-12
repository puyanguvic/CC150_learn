#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

// Function to randomly generate a set of m integers from an array of size n
std::vector<int> randomSet(const std::vector<int>& arr, int m) {
    int n = arr.size();
    std::vector<int> reservoir(m);

    // Step 1: Initialize the reservoir with the first m elements of the array
    for (int i = 0; i < m; ++i) {
        reservoir[i] = arr[i];
    }

    // Step 2: Process the remaining elements
    for (int i = m; i < n; ++i) {
        // Generate a random index j from 0 to i
        int j = rand() % (i + 1);

        // If j is within the range [0, m-1], replace the element at index j
        if (j < m) {
            reservoir[j] = arr[i];
        }
    }

    return reservoir;
}

int main() {
    // Example array
    std::vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int m = 4;  // Size of the subset

    // Seed the random number generator
    std::srand(std::time(0));

    // Get the random subset
    std::vector<int> result = randomSet(arr, m);

    // Output the random subset
    std::cout << "Random subset: ";
    for (int num : result) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
