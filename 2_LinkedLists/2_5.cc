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
    // Solution for digits stored in reverse order
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode dummy(0);
        ListNode* current = &dummy;
        int carry = 0;

        while (l1 || l2 || carry) {
            int sum = carry;
            if (l1) {
                sum += l1->val;
                l1 = l1->next;
            }
            if (l2) {
                sum += l2->val;
                l2 = l2->next;
            }

            carry = sum / 10;
            current->next = new ListNode(sum % 10);
            current = current->next;
        }

        return dummy.next;
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

    // Test for reverse order (which is the given input format)
    ListNode* l1 = createLinkedList({7, 1, 6});  // Represents 617
    ListNode* l2 = createLinkedList({5, 9, 2});  // Represents 295
    std::cout << "Number 1 (617): ";
    printLinkedList(l1);
    std::cout << "Number 2 (295): ";
    printLinkedList(l2);

    ListNode* sum = solution.addTwoNumbers(l1, l2);
    std::cout << "Sum (912): ";
    printLinkedList(sum);

    deleteLinkedList(l1);
    deleteLinkedList(l2);
    deleteLinkedList(sum);
}

int main() {
    runTests();
    return 0;
}