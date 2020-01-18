#include "Searchable.h"
template class Matrix<MyPoint>;

template<class T>
list<State<MyPoint>*>* Matrix<T>::getAllPossibleStates(State<MyPoint>* s) {
    /**TODO Currently this method is only suitable for Up,Down,Right,Left.
     * we need to Figure out how to make it work with 8 directions (AStar)*/
    list<State<MyPoint>*>* options = new list<State<MyPoint>*>();
    //add possible moves Up, Down, Right, Left as long as they're in the Matrix
    for(State<MyPoint>* state : *this->stateList) {
        if(state->getCurrentState()->getX() == s->getCurrentState()->getX()+1
            && state->getCurrentState()->getY() == s->getCurrentState()->getY()) {
            options->push_front(state);
            continue;
        }
        if(state->getCurrentState()->getX() == s->getCurrentState()->getX()-1
           && state->getCurrentState()->getY() == s->getCurrentState()->getY()) {
            options->push_front(state);
            continue;
        }
        if(state->getCurrentState()->getY() == s->getCurrentState()->getY()+1
           && state->getCurrentState()->getX() == s->getCurrentState()->getX()) {
            options->push_front(state);
            continue;
        }
        if(state->getCurrentState()->getY() == s->getCurrentState()->getY()-1
           && state->getCurrentState()->getX() == s->getCurrentState()->getX()) {
            options->push_front(state);
            continue;
        }
    }
    //update cameFrom
    for(auto* state : *options) {
        state->setCameFrom(s);
        state->setCost(s->getCost() + state->getCurrentState()->getValue());
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
        val = pointState->getCurrentState()->getValue();
        name = name + to_string(val) + ",";
    }
    int valStart = this->s->getCurrentState()->getValue();
    name = name + to_string(valStart) + ",";
    int valTarget = this->t->getCurrentState()->getValue();
    name = name + to_string(valTarget);
    return name;
}
