#ifndef MILESTONE2_SERVER_H
#define MILESTONE2_SERVER_H
#include "../client/ClientHandler.h"
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
    private:
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

        server_side::Server* serialServer = new server_side::MySerialServer();
        Searcher<MyPoint,string>* alg = new BestFS<MyPoint,string>();
        SolverAdapter<MyPoint,Matrix<MyPoint>*,string>* solverAdapter =
                new SolverAdapter<MyPoint,Matrix<MyPoint>*,string>(alg);
        CacheManager<Matrix<MyPoint>*,string>* cm = new FileCacheManager<Matrix<MyPoint>*,string>();
        ClientHandler* c = new MyClientHandler<Matrix<MyPoint>*,string>(solverAdapter,cm);
        serialServer->open(atoi(argv), c);

        /**
         * TEST MY_TEST_CLIENT_HANDLER
        server_side::Server* serialServer = new server_side::MySerialServer();
        Solver<string,string>* reverseSolver = new StringReverser<string,string>();
        CacheManager<string,string>* cm = new FileCacheManager<string,string>();
        ClientHandler* c = new MyTestClientHandler<string,string>(reverseSolver,cm);
        serialServer->open(atoi(argv), c);
        **/
        return 0;
    };
};

#endif //MILESTONE2_SERVER_H
