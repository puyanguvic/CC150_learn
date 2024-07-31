#include <iostream>
#include <stack>
#include <stdexcept>

class MinStack {
private:
    std::stack<int> mainStack;
    std::stack<int> minStack;

public:
    void push(int value) {
        mainStack.push(value);
        
        if (minStack.empty() || value <= minStack.top()) {
            minStack.push(value);
        }
    }

    void pop() {
        if (mainStack.empty()) {
            throw std::runtime_error("Stack is empty");
        }

        if (mainStack.top() == minStack.top()) {
            minStack.pop();
        }
        mainStack.pop();
    }

    int top() {
        if (mainStack.empty()) {
            throw std::runtime_error("Stack is empty");
        }
        return mainStack.top();
    }

    int min() {
        if (minStack.empty()) {
            throw std::runtime_error("Stack is empty");
        }
        return minStack.top();
    }

    bool isEmpty() {
        return mainStack.empty();
    }
};

// Test function
void testMinStack() {
    MinStack stack;

    std::cout << "Pushing elements: 3, 5, 2, 1, 4\n";
    stack.push(3);
    std::cout << "Min: " << stack.min() << "\n";
    stack.push(5);
    std::cout << "Min: " << stack.min() << "\n";
    stack.push(2);
    std::cout << "Min: " << stack.min() << "\n";
    stack.push(1);
    std::cout << "Min: " << stack.min() << "\n";
    stack.push(4);
    std::cout << "Min: " << stack.min() << "\n";

    std::cout << "\nPopping elements\n";
    while (!stack.isEmpty()) {
        std::cout << "Top: " << stack.top() << ", Min: " << stack.min() << "\n";
        stack.pop();
    }
}

int main() {
    testMinStack();
    return 0;
}