#include "ClientHandler.h"
using namespace std;

template class MyClientHandler <Matrix<MyPoint>*,string>;

template<class Problem, class Solution>
void MyClientHandler<Problem, Solution>::handleClient(int socket) {
    // clear for the next runs
    this->l->clear();
    // vector to restor the buffer lines
    vector<string>* vec =  new vector<string>();
    // initializations
    int row =0;
    int col;
    int sizeOfMatrix;
    // start and target points
    MyPoint* s;
    MyPoint* t;
    // states for them
    State<MyPoint>* startState;
    State<MyPoint>* targetState;
    char buffer[1024] = {0};
    // read from buffer
    string line = "";
    char ch;
    mu5.lock();
    while (buffer != "end") {
        // read char by char
        read(socket, &ch, 1);
        line.append(1,ch);

        if (line == "end") {
            break;
        }
        if (ch == '\n') {
            // end of line
            vec->push_back(line);
            line = "";
        }

    }
    mu5.unlock();
    // build the matrix
    for (int i=0; i<vec->size()-2; i++) {
        // current line
        string current = vec->at(i);
        if (current == "" || current == " " || current == "\n") {
            continue;
        }
        string accum = "";
        //col initialization (a new row)
        col=0;
        int val;
        for (int k=0; k<current.length(); k++) {
            if (current[k] == '\n') {
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
                row++;
                accum = "";
                break;
            }
            else if (current[k] == ',') {
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
                // accumulates the value
                accum = accum + current[k];
            }
        }
    }
    // start point
    string startString = vec->at(vec->size()-2);
    string acc = "";
    int i=0, j=0;
    int value;
    for (int w=0; w<startString.size(); w++) {
        if (startString[w] == '\n') {
            try {
                // col
                j = stoi(acc);
            }
            catch (...) {
                throw "bad input";
            }
            // search in the list of points
            for (State<MyPoint>* pointState : *(this->l)) {
                if (pointState->getCurrentState()->getX() == i && pointState->getCurrentState()->getY() == j) {
                    value = pointState->getCurrentState()->getValue();
                    startState = pointState;
                    startState->setCost(value);
                    startState->setPathCost(value);
                }
            }
        }
        else if (startString[w] == ',') {
            try {
                // row
                i = stoi(acc);
            }
            catch (...) {
                throw "bad input";
            }
            acc = "";
        }
        else {
            acc = acc + startString[w];
        }
    }
    // target point
    string targetString = vec->at(vec->size()-1);
    acc = "";
    i=0, j=0;
    for (int w=0; w<targetString.size(); w++) {
        if (targetString[w] == '\n') {
            try {
                // col
                j = stoi(acc);
            }
            catch (...) {
                throw "bad input";
            }
            // search in the list of points
            for (State<MyPoint>* pointState : *(this->l)) {
                if (pointState->getCurrentState()->getX() == i && pointState->getCurrentState()->getY() == j) {
                    value = pointState->getCurrentState()->getValue();
                    targetState = pointState;
                    targetState->setCost(value);
                    targetState->setPathCost(value);
                }
            }
        }
        else if (targetString[w] == ',') {
            try {
                // row
                i = stoi(acc);
            }
            catch (...) {
                throw "bad input";
            }
            acc = "";
        }
        else {
            acc = acc + targetString[w];
        }
    }
    Searchable<MyPoint>* matrix = new Matrix<MyPoint>(this->l, startState, targetState, sizeOfMatrix);
    string message;
    //search solution in cache
    bool solutionExist = this->cm->isExist((Matrix<MyPoint>*)matrix);
    //check if a solution has been found
    if(solutionExist) {
        message = this->cm->get((Matrix<MyPoint>*)matrix);
    }
    else {
        message = this->solver->solve((Matrix<MyPoint>*)matrix);
        this->cm->insert((Matrix<MyPoint>*)matrix,message);
    }
    //send solution to client
    message = message + "\n";
    char* messageSend = const_cast<char *>(message.c_str());
    mu4.lock();
    int toSend = send(socket , messageSend , strlen(messageSend), 0);
    mu4.unlock();
}

