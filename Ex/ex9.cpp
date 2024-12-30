#include <iostream>
#include <vector>
#include <cmath>

struct Point {
    double x, y;

    // Default constructor
    Point() : x(0), y(0) {}

    // Constructor with parameters
    Point(double x, double y) : x(x), y(y) {}

    // Function to calculate the distance from the origin
    double distanceFromOrigin() const {
        return std::sqrt(x * x + y * y);
    }
};

void bubbleSort(std::vector<Point>& points) {
    int n = points.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (points[j].distanceFromOrigin() > points[j + 1].distanceFromOrigin()) {
                std::swap(points[j], points[j + 1]);
            }
        }
    }
}

void merge(std::vector<Point>& points, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    std::vector<Point> L(n1), R(n2);

    for (int i = 0; i < n1; ++i)
        L[i] = points[left + i];
    for (int i = 0; i < n2; ++i)
        R[i] = points[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i].distanceFromOrigin() <= R[j].distanceFromOrigin()) {
            points[k] = L[i];
            ++i;
        } else {
            points[k] = R[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        points[k] = L[i];
        ++i;
        ++k;
    }
    while (j < n2) {
        points[k] = R[j];
        ++j;
        ++k;
    }
}

void mergeSort(std::vector<Point>& points, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(points, left, mid);
        mergeSort(points, mid + 1, right);
        merge(points, left, mid, right);
    }
}

int partition(std::vector<Point>& points, int low, int high) {
    double pivot = points[high].distanceFromOrigin();
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if (points[j].distanceFromOrigin() <= pivot) {
            ++i;
            std::swap(points[i], points[j]);
        }
    }

    std::swap(points[i + 1], points[high]);
    return i + 1;
}

void quickSort(std::vector<Point>& points, int low, int high) {
    if (low < high) {
        int pi = partition(points, low, high);
        quickSort(points, low, pi - 1);
        quickSort(points, pi + 1, high);
    }
}

int main() {
    int n;
    std::cout << "Enter the number of points: ";
    std::cin >> n;

    std::vector<Point> points;

    // Input the points from the user
    for (int i = 0; i < n; ++i) {
        double x, y;
        std::cout << "Enter x and y coordinates for point " << i + 1 << ": ";
        std::cin >> x >> y;
        points.push_back(Point(x, y));
    }

    std::cout << "\nOriginal points:\n";
    for (const auto& p : points) {
        std::cout << "(" << p.x << ", " << p.y << ") ";
    }
    std::cout << "\n";

    // Apply sorting algorithms
    // Uncomment one of the following to test different algorithms:

    // bubbleSort(points);  // Bubble Sort
    // mergeSort(points, 0, points.size() - 1);  // Merge Sort
    quickSort(points, 0, points.size() - 1);  // Quick Sort

    std::cout << "\nSorted points by distance from origin:\n";
    for (const auto& p : points) {
        std::cout << "(" << p.x << ", " << p.y << ") ";
    }
    std::cout << "\n";

    return 0;
}
