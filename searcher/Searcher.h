#ifndef MILESTONE2_SEARCHER_H
#define MILESTONE2_SEARCHER_H
using namespace std;
#include "../searchable/Searchable.h"
#include <string>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <stack>
#include <iostream>

template <class T, class Solution> class Searcher {
protected:
    int evaluatedNotes = 0;
public:
    virtual Solution search(Searchable<T>* s) = 0;
    string backTrace(State<T>* state) {
        if (state->getCameFrom() == nullptr) {
            return "";
        }
        return backTrace(state->getCameFrom()) + " " + state->getDirection();
    }
    int getNumberOfNodesEvaluated() {
        return this->evaluatedNotes;
    }
};

template <class T, class Solution> class BestFS : public Searcher<T, Solution> {
private:
    priority_queue<State<T>*, vector<State<T>*>, myComparator<T>>* openList =
            new priority_queue<State<T>*, vector<State<T>*>, myComparator<T>>();
    list<State<T>*>* closed = new list<State<T>*>();
public:
    string search(Searchable<T>* s) {
        addToOpenList(s->getIntialState());
        while(this->openListSize() > 0) {
            State<T>* n = this->popOpenList();
            this->closed->push_front(n);
            if(n == s->getGoalState()) {
                return this->backTrace(n);
            }
            list<State<T>*>* succerssors = s->getAllPossibleStates(n, this->closed);
            for(State<T>* state : *succerssors) {
                if(state->getCost() != -1
                   && !((find(this->closed->begin(),this->closed->end(),state) != this->closed->end()))
                   && !(this->isInOpenList(state))) {
                    state->setCameFrom(n);
                    state->setPathCost(n->getPathCost() + state->getCost());
                    s->updateDirection(state,n);
                    this->addToOpenList(state);
                }
                    //else if current path is shorter
                else if(state->getCost() != -1 &&
                        state->getPathCost() > n->getPathCost() + state->getCost()) {
                    state->setPathCost(n->getPathCost() + state->getCost());
                    state->setCameFrom(n);
                    s->updateDirection(n, state);
                    if(!(this->isInOpenList(state))) {
                        this->addToOpenList(state);
                    }
                    else {
                        this->updateOpenList();
                    }
                }
            }
        }
    }
    State<T>* popOpenList() {
        this->evaluatedNotes++;
        State<T>* poppedState = this->openList->top();
        this->openList->pop();
        return poppedState;
    }
    bool isInOpenList(State<T>* state) {
        //first we create a copy of openList
        priority_queue<State<T>*, vector<State<T>*>, myComparator<T>> tempOpenList =
                *this->openList;
        //iterate through the copy of open list
        while(tempOpenList.size() > 0) {
            if(tempOpenList.top() == state) {
                return true;
            }
            tempOpenList.pop();
        }
        return false;
    }
    void addToOpenList(State<T>* s) {
        this->openList->push(s);
    }
    int openListSize() {
        return this->openList->size();
    }
    void updateOpenList() {
        //first we create a copy of openList
        priority_queue<State<T>*, vector<State<T>*>, myComparator<T>> tempOpenList;
        while((*this->openList).size() > 0) {
            tempOpenList.push(this->openList->top());
            this->openList->pop();
        }
        while(tempOpenList.size() > 0) {
            (*this->openList).push(tempOpenList.top());
            tempOpenList.pop();
        }
    }
};

