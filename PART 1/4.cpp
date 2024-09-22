#include <iostream>

// Definition for singly-linked list node
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if (!headA || !headB) return nullptr;
        
        ListNode *ptrA = headA;
        ListNode *ptrB = headB;
        
        while (ptrA != ptrB) {
            ptrA = ptrA ? ptrA->next : headB;
            ptrB = ptrB ? ptrB->next : headA;
        }
        
        return ptrA;
    }
};

// Helper function to create a linked list
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
    int arrA[] = {4, 1, 8, 4, 5};
    int arrB[] = {5, 6, 1, 8, 4, 5};
    int nA = sizeof(arrA) / sizeof(arrA[0]);
    int nB = sizeof(arrB) / sizeof(arrB[0]);
    
    ListNode* headA = createList(arrA, nA);
    ListNode* headB = createList(arrB, nB);
    
    // Create intersection
    ListNode* intersect = headA;
    for (int i = 0; i < 2; i++) intersect = intersect->next;
    ListNode* temp = headB;
    for (int i = 0; i < 2; i++) temp = temp->next;
    temp->next = intersect;
    
    std::cout << "List A: ";
    printList(headA);
    std::cout << "List B: ";
    printList(headB);
    
    Solution solution;
    ListNode* intersection = solution.getIntersectionNode(headA, headB);
    
    if (intersection) {
        std::cout << "Intersection at node with value: " << intersection->val << std::endl;
    } else {
        std::cout << "No intersection found." << std::endl;
    }
    
    return 0;
}