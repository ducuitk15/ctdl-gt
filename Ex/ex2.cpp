#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <ctime>

// Bubble Sort
void bubble_sort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                std::swap(arr[j], arr[j+1]);
            }
        }
    }
}

// Quick Sort
int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i+1], arr[high]);
    return i+1;
}

void quick_sort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quick_sort(arr, low, pi-1);
        quick_sort(arr, pi+1, high);
    }
}

// Merge Sort
void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    std::vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];
    
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }
    
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void merge_sort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort(arr, left, mid);
        merge_sort(arr, mid+1, right);
        merge(arr, left, mid, right);
    }
}

// Insertion Sort
void insertion_sort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// Function to print vector (for debugging purposes)
void print_array(const std::vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

// Function to generate random vector of specified size
std::vector<int> generate_random_vector(int size) {
    std::vector<int> arr(size);
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 10000;  // Random number between 0 and 9999
    }
    return arr;
}

// Function to measure the sorting time of an algorithm
template <typename Func>
double measure_time(Func sort_func, std::vector<int>& arr) {
    auto start = std::chrono::high_resolution_clock::now();
    sort_func(arr);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    return duration.count();  // Return time in seconds
}

int main() {
    srand(time(0));  // Initialize random seed
    
    // Define array sizes for testing
    std::vector<int> sizes = {100, 1000, 10000};
    std::vector<std::string> algorithms = {"Bubble Sort", "Quick Sort", "Merge Sort", "Insertion Sort"};
    
    // Measure and display the time for each algorithm on each array size
    for (int size : sizes) {
        std::cout << "Array Size: " << size << std::endl;
        
        std::vector<int> arr = generate_random_vector(size);
        
        // Bubble Sort
        auto arr_copy = arr;
        double bubble_time = measure_time(bubble_sort, arr_copy);
        std::cout << algorithms[0] << " Time: " << bubble_time << " seconds" << std::endl;
        
        // Quick Sort
        arr_copy = arr;
        double quick_time = measure_time([](std::vector<int>& arr) { quick_sort(arr, 0, arr.size() - 1); }, arr_copy);
        std::cout << algorithms[1] << " Time: " << quick_time << " seconds" << std::endl;
        
        // Merge Sort
        arr_copy = arr;
        double merge_time = measure_time([](std::vector<int>& arr) { merge_sort(arr, 0, arr.size() - 1); }, arr_copy);
        std::cout << algorithms[2] << " Time: " << merge_time << " seconds" << std::endl;
        
        // Insertion Sort
        arr_copy = arr;
        double insert_time = measure_time(insertion_sort, arr_copy);
        std::cout << algorithms[3] << " Time: " << insert_time << " seconds" << std::endl;
        
        std::cout << std::endl;
    }

    return 0;
}
