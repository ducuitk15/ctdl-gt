// STT:02
// Full Name: NGUYEN TRAN CHI DUC
// STUDENT ID: 20521199
// CLASS: CS4343.P11.CTTT

#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <cmath> // For sqrt (used in Jump Search)
#include <algorithm> // For sorting (used in Binary Search and Jump Search)
using namespace std;

struct SearchResult {
    int index;             // Index of the target found
    int comparisons;       // Number of comparisons made during the search
    string algorithm;      // Name of the algorithm
    long long execution_time; // Time taken for the search
};

// Linear Search Algorithm
SearchResult linearSearch(const vector<int>& arr, int target) {
    auto start = chrono::high_resolution_clock::now();
    int comparisons = 0;

    for (int i = 0; i < arr.size(); ++i) {
        comparisons++;
        if (arr[i] == target) {
            auto end = chrono::high_resolution_clock::now();
            return {i, comparisons, "Linear Search", chrono::duration_cast<chrono::milliseconds>(end - start).count()};
        }
    }

    auto end = chrono::high_resolution_clock::now();
    return {-1, comparisons, "Linear Search", chrono::duration_cast<chrono::milliseconds>(end - start).count()};
}

// Binary Search Algorithm (Array must be sorted)
SearchResult binarySearch(const vector<int>& arr, int target) {
    auto start = chrono::high_resolution_clock::now();
    int comparisons = 0;
    int low = 0, high = arr.size() - 1;

    while (low <= high) {
        comparisons++;
        int mid = low + (high - low) / 2;

        if (arr[mid] == target) {
            auto end = chrono::high_resolution_clock::now();
            return {mid, comparisons, "Binary Search", chrono::duration_cast<chrono::milliseconds>(end - start).count()};
        }
        if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    auto end = chrono::high_resolution_clock::now();
    return {-1, comparisons, "Binary Search", chrono::duration_cast<chrono::milliseconds>(end - start).count()};
}

// Jump Search Algorithm (Array must be sorted)
SearchResult jumpSearch(vector<int>& arr, int target) {
    auto start = chrono::high_resolution_clock::now();
    int comparisons = 0;
    int n = arr.size();
    int step = sqrt(n);

    int prev = 0;
    while (arr[min(step, n) - 1] < target) {
        comparisons++;
        prev = step;
        step += sqrt(n);
        if (prev >= n) {
            auto end = chrono::high_resolution_clock::now();
            return {-1, comparisons, "Jump Search", chrono::duration_cast<chrono::milliseconds>(end - start).count()};
        }
    }

    for (int i = prev; i < min(step, n); ++i) {
        comparisons++;
        if (arr[i] == target) {
            auto end = chrono::high_resolution_clock::now();
            return {i, comparisons, "Jump Search", chrono::duration_cast<chrono::milliseconds>(end - start).count()};
        }
    }

    auto end = chrono::high_resolution_clock::now();
    return {-1, comparisons, "Jump Search", chrono::duration_cast<chrono::milliseconds>(end - start).count()};
}

// Function to run searches concurrently
void runSearches(const vector<int>& arr, int target) {
    // Copy the array for Binary and Jump search (since they require sorted arrays)
    vector<int> arrForBinary = arr;
    vector<int> arrForJump = arr;
    sort(arrForBinary.begin(), arrForBinary.end());
    sort(arrForJump.begin(), arrForJump.end());

    // Create threads for each search algorithm
    thread linear_thread([&]() {
        SearchResult result = linearSearch(arr, target);
        cout << result.algorithm << " found at index: " << result.index
             << ", Comparisons: " << result.comparisons
             << ", Execution Time: " << result.execution_time << " ms\n";
    });

    thread binary_thread([&]() {
        SearchResult result = binarySearch(arrForBinary, target);
        cout << result.algorithm << " found at index: " << result.index
             << ", Comparisons: " << result.comparisons
             << ", Execution Time: " << result.execution_time << " ms\n";
    });

    thread jump_thread([&]() {
        SearchResult result = jumpSearch(arrForJump, target);
        cout << result.algorithm << " found at index: " << result.index
             << ", Comparisons: " << result.comparisons
             << ", Execution Time: " << result.execution_time << " ms\n";
    });

    // Wait for all threads to finish
    linear_thread.join();
    binary_thread.join();
    jump_thread.join();
}

int main() {
    int n, target;
    cout << "Enter the number of elements in the array: ";
    cin >> n;
    vector<int> arr(n);

    cout << "Enter the array elements (distinct numbers): ";
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    cout << "Enter the target value to search for: ";
    cin >> target;

    // Run searches concurrently
    runSearches(arr, target);

    return 0;
}
