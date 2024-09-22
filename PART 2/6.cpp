#include <iostream>
#include <vector>

// Definition for singly-linked list node
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    std::vector<ListNode*> splitListToParts(ListNode* head, int k) {
        // Count the length of the linked list
        int length = 0;
        ListNode* current = head;
        while (current) {
            length++;
            current = current->next;
        }
        
        // Calculate the size of each part and the number of extra nodes
        int partSize = length / k;
        int extra = length % k;
        
        std::vector<ListNode*> parts(k, nullptr);
        current = head;
        
        for (int i = 0; i < k && current; i++) {
            parts[i] = current;
            int currentPartSize = partSize + (extra > 0 ? 1 : 0);
            
            for (int j = 0; j < currentPartSize - 1; j++) {
                current = current->next;
            }
            
            ListNode* next = current->next;
            current->next = nullptr;
            current = next;
            
            extra--;
        }
        
        return parts;
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
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    ListNode* head = createList(arr, n);
    
    std::cout << "Original List: ";
    printList(head);
    
    int k;
    std::cout << "Enter the number of parts to divide the list into: ";
    std::cin >> k;
    
    Solution solution;
    std::vector<ListNode*> parts = solution.splitListToParts(head, k);
    
    std::cout << "Divided List:" << std::endl;
    for (int i = 0; i < k; i++) {
        std::cout << "Part " << i+1 << ": ";
        printList(parts[i]);
    }
    
    return 0;
}
