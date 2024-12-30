// STT:02
// Full Name: NGUYEN TRAN CHI DUC
// STUDENT ID: 20521199
// CLASS: CS4343.P11.CTTT

#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;

// Define a point in a k-dimensional space
struct Point {
    vector<double> coordinates;
    
    Point(int k) : coordinates(k) {}

    // Calculate the Euclidean distance between two points
    double distanceTo(const Point& other) const {
        double dist = 0.0;
        for (size_t i = 0; i < coordinates.size(); ++i) {
            dist += (coordinates[i] - other.coordinates[i]) * (coordinates[i] - other.coordinates[i]);
        }
        return sqrt(dist);
    }
};

// K-D Tree Node
struct KDTreeNode {
    Point point;
    KDTreeNode* left;
    KDTreeNode* right;
    
    KDTreeNode(const Point& p) : point(p), left(nullptr), right(nullptr) {}
};

// K-D Tree Class
class KDTree {
private:
    KDTreeNode* root;
    int k;  // Number of dimensions
    
    // Helper function to insert a point in the tree
    KDTreeNode* insertRec(KDTreeNode* node, Point& point, int depth) {
        if (node == nullptr) {
            return new KDTreeNode(point);
        }

        int axis = depth % k;  // Alternate between axes
        if (point.coordinates[axis] < node->point.coordinates[axis]) {
            node->left = insertRec(node->left, point, depth + 1);
        } else {
            node->right = insertRec(node->right, point, depth + 1);
        }

        return node;
    }

    // Helper function for nearest neighbor search
    void nearestNeighborRec(KDTreeNode* node, const Point& target, int depth, KDTreeNode*& best, double& bestDist) {
        if (node == nullptr) return;

        double dist = node->point.distanceTo(target);
        if (dist < bestDist) {
            bestDist = dist;
            best = node;
        }

        int axis = depth % k;
        KDTreeNode* nextNode = nullptr;
        KDTreeNode* otherNode = nullptr;

        if (target.coordinates[axis] < node->point.coordinates[axis]) {
            nextNode = node->left;
            otherNode = node->right;
        } else {
            nextNode = node->right;
            otherNode = node->left;
        }

        nearestNeighborRec(nextNode, target, depth + 1, best, bestDist);

        if (abs(target.coordinates[axis] - node->point.coordinates[axis]) < bestDist) {
            nearestNeighborRec(otherNode, target, depth + 1, best, bestDist);
        }
    }

public:
    // Constructor
    KDTree(int dimensions) : root(nullptr), k(dimensions) {}

    // Insert a point into the tree
    void insert(Point& point) {
        root = insertRec(root, point, 0);
    }

    // Nearest neighbor search
    Point nearestNeighbor(const Point& target) {
        KDTreeNode* bestNode = nullptr;
        double bestDist = std::numeric_limits<double>::infinity();
        nearestNeighborRec(root, target, 0, bestNode, bestDist);
        return bestNode->point;
    }
};

int main() {
    int k;  // Number of dimensions
    cout << "Enter the number of dimensions (k): ";
    cin >> k;

    KDTree tree(k);

    int n;  // Number of points to insert
    cout << "Enter the number of points to insert: ";
    cin >> n;

    // Insert points into the tree
    for (int i = 0; i < n; ++i) {
        Point p(k);
        cout << "Enter coordinates for point " << i + 1 << ": ";
        for (int j = 0; j < k; ++j) {
            cin >> p.coordinates[j];
        }
        tree.insert(p);
    }

    // Query point for nearest neighbor search
    Point target(k);
    cout << "Enter coordinates for the query point: ";
    for (int j = 0; j < k; ++j) {
        cin >> target.coordinates[j];
    }

    // Nearest neighbor search
    Point nearest = tree.nearestNeighbor(target);

    // Output the nearest point
    cout << "Nearest point to (";
    for (int i = 0; i < k; ++i) {
        cout << target.coordinates[i];
        if (i != k - 1) cout << ", ";
    }
    cout << ") is (";
    for (int i = 0; i < k; ++i) {
        cout << nearest.coordinates[i];
        if (i != k - 1) cout << ", ";
    }
    cout << ")\n";

    return 0;
}
