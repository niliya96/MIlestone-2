#include "ClientHandler.h"
using namespace std;

template class MyClientHandler <Matrix<MyPoint>*,string>;

template<class Problem, class Solution>
void MyClientHandler<Problem, Solution>::handleClient(int socket) {
    int row = 1;
    int col;
    int sizeOfMatrix;
    int flag = 0;
    bool countSize = false;
    MyPoint* s;
    MyPoint* t;
    State<MyPoint>* startState;
    State<MyPoint>* targetState;
    while(true) {
        char buffer[1024] = {0};
        /**TODO flush*/
        int valread = read(socket, buffer, 1024);
        stringstream bufferedValues(buffer);
        if (bufferedValues.str().compare("end\r\n") == 0) {
            break;
        }
        else if (row == sizeOfMatrix+1 && countSize) {
            string acc = "";
            int i=0, j=0;
            int value;
            for (int w=0; w<strlen(buffer); w++) {
                if (buffer[w] == '\r') {
                    try {
                        j = stoi(acc);
                    }
                    catch (...) {
                        throw "bad input";
                    }
                    if (flag == 0) {
                        for (State<MyPoint>* pointState : *(this->l)) {
                            if (pointState->getCurrentState()->getX() == i && pointState->getCurrentState()->getY() == j) {
                                value =pointState->getCurrentState()->getValue();
                            }
                        }
                        s = new MyPoint(i,j,value);
                        startState = new State<MyPoint>(s);
                        startState->setCost(value);
                        flag = 1;
                    }
                    else {
                        for (State<MyPoint>* pointState : *(this->l)) {
                            if (pointState->getCurrentState()->getX() == i && pointState->getCurrentState()->getY() == j) {
                                value =pointState->getCurrentState()->getValue();
                            }
                        }
                        t = new MyPoint(i,j, value);
                        targetState = new State<MyPoint>(t);
                        targetState->setCost(value);
                    }
                    break;
                }
                else if (buffer[w] == ',') {
                    try {
                        i = stoi(acc);
                    }
                    catch (...) {
                        throw "bad input";
                    }
                    acc = "";
                }
                else {
                    acc = acc + buffer[w];
                }
            }
        }
        else {
            /**
           * build the matrix
           */
            string accum = "";
            col=1;
            int val;
            for (int k=0; k<strlen(buffer); k++) {
                if (buffer[k] == '\r') {
                    // a value
                    try {
                        val = stoi(accum);
                    }
                    catch(...) {
                        throw "bad input";
                    }
                    // new point
                    MyPoint* p = new MyPoint(row, col, val);
                    State<MyPoint>* state = new State<MyPoint>(p);
                    state->setCost(val);
                    this->l->push_front(state);
                    sizeOfMatrix = col;
                    countSize = true;
                    row++;
                    accum = "";
                    break;
                }
                else if (buffer[k] == ',') {
                    // a value
                    try {
                        val = stoi(accum);
                    }
                    catch(...) {
                        throw "bad input";
                    }
                    // new point
                    MyPoint* p = new MyPoint(row, col, val);
                    State<MyPoint>* state = new State<MyPoint>(p);
                    state->setCost(val);
                    this->l->push_front(state);
                    col++;
                    accum = "";
                    continue;
                }
                else {
                    accum = accum + buffer[k];
                }
            }
        }
    }
    Searchable<MyPoint>* matrix = new Matrix<MyPoint>(this->l, startState, targetState);
    //this->solve(matrix);
    /**TODO after cacheManager
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
     */
}

