#ifndef MILESTONE2_SERVER_H
#define MILESTONE2_SERVER_H
#include "../client/ClientHandler.h"
#include <thread>
#include <sys/socket.h>
#include <string>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
using namespace std;
namespace server_side {
    class Server;
}

class server_side::Server {
    virtual void open(int port, ClientHandler* c) = 0;
    virtual void stop() = 0;
};
class MySerialServer: public server_side::Server {
    void open(int port, ClientHandler* c);
    void stop();
};
#endif //MILESTONE2_SERVER_H