template <class T, class Solution> class AStar : public Searcher<T, Solution> {
private:
    priority_queue<State<T>*, vector<State<T>*>, struct AStarComparator<T>>* openList =
            new priority_queue<State<T>*, vector<State<T>*>, struct AStarComparator<T>>();
    list<State<T>*>* closed = new list<State<T>*>();
public:
    string search(Searchable<T>* s) {
        addToOpenList(s->getIntialState());
        while(this->openListSize() > 0) {
            State<T>* n = this->popOpenList();
            this->closed->push_front(n);
            if(n == s->getGoalState()) {
                return this->backTrace(n);
            }
            list<State<T>*>* succerssors = s->getAllPossibleStates(n, this->closed);
            for(State<T>* state : *succerssors) {
                if(state->getCost() != -1
                   && !((find(this->closed->begin(),this->closed->end(),state) != this->closed->end()))
                   && !(this->isInOpenList(state))) {
                    state->setCameFrom(n);
                    state->setDistanceFromGoalState(s->getDistance(state, s->getGoalState()));
                    state->setPathCost(n->getPathCost() + state->getCost());
                    s->updateDirection(state,n);
                    this->addToOpenList(state);
                }
                    //else if current path is shorter
                else if(state->getCost() != -1
                        && state->getPathCost() + state->getDistanceFromGoalState() >
                           n->getPathCost() + state->getCost() + n->getDistanceFromGoalState()) {
                    state->setDistanceFromGoalState(s->getDistance(state, s->getGoalState()));
                    state->setPathCost(n->getPathCost() + state->getCost());
                    state->setCameFrom(n);
                    s->updateDirection(n, state);
                    if(!(this->isInOpenList(state))) {
                        this->addToOpenList(state);
                    }
                    else {
                        this->updateOpenList();
                    }
                }
            }
        }
    }
    State<T>* popOpenList() {
        this->evaluatedNotes++;
        State<T>* poppedState = this->openList->top();
        this->openList->pop();
        return poppedState;
    }
    bool isInOpenList(State<T>* state) {
        //first we create a copy of openList
        priority_queue<State<T>*, vector<State<T>*>, struct AStarComparator<T>> tempOpenList =
                *this->openList;
        //iterate through the copy of open list
        while(tempOpenList.size() > 0) {
            if(tempOpenList.top() == state) {
                return true;
            }
            tempOpenList.pop();
        }
        return false;
    }
    void addToOpenList(State<T>* s) {
        this->openList->push(s);
    }
    int openListSize() {
        return this->openList->size();
    }
    void updateOpenList() {
        //first we create a copy of openList
        priority_queue<State<T>*, vector<State<T>*>, struct AStarComparator<T>> tempOpenList;
        while((*this->openList).size() > 0) {
            tempOpenList.push(this->openList->top());
            this->openList->pop();
        }
        while(tempOpenList.size() > 0) {
            (*this->openList).push(tempOpenList.top());
            tempOpenList.pop();
        }
    }
};

template <class T, class Solution> class BFS : public Searcher<T, Solution> {
private:
    list<State<T>*>* D = new list<State<T>*>;
    list<State<T>*>* closed = new list<State<T>*>();
public:
    Solution search(Searchable<T>* s) {
        D->push_front(s->getIntialState());
        while(!D->empty()) {
            cout << D->size() << " " << this->closed->size() << endl;
            State<MyPoint>* x = D->front();
            D->pop_front();
            this->closed->push_back(x);
            if(x == s->getGoalState()) {
                return this->backTrace(x);
            }
            for(State<MyPoint>* state : *(s->getAllPossibleStates(x,this->closed))) {
                if(state->getCost() != -1 && find(D->begin(), D->end(), state) == D->end()) {
                    state->setCameFrom(x);
                    state->setPathCost(x->getPathCost() + state->getCost());
                    s->updateDirection(state, x);
                    D->push_back(state);
                }
            }
        }
    }
};

template <class T, class Solution> class DFS : public Searcher<T, Solution> {
private:
    stack<State<T>*>* D = new stack<State<T>*>;
    list<State<T>*>* closed = new list<State<T>*>();
public:
    Solution search(Searchable<T>* s) {
        D->push(s->getIntialState());
        while(!D->empty()) {
            State<MyPoint>* x = D->top();
            D->pop();
            this->closed->push_front(x);
            if(x == s->getGoalState()) {
                return this->backTrace(x);
            }
            for(State<MyPoint>* state : *(s->getAllPossibleStates(x,this->closed))) {
                if(state->getCost() != -1) {
                    state->setCameFrom(x);
                    state->setPathCost(x->getPathCost() + state->getCost());
                    s->updateDirection(state, x);
                    D->push(state);
                }
            }
        }
    }
};
#endif //MILESTONE2_SEARCHER_H