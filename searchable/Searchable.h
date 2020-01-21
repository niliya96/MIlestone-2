#ifndef MILESTONE2_SEARCHABLE_H
#define MILESTONE2_SEARCHABLE_H
#include <list>
#include "State.h"
using namespace std;
class MyPoint;

template <class T> class Searchable {
public:
    virtual State<T>* getIntialState() = 0;
    virtual State<T>* getGoalState() = 0;
    virtual list<State<T>*>* getAllPossibleStates(State<T>* s, list<State<MyPoint>*>* closed) = 0;
    virtual ~Searchable() = default;
    virtual void updateDirection(State<T>* currentState, State<T>* cameFrom) = 0;
    virtual double getDistance(State<T>* s1, State<T>* s2) = 0;
};

template <class T> class Matrix: public Searchable<T> {
private:
    list<State<MyPoint>*>* stateList;
    State<MyPoint>* s;
    State<MyPoint>* t;
    int N;
public:
    Matrix(list<State<MyPoint>*>* l, State<MyPoint>* start, State<MyPoint>* target, int newN) {
        this->stateList = l;
        this->s = start;
        this->t = target;
        this->N = newN;
    }
    double getDistance(State<T>* s1, State<T>* s2);
    void updateDirection(State<MyPoint>* currentState, State<MyPoint>* cameFrom);
    State<MyPoint>* getIntialState();
    State<MyPoint>* getGoalState();
    list<State<MyPoint>*>* getAllPossibleStates(State<MyPoint>* s, list<State<MyPoint>*>* closed);
    int getN() {
        return this->N;
    }
    string toString();
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

    bool operator==(const MyPoint &rhs) const {
        return i == rhs.i &&
               j == rhs.j;
    }

    bool operator!=(const MyPoint &rhs) const {
        return !(rhs == *this);
    }
};
#endif //MILESTONE2_SEARCHABLE_H
