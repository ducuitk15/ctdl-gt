#include <iostream>

// Definition for singly-linked list node
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (!head || !head->next) return head;
        
        ListNode* current = head;
        
        while (current != nullptr && current->next != nullptr) {
            if (current->val == current->next->val) {
                ListNode* duplicate = current->next;
                current->next = current->next->next;
                delete duplicate;
            } else {
                current = current->next;
            }
        }
        
        return head;
    }
};

// Helper function to create a sorted linked list from an array
ListNode* createSortedList(int arr[], int n) {
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
    int arr[] = {1, 1, 2, 3, 3, 4, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    ListNode* head = createSortedList(arr, n);
    
    std::cout << "Original List: ";
    printList(head);
    
    Solution solution;
    ListNode* uniqueHead = solution.deleteDuplicates(head);
    
    std::cout << "List after removing duplicates: ";
    printList(uniqueHead);
    
    return 0;
}
