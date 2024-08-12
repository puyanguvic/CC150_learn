#include <iostream>
#include <unordered_set>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    // Solution 1: Using a temporary buffer (Hash Set)
    void removeDuplicatesWithBuffer(ListNode* head) {
        if (!head) return;

        std::unordered_set<int> seen;
        ListNode* current = head;
        ListNode* prev = nullptr;

        while (current) {
            if (seen.find(current->val) != seen.end()) {
                // Duplicate found, remove this node
                prev->next = current->next;
                delete current;
                current = prev->next;
            } else {
                seen.insert(current->val);
                prev = current;
                current = current->next;
            }
        }
    }

    // Solution 2: Without using a temporary buffer
    void removeDuplicatesWithoutBuffer(ListNode* head) {
        if (!head) return;

        ListNode* current = head;
        while (current) {
            ListNode* runner = current;
            while (runner->next) {
                if (runner->next->val == current->val) {
                    // Duplicate found, remove the next node
                    ListNode* duplicate = runner->next;
                    runner->next = runner->next->next;
                    delete duplicate;
                } else {
                    runner = runner->next;
                }
            }
            current = current->next;
        }
    }
};

// Helper functions for testing
ListNode* createLinkedList(std::initializer_list<int> values) {
    ListNode dummy(0);
    ListNode* current = &dummy;
    for (int val : values) {
        current->next = new ListNode(val);
        current = current->next;
    }
    return dummy.next;
}

void printLinkedList(ListNode* head) {
    while (head) {
        std::cout << head->val << " -> ";
        head = head->next;
    }
    std::cout << "NULL" << std::endl;
}

void deleteLinkedList(ListNode* head) {
    while (head) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
}

// Test function
void runTests() {
    Solution solution;

    // Test with buffer
    ListNode* list1 = createLinkedList({1, 2, 3, 2, 1, 4});
    std::cout << "Original list: ";
    printLinkedList(list1);
    solution.removeDuplicatesWithBuffer(list1);
    std::cout << "After removing duplicates (with buffer): ";
    printLinkedList(list1);
    deleteLinkedList(list1);

    // Test without buffer
    ListNode* list2 = createLinkedList({1, 2, 3, 2, 1, 4});
    std::cout << "Original list: ";
    printLinkedList(list2);
    solution.removeDuplicatesWithoutBuffer(list2);
    std::cout << "After removing duplicates (without buffer): ";
    printLinkedList(list2);
    deleteLinkedList(list2);
}

int main() {
    runTests();
    return 0;
}