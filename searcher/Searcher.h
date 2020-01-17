#ifndef MILESTONE2_SEARCHER_H
#define MILESTONE2_SEARCHER_H
using namespace std;
#include "../searchable/Searchable.h"
#include <string>
#include <queue>

template <class T, class Solution> class Searcher {
public:
    virtual Solution search(Searchable<T> s) = 0;
};

template <class T, class Solution> class BestFS : public Searcher<T, Solution> {
private:
    queue<State<MyPoint>*>* openList = new queue<State<MyPoint>*>();
    int evaluatedNotes;
public:
    Solution search(Searchable<T> s);
    State<MyPoint>* popOpenList();
};
#endif //MILESTONE2_SEARCHER_H
