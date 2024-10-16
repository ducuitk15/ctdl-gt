#include <iostream>
#include <stack>
#include <string>

using namespace std;

class Browser {
private:
    stack<string> backStack;
    stack<string> forwardStack;
    string currentURL;

public:
    Browser() : currentURL("homepage") {} // Default to some initial homepage

    void visit(const string& url) {
        if (!currentURL.empty()) {
            backStack.push(currentURL);
        }
        currentURL = url;
        // Clear the forward stack when visiting a new URL
        while (!forwardStack.empty()) {
            forwardStack.pop();
        }
        cout << "Visiting: " << currentURL << endl;
    }

    void back() {
        if (backStack.empty()) {
            cout << "No previous URL to go back to!" << endl;
            return;
        }
        forwardStack.push(currentURL);
        currentURL = backStack.top();
        backStack.pop();
        cout << "Going back to: " << currentURL << endl;
    }

    void forward() {
        if (forwardStack.empty()) {
            cout << "No next URL to go forward to!" << endl;
            return;
        }
        backStack.push(currentURL);
        currentURL = forwardStack.top();
        forwardStack.pop();
        cout << "Going forward to: " << currentURL << endl;
    }

    string getCurrentURL() const {
        return currentURL;
    }
};

int main() {
    Browser browser;
    string command;
    string url;

    cout << "Browser Navigation Simulation\n";
    cout << "Commands:\n";
    cout << "1. visit <url> - Visit a new URL\n";
    cout << "2. back - Go back to the previous URL\n";
    cout << "3. forward - Go forward to the next URL\n";
    cout << "4. exit - Exit the program\n";

    while (true) {
        cout << "\nEnter command: ";
        cin >> command;

        if (command == "visit") {
            cout << "Enter URL: ";
            cin >> url;
            browser.visit(url);
        } else if (command == "back") {
            browser.back();
        } else if (command == "forward") {
            browser.forward();
        } else if (command == "exit") {
            cout << "Exiting browser simulation.\n";
            break;
        } else {
            cout << "Invalid command. Please try again.\n";
        }
    }

    return 0;
}
