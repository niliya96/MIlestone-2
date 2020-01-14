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
    int client_socket;
    int result;
    // accepts clients
    while (!shouldStop) {
        fd_set rfds;
        FD_ZERO(&rfds);
        FD_SET(socketFD, &rfds);
        struct timeval tv;
        tv.tv_sec = (long)10;
        tv.tv_usec = 0;
        result = select(socketFD+1, &rfds, (fd_set*)0, (fd_set*)0, &tv);
        if (result > 0) {
            socklen_t addrlen = sizeof(sockaddr_in);
            client_socket = accept(socketFD, (struct sockaddr *) &address, &addrlen);
        }
        else {
            continue;
        }
        if (client_socket == -1) {
            return -4;
        }
        c->handleClient(client_socket);
        close(client_socket);
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