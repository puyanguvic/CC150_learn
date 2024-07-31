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
    ListNode *detectCycle(ListNode* head) {
        if (!head || !head->next) return NULL;

        // Phase 1: Detect if there's a cycle
        ListNode *slow = head;
        ListNode *fast = head;
        bool hasCycle = false;

        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) {
                hasCycle = true;
                break;
            }
        }

        // If no cycle, return NULL
        if (!hasCycle) return NULL;

        // Phase 2: Find the start of the cycle
        slow = head;
        while (slow != fast) {
            slow = slow->next;
            fast = fast->next;
        }

        return slow; // This is the start of the cycle
    }
};

// Helper function to create a linked list with a cycle
ListNode* createLinkedListWithCycle(std::initializer_list<int> values, int cyclePos) {
    ListNode dummy(0);
    ListNode* current = &dummy;
    ListNode* cycleStart = NULL;
    int pos = 0;

    for (int val : values) {
        current->next = new ListNode(val);
        current = current->next;
        if (pos == cyclePos) {
            cycleStart = current;
        }
        pos++;
    }

    // Create the cycle
    if (cycleStart) {
        current->next = cycleStart;
    }

    return dummy.next;
}

// Test function
void runTests() {
    Solution solution;

    // Create a linked list with a cycle: A -> B -> C -> D -> E -> C
    ListNode* head = createLinkedListWithCycle({1, 2, 3, 4, 5}, 2); // Cycle starts at node with value 3

    ListNode* cycleStart = solution.detectCycle(head);

    if (cycleStart) {
        std::cout << "Cycle detected. It starts at node with value: " << cycleStart->val << std::endl;
    } else {
        std::cout << "No cycle detected." << std::endl;
    }

    // Clean up (Note: We can't use the usual deleteLinkedList function due to the cycle)
    // In a real scenario, you'd need to break the cycle before deleting to avoid infinite loop
}

int main() {
    runTests();
    return 0;
}