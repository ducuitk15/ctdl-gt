#include <iostream>
#include <unordered_map>
#include <vector>  // Add this line

// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = nullptr;
        random = nullptr;
    }
};

class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (!head) return nullptr;
        
        std::unordered_map<Node*, Node*> oldToNew;
        
        // First pass: create new nodes
        Node* curr = head;
        while (curr) {
            oldToNew[curr] = new Node(curr->val);
            curr = curr->next;
        }
        
        // Second pass: connect next and random pointers
        curr = head;
        while (curr) {
            oldToNew[curr]->next = oldToNew[curr->next];
            oldToNew[curr]->random = oldToNew[curr->random];
            curr = curr->next;
        }
        
        return oldToNew[head];
    }
};

// Helper function to create a linked list with random pointers
Node* createList(int arr[], int n, int randomIndices[]) {
    if (n == 0) return nullptr;
    
    std::vector<Node*> nodes;
    for (int i = 0; i < n; i++) {
        nodes.push_back(new Node(arr[i]));
        if (i > 0) nodes[i-1]->next = nodes[i];
    }
    
    for (int i = 0; i < n; i++) {
        if (randomIndices[i] != -1) {
            nodes[i]->random = nodes[randomIndices[i]];
        }
    }
    
    return nodes[0];
}

// Helper function to print a linked list with random pointers
void printList(Node* head) {
    Node* curr = head;
    while (curr) {
        std::cout << "Node " << curr->val << ": ";
        std::cout << "Next = " << (curr->next ? std::to_string(curr->next->val) : "nullptr") << ", ";
        std::cout << "Random = " << (curr->random ? std::to_string(curr->random->val) : "nullptr") << std::endl;
        curr = curr->next;
    }
}

int main() {
    int arr[] = {7, 13, 11, 10, 1};
    int randomIndices[] = {-1, 0, 4, 2, 0};  // -1 means null
    int n = sizeof(arr) / sizeof(arr[0]);
    
    Node* head = createList(arr, n, randomIndices);
    
    std::cout << "Original list:" << std::endl;
    printList(head);
    
    Solution solution;
    Node* copiedHead = solution.copyRandomList(head);
    
    std::cout << "\nCopied list:" << std::endl;
    printList(copiedHead);
    
    return 0;
}
