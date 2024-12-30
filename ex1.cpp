// STT:02
// Full Name: NGUYEN TRAN CHI DUC
// STUDENT ID: 20521199
// CLASS: CS4343.P11.CTTT

#include <iostream>
#include <vector>
using namespace std;

// Function to perform binary search to find the leftmost occurrence of the target
int findLeftIndex(const vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1, result = -1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            result = mid;
            right = mid - 1; // Search in the left half for any earlier occurrences
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return result;
}

// Function to perform binary search to find the rightmost occurrence of the target
int findRightIndex(const vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1, result = -1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            result = mid;
            left = mid + 1; // Search in the right half for any later occurrences
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return result;
}

// Function to count occurrences of the target
int countOccurrences(const vector<int>& arr, int target) {
    int leftIndex = findLeftIndex(arr, target);
    if (leftIndex == -1) {
        // Target not found in the array
        return 0;
    }

    int rightIndex = findRightIndex(arr, target);

    // The number of occurrences is the difference between the rightmost and leftmost indices + 1
    return rightIndex - leftIndex + 1;
}

int main() {
    int n, target;

    // Input: the size of the array and the array itself
    cout << "Enter the size of the array: ";
    cin >> n;
    
    vector<int> arr(n);
    cout << "Enter the sorted array elements: ";
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    // Input: target value
    cout << "Enter the target value to count occurrences: ";
    cin >> target;

    // Output: the count of occurrences of the target
    int count = countOccurrences(arr, target);
    cout << "The target value " << target << " appears " << count << " times in the array." << endl;

    return 0;
}
