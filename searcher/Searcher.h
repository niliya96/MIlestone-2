#ifndef MILESTONE2_SEARCHER_H
#define MILESTONE2_SEARCHER_H
using namespace std;
#include "../searchable/Searchable.h"
#include <string>

template <class Problem, class Solution> class Searcher {
public:
    virtual Solution search(Searchable<Problem, Solution> s) = 0;
};
#endif //MILESTONE2_SEARCHER_H
