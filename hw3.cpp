#include <iostream>
#include <vector>
#include <stack>

using namespace std;

vector<int> canSeePersonsCount(const vector<int>& heights) {
    int n = heights.size();
    vector<int> answer(n, 0); // Initialize the result array with zeros
    stack<int> stk; // Stack to store the indices of people

    // Iterate from the end of the array to the start
    for (int i = n - 1; i >= 0; --i) {
        // Count of people the current person can see
        int count = 0;
        while (!stk.empty() && heights[i] > heights[stk.top()]) {
            stk.pop();
            count++;
        }
        // If there's still a person left on the stack, this person can also be seen
        if (!stk.empty()) {
            count++;
        }
        // Update the answer for the current person
        answer[i] = count;
        // Push the current index onto the stack
        stk.push(i);
    }
    return answer;
}

int main() {
    int n;
    cout << "\n Enter the number of people: ";
    cin >> n;

    vector<int> heights(n);
    cout << "Enter the heights of the people: ";
    for (int i = 0; i < n; ++i) {
        cin >> heights[i];
    }

    vector<int> result = canSeePersonsCount(heights);

    cout << "Number of people each person can see: ";
    for (int num : result) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
