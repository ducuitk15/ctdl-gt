#include <iostream>
using namespace std;

// Function to heapify a subtree rooted at index i
void heapify(int arr[], int n, int i) {
    int largest = i;    // Initialize largest as root
    int left = 2 * i + 1;  // Left child
    int right = 2 * i + 2; // Right child

    // If left child is larger than root
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    // If right child is larger than largest so far
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    // If largest is not root
    if (largest != i) {
        swap(arr[i], arr[largest]);  // Swap root and largest
        heapify(arr, n, largest);    // Recursively heapify the affected subtree
    }
}

// Function to build a max-heap from the given array
void buildMaxHeap(int arr[], int n) {
    // Start from the last non-leaf node and heapify each node
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
}

// Function to find the maximum value in the array using Heap Sort approach
int findMax(int arr[], int n) {
    buildMaxHeap(arr, n);  // Build a max-heap
    return arr[0];  // The maximum element will be at the root (index 0)
}

int main() {
    int n;
    
    // Ask the user for the size of the array
    cout << "Enter the number of elements in the array: ";
    cin >> n;
    
    int arr[n];
    
    // Input the elements of the array
    cout << "Enter the elements of the array: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    int maxVal = findMax(arr, n);
    cout << "The maximum value is: " << maxVal << endl;

    return 0;
}
