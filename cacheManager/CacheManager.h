#ifndef MILESTONE2_CACHEMANAGER_H
#define MILESTONE2_CACHEMANAGER_H
template <class Problem, class Solution> class CacheManager {
    virtual bool isExist(Problem p) = 0;
    virtual void remove(Solution s) = 0;
    virtual void insert(Problem p, Solution s) = 0;
};
template <class Problem, class Solution> class FileCacheManager : public CacheManager<Problem, Solution> {
    bool isExist(Problem p);
    void remove(Solution s);
    void insert(Problem p, Solution s);
};
#endif //MILESTONE2_CACHEMANAGER_H
