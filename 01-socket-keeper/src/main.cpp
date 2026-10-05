#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <thread>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

constexpr int PORT = 8080;
constexpr int BUFFER_SIZE = 4096;

std::string load_html_resume() {
    const char* env_p = std::getenv("STATIC_PATH");
    std::string path = (env_p != nullptr) ? env_p : "public/index.html";
    
    std::ifstream file(path);
    if (!file.is_open()) {
        return "<html><body><h1>404 Not Found</h1></body></html>";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void handle_client(int client_socket, std::string html_content) {
    char buffer[BUFFER_SIZE] = {0};
    ssize_t bytes_read = read(client_socket, buffer, BUFFER_SIZE - 1);

    if (bytes_read > 0) {
        std::string http_response = 
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html; charset=UTF-8\r\n"
            "Content-Length: " + std::to_string(html_content.size()) + "\r\n"
            "Connection: close\r\n\r\n" + 
            html_content;

        write(client_socket, http_response.c_str(), http_response.size());
    }

    close(client_socket);
}

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        std::cerr << "[ERROR] Failed to create socket" << std::endl;
        return 1;
    }

    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        std::cerr << "[ERROR] setsockopt failed" << std::endl;
        close(server_fd);
        return 1;
    }

    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        std::cerr << "[ERROR] Bind failed on port " << PORT << std::endl;
        close(server_fd);
        return 1;
    }

    if (listen(server_fd, 10) < 0) {
        std::cerr << "[ERROR] Listen failed" << std::endl;
        close(server_fd);
        return 1;
    }

    std::cout << "[INFO] Socket Keeper server running on http://0.0.0.0:" << PORT << std::endl;

    std::string resume_page = load_html_resume();
    while (true) {
        sockaddr_in client_addr{};
        socklen_t addrlen = sizeof(client_addr);
        int client_socket = accept(server_fd, (struct sockaddr*)&client_addr, &addrlen);

        if (client_socket < 0) {
            continue;
        }

        char client_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, INET_ADDRSTRLEN);
        std::cout << "[REQUEST] Incoming connection from: " << client_ip << std::endl;

        std::thread(handle_client, client_socket, resume_page).detach();
    }

    close(server_fd);
    return 0;
}
