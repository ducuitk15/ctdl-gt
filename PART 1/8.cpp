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
    std::vector<ListNode*> searchNodes(ListNode* head, int x) {
        std::vector<ListNode*> result;
        ListNode* current = head;
        
        while (current != nullptr) {
            if (current->val == x) {
                result.push_back(current);
            }
            current = current->next;
        }
        
        return result.empty() ? std::vector<ListNode*>{nullptr} : result;
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
    int arr[] = {1, 2, 3, 2, 4, 2, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    ListNode* head = createList(arr, n);
    
    std::cout << "Original List: ";
    printList(head);
    
    Solution solution;
    int searchValue = 2;
    std::vector<ListNode*> foundNodes = solution.searchNodes(head, searchValue);
    
    if (foundNodes[0] == nullptr) {
        std::cout << "No nodes found with value " << searchValue << std::endl;
    } else {
        std::cout << "Nodes found with value " << searchValue << " at addresses: ";
        for (ListNode* node : foundNodes) {
            std::cout << node << " ";
        }
        std::cout << std::endl;
    }
    
    return 0;
}
