#ifndef MILESTONE2_SOLVER_H
#define MILESTONE2_SOLVER_H
using namespace std;
#include <string>
template <class Problem, class Solution> class Solver {
public:
    virtual Solution solve(Problem p) = 0;
};
template <class Problem, class Solution> class StringReverser : public Solver<Problem, Solution> {
    string solve(string p);
};
#endif //MILESTONE2_SOLVER_H
