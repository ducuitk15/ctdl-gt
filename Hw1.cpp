#include <iostream>
#include <string>

struct Node {
    std::string songName; // Name of the song
    Node* next;           // Pointer to the next song
    Node* prev;           // Pointer to the previous song

    Node(std::string name) : songName(name), next(nullptr), prev(nullptr) {} // Constructor
};

class Playlist {
private:
    Node* head;    // Head of the list
    Node* tail;    // Tail of the list
    Node* current; // Currently playing song

public:
    Playlist() : head(nullptr), tail(nullptr), current(nullptr) {} // Initialize empty playlist

    // Add a song to the end of the playlist
    void addSong(const std::string& songName) {
        Node* newNode = new Node(songName); // Create a new node
        if (!head) { // If the playlist is empty
            head = newNode;
            tail = newNode;
            current = newNode; // The current song is the first one
        } else {
            tail->next = newNode; // Link the new song at the end
            newNode->prev = tail;  // Update previous pointer
            tail = newNode; // Update tail
        }
    }

    // Move to the next song
    void playNext() {
        if (current) {
            current = current->next ? current->next : head; // Loop to the first song
        }
    }

    // Move to the previous song
    void playPrevious() {
        if (current) {
            current = current->prev ? current->prev : tail; // Loop to the last song
        }
    }

    // Remove a song by name
    void removeSong(const std::string& songName) {
        Node* temp = head;
        while (temp) {
            if (temp->songName == songName) { // Find the song
                // Update pointers of the previous and next nodes
                if (temp->prev) {
                    temp->prev->next = temp->next;
                } else {
                    head = temp->next; // If removing the head
                }
                if (temp->next) {
                    temp->next->prev = temp->prev;
                } else {
                    tail = temp->prev; // If removing the tail
                }
                if (current == temp) {
                    current = temp->next ? temp->next : head; // Update current song if needed
                }
                delete temp; // Free memory
                return;
            }
            temp = temp->next; // Move to the next song
        }
        std::cout << "Song not found." << std::endl; // Notify if the song is not found
    }

    // Display the playlist
    void displayPlaylist() const {
        Node* temp = head; // Start from the head of the list
        if (!temp) {
            std::cout << "Playlist is empty." << std::endl; // Notify if the playlist is empty
            return;
        }
        while (temp) {
            std::cout << temp->songName << " "; // Print song name
            temp = temp->next; // Move to the next song
        }
        std::cout << std::endl; // New line after displaying
    }
};

int main() {
    Playlist playlist; // Create a new playlist
    int n;
    std::cout << "There are 6 operations." << std::endl;
    std::cout << "ADD <song name> to add a song." << std::endl;
    std::cout << "NEXT to move to the next song." << std::endl;
    std::cout << "PREV to go back to the previous song." << std::endl;
    std::cout << "REMOVE <song name> to remove a song." << std::endl;
    std::cout << "DISPLAY to show the current playlist." << std::endl;
    std::cout << "Enter the number of operations: "; // Prompt to enter the number of operations
    std::cin >> n; // Input number of operations
    std::cin.ignore(); // Ignore newline character

    std::cout << "Then, enter operations in the following format:" << std::endl;
    std::cout << "ADD <song name> to add a song." << std::endl;
    std::cout << "NEXT to move to the next song." << std::endl;
    std::cout << "PREV to go back to the previous song." << std::endl;
    std::cout << "REMOVE <song name> to remove a song." << std::endl;
    std::cout << "DISPLAY to show the current playlist." << std::endl;

    for (int i = 0; i < n; ++i) {
        std::string command;
        std::getline(std::cin, command); // Read command from user

        if (command.substr(0, 4) == "ADD ") {
            std::string songName = command.substr(4); // Extract song name
            playlist.addSong(songName); // Add song
        } else if (command == "NEXT") {
            playlist.playNext(); // Move to the next song
        } else if (command == "PREV") {
            playlist.playPrevious(); // Go back to the previous song
        } else if (command.substr(0, 7) == "REMOVE ") {
            std::string songName = command.substr(7); // Extract song name to remove
            playlist.removeSong(songName); // Remove song
        } else if (command == "DISPLAY") {
            playlist.displayPlaylist(); // Display current playlist
        }
    }

    return 0; // End the program
}
