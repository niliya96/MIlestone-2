#include "Solver.h"

template class StringReverser<string,string>;

template<class Problem, class Solution> Solution StringReverser< Problem, Solution>::solve(Problem p) {
    int len = p.length();
    int i;
    for (i=0; i < (len / 2); i++) {
        swap(p[i], p[len-i-1]);
    }
    return p;
}