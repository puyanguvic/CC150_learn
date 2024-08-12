#include <iostream>
#include <vector>
#include <bitset>

void drawLine(std::vector<uint8_t>& screen, int width, int x1, int x2, int y) {
    int startOffset = x1 % 8;
    int firstFullByte = x1 / 8;
    if (startOffset != 0) {
        firstFullByte++;
    }

    int endOffset = x2 % 8;
    int lastFullByte = x2 / 8;
    if (endOffset != 7) {
        lastFullByte--;
    }

    // Set full bytes
    for (int b = firstFullByte; b <= lastFullByte; b++) {
        screen[(width / 8) * y + b] = 0xFF;
    }

    // Create masks for start and end of line
    uint8_t startMask = 0xFF >> startOffset;
    uint8_t endMask = ~(0xFF >> (endOffset + 1));

    // Set start and end of line
    if ((x1 / 8) == (x2 / 8)) { // x1 and x2 are in the same byte
        uint8_t mask = startMask & endMask;
        screen[(width / 8) * y + (x1 / 8)] |= mask;
    } else {
        if (startOffset != 0) {
            int byteNumber = (width / 8) * y + (x1 / 8);
            screen[byteNumber] |= startMask;
        }
        if (endOffset != 7) {
            int byteNumber = (width / 8) * y + (x2 / 8);
            screen[byteNumber] |= endMask;
        }
    }
}

int main() {
    int width = 32;  // Screen width in pixels
    int height = 3;  // Screen height in rows
    std::vector<uint8_t> screen(width * height / 8, 0);

    int x1 = 10;
    int x2 = 25;
    int y = 1;

    drawLine(screen, width, x1, x2, y);

    // Print the screen
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width / 8; ++col) {
            std::cout << std::bitset<8>(screen[row * (width / 8) + col]) << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
