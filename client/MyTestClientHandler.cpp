#include "ClientHandler.h"
using namespace std;

// this is just a test for a client
template<> void MyTestClientHandler<String*, string>::handleClient(int socket) {
    while(true) {
        char buffer[1024] = {0};
        int valread = read(socket, buffer, 1024);
        stringstream bufferedValues(buffer);
        if (bufferedValues.str().compare("end\r\n") == 0) {
            break;
        }
        String* p = new String(bufferedValues.str());
        string message;
        //search solution in cache
        bool solutionExist = this->cm->isExist(p);
        //check if a solution has been found
        if(solutionExist) {
            message = this->cm->get(p);
        }
        else {
            message = this->solver->solve(p);
            this->cm->insert(p,message);
        }
        //send solution to client
        message = message + "\n";
        char* messageSend = const_cast<char *>(message.c_str());
        int toSend = send(socket , messageSend , strlen(messageSend), 0);
    }
}
