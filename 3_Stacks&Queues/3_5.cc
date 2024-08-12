#include <iostream>
#include <stack>

class SortedStack {
private:
    std::stack<int> mainStack;
    std::stack<int> tempStack;

public:
    void push(int value) {
        if (isEmpty() || value <= peek()) {
            mainStack.push(value);
        } else {
            while (!isEmpty() && peek() < value) {
                tempStack.push(mainStack.top());
                mainStack.pop();
            }
            mainStack.push(value);
            while (!tempStack.empty()) {
                mainStack.push(tempStack.top());
                tempStack.pop();
            }
        }
    }

    void pop() {
        if (isEmpty()) {
            throw std::runtime_error("Stack is empty");
        }
        mainStack.pop();
    }

    int peek() {
        if (isEmpty()) {
            throw std::runtime_error("Stack is empty");
        }
        return mainStack.top();
    }

    bool isEmpty() {
        return mainStack.empty();
    }

    // Helper function to print the stack
    void printStack() {
        std::stack<int> printTemp;
        while (!mainStack.empty()) {
            std::cout << mainStack.top() << " ";
            printTemp.push(mainStack.top());
            mainStack.pop();
        }
        std::cout << std::endl;
        while (!printTemp.empty()) {
            mainStack.push(printTemp.top());
            printTemp.pop();
        }
    }
};

// Function to sort an existing stack
void sortStack(std::stack<int>& s) {
    std::stack<int> tempStack;

    while (!s.empty()) {
        int tmp = s.top();
        s.pop();

        while (!tempStack.empty() && tempStack.top() > tmp) {
            s.push(tempStack.top());
            tempStack.pop();
        }

        tempStack.push(tmp);
    }

    // Copy the sorted elements back to the original stack
    while (!tempStack.empty()) {
        s.push(tempStack.top());
        tempStack.pop();
    }
}

// Test function
void testSortedStack() {
    SortedStack ss;

    std::cout << "Pushing elements: 5, 2, 7, 1, 3\n";
    ss.push(5);
    ss.push(2);
    ss.push(7);
    ss.push(1);
    ss.push(3);

    std::cout << "Sorted stack (top to bottom): ";
    ss.printStack();

    std::cout << "Popping two elements\n";
    ss.pop();
    ss.pop();

    std::cout << "Stack after popping: ";
    ss.printStack();

    std::cout << "Pushing 6\n";
    ss.push(6);

    std::cout << "Final stack: ";
    ss.printStack();

    // Testing the sortStack function
    std::cout << "\nTesting sortStack function:\n";
    std::stack<int> regularStack;
    regularStack.push(5);
    regularStack.push(2);
    regularStack.push(7);
    regularStack.push(1);
    regularStack.push(3);

    std::cout << "Original stack (bottom to top): 5 2 7 1 3\n";
    sortStack(regularStack);

    std::cout << "Sorted stack (top to bottom): ";
    while (!regularStack.empty()) {
        std::cout << regularStack.top() << " ";
        regularStack.pop();
    }
    std::cout << std::endl;
}

int main() {
    testSortedStack();
    return 0;
}