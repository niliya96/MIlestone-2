#ifndef MILESTONE2_SOLVER_H
#define MILESTONE2_SOLVER_H

template <class Problem, class Solution> class Solver {
public:
    Solution solve(Problem p) = 0;
};

#endif //MILESTONE2_SOLVER_H
