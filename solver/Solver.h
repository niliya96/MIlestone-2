#ifndef MILESTONE2_SOLVER_H
#define MILESTONE2_SOLVER_H
using namespace std;
#include "../searcher/Searcher.h"
#include <string>

template <class Problem, class Solution> class Solver {
public:
    virtual Solution solve(Problem p) = 0;
};
template <class Problem, class Solution> class StringReverser : public Solver<Problem, Solution> {
    Solution solve(Problem p);
};
template <class Problem, class Solution> class SolverAdapter : public Solver<Problem, Solution> {
private:
    Searcher<Problem, Solution> s = new Searcher<Problem, Solution>();
public:
    SolverAdapter();
    Solution solve(Problem p);
};
#endif //MILESTONE2_SOLVER_H
