#include <iostream>
#include <stack>

// Definition for singly-linked list node
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    bool isPalindrome(ListNode* head) {
        if (!head || !head->next) return true;
        
        // Find the middle of the linked list
        ListNode *slow = head, *fast = head;
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
            slow = slow->next;
            firstHalf.pop();
        }
        
        return true;
    }
};

// Helper function to create a linked list from an array
ListNode* createList(int arr[], int n) {
    if (n == 0) return nullptr;
    ListNode* head = new ListNode(arr[0]);
    ListNode* current = head;
    for (int i = 1; i < n; i++) {
        current->next = new ListNode(arr[i]);
        current = current->next;
    }
    return head;
}

// Helper function to print a linked list
void printList(ListNode* head) {
    while (head) {
        std::cout << head->val << " -> ";
        head = head->next;
    }
    std::cout << "nullptr" << std::endl;
}

int main() {
    int arr1[] = {1, 2, 3, 2, 1};
    int arr2[] = {1, 2, 3, 4, 5};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    
    ListNode* head1 = createList(arr1, n1);
    ListNode* head2 = createList(arr2, n2);
    
    std::cout << "List 1: ";
    printList(head1);
    std::cout << "List 2: ";
    printList(head2);
    
    Solution solution;
    std::cout << "Is List 1 a palindrome? " << (solution.isPalindrome(head1) ? "Yes" : "No") << std::endl;
    std::cout << "Is List 2 a palindrome? " << (solution.isPalindrome(head2) ? "Yes" : "No") << std::endl;
    
    return 0;
}
