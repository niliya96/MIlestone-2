#include "Searcher.h"
#include <stdlib.h>
#include <string>

using namespace std;
template<class T,class Solution> class BestFS;

template<class T, class Solution>
Solution BestFS<T, Solution>::search(Searchable <T> s) {

}

template<class T, class Solution>
State<MyPoint> *BestFS<T, Solution>::popOpenList() {
    evaluatedNotes++;
    State<MyPoint>* poppedState = this->openList->front();
    this->openList->pop();
    //return
};