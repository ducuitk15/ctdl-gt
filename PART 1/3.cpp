#include <iostream>

// Definition for singly-linked list node
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        // Dummy node to simplify the merging process
        ListNode dummy(0);
        ListNode* current = &dummy;
        
        while (l1 && l2) {
            if (l1->val <= l2->val) {
                current->next = l1;
                l1 = l1->next;
            } else {
                current->next = l2;
                l2 = l2->next;
            }
            current = current->next;
        }
        
        // Append remaining nodes of l1 or l2, if any
        current->next = l1 ? l1 : l2;
        
        return dummy.next;
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
    int arr1[] = {1, 2, 4};
    int arr2[] = {1, 3, 4};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    
    ListNode* l1 = createList(arr1, n1);
    ListNode* l2 = createList(arr2, n2);
    
    std::cout << "List 1: ";
    printList(l1);
    std::cout << "List 2: ";
    printList(l2);
    
    Solution solution;
    ListNode* mergedList = solution.mergeTwoLists(l1, l2);
    
    std::cout << "Merged List: ";
    printList(mergedList);
    
    return 0;
}