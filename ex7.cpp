// STT:02
// Full Name: NGUYEN TRAN CHI DUC
// STUDENT ID: 20521199
// CLASS: CS4343.P11.CTTT

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

// Function to partition the array around the pivot
int partition(vector<int>& arr, int low, int high) {
    // Choose a pivot element (randomly for better average case performance)
    int pivotIndex = low + rand() % (high - low + 1);
    int pivot = arr[pivotIndex];

    // Move pivot to the end
    swap(arr[pivotIndex], arr[high]);

    int i = low - 1;

    // Partition the array into two halves
    for (int j = low; j <= high - 1; ++j) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    // Move pivot to its correct position
    swap(arr[i + 1], arr[high]);
    return i + 1;  // Return the pivot's final index
}

// Function to find the k-th smallest element using Quickselect
int quickselect(vector<int>& arr, int low, int high, int k) {
    if (low <= high) {
        int pivotIndex = partition(arr, low, high);

        // Check the position of the pivot
        if (pivotIndex == k) {
            return arr[pivotIndex];  // Found the k-th smallest element
        } else if (pivotIndex < k) {
            return quickselect(arr, pivotIndex + 1, high, k);  // Search on the right side
        } else {
            return quickselect(arr, low, pivotIndex - 1, k);  // Search on the left side
        }
    }
    return -1;  // Error case (shouldn't happen if input is valid)
}

int main() {
    srand(time(0));  // Initialize random seed for better pivot choice

    int n, k;
    cout << "Enter the number of elements in the array: ";
    cin >> n;
    vector<int> arr(n);

    cout << "Enter the array elements: ";
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    cout << "Enter the value of k to find the k-th smallest element: ";
    cin >> k;

    // Quickselect returns the k-th smallest element, remember k is 1-indexed.
    int result = quickselect(arr, 0, n - 1, k - 1);
    
    if (result != -1) {
        cout << "The " << k << "-th smallest element is: " << result << endl;
    } else {
        cout << "Error: Invalid k!" << endl;
    }

    return 0;
}
