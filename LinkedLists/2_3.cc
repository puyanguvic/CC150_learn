#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    void deleteMiddleNode(ListNode* node) {
        if (node == NULL || node->next == NULL) {
            // Cannot delete if it's the last node or an invalid node
            return;
        }
        
        ListNode* nextNode = node->next;
        node->val = nextNode->val;
        node->next = nextNode->next;
        delete nextNode;
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

    ListNode* list = createLinkedList({'a', 'b', 'c', 'd', 'e', 'f'});
    std::cout << "Original list: ";
    printLinkedList(list);

    // Get the node 'c'
    ListNode* nodeToDelete = list->next->next;

    solution.deleteMiddleNode(nodeToDelete);

    std::cout << "List after deleting 'c': ";
    printLinkedList(list);

    deleteLinkedList(list);
}

int main() {
    runTests();
    return 0;
}