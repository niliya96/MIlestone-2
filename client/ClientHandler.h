#ifndef MILESTONE2_CLIENTHANDLER_H
#define MILESTONE2_CLIENTHANDLER_H
#include "../solver/Solver.h"
#include "../cacheManager/CacheManager.h"
#include "String.h"
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
    virtual ClientHandler* clone() = 0;
};

template <class Problem, class Solution> class MyTestClientHandler: public ClientHandler {
private:
    Solver<Problem,Solution>* solver;
    CacheManager<Problem, Solution>* cm;
public:
    ClientHandler* clone(){};
    MyTestClientHandler(Solver<String*,string>* newSolver, CacheManager<String*,string>* newCM) {
        this->solver = newSolver;
        this->cm = newCM;
    };
    void handleClient(int socket);
};

template <class Problem, class Solution> class MyClientHandler: public ClientHandler {
private:
    mutex mu4;
    mutex mu5;
    Solver<Problem,Solution>* solver;
    CacheManager<Problem, Solution>* cm;
    list<State<MyPoint>*>* l = new list<State<MyPoint>*>();
public:
    ClientHandler* clone() {
      return new MyClientHandler(solver->clone(), cm);
    };
    MyClientHandler(Solver<Problem,Solution>* newSolver, CacheManager<Problem,Solution>* newCM) {
        this->solver = newSolver;
        this->cm = newCM;
    };
    void handleClient(int socket);
};
#endif //MILESTONE2_CLIENTHANDLER_H
