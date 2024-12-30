#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <chrono>

// Product structure
struct Product {
    std::string name;
    double price;
    double rating;
    int popularity;

    Product(const std::string& n, double p, double r, int pop)
        : name(n), price(p), rating(r), popularity(pop) {}
};

// Quick Sort
void quickSort(std::vector<Product>& products, int low, int high, auto comparator) {
    if (low < high) {
        int pivotIndex = partition(products, low, high, comparator);
        quickSort(products, low, pivotIndex - 1, comparator);
        quickSort(products, pivotIndex + 1, high, comparator);
    }
}

int partition(std::vector<Product>& products, int low, int high, auto comparator) {
    Product pivot = products[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (comparator(products[j], pivot)) {
            ++i;
            std::swap(products[i], products[j]);
        }
    }
    std::swap(products[i + 1], products[high]);
    return i + 1;
}

// Bubble Sort (for comparison)
void bubbleSort(std::vector<Product>& products, auto comparator) {
    size_t n = products.size();
    for (size_t i = 0; i < n - 1; ++i) {
        for (size_t j = 0; j < n - i - 1; ++j) {
            if (!comparator(products[j], products[j + 1])) {
                std::swap(products[j], products[j + 1]);
            }
        }
    }
}

// Comparator functions
bool compareByPrice(const Product& a, const Product& b) {
    return a.price < b.price; // Ascending
}

bool compareByRating(const Product& a, const Product& b) {
    return a.rating > b.rating; // Descending
}

bool compareByPopularity(const Product& a, const Product& b) {
    return a.popularity > b.popularity; // Descending
}

// Read products from CSV file
std::vector<Product> readDataset(const std::string& filename) {
    std::vector<Product> products;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << "\n";
        return products;
    }

    std::string line;
    // Skip header
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string name;
        double price = 0, rating = 0;
        int popularity = 0;

        std::getline(ss, name, ',');
        ss >> price;
        ss.ignore(1); // Ignore the comma
        ss >> rating;
        ss.ignore(1); // Ignore the comma
        ss >> popularity;

        products.emplace_back(name, price, rating, popularity);
    }
    return products;
}

// Measure performance of sorting
template <typename Func>
void measurePerformance(Func sortFunction, std::vector<Product>& products, const std::string& sortType) {
    auto start = std::chrono::high_resolution_clock::now();
    sortFunction(products);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << sortType << " took " << duration.count() << " seconds.\n";
}

int main() {
    // Dataset path
    std::string datasetPath = "dataset.csv"; // Replace with your dataset path

    // Load products
    std::vector<Product> products = readDataset(datasetPath);
    if (products.empty()) {
        std::cerr << "No products loaded. Exiting.\n";
        return 1;
    }

    // Display initial data
    std::cout << "Loaded " << products.size() << " products.\n";

    // Create copies for different sorts
    auto quickSortProducts = products;
    auto bubbleSortProducts = products;

    // Measure performance of Quick Sort by price
    measurePerformance([&](std::vector<Product>& data) {
        quickSort(data, 0, data.size() - 1, compareByPrice);
    }, quickSortProducts, "Quick Sort by Price");

    // Measure performance of Bubble Sort by price
    measurePerformance([&](std::vector<Product>& data) {
        bubbleSort(data, compareByPrice);
    }, bubbleSortProducts, "Bubble Sort by Price");

    // Display sorted products (Quick Sort by price example)
    std::cout << "Top 5 products sorted by price:\n";
    for (size_t i = 0; i < 5 && i < quickSortProducts.size(); ++i) {
        const auto& p = quickSortProducts[i];
        std::cout << "Name: " << p.name << ", Price: " << p.price
                  << ", Rating: " << p.rating << ", Popularity: " << p.popularity << "\n";
    }

    return 0;
}
