#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <ctime>
#include <iomanip>

using namespace std;

// Define a structure to represent a social media post
struct Post {
    string content;
    int likes;
    int shares;
    int comments;
    time_t timestamp;

    // Constructor
    Post(string c, int l, int s, int cm, time_t t)
        : content(c), likes(l), shares(s), comments(cm), timestamp(t) {}
};

// Helper function to parse the timestamp in "YYYY-MM-DD HH:MM:SS" format
time_t parseTimestamp(const string &timestampStr) {
    struct tm tm = {};
    istringstream ss(timestampStr);
    ss >> get_time(&tm, "%Y-%m-%d %H:%M:%S");
    if (ss.fail()) {
        throw invalid_argument("Invalid timestamp format: " + timestampStr);
    }
    return mktime(&tm);
}

// Comparator function to sort posts based on engagement and time
bool sortPosts(const Post &a, const Post &b) {
    int engagementA = a.likes + a.shares + a.comments;
    int engagementB = b.likes + b.shares + b.comments;
    if (engagementA != engagementB) {
        return engagementA > engagementB; // Higher engagement first
    }
    return a.timestamp > b.timestamp; // More recent first
}

// Function to read posts from a CSV file
vector<Post> readPostsFromCSV(const string &filename) {
    vector<Post> posts;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return posts;
    }

    string line, content;
    int likes, shares, comments;
    time_t timestamp;

    // Skip the header line
    getline(file, line);

    // Read each line
    while (getline(file, line)) {
        stringstream ss(line);
        string likesStr, sharesStr, commentsStr, timestampStr;

        // Parse CSV line
        getline(ss, content, ',');
        getline(ss, likesStr, ',');
        getline(ss, sharesStr, ',');
        getline(ss, commentsStr, ',');
        getline(ss, timestampStr, ',');

        try {
            // Validate and convert strings to appropriate data types
            likes = !likesStr.empty() && isdigit(likesStr[0]) ? stoi(likesStr) : 0;
            shares = !sharesStr.empty() && isdigit(sharesStr[0]) ? stoi(sharesStr) : 0;
            comments = !commentsStr.empty() && isdigit(commentsStr[0]) ? stoi(commentsStr) : 0;
            timestamp = parseTimestamp(timestampStr);

            // Add post to the vector
            posts.emplace_back(content, likes, shares, comments, timestamp);
        } catch (const exception &e) {
            cerr << "Invalid data in line: " << line << " (" << e.what() << ")" << endl;
        }
    }

    file.close();
    return posts;
}

int main() {
    string filename = "social_media_data.csv";
    vector<Post> posts = readPostsFromCSV(filename);

    if (posts.empty()) {
        cout << "No posts to display." << endl;
        return 1;
    }

    // Sort posts based on the comparator
    sort(posts.begin(), posts.end(), sortPosts);

    // Display the sorted feed
    cout << "Sorted Social Media Feed:" << endl;
    for (const auto &post : posts) {
        cout << "Content: " << post.content << endl;
        cout << "Likes: " << post.likes
             << ", Shares: " << post.shares
             << ", Comments: " << post.comments << endl;
        cout << "Posted: " << ctime(&post.timestamp);
        cout << "--------------------------------------" << endl;
    }

    return 0;
}
