#include <iostream>
#include <vector>
#include <stack>
#include <stdexcept>

class SetOfStacks {
private:
    std::vector<std::stack<int>> stacks;
    int capacity;

    void addStack() {
        stacks.push_back(std::stack<int>());
    }

    void removeLastStackIfEmpty() {
        if (!stacks.empty() && stacks.back().empty()) {
            stacks.pop_back();
        }
    }

public:
    SetOfStacks(int cap) : capacity(cap) {
        if (capacity <= 0) {
            throw std::invalid_argument("Capacity must be positive");
        }
    }

    void push(int value) {
        if (stacks.empty() || stacks.back().size() == capacity) {
            addStack();
        }
        stacks.back().push(value);
    }

    int pop() {
        if (stacks.empty()) {
            throw std::runtime_error("Stack is empty");
        }
        int value = stacks.back().top();
        stacks.back().pop();
        removeLastStackIfEmpty();
        return value;
    }

    int popAt(int index) {
        if (index < 0 || index >= stacks.size()) {
            throw std::out_of_range("Invalid stack index");
        }
        int value = stacks[index].top();
        stacks[index].pop();
        shiftElements(index);
        removeLastStackIfEmpty();
        return value;
    }

    void shiftElements(int index) {
        for (size_t i = index; i < stacks.size() - 1; ++i) {
            if (!stacks[i + 1].empty()) {
                stacks[i].push(stacks[i + 1].top());
                stacks[i + 1].pop();
            }
        }
    }

    bool isEmpty() const {
        return stacks.empty();
    }

    // For debugging and testing
    void printStacks() const {
        for (size_t i = 0; i < stacks.size(); ++i) {
            std::cout << "Stack " << i << ": ";
            std::stack<int> temp = stacks[i];
            while (!temp.empty()) {
                std::cout << temp.top() << " ";
                temp.pop();
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
};

// Test function
void testSetOfStacks() {
    SetOfStacks sos(3);  // Each sub-stack has a capacity of 3

    std::cout << "Pushing elements: 1, 2, 3, 4, 5, 6, 7, 8\n";
    for (int i = 1; i <= 8; ++i) {
        sos.push(i);
    }
    std::cout << "Current state of SetOfStacks:\n";
    sos.printStacks();

    std::cout << "Popping two elements\n";
    std::cout << "Popped: " << sos.pop() << std::endl;
    std::cout << "Popped: " << sos.pop() << std::endl;
    std::cout << "Current state of SetOfStacks:\n";
    sos.printStacks();

    std::cout << "Popping from the first stack (index 0)\n";
    std::cout << "Popped: " << sos.popAt(0) << std::endl;
    std::cout << "Current state of SetOfStacks:\n";
    sos.printStacks();

    std::cout << "Pushing 9 and 10\n";
    sos.push(9);
    sos.push(10);
    std::cout << "Current state of SetOfStacks:\n";
    sos.printStacks();
}

int main() {
    testSetOfStacks();
    return 0;
}