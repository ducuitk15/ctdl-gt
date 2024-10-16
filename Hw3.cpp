#include <iostream>
#include <unordered_map>
#include <string>

class AuthenticationManager {
public:
    AuthenticationManager(int timeToLive) : ttl(timeToLive) {}

    void generate(const std::string& tokenId, int currentTime) {
        tokens[tokenId] = currentTime + ttl; // Lưu token với thời gian hết hạn
    }

    void renew(const std::string& tokenId, int currentTime) {
        if (tokens.find(tokenId) != tokens.end() && tokens[tokenId] > currentTime) {
            tokens[tokenId] = currentTime + ttl; // Gia hạn thời gian hết hạn
        }
    }

    int countUnexpiredTokens(int currentTime) {
        int count = 0;
        for (const auto& entry : tokens) {
            if (entry.second > currentTime) {
                count++; // Đếm token còn hiệu lực
            }
        }
        return count;
    }

private:
    int ttl; // Thời gian sống của token
    std::unordered_map<std::string, int> tokens; // Lưu token và thời gian hết hạn
};

int main() {
    int timeToLive;
    std::cout << "Nhập thời gian sống cho token (timeToLive): ";
    std::cin >> timeToLive;

    AuthenticationManager authManager(timeToLive);

    while (true) {
        std::string command;
        std::cout << "Nhập lệnh (generate, renew, count, exit): ";
        std::cin >> command;

        if (command == "exit") {
            break; // Thoát chương trình
        }

        if (command == "generate") {
            std::string tokenId;
            int currentTime;
            std::cout << "Nhập tokenId và currentTime: ";
            std::cin >> tokenId >> currentTime;
            authManager.generate(tokenId, currentTime);
            std::cout << "Token " << tokenId << " đã được tạo." << std::endl;

        } else if (command == "renew") {
            std::string tokenId;
            int currentTime;
            std::cout << "Nhập tokenId và currentTime: ";
            std::cin >> tokenId >> currentTime;
            authManager.renew(tokenId, currentTime);
            std::cout << "Token " << tokenId << " đã được gia hạn nếu còn hiệu lực." << std::endl;

        } else if (command == "count") {
            int currentTime;
            std::cout << "Nhập currentTime: ";
            std::cin >> currentTime;
            int count = authManager.countUnexpiredTokens(currentTime);
            std::cout << "Số lượng token còn hiệu lực: " << count << std::endl;

        } else {
            std::cout << "Lệnh không hợp lệ. Vui lòng thử lại." << std::endl;
        }
    }

    return 0;
}
