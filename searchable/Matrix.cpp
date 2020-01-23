#include "Searchable.h"
#include <algorithm>
#include <math.h>
template class Matrix<MyPoint>;

template<class T>
list<State<MyPoint>*>* Matrix<T>::getAllPossibleStates(State<MyPoint>*s, list<State<MyPoint>*>* closed) {
    /**TODO Currently this method is only suitable for Up,Down,Right,Left.
     * we need to Figure out how to make it work with 8 directions (AStar)*/
    list<State<MyPoint>*>* options = new list<State<MyPoint>*>();
    //add possible moves Up, Down, Right, Left as long as they're in the Matrix
    for(State<MyPoint>* state : *this->stateList) {
        //if the state isn't in closed
        if (!(find(closed->begin(), closed->end(), state) != closed->end())) {
            if (state->getCurrentState()->getX() == s->getCurrentState()->getX() + 1
                && state->getCurrentState()->getY() == s->getCurrentState()->getY()) {
                options->push_front(state);
                continue;
            }
            if (state->getCurrentState()->getX() == s->getCurrentState()->getX() - 1
                && state->getCurrentState()->getY() == s->getCurrentState()->getY()) {
                options->push_front(state);
                continue;
            }
            if (state->getCurrentState()->getY() == s->getCurrentState()->getY() + 1
                && state->getCurrentState()->getX() == s->getCurrentState()->getX()) {
                options->push_front(state);
                continue;
            }
            if (state->getCurrentState()->getY() == s->getCurrentState()->getY() - 1
                && state->getCurrentState()->getX() == s->getCurrentState()->getX()) {
                options->push_front(state);
                continue;
            }
        }
    }

    return options;
}

template<class T>
State<MyPoint>* Matrix<T>::getGoalState() {
    return this->t;
}

template<class T>
State<MyPoint>* Matrix<T>::getIntialState() {
    return this->s;
}

template<class T>
string Matrix<T>::toString() {
    int val;
    string name;
    for (State<MyPoint>* pointState : *(this->stateList)) {
        val = pointState->getCost();
        name = name + to_string(val) + ",";
    }
    int valStart = this->getIntialState()->getCost();
    name = name + to_string(valStart) + ",";
    int valTarget = this->getGoalState()->getCost();
    name = name + to_string(valTarget);
    return name;
}

template<class T>
void Matrix<T>::updateDirection(State<MyPoint> *currentState, State<MyPoint> *cameFrom) {
    if (currentState->getCurrentState()->getX() == cameFrom->getCurrentState()->getX() + 1
        && currentState->getCurrentState()->getY() == cameFrom->getCurrentState()->getY()) {
        currentState->setDirection("Down");
    }
    else if (currentState->getCurrentState()->getX() == cameFrom->getCurrentState()->getX() - 1
             && currentState->getCurrentState()->getY() == cameFrom->getCurrentState()->getY()) {
        currentState->setDirection("Up");
    }
    else if (currentState->getCurrentState()->getY() == cameFrom->getCurrentState()->getY() + 1
             && currentState->getCurrentState()->getX() == cameFrom->getCurrentState()->getX()) {
        currentState->setDirection("Right");
    }
    else if (currentState->getCurrentState()->getY() == cameFrom->getCurrentState()->getY() + 1
             && currentState->getCurrentState()->getX() == cameFrom->getCurrentState()->getX()) {
        currentState->setDirection("Left");
    }
}
template <class T>
double Matrix<T>::getDistance(State<T> *s1, State<T> *s2) {
    double partA = s2->getCurrentState()->getX() - s1->getCurrentState()->getX();
    double partB = s2->getCurrentState()->getY() - s1->getCurrentState()->getY();
    double a = abs(partA*partA);
    double b = abs(partB*partB);
    return sqrt(a+b);
}
