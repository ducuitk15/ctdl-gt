//STT: 2
//Name: Nguyễn Trần Chí Đức
//MSSV: 20521199

#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <climits>
using namespace std;

// Node structure for the binary tree
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int value) : val(value), left(nullptr), right(nullptr) {}
};

class BinaryTree {
protected:
    TreeNode* root;

    void preOrder(TreeNode* node, vector<int>& result) {
        if (!node) return;
        result.push_back(node->val);
        preOrder(node->left, result);
        preOrder(node->right, result);
    }

    void inOrder(TreeNode* node, vector<int>& result) {
        if (!node) return;
        inOrder(node->left, result);
        result.push_back(node->val);
        inOrder(node->right, result);
    }

    void postOrder(TreeNode* node, vector<int>& result) {
        if (!node) return;
        postOrder(node->left, result);
        postOrder(node->right, result);
        result.push_back(node->val);
    }

    int calculateHeight(TreeNode* node) {
        if (!node) return 0;
        return 1 + max(calculateHeight(node->left), calculateHeight(node->right));
    }

    int calculateDiameter(TreeNode* node, int& maxDiameter) {
        if (!node) return 0;
        int leftHeight = calculateDiameter(node->left, maxDiameter);
        int rightHeight = calculateDiameter(node->right, maxDiameter);
        maxDiameter = max(maxDiameter, leftHeight + rightHeight);
        return 1 + max(leftHeight, rightHeight);
    }

    bool isBalanced(TreeNode* node) {
        if (!node) return true;
        int leftHeight = calculateHeight(node->left);
        int rightHeight = calculateHeight(node->right);
        return abs(leftHeight - rightHeight) <= 1 && isBalanced(node->left) && isBalanced(node->right);
    }

    TreeNode* findLCA(TreeNode* node, int p, int q) {
        if (!node || node->val == p || node->val == q) return node;
        TreeNode* left = findLCA(node->left, p, q);
        TreeNode* right = findLCA(node->right, p, q);
        if (left && right) return node;
        return left ? left : right;
    }

    void verticalOrderTraversal(TreeNode* node, int hd, map<int, vector<int>>& result) {
        if (!node) return;
        result[hd].push_back(node->val);
        verticalOrderTraversal(node->left, hd - 1, result);
        verticalOrderTraversal(node->right, hd + 1, result);
    }

    TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
        if (!t1) return t2;
        if (!t2) return t1;
        t1->val += t2->val;
        t1->left = mergeTrees(t1->left, t2->left);
        t1->right = mergeTrees(t1->right, t2->right);
        return t1;
    }

public:
    BinaryTree() : root(nullptr) {}

    void insert(int value) {
        if (!root) {
            root = new TreeNode(value);
            return;
        }
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            TreeNode* current = q.front();
            q.pop();
            if (!current->left) {
                current->left = new TreeNode(value);
                break;
            } else {
                q.push(current->left);
            }
            if (!current->right) {
                current->right = new TreeNode(value);
                break;
            } else {
                q.push(current->right);
            }
        }
    }

    vector<int> preOrderTraversal() {
        vector<int> result;
        preOrder(root, result);
        return result;
    }

    vector<int> inOrderTraversal() {
        vector<int> result;
        inOrder(root, result);
        return result;
    }

    vector<int> postOrderTraversal() {
        vector<int> result;
        postOrder(root, result);
        return result;
    }

    vector<vector<int>> levelOrderTraversal() {
        vector<vector<int>> result;
        if (!root) return result;
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            int size = q.size();
            vector<int> level;
            for (int i = 0; i < size; ++i) {
                TreeNode* current = q.front();
                q.pop();
                level.push_back(current->val);
                if (current->left) q.push(current->left);
                if (current->right) q.push(current->right);
            }
            result.push_back(level);
        }
        return result;
    }

    int height() {
        return calculateHeight(root);
    }

    int diameter() {
        int maxDiameter = 0;
        calculateDiameter(root, maxDiameter);
        return maxDiameter;
    }

    bool isHeightBalanced() {
        return isBalanced(root);
    }

    int lowestCommonAncestor(int p, int q) {
        TreeNode* lca = findLCA(root, p, q);
        return lca ? lca->val : -1;
    }

    vector<vector<int>> verticalOrderTraversal() {
        map<int, vector<int>> result;
        verticalOrderTraversal(root, 0, result);
        vector<vector<int>> vertical;
        for (auto& pair : result) {
            vertical.push_back(pair.second);
        }
        return vertical;
    }

    void mergeWith(BinaryTree& other) {
        root = mergeTrees(root, other.root);
    }
};

int main() {
    BinaryTree tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);
    tree.insert(6);
    tree.insert(7);

    BinaryTree tree2;
    tree2.insert(1);
    tree2.insert(3);
    tree2.insert(2);
    tree2.insert(5);
    tree2.insert(4);

    // Merge two trees
    tree.mergeWith(tree2);

    // Traversals
    vector<int> preOrder = tree.preOrderTraversal();
    vector<int> inOrder = tree.inOrderTraversal();
    vector<int> postOrder = tree.postOrderTraversal();
    vector<vector<int>> levelOrder = tree.levelOrderTraversal();

    cout << "Pre-order Traversal: ";
    for (int val : preOrder) cout << val << " ";
    cout << endl;

    cout << "In-order Traversal: ";
    for (int val : inOrder) cout << val << " ";
    cout << endl;

    cout << "Post-order Traversal: ";
    for (int val : postOrder) cout << val << " ";
    cout << endl;

    cout << "Level-order Traversal: \n";
    for (auto& level : levelOrder) {
        for (int val : level) cout << val << " ";
        cout << endl;
    }

    cout << "Tree Height: " << tree.height() << endl;
    cout << "Tree Diameter: " << tree.diameter() << endl;
    cout << "Is Height Balanced: " << (tree.isHeightBalanced() ? "Yes" : "No") << endl;

    cout << "Lowest Common Ancestor of 4 and 5: " << tree.lowestCommonAncestor(4, 5) << endl;

    vector<vector<int>> verticalOrder = tree.verticalOrderTraversal();
    cout << "Vertical Order Traversal: \n";
    for (auto& slice : verticalOrder) {
        for (int val : slice) cout << val << " ";
        cout << endl;
    }

    return 0;
}
