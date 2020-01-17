#include "Searchable.h"
template class Matrix<MyPoint>;

template<class T>
list<State<MyPoint>*>* Matrix<T>::getAllPossibleStates(State<MyPoint> *s) {
    return this->stateList;
}

template<class T>
State<MyPoint> *Matrix<T>::getGoalState() {
    return this->t;
}

template<class T>
State<MyPoint> *Matrix<T>::getIntialState() {
    return this->s;
}
