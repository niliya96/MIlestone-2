#ifndef MILESTONE2_SERVER_H
#define MILESTONE2_SERVER_H

#include "../client/ClientHandler.h"

namespace server_side {
    class Server;
}

class server_side::Server {
    virtual void open(int port, ClientHandler c) = 0;
    virtual void stop() = 0;
};
#endif //MILESTONE2_SERVER_H
