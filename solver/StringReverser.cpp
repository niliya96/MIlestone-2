#include "Solver.h"
#include "../client/String.h"
template class StringReverser<String*,string>;

template<class Problem, class Solution> Solution StringReverser< Problem, Solution>::solve(Problem p) {
    string reversed = p->toString();
    int len = reversed.length();
    int i;
    for (i=0; i < (len / 2); i++) {
        swap(reversed[i], reversed[len-i-1]);
    }
    return reversed;
}