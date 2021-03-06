#ifndef MILESTONE2_SOLVER_H
#define MILESTONE2_SOLVER_H
using namespace std;
#include "../searcher/Searcher.h"
#include <string>

template <class Problem, class Solution> class Solver {
public:
    virtual Solution solve(Problem p) = 0;
    virtual  Solver* clone() = 0;
};
template <class Problem, class Solution> class StringReverser : public Solver<Problem, Solution> {
    Solution solve(Problem p);
    Solver<Problem, Solution>* clone() {return new StringReverser();};
};
template<class T, class Problem, class Solution> class SolverAdapter : public Solver<Problem, Solution> {
private:
    Searcher<T,Solution>* s;
public:
    Solver<Problem, Solution>* clone() {
        return new SolverAdapter(s->clone());
    };
    SolverAdapter(Searcher<T,Solution>* newS) {
        this-> s = newS;
    };
    Solution solve(Problem p) {
        return s->search(p);
    };
    Searcher<T,Solution>* getSearcher() {
        return this->s;
    }
};
#endif //MILESTONE2_SOLVER_H
