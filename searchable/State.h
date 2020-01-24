
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
    double cost;
    // initialize path cost for a state of a point
    double pathCost = 0;
    double distanceFromGoalState;
    T* currentState;
    State<T>* cameFrom;
    string direction;
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
    double getPathCost(){
        return this->pathCost;
    }
    void setPathCost(double newCost) {
        this->pathCost = newCost;
    }
    T* getCurrentState() {
        return this->currentState;
    }
    string getDirection(){
        return this->direction;
    }
    void setDirection(string s) {
        this->direction = s;
    }

    double getDistanceFromGoalState() {
        return this->distanceFromGoalState;
    }

    void setDistanceFromGoalState(double newDistanceFromGoalState) {
        this->distanceFromGoalState = newDistanceFromGoalState;
    }
    bool operator==(const State &rhs) const {
        return currentState == rhs.currentState;
    }

    bool operator!=(const State &rhs) const {
        return !(rhs == *this);
    }
};

template <class T>
struct myComparator
{
public:
    // comparator for BestFs
    int operator() (State<T>* s1, State<T>* s2)
    {
        return s1->getPathCost() > s2->getPathCost();
    }
};
typedef struct myCompartor myCompartor;

template <class T>
struct AStarComparator
{
public:
    // comparator for AStar
    int operator() (State<T>* s1, State<T>* s2)
    {
        // path cost + distance
        return s1->getPathCost() + s1->getDistanceFromGoalState() >
        s2->getPathCost() + s2->getDistanceFromGoalState();
    }
};

#endif //MILESTONE2_STATE_H