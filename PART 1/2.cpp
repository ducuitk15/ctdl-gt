#include <iostream>

class ListNode {
public:
    int val;
    ListNode* next;
    
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    bool hasCycle(ListNode *head) {
        if (head == nullptr || head->next == nullptr) {
            return false;
        }
        
        ListNode *slow = head;
        ListNode *fast = head->next;
        
        while (slow != fast) {
            if (fast == nullptr || fast->next == nullptr) {
                return false;
            }
            slow = slow->next;
            fast = fast->next->next;
        }
        
        return true;
    }
};

// Helper function to create a linked list with a cycle
ListNode* createLinkedListWithCycle(int arr[], int n, int pos) {
    if (n == 0) return nullptr;
    
    ListNode* head = new ListNode(arr[0]);
    ListNode* current = head;
    ListNode* cycleNode = nullptr;
    
    for (int i = 1; i < n; i++) {
        current->next = new ListNode(arr[i]);
        current = current->next;
        if (i == pos) cycleNode = current;
    }
    
    if (cycleNode != nullptr) {
        current->next = cycleNode;
    }
    
    return head;
}

// int main() {
//     int arr[] = {3, 2, 0, -4};
//     int n = sizeof(arr) / sizeof(arr[0]);
//     int pos = 1;  // Position of the node where the cycle begins (0-indexed)
    
//     ListNode* head = createLinkedListWithCycle(arr, n, pos);

//     Solution solution;
//     bool hasCycle = solution.hasCycle(head);
    
//     std::cout << "Does the linked list have a cycle? " << (hasCycle ? "Yes" : "No") << std::endl;
    
//     return 0;
// }

int main() {
    int arr[] = {3, 2, 0, -4};
    int n = sizeof(arr) / sizeof(arr[0]);
    int pos = -1;  // Set to -1 to create a list without a cycle
    
    ListNode* head = createLinkedListWithCycle(arr, n, pos);
    
    Solution solution;
    bool hasCycle = solution.hasCycle(head);
    
    std::cout << "Does the linked list have a cycle? " << (hasCycle ? "Yes" : "No") << std::endl;
    
    return 0;
}