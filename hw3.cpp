// STT:02
// Full Name: NGUYEN TRAN CHI DUC
// STUDENT ID: 20521199
// CLASS: CS4343.P11.CTTT

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <cstdlib>
#include <ctime>

// Simulate searching a resource in a node (random success/failure)
bool searchInNode(int nodeID) {
    // Simulate a failure (80% failure rate) for the sake of the example
    return (rand() % 10) < 2;  // 20% chance of success
}

// Exponential backoff search function
bool searchWithExponentialBackoff(const std::vector<int>& nodes, int maxRetries, int baseDelayMs) {
    int attemptCount = 0;
    bool success = false;

    while (attemptCount < maxRetries) {
        for (int nodeID : nodes) {
            std::cout << "Searching node " << nodeID << " (attempt " << attemptCount + 1 << ")...\n";
            
            // Attempt to search the node
            if (searchInNode(nodeID)) {
                std::cout << "Found resource at node " << nodeID << "!\n";
                success = true;
                break;
            } else {
                std::cout << "Search failed at node " << nodeID << ". Retrying...\n";
            }
        }
        
        // If success is found, exit
        if (success) {
            break;
        }

        // Exponential backoff delay calculation
        int delay = baseDelayMs * (1 << attemptCount);  // 2^attemptCount
        std::cout << "Retrying after " << delay << "ms...\n";
        
        // Sleep for the calculated delay
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        
        // Increment the attempt count
        attemptCount++;
    }
    
    return success;
}

int main() {
    // Seed the random number generator for simulating search success/failure
    srand(time(0));

    // Simulated nodes in the distributed system
    std::vector<int> nodes = {1, 2, 3, 4, 5};

    // Set the parameters for the exponential backoff search
    int maxRetries = 5;      // Maximum number of retries
    int baseDelayMs = 100;   // Base delay in milliseconds before the first retry

    // Call the exponential backoff search
    bool result = searchWithExponentialBackoff(nodes, maxRetries, baseDelayMs);

    if (result) {
        std::cout << "Search completed successfully.\n";
    } else {
        std::cout << "Search failed after " << maxRetries << " attempts.\n";
    }

    return 0;
}
