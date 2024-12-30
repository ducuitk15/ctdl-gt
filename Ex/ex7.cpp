#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>  // Include this header for std::sort

// Insertion Sort implementation
void insertionSort(std::vector<int>& arr, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int key = arr[i];
        int j = i - 1;
        
        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Merge Sort implementation
void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    std::vector<int> leftArr(n1), rightArr(n2);
    
    // Copy data to temp arrays
    for (int i = 0; i < n1; i++) {
        leftArr[i] = arr[left + i];
    }
    for (int i = 0; i < n2; i++) {
        rightArr[i] = arr[mid + 1 + i];
    }
    
    int i = 0, j = 0, k = left;
    
    // Merge the temp arrays back into the original array
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }
    
    // Copy remaining elements of leftArr if any
    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }
    
    // Copy remaining elements of rightArr if any
    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

// Hybrid Sort that uses Merge Sort or Insertion Sort based on array size
void hybridSort(std::vector<int>& arr, int left, int right) {
    if (right - left <= 10) {  // Threshold for using Insertion Sort
        insertionSort(arr, left, right);
    } else {
        if (left < right) {
            int mid = left + (right - left) / 2;
            
            // Recursively sort the two halves
            hybridSort(arr, left, mid);
            hybridSort(arr, mid + 1, right);
            
            // Merge the sorted halves
            merge(arr, left, mid, right);
        }
    }
}

// Function to compare the performance of Merge Sort vs Hybrid Sort
void comparePerformance(const std::vector<int>& arr) {
    std::vector<int> arr1 = arr;
    std::vector<int> arr2 = arr;
    
    // Measure performance of Hybrid Sort
    clock_t start = clock();
    hybridSort(arr1, 0, arr1.size() - 1);
    clock_t end = clock();
    std::cout << "Hybrid Sort Time: " << (double)(end - start) / CLOCKS_PER_SEC << " seconds\n";
    
    // Measure performance of Merge Sort
    start = clock();
    std::sort(arr2.begin(), arr2.end());  // Standard merge sort is just std::sort in C++
    end = clock();
    std::cout << "Standard Merge Sort Time: " << (double)(end - start) / CLOCKS_PER_SEC << " seconds\n";
}

int main() {
    // Example array to sort
    std::vector<int> arr;
    
    // Generate a random array of size 1000
    for (int i = 0; i < 1000; i++) {
        arr.push_back(rand() % 1000);  // Random number between 0 and 999
    }
    
    // Compare performance of Hybrid Sort and Merge Sort
    comparePerformance(arr);
    
    return 0;
}
