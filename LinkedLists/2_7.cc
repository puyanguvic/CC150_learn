#include <iostream>
#include <cmath>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if (!headA || !headB) return nullptr;

        ListNode *pA = headA;
        ListNode *pB = headB;

        while (pA != pB) {
            // If pA reaches the end, redirect it to headB
            pA = pA ? pA->next : headB;
            // If pB reaches the end, redirect it to headA
            pB = pB ? pB->next : headA;
        }

        return pA; // pA is either the intersection point or NULL
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

    // Create two intersecting lists
    ListNode* commonPart = createLinkedList({7, 8, 9});
    ListNode* listA = createLinkedList({1, 2, 3, 4, 5, 6});
    ListNode* listB = createLinkedList({10, 11, 12});

    // Make listA and listB intersect at commonPart
    ListNode* tailA = listA;
    while (tailA->next) tailA = tailA->next;
    tailA->next = commonPart;

    ListNode* tailB = listB;
    while (tailB->next) tailB = tailB->next;
    tailB->next = commonPart;

    // Find the intersection
    ListNode* intersection = solution.getIntersectionNode(listA, listB);

    if (intersection) {
        std::cout << "Intersection found at node with value: " << intersection->val << std::endl;
    } else {
        std::cout << "No intersection found." << std::endl;
    }

    // Clean up (be careful not to delete commonPart twice)
    tailA->next = NULL;
    tailB->next = NULL;
    deleteLinkedList(listA);
    deleteLinkedList(listB);
    deleteLinkedList(commonPart);
}

int main() {
    runTests();
    return 0;
}