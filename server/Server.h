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
    class Server {
    public:
        virtual void stop() = 0;
        virtual void open(int port, ClientHandler* c) = 0;
        virtual ~Server() {};
    };
}

static bool shouldStop = false;

class MySerialServer: public server_side::Server {
public:
    MySerialServer() {};
    ~MySerialServer() {};
private:
    void open(int port, ClientHandler* c);
    void stop();
};

namespace boot {
    class Main;
}

class boot::Main {
public:
    Main() {};
    ~Main() {};
    int main(int argc, char* argv[]) {
        server_side::Server* serialServer = new MySerialServer();
        Solver<string,string>* reverseSolver = new StringReverser<string,string>();
        CacheManager<string,string>* cm = new FileCacheManager<string,string>();
        ClientHandler* c = new MyTestClientHandler<string,string>(reverseSolver,cm);
        serialServer->open(atoi(argv[0]), c);
        return 0;
    };
};

#endif //MILESTONE2_SERVER_H
