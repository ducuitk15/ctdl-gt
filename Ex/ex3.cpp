#include <iostream>
#include <string>
using namespace std;

// Template for Bubble Sort
template <typename T>
void bubbleSort(T arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Template for Selection Sort
template <typename T>
void selectionSort(T arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        swap(arr[i], arr[minIdx]);
    }
}

// Template for Insertion Sort
template <typename T>
void insertionSort(T arr[], int n) {
    for (int i = 1; i < n; i++) {
        T key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Print array
template <typename T>
void printArray(T arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    // Test with integers
    int intArr[] = {5, 2, 9, 1, 5, 6};
    int intSize = sizeof(intArr) / sizeof(intArr[0]);
    cout << "Original integer array: ";
    printArray(intArr, intSize);
    
    // Bubble Sort with integers
    bubbleSort(intArr, intSize);
    cout << "Sorted integer array (Bubble Sort): ";
    printArray(intArr, intSize);
    
    // Selection Sort with integers
    selectionSort(intArr, intSize);
    cout << "Sorted integer array (Selection Sort): ";
    printArray(intArr, intSize);
    
    // Insertion Sort with integers
    insertionSort(intArr, intSize);
    cout << "Sorted integer array (Insertion Sort): ";
    printArray(intArr, intSize);

    // Test with floating-point numbers
    float floatArr[] = {5.5, 2.2, 9.9, 1.1, 5.5};
    int floatSize = sizeof(floatArr) / sizeof(floatArr[0]);
    cout << "Original float array: ";
    printArray(floatArr, floatSize);
    
    // Bubble Sort with floats
    bubbleSort(floatArr, floatSize);
    cout << "Sorted float array (Bubble Sort): ";
    printArray(floatArr, floatSize);
    
    // Selection Sort with floats
    selectionSort(floatArr, floatSize);
    cout << "Sorted float array (Selection Sort): ";
    printArray(floatArr, floatSize);
    
    // Insertion Sort with floats
    insertionSort(floatArr, floatSize);
    cout << "Sorted float array (Insertion Sort): ";
    printArray(floatArr, floatSize);

    // Test with strings
    string strArr[] = {"banana", "apple", "cherry", "date"};
    int strSize = sizeof(strArr) / sizeof(strArr[0]);
    cout << "Original string array: ";
    printArray(strArr, strSize);
    
    // Bubble Sort with strings
    bubbleSort(strArr, strSize);
    cout << "Sorted string array (Bubble Sort): ";
    printArray(strArr, strSize);
    
    // Selection Sort with strings
    selectionSort(strArr, strSize);
    cout << "Sorted string array (Selection Sort): ";
    printArray(strArr, strSize);
    
    // Insertion Sort with strings
    insertionSort(strArr, strSize);
    cout << "Sorted string array (Insertion Sort): ";
    printArray(strArr, strSize);

    return 0;
}
