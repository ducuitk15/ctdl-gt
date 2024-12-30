#include <iostream>
#include <queue>
#include <stack>
#include <chrono>
#include <functional>  // For std::function
using namespace std;
using namespace chrono;

// Linked List Implementation
struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class LinkedList {
public:
    Node* head;
    LinkedList() : head(nullptr) {}

    void append(int val) {
        Node* newNode = new Node(val);
        if (!head) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = newNode;
        }
    }

    void printList() {
        Node* temp = head;
        while (temp) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    // Merge Sort for Linked List
    Node* mergeSort(Node* head) {
        if (!head || !head->next)
            return head;

        Node* mid = getMiddle(head);
        Node* left = mergeSort(head);
        Node* right = mergeSort(mid);

        return merge(left, right);
    }

    // Helper functions for Merge Sort
    Node* getMiddle(Node* head) {
        if (!head) return head;
        Node* slow = head;
        Node* fast = head;
        while (fast->next && fast->next->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        Node* middle = slow->next;
        slow->next = nullptr;
        return middle;
    }

    Node* merge(Node* left, Node* right) {
        if (!left) return right;
        if (!right) return left;

        if (left->data < right->data) {
            left->next = merge(left->next, right);
            return left;
        } else {
            right->next = merge(left, right->next);
            return right;
        }
    }

    void sortList() {
        head = mergeSort(head);
    }
};

// Queue Implementation (Insertion Sort)
void insertionSortQueue(queue<int>& q) {
    if (q.empty()) return;

    // Create a temporary queue for sorted elements
    queue<int> sortedQueue;

    // Insertion Sort on Queue
    while (!q.empty()) {
        int current = q.front();
        q.pop();

        // Insert the element in sorted order into the sortedQueue
        while (!sortedQueue.empty() && sortedQueue.front() > current) {
            q.push(sortedQueue.front());
            sortedQueue.pop();
        }
        sortedQueue.push(current);
    }

    // Refill the original queue with sorted values
    while (!sortedQueue.empty()) {
        q.push(sortedQueue.front());
        sortedQueue.pop();
    }
}

// Stack Implementation (Selection Sort)
void selectionSortStack(stack<int>& s) {
    if (s.empty()) return;

    stack<int> sortedStack;
    while (!s.empty()) {
        int current = s.top();
        s.pop();

        while (!sortedStack.empty() && sortedStack.top() > current) {
            s.push(sortedStack.top());
            sortedStack.pop();
        }
        sortedStack.push(current);
    }

    // Transfer sorted elements back to the original stack
    while (!sortedStack.empty()) {
        s.push(sortedStack.top());
        sortedStack.pop();
    }
}

// Function to measure execution time
void measureTime(std::function<void()> sortFunc, const string& name) {
    auto start = high_resolution_clock::now();
    sortFunc();
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << name << " Time taken: " << duration.count() << " microseconds" << endl;
}

int main() {
    int choice, n, value;

    // Linked List Sorting
    cout << "Enter number of elements for Linked List: ";
    cin >> n;
    LinkedList list;
    cout << "Enter elements for Linked List: ";
    for (int i = 0; i < n; i++) {
        cin >> value;
        list.append(value);
    }

    cout << "Original Linked List: ";
    list.printList();

    // Measure sorting time
    measureTime([&]() { list.sortList(); }, "Linked List");

    cout << "Sorted Linked List: ";
    list.printList();

    // Queue Sorting
    cout << "\nEnter number of elements for Queue: ";
    cin >> n;
    queue<int> q;
    cout << "Enter elements for Queue: ";
    for (int i = 0; i < n; i++) {
        cin >> value;
        q.push(value);
    }

    cout << "Original Queue: ";
    queue<int> tempQueue = q;
    while (!tempQueue.empty()) {
        cout << tempQueue.front() << " ";
        tempQueue.pop();
    }
    cout << endl;

    // Measure sorting time
    measureTime([&]() { insertionSortQueue(q); }, "Queue");

    cout << "Sorted Queue: ";
    while (!q.empty()) {
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;

    // Stack Sorting
    cout << "\nEnter number of elements for Stack: ";
    cin >> n;
    stack<int> s;
    cout << "Enter elements for Stack: ";
    for (int i = 0; i < n; i++) {
        cin >> value;
        s.push(value);
    }

    cout << "Original Stack: ";
    stack<int> tempStack = s;
    while (!tempStack.empty()) {
        cout << tempStack.top() << " ";
        tempStack.pop();
    }
    cout << endl;

    // Measure sorting time
    measureTime([&]() { selectionSortStack(s); }, "Stack");

    cout << "Sorted Stack: ";
    while (!s.empty()) {
        cout << s.top() << " ";
        s.pop();
    }
    cout << endl;

    return 0;
}
