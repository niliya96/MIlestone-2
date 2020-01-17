#ifndef MILESTONE2_CLIENTHANDLER_H
#define MILESTONE2_CLIENTHANDLER_H
#include "../solver/Solver.h"
#include "../cacheManager/CacheManager.h"
#include <sys/socket.h>
#include <string>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <sstream>
#include <list>

class ClientHandler {
public:
    virtual void handleClient(int socket) = 0;
};

template <class Problem, class Solution> class MyTestClientHandler: public ClientHandler {
private:
    Solver<Problem,Solution>* solver;
    CacheManager<Problem, Solution>* cm;
public:
    MyTestClientHandler(Solver<string,string>* newSolver, CacheManager<string,string>* newCM) {
        this->solver = newSolver;
        this->cm = newCM;
    };
    void handleClient(int socket);
};

template <class Problem, class Solution> class MyClientHandler: public ClientHandler {
private:
    Solver<Problem,Solution>* solver;
    CacheManager<Problem, Solution>* cm;
    list<State<MyPoint>*>* l = new list<State<MyPoint>*>();
public:
    MyClientHandler(Solver<string,string>* newSolver, CacheManager<string,string>* newCM) {
        this->solver = newSolver;
        this->cm = newCM;
    };
    void handleClient(int socket);
};
#endif //MILESTONE2_CLIENTHANDLER_H
