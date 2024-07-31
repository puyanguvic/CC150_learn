#include <iostream>
#include <stdexcept>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    // Iterative approach
    ListNode* findKthToLastIterative(ListNode* head, int k) {
        if (!head || k <= 0) return nullptr;

        ListNode* slow = head;
        ListNode* fast = head;

        // Move fast pointer k nodes ahead
        for (int i = 0; i < k; i++) {
            if (!fast) return nullptr; // k is larger than the length of the list
            fast = fast->next;
        }

        // Move both pointers until fast reaches the end
        while (fast) {
            slow = slow->next;
            fast = fast->next;
        }

        return slow;
    }

    // Recursive approach
    ListNode* findKthToLastRecursive(ListNode* head, int k, int& i) {
        if (!head) return nullptr;

        ListNode* node = findKthToLastRecursive(head->next, k, i);
        i++;

        if (i == k) return head;
        return node;
    }

    ListNode* findKthToLast(ListNode* head, int k) {
        int i = 0;
        return findKthToLastRecursive(head, k, i);
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

    ListNode* list = createLinkedList({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    std::cout << "Original list: ";
    printLinkedList(list);

    int k = 4;
    ListNode* result1 = solution.findKthToLastIterative(list, k);
    ListNode* result2 = solution.findKthToLast(list, k);

    if (result1) {
        std::cout << k << "th to last element (Iterative): " << result1->val << std::endl;
    } else {
        std::cout << "Iterative: Invalid k or empty list" << std::endl;
    }

    if (result2) {
        std::cout << k << "th to last element (Recursive): " << result2->val << std::endl;
    } else {
        std::cout << "Recursive: Invalid k or empty list" << std::endl;
    }

    deleteLinkedList(list);
}

int main() {
    runTests();
    return 0;
}