// STT:02
// Full Name: NGUYEN TRAN CHI DUC
// STUDENT ID: 20521199
// CLASS: CS4343.P11.CTTT

#include <iostream>
#include <vector>
#include <algorithm> // For sorting
using namespace std;

// Function to find the missing number using binary search
int findMissingNumber(vector<int>& arr) {
    // Sort the array first
    sort(arr.begin(), arr.end());

    int low = 0;
    int high = arr.size();

    // Apply binary search logic
    while (low <= high) {
        int mid = low + (high - low) / 2;

        // Check if the current index and value are not matching
        if (arr[mid] != mid) {
            // Missing number is at mid
            return mid;
        } else if (arr[mid] == mid) {
            // Missing number is in the right half
            low = mid + 1;
        }
    }

    // If no missing number is found, the missing number is n
    return arr.size();
}

int main() {
    int n;
    cout << "Enter the number of elements in the array: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter the array elements: ";
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    // Find the missing number
    int missingNumber = findMissingNumber(arr);
    cout << "The missing number is: " << missingNumber << endl;

    return 0;
}
