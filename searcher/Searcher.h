#ifndef MILESTONE2_SEARCHER_H
#define MILESTONE2_SEARCHER_H
using namespace std;
#include "../searchable/Searchable.h"
#include <string>
#include <queue>
#include <map>
#include <set>
#include <algorithm>

template <class T, class Solution> class Searcher {
public:
    virtual Solution search(Searchable<T>* s) = 0;

};

template <class MyPoint, class string> class BestFS : public Searcher<MyPoint, string> {
private:
    list<State<MyPoint>*>* openList = new list<State<MyPoint>*>();
    int evaluatedNotes = 0;
public:
    int getNumberOfNodesEvaluated() {
        return this->evaluatedNotes;
    }
    State<MyPoint>* popOpenList() {
        evaluatedNotes++;
        State<MyPoint>* poppedState = this->openList->front();
        this->openList->pop_front();
        return poppedState;
    }
    int openListSize() {
        return this->openList->size();
    }
    string backTrace(State<MyPoint>* state) {
        if (state->getCameFrom() == nullptr) {
            return nullptr;
        }
        if(state->getCameFrom()->getCurrentState()->getX() > state->getCurrentState()->getX())
            return backTrace(state->getCameFrom()) + "Left";
        else if(state->getCameFrom()->getCurrentState()->getX() < state->getCurrentState()->getX())
            return backTrace(state->getCameFrom()) + "Right";
        else if(state->getCameFrom()->getCurrentState()->getY() > state->getCurrentState()->getY())
            return backTrace(state->getCameFrom()) + "Down";
        else if(state->getCameFrom()->getCurrentState()->getY() < state->getCurrentState()->getY())
            return backTrace(state->getCameFrom()) + "Up";
    }
    string search(Searchable<MyPoint>* s) {
        //"initializeState->cost" will be MyPoint value;
        s->getIntialState()->setCost(s->getIntialState()->getCurrentState()->getValue());
        openList->push_front(s->getIntialState());
        set<State<MyPoint>*>* closed = new set<State<MyPoint>*>();
        while(openListSize() > 0) {
            State<MyPoint>* n = popOpenList();
            closed->insert(n);
            if(n == s->getGoalState()) {
                return backTrace(n);
            }
            list<State<MyPoint>*>* succerssors = s->getAllPossibleStates(n);
            for(State<MyPoint>* state : *succerssors) {
                if(!(closed->find(state) != closed->end())
                    && !(find(openList->begin(),openList->end(), state) != openList->end())) {
                    openList->push_back(state);
                }
                //else if current path is shorter
                else if(n->getCost() + state->getCurrentState()->getValue() < state->getCost()
                        //&& !(closed->find(state) != closed->end())
                        /**TODO CHECK WHAT TO DO WITH 1,1 COMING BACK*/
                        ) {
                    if(!(find(openList->begin(),openList->end(), state) != openList->end())) {
                        openList->push_front(state);
                    }
                    else {
                        //remove "state" from openList and push it again
                        openList->remove(state);
                        openList->push_front(state);
                    }
                }
            }

        }
    }

};


template <class T, class Solution> class AStar : public Searcher<T, Solution> {
private:
public:
    Solution search(Searchable<T>* s) {

    }
};
#endif //MILESTONE2_SEARCHER_H
