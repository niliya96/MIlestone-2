#ifndef MILESTONE2_CACHEMANAGER_H
#define MILESTONE2_CACHEMANAGER_H
using namespace std;
#include <map>
#include <string>
#include <list>
template <class Problem, class Solution> class CacheManager {
public:
    virtual bool isExist(Problem p) = 0;
    virtual Solution get(Problem p) = 0;
    virtual void insert(Problem p, Solution s) = 0;
};
template <class Problem, class Solution> class FileCacheManager : public CacheManager<Problem, Solution> {
private:
    int size = 5;
    map<string, typename list<std::pair<string,string>>::iterator>* cache =
            new map<string, typename list<std::pair<string,string>>::iterator>;
    list<std::pair<string,string>>* orderedList = new list<std::pair<string,string>>();
public:
    //FileCacheManager<Problem,Solution>() {};
    bool isExist(Problem p);
    Solution get(Problem p);
    void insert(Problem p, Solution s);
    string readFile(Problem p);
    void writeFile(Problem problem, Solution solution);
};

#endif //MILESTONE2_CACHEMANAGER_H
