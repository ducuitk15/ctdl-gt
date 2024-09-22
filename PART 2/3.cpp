#include <iostream>

// Definition for singly-linked list node
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode* swapNodes(ListNode* head, int pos1, int pos2) {
        if (!head || pos1 == pos2) return head;
        
        ListNode dummy(0);
        dummy.next = head;
        ListNode *prev1 = &dummy, *prev2 = &dummy;
        ListNode *node1 = head, *node2 = head;
        
        // Find the nodes and their previous nodes
        for (int i = 0; i < pos1 && node1; i++) {
            prev1 = node1;
            node1 = node1->next;
        }
        
        for (int i = 0; i < pos2 && node2; i++) {
            prev2 = node2;
            node2 = node2->next;
        }
        
        // If either position is out of bounds, return original list
        if (!node1 || !node2) return head;
        
        // Swap the nodes
        prev1->next = node2;
        prev2->next = node1;
        ListNode* temp = node1->next;
        node1->next = node2->next;
        node2->next = temp;
        
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
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    ListNode* head = createList(arr, n);
    
    std::cout << "Original List: ";
    printList(head);
    
    int pos1, pos2;
    std::cout << "Enter two positions to swap (0-indexed): ";
    std::cin >> pos1 >> pos2;
    
    Solution solution;
    ListNode* swappedHead = solution.swapNodes(head, pos1, pos2);
    
    std::cout << "Swapped List:  ";
    printList(swappedHead);
    
    return 0;
}
