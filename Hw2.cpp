#include <iostream>
#include <vector>
#include <string>
#include <stack>

class BrowserHistory {
private:
    std::stack<std::string> backStack;   // History for going back
    std::stack<std::string> forwardStack; // History for going forward
    std::string current;                   // Current URL

public:
    // Constructor
    BrowserHistory(std::string homepage) {
        current = homepage;
    }

    // Visit a new URL
    void visit(std::string url) {
        backStack.push(current); // Push current URL to the back stack
        current = url;           // Update current URL
        while (!forwardStack.empty()) {
            forwardStack.pop();  // Clear forward history
        }
    }

    // Go back a number of steps
    std::string back(int steps) {
        while (steps > 0 && !backStack.empty()) {
            forwardStack.push(current); // Push current URL to the forward stack
            current = backStack.top();   // Get the URL from the back stack
            backStack.pop();              // Remove the URL from the back stack
            steps--;
        }
        return current; // Return current URL
    }

    // Go forward a number of steps
    std::string forward(int steps) {
        while (steps > 0 && !forwardStack.empty()) {
            backStack.push(current);      // Push current URL to the back stack
            current = forwardStack.top();  // Get the URL from the forward stack
            forwardStack.pop();             // Remove the URL from the forward stack
            steps--;
        }
        return current; // Return current URL
    }

    // Get the current URL
    std::string getCurrent() {
        return current;
    }
};

// Main function
int main() {
    std::string homepage;
    std::cout << "Enter homepage URL: ";
    std::cin >> homepage;
    
    BrowserHistory browser(homepage);
    
    while (true) {
        std::string command;
        std::cout << "Enter command (visit, back <steps>, forward <steps>, exit): ";
        std::cin.ignore(); // Clear the newline character from the input buffer
        std::getline(std::cin, command); // Read command from user

        if (command == "exit") {
            break; // Exit the loop
        }

        if (command.find("visit") == 0) {
        std::string url = command.substr(6); // Get URL after "visit "
        browser.visit(url);
        std::cout << "Visited: " << url << std::endl; // In thông báo cho lệnh visit
        }

        else if (command.find("back") == 0) {
            int steps = std::stoi(command.substr(5)); // Get the number of steps
            std::string currentUrl = browser.back(steps);
            std::cout << "Back to: " << currentUrl << std::endl;
        } 
        else if (command.find("forward") == 0) {
            int steps = std::stoi(command.substr(7)); // Get the number of steps
            std::string currentUrl = browser.forward(steps);
            std::cout << "Forward to: " << currentUrl << std::endl;
        }
        
        std::cout << "Current URL: " << browser.getCurrent() << std::endl;
    }

    return 0;
}
