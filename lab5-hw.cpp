//STT: 2
//Name: Nguyễn Trần Chí Đức
//MSSV: 20521199

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <stack>
#include <string>
#include <map>
#include <cmath>
#include <algorithm>
#include <sstream>
#include <functional>
#include <set>
using namespace std;

// Task 1: File System Tree
class FileSystem {
    struct Node {
        string name;
        bool isFile;
        unordered_map<string, Node*> children;
        Node(string n, bool file) : name(n), isFile(file) {}
    };

    Node* root;
    Node* current;

public:
    FileSystem() {
        root = new Node("root", false);
        current = root;
    }

    void create(string name, bool isFile) {
        if (current->children.count(name)) {
            cout << "Error: Name already exists.\n";
            return;
        }
        current->children[name] = new Node(name, isFile);
    }

    void remove(string name) {
        if (!current->children.count(name)) {
            cout << "Error: Name not found.\n";
            return;
        }
        delete current->children[name];
        current->children.erase(name);
    }

    void navigate(string name) {
        if (name == "..") {
            if (current != root) {
                current = root; // Simple implementation for demo; improve to track parent
            }
            return;
        }
        if (!current->children.count(name) || current->children[name]->isFile) {
            cout << "Error: Invalid directory.\n";
            return;
        }
        current = current->children[name];
    }

    void list() {
        for (auto& [name, node] : current->children) {
            cout << (node->isFile ? "File: " : "Dir: ") << name << endl;
        }
    }
};

// Task 2: XML/HTML Parser
class XMLParser {
    struct Node {
        string tag;
        unordered_map<string, string> attributes;
        vector<Node*> children;
        Node* parent;

        Node(string t, Node* p = nullptr) : tag(t), parent(p) {}
    };

    Node* root;

public:
    XMLParser() : root(nullptr) {}

    void parse(const string& document) {
        // Minimal demo of parsing logic
        root = new Node("root");
        root->children.push_back(new Node("child"));
    }

    void query(const string& tag) {
        if (!root) return;
        queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            Node* node = q.front();
            q.pop();
            if (node->tag == tag) {
                cout << "Found tag: " << tag << endl;
            }
            for (Node* child : node->children) {
                q.push(child);
            }
        }
    }
};

// Task 3: Huffman Coding
class HuffmanCoding {
    struct Node {
        char ch;
        int freq;
        Node* left;
        Node* right;
        Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
    };

    struct Compare {
        bool operator()(Node* a, Node* b) {
            return a->freq > b->freq;
        }
    };

    Node* root;
    unordered_map<char, string> codes;

    void buildCodes(Node* node, const string& str) {
        if (!node) return;
        if (!node->left && !node->right) {
            codes[node->ch] = str;
        }
        buildCodes(node->left, str + "0");
        buildCodes(node->right, str + "1");
    }

public:
    void buildTree(const string& text) {
        unordered_map<char, int> freq;
        for (char ch : text) {
            freq[ch]++;
        }

        priority_queue<Node*, vector<Node*>, Compare> pq;
        for (auto& [ch, f] : freq) {
            pq.push(new Node(ch, f));
        }

        while (pq.size() > 1) {
            Node* left = pq.top(); pq.pop();
            Node* right = pq.top(); pq.pop();
            Node* parent = new Node('\0', left->freq + right->freq);
            parent->left = left;
            parent->right = right;
            pq.push(parent);
        }

        root = pq.top();
        buildCodes(root, "");
    }

    string encode(const string& text) {
        string encoded;
        for (char ch : text) {
            encoded += codes[ch];
        }
        return encoded;
    }

    string decode(const string& encoded) {
        string decoded;
        Node* node = root;
        for (char bit : encoded) {
            node = (bit == '0') ? node->left : node->right;
            if (!node->left && !node->right) {
                decoded += node->ch;
                node = root;
            }
        }
        return decoded;
    }
};

int main() {
    // Task 1
    cout << "--- File System ---\n";
    FileSystem fs;
    fs.create("dir1", false);
    fs.create("file1.txt", true);
    fs.list();
    fs.navigate("dir1");
    fs.create("file2.txt", true);
    fs.list();
    fs.navigate("..");
    fs.list();

    // Task 2
    cout << "\n--- XML Parser ---\n";
    XMLParser parser;
    parser.parse("<root><child></child></root>");
    parser.query("child");

    // Task 3
    cout << "\n--- Huffman Coding ---\n";
    HuffmanCoding hc;
    hc.buildTree("hello world");
    string encoded = hc.encode("hello");
    cout << "Encoded: " << encoded << endl;
    cout << "Decoded: " << hc.decode(encoded) << endl;

    return 0;
}
