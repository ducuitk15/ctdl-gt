#include <iostream>
#include <cstdlib>
#include <ctime>

// Definition for singly-linked list node
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class LinkedList {
private:
    ListNode* head;

public:
    LinkedList() : head(nullptr) {}

    // Function to insert a node at the end of the list
    void insertAtEnd(int value) {
        ListNode* newNode = new ListNode(value);
        if (!head) {
            head = newNode;
            return;
        }
        ListNode* current = head;
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;
    }

    // Function to generate random number in range [min, max]
    static int randomInRange(int min, int max) {
        return min + rand() % (max - min + 1);
    }

    // Function to automatically input values for the list
    void autoInputList() {
        int numEntries = randomInRange(39, 59);
        for (int i = 0; i < numEntries; ++i) {
            int value = randomInRange(-99, 99);
            insertAtEnd(value);
        }
    }

    // Function to print the list
    void printList() {
        ListNode* current = head;
        while (current) {
            std::cout << current->val << " -> ";
            current = current->next;
        }
        std::cout << "nullptr" << std::endl;
    }

    // Function to get the number of nodes in the list
    int getSize() {
        int count = 0;
        ListNode* current = head;
        while (current) {
            ++count;
            current = current->next;
        }
        return count;
    }
};

int main() {
    // Seed the random number generator
    srand(static_cast<unsigned int>(time(nullptr)));

    LinkedList list;
    list.autoInputList();

    std::cout << "Generated List:" << std::endl;
    list.printList();

    std::cout << "Number of nodes in the list: " << list.getSize() << std::endl;

    return 0;
}
