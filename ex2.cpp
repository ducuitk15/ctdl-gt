#include <iostream>
using namespace std;

// Node structure for linked list
struct Node {
    int data;
    Node* next;
};

// Queue class
class Queue {
private:
    Node* front;
    Node* rear;

public:
    // Constructor to initialize the queue
    Queue() {
        front = nullptr;
        rear = nullptr;
    }

    // Check if the queue is empty
    bool isEmpty() {
        return front == nullptr;
    }

    // Enqueue an element
    void enqueue(int value) {
        Node* newNode = new Node();
        newNode->data = value;
        newNode->next = nullptr;

        if (rear == nullptr) {
            front = rear = newNode;
            return;
        }

        rear->next = newNode;
        rear = newNode;
    }

    // Dequeue an element
    int dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty!" << endl;
            return -1; // Indicating queue is empty
        }

        int value = front->data;
        Node* temp = front;
        front = front->next;

        // If the queue is now empty, update rear
        if (front == nullptr) {
            rear = nullptr;
        }

        delete temp;
        return value;
    }

    // Print front and rear elements
    void printFrontAndRear() {
        if (isEmpty()) {
            cout << "Queue is empty!" << endl;
            return;
        }
        cout << "FRONT: " << front->data << endl;
        cout << "REAR: " << rear->data << endl;
    }

    // Destructor to free up memory
    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }
};

// Main function to demonstrate queue operations
int main() {
    Queue queue;
    int choice, value;

    do {
        cout << "\nQueue Menu:\n";
        cout << "1. Enqueue\n";
        cout << "2. Dequeue\n";
        cout << "3. Print FRONT and REAR\n";
        cout << "4. Check if Queue is Empty\n";
        cout << "5. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1: // Enqueue operation
                cout << "Enter value to enqueue: ";
                cin >> value;
                queue.enqueue(value);
                break;
            case 2: // Dequeue operation
                value = queue.dequeue();
                if (value != -1) {
                    cout << "Dequeued: " << value << endl;
                }
                break;
            case 3: // Print FRONT and REAR
                queue.printFrontAndRear();
                break;
            case 4: // Check if the queue is empty
                if (queue.isEmpty()) {
                    cout << "Queue is empty." << endl;
                } else {
                    cout << "Queue is not empty." << endl;
                }
                break;
            case 5: // Exit
                cout << "Exiting...\n";
                break;
            default: // Handle invalid choice
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
