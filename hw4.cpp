#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int minCoinsToBuyAllFruits(vector<int>& prices) {
    int n = prices.size();
    int total_cost = 0;
    int i = 0;

    while (i < n) {
        // Buy the current fruit and add its price to the total cost
        total_cost += prices[i];
        // Move the pointer by (i + 1) positions to skip the fruits you can take for free
        i += (i + 1);
    }

    return total_cost;
}

int main() {
    int n;
    cout << "\n Enter the number of fruits: ";
    cin >> n;

    vector<int> prices(n);
    cout << "\n Enter the prices of the fruits: ";
    for (int i = 0; i < n; ++i) {
        cin >> prices[i];
    }

    int result = minCoinsToBuyAllFruits(prices);
    cout << "The minimum number of coins required: " << result << endl;

    return 0;
}
