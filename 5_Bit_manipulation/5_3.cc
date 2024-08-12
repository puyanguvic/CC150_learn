#include <iostream>
#include <vector>
#include <algorithm>

int flipBitToWin(int num) {
    if (~num == 0) { // 如果num全为1，直接返回其位数
        return sizeof(num) * 8;
    }

    int maxLen = 1; // 最少可以有一个1
    int currentLen = 0; // 当前窗口内的1的长度
    int prevLen = 0; // 前一个连续1的长度
    bool flipped = false; // 标记是否已经翻转过一个0

    while (num != 0) {
        if ((num & 1) == 1) {
            currentLen++;
        } else {
            // 如果已经翻转过一个0
            prevLen = (flipped) ? currentLen : 0;
            currentLen = 0;
            flipped = true;
        }
        maxLen = std::max(maxLen, prevLen + currentLen + 1);
        num >>= 1;
    }

    return maxLen;
}

int main() {
    int num = 1775; // 11011101111
    int result = flipBitToWin(num);
    std::cout << "The length of the longest sequence of 1s after flipping one bit is: " << result << std::endl;
    return 0;
}
