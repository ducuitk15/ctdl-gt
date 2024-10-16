#include <iostream>
#include <stack>
#include <vector>

using namespace std;

// Function to move disks between towers
bool moveDisk(stack<int> &source, stack<int> &destination, char s, char d) {
    if (source.empty()) {
        cout <<" Error: Source tower is empty!" << endl;
        return false;
    }
    if (!destination.empty() && source.top() > destination.top()) {
        cout << "Error: Cannot place larger disk on top of a smaller disk!" << endl;
        return false;
    }
    int disk = source.top();
    source.pop();
    destination.push(disk);
    cout << s << " -> " << d << endl;
    return true;
}

// Function to print the state of the towers
void printTowers(vector<stack<int>> &towers) {
    char towerNames[3] = {'A', 'B', 'C'};
    for (int i = 0; i < 3; ++i) {
        cout << towerNames[i] << " Tower\nSTACK = < ";
        stack<int> tempStack = towers[i];
        vector<int> tempVector;
        while (!tempStack.empty()) {
            tempVector.push_back(tempStack.top());
            tempStack.pop();
        }
        for (auto it = tempVector.rbegin(); it != tempVector.rend(); ++it) {
            cout << *it << " ";
        }
        cout << ">\n";
    }
    cout << "=========================\n";
}

// Function to handle user input and move disks accordingly
void userMove(vector<stack<int>> &towers) {
    int choice;
    while (true) {
        cout << "Choose an option:\n";
        cout << "1. A -> B\n";
        cout << "2. B -> A\n";
        cout << "3. A -> C\n";
        cout << "4. C -> A\n";
        cout << "5. B -> C\n";
        cout << "6. C -> B\n";
        cout << "Enter your choice (1-6), or 0 to quit: ";
        cin >> choice;

        bool success = false;
        switch (choice) {
            case 1:
                success = moveDisk(towers[0], towers[1], 'A', 'B');
                break;
            case 2:
                success = moveDisk(towers[1], towers[0], 'B', 'A');
                break;
            case 3:
                success = moveDisk(towers[0], towers[2], 'A', 'C');
                break;
            case 4:
                success = moveDisk(towers[2], towers[0], 'C', 'A');
                break;
            case 5:
                success = moveDisk(towers[1], towers[2], 'B', 'C');
                break;
            case 6:
                success = moveDisk(towers[2], towers[1], 'C', 'B');
                break;
            case 0:
                cout << "Exiting the game.\n";
                return;
            default:
                cout << "Invalid choice. Please choose again.\n";
        }

        if (success) {
            printTowers(towers);
        }
    }
}

int main() {
    int n;
    cout << "\n Enter the number of disks: ";
    cin >> n;

    // Create three towers as stacks
    stack<int> towerA, towerB, towerC;
    vector<stack<int>> towers = {towerA, towerB, towerC};

    // Initialize the first tower with disks in descending order
    for (int i = n; i >= 1; --i) {
        towers[0].push(i);
    }

    cout << "======== Demo Stack ========\n";
    cout << "0. Creating Tower.\n";
    printTowers(towers);

    // Allow user to make moves manually
    userMove(towers);

    return 0;
}
