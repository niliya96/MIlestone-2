#ifndef MILESTONE2_CACHEMANAGER_H
#define MILESTONE2_CACHEMANAGER_H
using namespace std;
#include <map>
#include <string>
#include <list>
#include <fstream>
template <class Problem, class Solution> class CacheManager {
public:
    virtual bool isExist(Problem p) = 0;
    virtual Solution get(Problem p) = 0;
    virtual void insert(Problem p, Solution s) = 0;
};
template <class Problem, class Solution> class FileCacheManager : public CacheManager<Problem, Solution> {
private:
    int size = 5;
    map<Problem, typename list<std::pair<Problem,Solution>>::iterator>* cache =
            new map<Problem, typename list<std::pair<Problem,Solution>>::iterator>;
    list<std::pair<Problem,Solution>>* orderedList = new list<std::pair<Problem,Solution>>();
public:
    //FileCacheManager<Problem,Solution>() {};
    bool isExist(Problem p) {
        //search in cache
        if(this->cache->find(p) != this->cache->end()) {
            return true;
        }
            //if it's not in cache, search in disk
        else {
            string s = p->toString() +".txt";
            ifstream f(s);
            return f.good();
        }
    };
    Solution get(Problem p) {
        if(isExist(p)) {
            //the item is not in the cache map
            if(this->cache->find(p) == this->cache->end()) {
                //look it up in disk
                Solution solution =  this->readFile(p);
                //update cache
                //if the cache is full
                if(orderedList->size() == this->size) {
                    //get the last item used
                    Solution lastItem = orderedList->back().second;
                    Problem k = orderedList->back().first;
                    //pop it
                    orderedList->pop_back();
                    //erase it from map;
                    cache->erase(k);
                    //push new entry
                    orderedList->push_front(std::make_pair(p,solution));
                    (*cache)[p] = orderedList->begin();
                }
                    //if there's room in the cache
                else {
                    //just push the new entry
                    orderedList->push_front(std::make_pair(p, solution));
                    (*cache)[p] = orderedList->begin();
                }
                return solution;
            }
                //it is in cache
            else {
                //erase item from list and push it again
                orderedList->push_front(*(*cache)[p]);
                orderedList->erase((*cache)[p]);
                (*cache)[p] = orderedList->begin();
                return orderedList->front().second;
            }
        }
            //its not in cache or disk
        else {
            return nullptr;
        }
    };
    void insert(Problem p, Solution s) {
        //the item is not in the cache
        if(cache->find(p) == cache->end()) {
            //if the cache is full
            if(orderedList->size() == this->size) {
                //get the last item used
                Solution lastItem = orderedList->back().second;
                Problem k = orderedList->back().first;
                //pop it
                orderedList->pop_back();
                //erase it from map;
                cache->erase(k);
                //push new entry
                orderedList->push_front(std::make_pair(p,s));
                (*cache)[p] = orderedList->begin();
            }
                //if there's room in the cache
            else {
                //just push the new entry
                orderedList->push_front(std::make_pair(p,s));
                (*cache)[p] = orderedList->begin();
            }
        }
            //the item is in the cache
        else {
            //erase item from list and push it again
            orderedList->erase((*cache)[p]);
            orderedList->push_front(std::make_pair(p,s));
            //change the value to this
            (*cache)[p] = orderedList->begin();
        }
        //write it in disk
        writeFile(p,s);
    };
    string readFile(Problem p) {
        string s = p->toString() +".txt";
        ifstream in_file(s);
        string solution;
        getline(in_file, solution);
        in_file.close();
        return solution;
    };
    void writeFile(Problem problem, Solution solution) {
        string s = problem->toString() +".txt";
        ofstream out_file;
        out_file.open (s);
        out_file << solution;
        out_file.close();
    };
};

#endif //MILESTONE2_CACHEMANAGER_H
