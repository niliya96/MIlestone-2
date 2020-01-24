#ifndef MILESTONE2_SERVER_H
#define MILESTONE2_SERVER_H
#include "../client/ClientHandler.h"
#include "../client/String.h"
#include "../solver/Solver.h"
#include "../searchable/Searchable.h"
#include <thread>
#include <sys/socket.h>
#include <string>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <mutex>
using namespace std;
namespace server_side {
    class Server {
    public:
        virtual void stop() = 0;
        virtual void open(int port, ClientHandler* c) = 0;
        virtual ~Server() = default;
    };
    static bool shouldStop = false;

    class MySerialServer: public Server {
    public:
        MySerialServer() = default;
        ~MySerialServer() = default;

    public:
        void open(int port, ClientHandler* c);
        void stop();
    };

    class MyParallelServer: public Server {
    public:
        MyParallelServer() = default;
        ~MyParallelServer() = default;

    public:
        void open(int port, ClientHandler* c);
        void stop();
    };
}

namespace boot {
    class Main;
}

class boot::Main {
public:
    Main() {};
    ~Main() {};
    int main(int argc, char* argv) {
        int port = 5600;
        // this is actually what the program runs
        // new server, shearchable, searcher and chache
        server_side::Server* serialServer = new server_side::MyParallelServer();
        Searcher<MyPoint,string>* alg = new BestFS<MyPoint,string>();
        SolverAdapter<MyPoint,Matrix<MyPoint>*,string>* solverAdapter =
                new SolverAdapter<MyPoint,Matrix<MyPoint>*,string>(alg);
        CacheManager<Matrix<MyPoint>*,string>* cm = new FileCacheManager<Matrix<MyPoint>*,string>();
        // new client handler
        ClientHandler* c = new MyClientHandler<Matrix<MyPoint>*,string>(solverAdapter,cm);
        // calls to the server to accepts clients
        if (argv == nullptr) {
            serialServer->open(port, c);
        }
        else {
            serialServer->open(atoi(argv), c);
        }
        /**
         *  TEST MY_TEST_CLIENT_HANDLER
        server_side::Server* serialServer = new server_side::MySerialServer();
        Solver<String*,string>* reverseSolver = new StringReverser<String*,string>();
        CacheManager<String*,string>* cm = new FileCacheManager<String*,string>();
        ClientHandler* c = new MyTestClientHandler<String*,string>(reverseSolver,cm);
        serialServer->open(atoi(argv), c);
        **/
        return 0;
    };
};

#endif //MILESTONE2_SERVER_H