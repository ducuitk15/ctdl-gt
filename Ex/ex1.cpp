#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <algorithm>

std::vector<int> generateRandomVector(int size) {
    std::vector<int> vec(size);
    for (int i = 0; i < size; i++) {
        vec[i] = rand() % 10000;  // Random integers between 0 and 9999
    }
    return vec;
}

// Bubble Sort Implementation
void bubbleSort(std::vector<int>& vec) {
    int n = vec.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (vec[j] > vec[j + 1]) {
                std::swap(vec[j], vec[j + 1]);
            }
        }
    }
}

// Selection Sort Implementation
void selectionSort(std::vector<int>& vec) {
    int n = vec.size();
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (vec[j] < vec[minIdx]) {
                minIdx = j;
            }
        }
        std::swap(vec[i], vec[minIdx]);
    }
}

// Insertion Sort Implementation
void insertionSort(std::vector<int>& vec) {
    int n = vec.size();
    for (int i = 1; i < n; i++) {
        int key = vec[i];
        int j = i - 1;
        while (j >= 0 && vec[j] > key) {
            vec[j + 1] = vec[j];
            j--;
        }
        vec[j + 1] = key;
    }
}

// Quick Sort Implementation
int partition(std::vector<int>& vec, int low, int high) {
    int pivot = vec[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (vec[j] < pivot) {
            i++;
            std::swap(vec[i], vec[j]);
        }
    }
    std::swap(vec[i + 1], vec[high]);
    return i + 1;
}

void quickSort(std::vector<int>& vec, int low, int high) {
    if (low < high) {
        int pi = partition(vec, low, high);
        quickSort(vec, low, pi - 1);
        quickSort(vec, pi + 1, high);
    }
}

// Merge Sort Implementation
void merge(std::vector<int>& vec, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    std::vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++) {
        L[i] = vec[left + i];
    }
    for (int i = 0; i < n2; i++) {
        R[i] = vec[mid + 1 + i];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            vec[k] = L[i];
            i++;
        } else {
            vec[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        vec[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        vec[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(std::vector<int>& vec, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(vec, left, mid);
        mergeSort(vec, mid + 1, right);
        merge(vec, left, mid, right);
    }
}

// Standard Library Sort (for comparison)
void standardSort(std::vector<int>& vec) {
    std::sort(vec.begin(), vec.end());
}

int main() {
    srand(time(0));
    const int SIZE = 1000;
    
    std::vector<int> vec = generateRandomVector(SIZE);

    // Measure and compare execution time of Bubble Sort
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<int> bubbleVec = vec;
    bubbleSort(bubbleVec);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> bubbleDuration = end - start;
    std::cout << "Bubble Sort Time: " << bubbleDuration.count() << " seconds\n";

    // Measure and compare execution time of Selection Sort
    start = std::chrono::high_resolution_clock::now();
    std::vector<int> selectionVec = vec;
    selectionSort(selectionVec);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> selectionDuration = end - start;
    std::cout << "Selection Sort Time: " << selectionDuration.count() << " seconds\n";

    // Measure and compare execution time of Insertion Sort
    start = std::chrono::high_resolution_clock::now();
    std::vector<int> insertionVec = vec;
    insertionSort(insertionVec);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> insertionDuration = end - start;
    std::cout << "Insertion Sort Time: " << insertionDuration.count() << " seconds\n";

    // Measure and compare execution time of Quick Sort
    start = std::chrono::high_resolution_clock::now();
    std::vector<int> quickVec = vec;
    quickSort(quickVec, 0, SIZE - 1);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> quickDuration = end - start;
    std::cout << "Quick Sort Time: " << quickDuration.count() << " seconds\n";

    // Measure and compare execution time of Merge Sort
    start = std::chrono::high_resolution_clock::now();
    std::vector<int> mergeVec = vec;
    mergeSort(mergeVec, 0, SIZE - 1);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> mergeDuration = end - start;
    std::cout << "Merge Sort Time: " << mergeDuration.count() << " seconds\n";

    // Measure and compare execution time of C++ Standard Sort
    start = std::chrono::high_resolution_clock::now();
    std::vector<int> standardVec = vec;
    standardSort(standardVec);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> standardDuration = end - start;
    std::cout << "Standard Sort Time: " << standardDuration.count() << " seconds\n";

    return 0;
}
