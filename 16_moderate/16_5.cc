#include <stdio.h>

int trailingZeros(int n) {
    int count = 0;
    
    // Count factors of 5
    for (int i = 5; n / i >= 1; i *= 5) {
        count += n / i;
    }
    
    return count;
}

int main() {
    int n;
    printf("Enter a number to calculate trailing zeros in its factorial: ");
    scanf("%d", &n);
    
    int zeros = trailingZeros(n);
    
    printf("Number of trailing zeros in %d! is %d\n", n, zeros);
    
    return 0;
}