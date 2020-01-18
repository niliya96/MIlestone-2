
#ifndef MILESTONE2_STATE_H
#define MILESTONE2_STATE_H
using namespace std;
#include "Searchable.h"
#include<stdio.h>
#include<string>
#include<string.h>

template <class T> class State{
private:
    string stateName;
    double cost = 99999999999;
    T* currentState;
    State<T>* cameFrom;
public:
    State(string newState) {
        this->stateName = newState;
    };
    State(T* newState) {
        this->currentState = newState;
    };
    bool equals(State<T>* otherState) {
        return (strcmp(this->stateName, otherState->getStateName()) == 0);
    };
    string getStateName() {
        return this->stateName;
    };
    State<T>* getCameFrom() {
        return this->cameFrom;
    }
    void setCameFrom(State<T>* s) {
        this->cameFrom = s;
    }
    double getCost(){
        return this->cost;
    }
    void setCost(double newCost) {
        this->cost = newCost;
    }
    T* getCurrentState() {
        return this->currentState;
    }
};

#endif //MILESTONE2_STATE_H