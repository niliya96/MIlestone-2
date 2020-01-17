#ifndef MILESTONE2_SEARCHABLE_H
#define MILESTONE2_SEARCHABLE_H
#include <list>
#include "State.h"
using namespace std;
class MyPoint;

template <class T> class Searchable {
    virtual State<T>* getIntialState() = 0;
    virtual State<T>* getGoalState() = 0;
    virtual list<State<T>*>* getAllPossibleStates(State<T>* s) = 0;
};

template <class T> class Matrix: public Searchable<T> {
private:
    list<State<MyPoint>*>* stateList;
    State<MyPoint>* s;
    State<MyPoint>* t;
public:
    Matrix(list<State<MyPoint>*>* l, State<MyPoint>* start, State<MyPoint>* target) {
        this->stateList = l;
        this->s = start;
        this->t = target;
    }
    State<MyPoint>* getIntialState();
    State<MyPoint>* getGoalState();
    list<State<MyPoint>*>* getAllPossibleStates(State<MyPoint>* s);
    string toString() {
        return "nili";
    }
};

class MyPoint {
private:
    int i,j;
    int val;
public:
    MyPoint(int i, int j, int v) {
        this->i = i;
        this->j = j;
        this->val = v;
    }
    int getX() {
        return this->i;
    }
    int getY() {
        return this->j;
    }
    int getValue() {
        return this->val;
    }
    void setX(int i) {
        this->i = i;
    }
    void setY(int j) {
        this->j = j;
    }
    MyPoint getPoint() {
        return *this;
    }
};
#endif //MILESTONE2_SEARCHABLE_H
