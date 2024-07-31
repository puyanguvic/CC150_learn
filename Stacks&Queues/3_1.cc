#include <iostream>
#include <vector>
#include <stdexcept>

class FlexibleMultiStack {
private:
    struct StackInfo {
        int start, size, capacity;
        StackInfo(int start, int capacity) : start(start), size(0), capacity(capacity) {}
    };

    std::vector<int> array;
    std::vector<StackInfo> stacks;

    void expand(int stackNum) {
        shift((stackNum + 1) % stacks.size());
        stacks[stackNum].capacity++;
    }

    void shift(int stackNum) {
        StackInfo& stack = stacks[stackNum];
        if (stack.size >= stack.capacity) {
            int nextStack = (stackNum + 1) % stacks.size();
            shift(nextStack);
            stack.capacity++;
        }
        
        int index = adjustIndex(stack.start + stack.size);
        while (stack.size > 0) {
            array[index] = array[adjustIndex(index - 1)];
            index = adjustIndex(index - 1);
            stack.size--;
        }
        
        stack.start = adjustIndex(stack.start + 1);
        stack.capacity--;
    }

    int adjustIndex(int index) const {
        int max = array.size();
        return ((index % max) + max) % max;
    }

    bool allStacksAreFull() const {
        int totalSize = 0;
        for (const auto& stack : stacks) {
            totalSize += stack.size;
        }
        return totalSize == array.size();
    }

public:
    FlexibleMultiStack(int numberOfStacks, int defaultSize) : array(numberOfStacks * defaultSize) {
        for (int i = 0; i < numberOfStacks; i++) {
            stacks.emplace_back(defaultSize * i, defaultSize);
        }
    }

    void push(int stackNum, int value) {
        if (allStacksAreFull()) throw std::runtime_error("All stacks are full");
        
        StackInfo& stack = stacks[stackNum];
        if (stack.size >= stack.capacity) {
            expand(stackNum);
        }
        
        stack.size++;
        array[adjustIndex(stack.start + stack.size - 1)] = value;
    }

    int pop(int stackNum) {
        StackInfo& stack = stacks[stackNum];
        if (stack.size == 0) throw std::runtime_error("Stack is empty");
        
        int value = array[adjustIndex(stack.start + stack.size - 1)];
        array[adjustIndex(stack.start + stack.size - 1)] = 0; // Clear the value
        stack.size--;
        return value;
    }

    int peek(int stackNum) const {
        const StackInfo& stack = stacks[stackNum];
        if (stack.size == 0) throw std::runtime_error("Stack is empty");
        return array[adjustIndex(stack.start + stack.size - 1)];
    }

    bool isEmpty(int stackNum) const {
        return stacks[stackNum].size == 0;
    }

    int size(int stackNum) const {
        return stacks[stackNum].size;
    }
};

// Test function
void testStack(FlexibleMultiStack& stacks, int stackNum) {
    std::cout << "Testing Stack " << stackNum << ":\n";
    
    try {
        std::cout << "Pushing 1, 2, 3\n";
        stacks.push(stackNum, 1);
        stacks.push(stackNum, 2);
        stacks.push(stackNum, 3);
        
        std::cout << "Peek: " << stacks.peek(stackNum) << "\n";
        std::cout << "Pop: " << stacks.pop(stackNum) << "\n";
        std::cout << "Peek: " << stacks.peek(stackNum) << "\n";
        std::cout << "Pop: " << stacks.pop(stackNum) << "\n";
        std::cout << "Pop: " << stacks.pop(stackNum) << "\n";
        
        std::cout << "Is empty? " << (stacks.isEmpty(stackNum) ? "Yes" : "No") << "\n";
        
        std::cout << "Popping from empty stack...\n";
        stacks.pop(stackNum);
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << "\n";
    }
    
    std::cout << "\n";
}

int main() {
    FlexibleMultiStack stacks(3, 4);  // 3 stacks, each with initial capacity of 4

    for (int i = 0; i < 3; ++i) {
        testStack(stacks, i);
    }

    std::cout << "Testing stack expansion:\n";
    try {
        for (int i = 0; i < 15; ++i) {
            std::cout << "Pushing " << i << " to stack 0\n";
            stacks.push(0, i);
        }
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << "\n";
    }

    std::cout << "\nFinal stack sizes:\n";
    for (int i = 0; i < 3; ++i) {
        std::cout << "Stack " << i << " size: " << stacks.size(i) << "\n";
    }

    return 0;
}