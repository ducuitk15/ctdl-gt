#include <iostream>
#include <vector>
#include <algorithm>

// Binary Search to find the insertion position
int binarySearch(const std::vector<int>& arr, int key, int low, int high) {
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] < key) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }
    return low;
}

// Enhanced Insertion Sort with Binary Search
void binaryInsertionSort(std::vector<int>& arr) {
    for (int i = 1; i < arr.size(); ++i) {
        int key = arr[i];
        // Find the insertion position using binary search
        int pos = binarySearch(arr, key, 0, i);

        // Shift elements to make space for the key
        for (int j = i; j > pos; --j) {
            arr[j] = arr[j - 1];
        }
        // Insert the key at the correct position
        arr[pos] = key;
    }
}

// Standard Insertion Sort for comparison
void insertionSort(std::vector<int>& arr) {
    for (int i = 1; i < arr.size(); ++i) {
        int key = arr[i];
        int j = i - 1;
        
        // Shift elements to the right to make space for the key
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

// Function to print the array
void printArray(const std::vector<int>& arr) {
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

int main() {
    int n;

    // Input the size of the array
    std::cout << "Enter the number of elements in the array: ";
    std::cin >> n;

    std::vector<int> arr1(n);
    
    // Input the elements of the array
    std::cout << "Enter the elements of the array: ";
    for (int i = 0; i < n; ++i) {
        std::cin >> arr1[i];
    }

    // Make a copy of the array for comparison
    std::vector<int> arr2 = arr1;

    std::cout << "Original Array: ";
    printArray(arr1);

    // Perform Binary Insertion Sort
    binaryInsertionSort(arr1);
    std::cout << "Sorted Array (Binary Insertion Sort): ";
    printArray(arr1);

    // Perform Standard Insertion Sort for comparison
    insertionSort(arr2);
    std::cout << "Sorted Array (Standard Insertion Sort): ";
    printArray(arr2);

    return 0;
}
