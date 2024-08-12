#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm> // for std::swap

// Function to shuffle the deck using Fisher-Yates algorithm
void shuffleDeck(std::vector<int>& deck) {
    int n = deck.size();
    for (int i = n - 1; i > 0; --i) {
        // Generate a random index j such that 0 <= j <= i
        int j = rand() % (i + 1);

        // Swap the ith card with the jth card
        std::swap(deck[i], deck[j]);
    }
}

int main() {
    // Initialize a deck of cards (represented as numbers 0 to 51)
    std::vector<int> deck(52);
    for (int i = 0; i < 52; ++i) {
        deck[i] = i;
    }

    // Seed the random number generator
    std::srand(std::time(0));

    // Shuffle the deck
    shuffleDeck(deck);

    // Print the shuffled deck
    std::cout << "Shuffled deck: ";
    for (int card : deck) {
        std::cout << card << " ";
    }
    std::cout << std::endl;

    return 0;
}
