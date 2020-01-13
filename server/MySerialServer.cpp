#include <sys/socket.h>
#include "Server.h"
using namespace server_side;

int openServer(int port, ClientHandler* c) {
    //creates socket and checks if created
    int socketFD = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFD == -1) {
        std::cerr << "Could not create a socket" << std::endl;
        return -1;
    }
    //binds socket to IP address (we want to listen to al IP)
    sockaddr_in address;
    address.sin_family = AF_INET;
    // any IP in IPV4
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    // Binds the socket to the given port at localhost.
    if (bind(socketFD, (struct sockaddr *) &address, sizeof(address)) == -1) {
        std::cerr << "Could not bind the socket to an IP" << std::endl;
        return -2;
    }
    // listens to clients (1 can wait in the queue)
    if (listen(socketFD, 1) == -1) {
        std::cerr << "Error during listening command" << std::endl;
        return -3;
    } else {
        std::cout << "Server is now listening ..." << std::endl;
    }
    struct timeval tv;
    tv.tv_sec = 120;
    setsockopt(socketFD, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);
    // accepts clients
    while (true) {
        socklen_t addrlen = sizeof(sockaddr_in);
        int client_socket = accept(socketFD, (struct sockaddr *) &address,
                                   &addrlen);
        if (client_socket == -1) {
            std::cerr << "Error accepting client" << std::endl;
            return -4;
        }
        c->handleClient(addrlen);
    }
    close(socketFD);
    return 0;

}
void Server::open(int port, ClientHandler* c) {
    thread server(openServer, port, c);
    server.join();
}
void Server::stop() {

}