#include "ClientHandler.h"
using namespace std;
template<> void MyTestClientHandler<string, string>::handleClient(int socket) {
    while(true) {
        char buffer[1024] = {0};
        /**TODO flush*/
        int valread = read(socket, buffer, 1024);
        stringstream bufferedValues(buffer);
        if (bufferedValues.str().compare("end") == 0) {
            break;
        }
        string message;
        //search solution in cache
        bool solutionExist = this->cm->isExist(bufferedValues.str());
        //check if a solution has been found
        if(solutionExist) {
            message = this->cm->get(bufferedValues.str());
        }
        else {
            message = this->solver->solve(bufferedValues.str());
            this->cm->insert(bufferedValues.str(),message);
        }
        //send solution to client
        message = message + "\n";
        char* messageSend = const_cast<char *>(message.c_str());
        int toSend = send(socket , messageSend , strlen(messageSend), 0);
    }
}
