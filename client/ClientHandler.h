#ifndef MILESTONE2_CLIENTHANDLER_H
#define MILESTONE2_CLIENTHANDLER_H

#include "../solver/Solver.h"
#include "../cacheManager/CacheManager.h"

class ClientHandler {
    virtual void handleClient(int socket) = 0;
};

template <class Problem, class Solution> class MyTestClientHandler: public ClientHandler {
private:
    Solver<Problem,Solution> solver;
    CacheManager<Problem, Solution> cm;
public:
    void handleClient(int socket);
};
#endif //MILESTONE2_CLIENTHANDLER_H
