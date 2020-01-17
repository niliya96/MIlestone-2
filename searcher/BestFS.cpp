#include "Searcher.h"
#include <stdlib.h>
#include <string>

using namespace std;
template<class T,class Solution> class BestFS;

template<class T, class Solution>
State<T>* BestFS<T, Solution>::popOpenList() {
    evaluatedNotes++;
    State<T>* poppedState = this->openList->front();
    this->openList->pop();
    return poppedState;
};