// STT:02
// Full Name: NGUYEN TRAN CHI DUC
// STUDENT ID: 20521199
// CLASS: CS4343.P11.CTTT

#include <iostream>
#include <vector>
#include <chrono>
using namespace std;

// Bidirectional Binary Search Algorithm
int bidirectionalBinarySearch(const vector<int>& arr, int target) {
    int low = 0;
    int high = arr.size() - 1;
    int comparisons = 0;

    while (low <= high) {
        comparisons++;

        // Calculate mid points from both ends
        int leftMid = low + (high - low) / 2;
        int rightMid = high - (high - low) / 2;

        // Compare target with elements at both mid points
        if (arr[leftMid] == target) {
            return leftMid;  // Target found at leftMid
        }
        if (arr[rightMid] == target) {
            return rightMid;  // Target found at rightMid
        }

        // Adjust search range based on the comparisons
        if (arr[leftMid] > target) {
            high = leftMid - 1;  // Narrow the range from the right
        } else if (arr[rightMid] < target) {
            low = rightMid + 1;  // Narrow the range from the left
        } else {
            // If target is between the values at leftMid and rightMid
            low = leftMid + 1;
            high = rightMid - 1;
        }
    }

    return -1;  // Target not found
}

// Traditional Binary Search Algorithm
int binarySearch(const vector<int>& arr, int target) {
    int low = 0;
    int high = arr.size() - 1;
    int comparisons = 0;

    while (low <= high) {
        comparisons++;
        int mid = low + (high - low) / 2;

        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return -1;  // Target not found
}

int main() {
    int n, target;
    cout << "Enter the number of elements in the array: ";
    cin >> n;
    vector<int> arr(n);

    cout << "Enter the sorted array elements: ";
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    cout << "Enter the target value to search for: ";
    cin >> target;

    // Measure execution time for Bidirectional Binary Search
    auto start = chrono::high_resolution_clock::now();
    int bidirectionalResult = bidirectionalBinarySearch(arr, target);
    auto end = chrono::high_resolution_clock::now();
    long long bidirectionalTime = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "Bidirectional Binary Search Result: " << bidirectionalResult << ", Time: " << bidirectionalTime << " ms\n";

    // Measure execution time for Traditional Binary Search
    start = chrono::high_resolution_clock::now();
    int binarySearchResult = binarySearch(arr, target);
    end = chrono::high_resolution_clock::now();
    long long binarySearchTime = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "Traditional Binary Search Result: " << binarySearchResult << ", Time: " << binarySearchTime << " ms\n";

    return 0;
}
