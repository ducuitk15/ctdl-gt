#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

// Insertion Sort function
void insertionSort(vector<int>& arr, int low, int high) {
    for (int i = low + 1; i <= high; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= low && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

// Partition function for Quick Sort
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Quick Sort function with hybrid Insertion Sort
void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        // Switch to Insertion Sort for small subarrays
        if (high - low <= 10) {
            insertionSort(arr, low, high);
        } else {
            int pi = partition(arr, low, high);
            quickSort(arr, low, pi - 1);  // Left subarray
            quickSort(arr, pi + 1, high); // Right subarray
        }
    }
}

// Function to print the array
void printArray(const vector<int>& arr) {
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

int main() {
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;

    vector<int> arr(n);

    cout << "Enter the elements: ";
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    // Measure time taken for the hybrid sorting algorithm
    auto start = chrono::high_resolution_clock::now();
    
    // Perform hybrid sort (Quick Sort + Insertion Sort)
    quickSort(arr, 0, n - 1);
    
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    
    // Print sorted array
    cout << "Sorted array: ";
    printArray(arr);
    
    cout << "Time taken by hybrid sorting algorithm: " << duration.count() << " seconds." << endl;

    return 0;
}
