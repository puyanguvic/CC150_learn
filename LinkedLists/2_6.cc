#include <iostream>
#include <stack>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    bool isPalindrome(ListNode* head) {
        if (!head || !head->next) {
            return true;  // Empty list or single node is palindrome
        }

        // Find the middle of the linked list
        ListNode* slow = head;
        ListNode* fast = head;
        std::stack<int> firstHalf;

        while (fast && fast->next) {
            firstHalf.push(slow->val);
            slow = slow->next;
            fast = fast->next->next;
        }

        // If the list has odd number of elements, skip the middle element
        if (fast) {
            slow = slow->next;
        }

        // Compare second half with the reversed first half
        while (slow) {
            if (slow->val != firstHalf.top()) {
                return false;
            }
            firstHalf.pop();
            slow = slow->next;
        }

        return true;
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

    ListNode* palindrome1 = createLinkedList({1, 2, 3, 2, 1});
    ListNode* palindrome2 = createLinkedList({1, 2, 3, 3, 2, 1});
    ListNode* notPalindrome = createLinkedList({1, 2, 3, 4, 5});

    std::cout << "Is [1,2,3,2,1] a palindrome? " 
              << (solution.isPalindrome(palindrome1) ? "Yes" : "No") << std::endl;
    
    std::cout << "Is [1,2,3,3,2,1] a palindrome? " 
              << (solution.isPalindrome(palindrome2) ? "Yes" : "No") << std::endl;
    
    std::cout << "Is [1,2,3,4,5] a palindrome? " 
              << (solution.isPalindrome(notPalindrome) ? "Yes" : "No") << std::endl;

    deleteLinkedList(palindrome1);
    deleteLinkedList(palindrome2);
    deleteLinkedList(notPalindrome);
}

int main() {
    runTests();
    return 0;
}