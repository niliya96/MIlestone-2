#include "../solver/Solver.h"

template<> string StringReverser<class Problem, class Solution>::solve(string p) {
    int len = p.length();
    int i;
    for (i=0; i<len/2; i++) {
        swap(p[i], p[len-i-1]);
    }
    return p;
}