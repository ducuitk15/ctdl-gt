// STT:02
// Full Name: NGUYEN TRAN CHI DUC
// STUDENT ID: 20521199
// CLASS: CS4343.P11.CTTT

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Function to perform interpolation search on a sorted array of strings
int interpolationSearch(const vector<string>& arr, const string& target) {
    int low = 0;
    int high = arr.size() - 1;

    while (low <= high && target >= arr[low] && target <= arr[high]) {
        // Estimate the position of the target using the interpolation formula
        int pos = low + ((high - low) / (arr[high] < arr[low] ? 1 : (arr[high] > arr[low] ? arr[high].compare(target) : 0))) ;
        // Ensure that the position is within the bounds of the array
        if (pos < low || pos > high) {
            break;
        }

        // Check if the target is at the estimated position
        if (arr[pos] == target) {
            return pos;
        }
        
        // If target is smaller, move the high pointer to the left
        if (arr[pos] > target) {
            high = pos - 1;
        }
        // If target is larger, move the low pointer to the right
        else {
            low = pos + 1;
        }
    }

    return -1;  // Return -1 if the target is not found
}

int main() {
    int n;
    string target;

    // Input: the size of the array and the array of strings
    cout << "Enter the number of strings: ";
    cin >> n;
    
    vector<string> arr(n);
    cout << "Enter the sorted strings: ";
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    // Input: the target string
    cout << "Enter the target string to search: ";
    cin >> target;

    // Output: the index of the target string
    int index = interpolationSearch(arr, target);
    if (index != -1) {
        cout << "The target string \"" << target << "\" is found at index " << index << "." << endl;
    } else {
        cout << "The target string \"" << target << "\" was not found in the array." << endl;
    }

    return 0;
}
