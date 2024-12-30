// STT:02
// Full Name: NGUYEN TRAN CHI DUC
// STUDENT ID: 20521199
// CLASS: CS4343.P11.CTTT

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>

using namespace std;

// Define a point structure
struct Point {
    double x, y;
    
    Point(double x, double y) : x(x), y(y) {}
};

// Utility function to calculate Euclidean distance between two points
double distance(const Point &p1, const Point &p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

// Comparator for sorting points by x-coordinate
bool compareX(const Point &p1, const Point &p2) {
    return p1.x < p2.x;
}

// Comparator for sorting points by y-coordinate
bool compareY(const Point &p1, const Point &p2) {
    return p1.y < p2.y;
}

// Brute force method to find the closest pair of points in a small set of points
double bruteForce(vector<Point> &points) {
    double minDist = numeric_limits<double>::infinity();
    for (size_t i = 0; i < points.size(); ++i) {
        for (size_t j = i + 1; j < points.size(); ++j) {
            minDist = min(minDist, distance(points[i], points[j]));
        }
    }
    return minDist;
}

// Helper function to find the closest pair in a strip
double stripClosest(vector<Point> &strip, double d) {
    double minDist = d;
    
    // Check points in the strip and only those that are close enough to the dividing line
    for (size_t i = 0; i < strip.size(); ++i) {
        for (size_t j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < minDist; ++j) {
            minDist = min(minDist, distance(strip[i], strip[j]));
        }
    }
    
    return minDist;
}

// Recursive function to find the closest pair of points
double closestPairRecursive(vector<Point> &pointsX, vector<Point> &pointsY) {
    size_t n = pointsX.size();
    if (n <= 3) {
        return bruteForce(pointsX); // Base case: if 3 or fewer points, use brute force
    }

    size_t mid = n / 2;
    Point midPoint = pointsX[mid];

    // Divide the points into two halves
    vector<Point> leftY, rightY;
    for (const auto &p : pointsY) {
        if (p.x <= midPoint.x) {
            leftY.push_back(p);
        } else {
            rightY.push_back(p);
        }
    }

    // Recursively find the closest pair in the left and right halves
    double leftDist = closestPairRecursive(pointsX, leftY);
    double rightDist = closestPairRecursive(pointsX, rightY);
    double d = min(leftDist, rightDist); // Minimum distance from left and right halves

    // Now check the strip (points near the dividing line)
    vector<Point> strip;
    for (const auto &p : pointsY) {
        if (abs(p.x - midPoint.x) < d) {
            strip.push_back(p);
        }
    }

    // Check the closest pair in the strip
    return min(d, stripClosest(strip, d));
}

// Main function to find the closest pair of points
double closestPair(vector<Point> &points) {
    if (points.size() < 2) return 0.0;

    // Sort points by x and y coordinates
    vector<Point> pointsX = points, pointsY = points;
    sort(pointsX.begin(), pointsX.end(), compareX);
    sort(pointsY.begin(), pointsY.end(), compareY);

    return closestPairRecursive(pointsX, pointsY);
}

int main() {
    int n;
    cout << "Enter the number of points: ";
    cin >> n;
    
    vector<Point> points;
    cout << "Enter the points (x y):\n";
    for (int i = 0; i < n; ++i) {
        double x, y;
        cin >> x >> y;
        points.push_back(Point(x, y));
    }

    double minDist = closestPair(points);
    cout << "The smallest distance between any two points is: " << minDist << endl;

    return 0;
}
