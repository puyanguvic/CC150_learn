#include <iostream>

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        if (!head || !head->next) return head;

        ListNode* beforeStart = NULL;
        ListNode* beforeEnd = NULL;
        ListNode* afterStart = NULL;
        ListNode* afterEnd = NULL;

        // Partition list
        while (head) {
            ListNode* next = head->next;
            head->next = NULL;

            if (head->val < x) {
                if (!beforeStart) {
                    beforeStart = head;
                    beforeEnd = beforeStart;
                } else {
                    beforeEnd->next = head;
                    beforeEnd = head;
                }
            } else {
                if (!afterStart) {
                    afterStart = head;
                    afterEnd = afterStart;
                } else {
                    afterEnd->next = head;
                    afterEnd = head;
                }
            }
            head = next;
        }

        // Merge partitioned lists
        if (!beforeStart) {
            return afterStart;
        }

        beforeEnd->next = afterStart;
        return beforeStart;
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

    ListNode* list = createLinkedList({3, 5, 8, 5, 10, 2, 1});
    std::cout << "Original list: ";
    printLinkedList(list);

    int x = 5;
    ListNode* partitionedList = solution.partition(list, x);

    std::cout << "List after partitioning around " << x << ": ";
    printLinkedList(partitionedList);

    deleteLinkedList(partitionedList);
}

int main() {
    runTests();
    return 0;
} 