#ifndef MILESTONE2_CACHEMANAGER_H
#define MILESTONE2_CACHEMANAGER_H

#include "map"
template <class Problem, class Solution> class CacheManager {
public:
    virtual bool isExist(Problem p) = 0;
    virtual Solution get(Problem p) = 0;
    virtual void insert(Problem p, Solution s) = 0;
};
template <class Problem, class Solution> class FileCacheManager : public CacheManager<Problem, Solution> {
private:
public:
    FileCacheManager() {
    }
    bool isExist(Problem p);
    Solution get(Problem p);
    void insert(Problem p, Solution s);
};

template<class Problem, class Solution>
void FileCacheManager<Problem, Solution>::insert(Problem p, Solution s) {

}

template<class Problem, class Solution>
Solution FileCacheManager<Problem, Solution>::get(Problem p) {
    return nullptr;
}

template<class Problem, class Solution>
bool FileCacheManager<Problem, Solution>::isExist(Problem p) {
    return false;
}

#endif //MILESTONE2_CACHEMANAGER_H
