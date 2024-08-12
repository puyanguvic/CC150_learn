#include <iostream>
#include <stack>
#include <stdexcept>

class MyQueue {
private:
    std::stack<int> stackNewest; // for enqueue
    std::stack<int> stackOldest; // for dequeue

    // Move elements from stackNewest to stackOldest when necessary
    void shiftStacks() {
        if (stackOldest.empty()) {
            while (!stackNewest.empty()) {
                stackOldest.push(stackNewest.top());
                stackNewest.pop();
            }
        }
    }

public:
    void enqueue(int value) {
        stackNewest.push(value);
    }

    int dequeue() {
        shiftStacks(); // Ensure stackOldest has the oldest elements
        if (stackOldest.empty()) {
            throw std::runtime_error("Queue is empty");
        }
        int value = stackOldest.top();
        stackOldest.pop();
        return value;
    }

    int peek() {
        shiftStacks(); // Ensure stackOldest has the oldest elements
        if (stackOldest.empty()) {
            throw std::runtime_error("Queue is empty");
        }
        return stackOldest.top();
    }

    bool isEmpty() {
        return stackNewest.empty() && stackOldest.empty();
    }
};

// Test function
void testMyQueue() {
    MyQueue queue;

    std::cout << "Enqueuing: 1, 2, 3, 4, 5\n";
    for (int i = 1; i <= 5; ++i) {
        queue.enqueue(i);
    }

    std::cout << "Peek: " << queue.peek() << std::endl;

    std::cout << "Dequeuing two elements\n";
    std::cout << "Dequeued: " << queue.dequeue() << std::endl;
    std::cout << "Dequeued: " << queue.dequeue() << std::endl;

    std::cout << "Enqueuing: 6, 7\n";
    queue.enqueue(6);
    queue.enqueue(7);

    std::cout << "Dequeuing all remaining elements:\n";
    while (!queue.isEmpty()) {
        std::cout << "Dequeued: " << queue.dequeue() << std::endl;
    }

    try {
        queue.dequeue();
    } catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }
}

int main() {
    testMyQueue();
    return 0;
}