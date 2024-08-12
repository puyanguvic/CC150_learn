#include <iostream>
#include <bitset>

int getNextLarger(int n) {
    int c = n;
    int c0 = 0;
    int c1 = 0;
    
    // 计算 c0 和 c1
    while ((c & 1) == 0 && (c != 0)) {
        c0++;
        c >>= 1;
    }
    
    while ((c & 1) == 1) {
        c1++;
        c >>= 1;
    }
    
    // 如果 n 是111...000 或 0，则不存在更大的数
    if (c0 + c1 == 31 || c0 + c1 == 0) {
        return -1;
    }
    
    // 位置 p 是第一个非拖尾 0 的位置
    int p = c0 + c1;
    
    // 翻转位置 p 的位
    n |= (1 << p);
    // 将 p 右边的所有位清零
    n &= ~((1 << p) - 1);
    // 将右边的 (c1-1) 个 1 插入到末尾
    n |= (1 << (c1 - 1)) - 1;
    
    return n;
}

int getNextSmaller(int n) {
    int temp = n;
    int c0 = 0;
    int c1 = 0;
    
    // 计算 c0 和 c1
    while ((temp & 1) == 1) {
        c1++;
        temp >>= 1;
    }
    
    // 如果 n 是 0 或 1，没有更小的数
    if (temp == 0) {
        return -1;
    }
    
    while ((temp & 1) == 0 && (temp != 0)) {
        c0++;
        temp >>= 1;
    }
    
    // 位置 p 是第一个非拖尾 1 的位置
    int p = c0 + c1;
    
    // 翻转位置 p 的位
    n &= ((~0) << (p + 1));
    // 将 p 右边的所有位清零
    int mask = (1 << (c1 + 1)) - 1;
    n |= mask << (c0 - 1);
    
    return n;
}

int main() {
    int num = 13948; // 示例数字
    std::cout << "Original number: " << num << " (" << std::bitset<32>(num) << ")" << std::endl;
    int nextLarger = getNextLarger(num);
    int nextSmaller = getNextSmaller(num);
    
    if (nextLarger != -1) {
        std::cout << "Next larger number: " << nextLarger << " (" << std::bitset<32>(nextLarger) << ")" << std::endl;
    } else {
        std::cout << "No larger number with same number of 1 bits." << std::endl;
    }
    
    if (nextSmaller != -1) {
        std::cout << "Next smaller number: " << nextSmaller << " (" << std::bitset<32>(nextSmaller) << ")" << std::endl;
    } else {
        std::cout << "No smaller number with same number of 1 bits." << std::endl;
    }
    
    return 0;
}
