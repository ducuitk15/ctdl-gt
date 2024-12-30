// STT:02
// Full Name: NGUYEN TRAN CHI DUC
// STUDENT ID: 20521199
// CLASS: CS4343.P11.CTTT

#include <iostream>
#include <vector>
#include <cmath>  // For sqrt function
using namespace std;

// Function to perform Jump Search
int jumpSearch(const vector<int>& arr, int target) {
    int n = arr.size();
    // Calculate the optimal step size
    int step = sqrt(n);  // You can adjust this if needed based on distribution

    int prev = 0;
    // Jump through the array
    while (arr[min(step, n) - 1] < target) {
        prev = step;
        step += sqrt(n);  // Move ahead by sqrt(n) steps
        if (prev >= n) {
            return -1;  // If we have surpassed the array bounds
        }
    }

    // Perform linear search within the block
    for (int i = prev; i < min(step, n); i++) {
        if (arr[i] == target) {
            return i;  // Return the index of the target
        }
    }

    return -1;  // Target not found
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
    cout << "Enter the target value to search: ";
    cin >> target;

    // Output: the index of the target
    int index = jumpSearch(arr, target);
    if (index != -1) {
        cout << "The target value " << target << " is found at index " << index << "." << endl;
    } else {
        cout << "The target value " << target << " was not found in the array." << endl;
    }

    return 0;
}
