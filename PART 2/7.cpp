#include <iostream>
#include <unordered_map>

// Definition for singly-linked list node
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode* removeZeroSumSublists(ListNode* head) {
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        
        std::unordered_map<int, ListNode*> prefixSum;
        int sum = 0;
        
        for (ListNode* current = dummy; current != nullptr; current = current->next) {
            sum += current->val;
            
            if (prefixSum.find(sum) != prefixSum.end()) {
                ListNode* prev = prefixSum[sum];
                ListNode* toRemove = prev->next;
                int tempSum = sum + toRemove->val;
                
                while (tempSum != sum) {
                    prefixSum.erase(tempSum);
                    toRemove = toRemove->next;
                    tempSum += toRemove->val;
                }
                
                prev->next = current->next;
            } else {
                prefixSum[sum] = current;
            }
        }
        
        return dummy->next;
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
    int arr[] = {1, 2, -3, 3, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    ListNode* head = createList(arr, n);
    
    std::cout << "Original List: ";
    printList(head);
    
    Solution solution;
    ListNode* newHead = solution.removeZeroSumSublists(head);
    
    std::cout << "Modified List: ";
    printList(newHead);
    
    return 0;
}
