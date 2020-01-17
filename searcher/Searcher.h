#ifndef MILESTONE2_SEARCHER_H
#define MILESTONE2_SEARCHER_H
using namespace std;
#include "../searchable/Searchable.h"
#include <string>
#include <queue>

template <class T, class Solution> class Searcher {
public:
    virtual Solution search(Searchable<T>* s) = 0;

};

template <class T, class Solution> class BestFS : public Searcher<T, Solution> {
private:
    queue<State<T>*>* openList = new queue<State<T>*>();
    int evaluatedNotes = 0;
public:
    Solution search(Searchable<T>* s) {

    }
    State<T>* popOpenList();
};
#endif //MILESTONE2_SEARCHER_H
