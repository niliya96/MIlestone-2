#ifndef MILESTONE2_CACHEMANAGER_H
#define MILESTONE2_CACHEMANAGER_H
using namespace std;
#include <map>
#include <string>
#include <list>
#include <fstream>
#include <sstream>

template <class Problem, class Solution> class CacheManager {
public:
    virtual bool isExist(Problem p) = 0;
    virtual Solution get(Problem p) = 0;
    virtual void insert(Problem p, Solution s) = 0;
};
template <class Problem, class Solution> class FileCacheManager : public CacheManager<Problem, Solution> {
private:
    int size = 5;
    map<string, typename list<std::pair<string,Solution>>::iterator>* cache =
            new map<string, typename list<std::pair<string,Solution>>::iterator>;
    list<std::pair<string,Solution>>* orderedList = new list<std::pair<string,Solution>>();
public:
    bool isExist(Problem p) {
        string hashedProblem = hashProblem(p);
        //search in cache
        if(this->cache->find(hashedProblem) != this->cache->end()) {
            return true;
        }
            //if it's not in cache, search in disk
        else {
            //if problem is a custom object
            ifstream f(hashedProblem);
            return f.good();
        }
    };
    Solution get(Problem p) {
        if(isExist(p)) {
            string hashedProblem = hashProblem(p);
            //the item is not in the cache map
            if(this->cache->find(hashedProblem) == this->cache->end()) {
                //look it up in disk
                Solution solution =  this->readFile(p);
                //update cache
                //if the cache is full
                if(orderedList->size() == this->size) {
                    //get the last item used
                    Solution lastItem = orderedList->back().second;
                    string k = orderedList->back().first;
                    //pop it
                    orderedList->pop_back();
                    //erase it from map;
                    cache->erase(k);
                    //push new entry
                    orderedList->push_front(std::make_pair(hashedProblem,solution));
                    (*cache)[hashedProblem] = orderedList->begin();
                }
                    //if there's room in the cache
                else {
                    //just push the new entry
                    orderedList->push_front(std::make_pair(hashedProblem, solution));
                    (*cache)[hashedProblem] = orderedList->begin();
                }
                return solution;
            }
                //it is in cache
            else {
                //erase item from list and push it again
                orderedList->push_front(*(*cache)[hashedProblem]);
                orderedList->erase((*cache)[hashedProblem]);
                (*cache)[hashedProblem] = orderedList->begin();
                return orderedList->front().second;
            }
        }
            //its not in cache or disk
        else {
            return nullptr;
        }
    };
    void insert(Problem p, Solution s) {
        string hashedProblem = hashProblem(p);
        //the item is not in the cache
        if(cache->find(hashedProblem) == cache->end()) {
            //if the cache is full
            if(orderedList->size() == this->size) {
                //get the last item used
                Solution lastItem = orderedList->back().second;
                string k = orderedList->back().first;
                //pop it
                orderedList->pop_back();
                //erase it from map;
                cache->erase(k);
                //push new entry
                orderedList->push_front(std::make_pair(hashedProblem,s));
                (*cache)[hashedProblem] = orderedList->begin();
            }
                //if there's room in the cache
            else {
                //just push the new entry
                orderedList->push_front(std::make_pair(hashedProblem,s));
                (*cache)[hashedProblem] = orderedList->begin();
            }
        }
            //the item is in the cache
        else {
            //erase item from list and push it again
            orderedList->erase((*cache)[hashedProblem]);
            orderedList->push_front(std::make_pair(hashedProblem,s));
            //change the value to this
            (*cache)[hashedProblem] = orderedList->begin();
        }
        //write it in disk
        writeFile(p,s);
    };
    string readFile(Problem problem) {
        string solution;
        ifstream in_file(hashProblem(problem));
        getline(in_file, solution);
        in_file.close();
        return solution;
    };
    void writeFile(Problem problem, Solution solution) {
            ofstream out_file;
            out_file.open (hashProblem(problem));
            out_file << solution;
            out_file.close();
    };
    string hashProblem(Problem problem) {
        string afterHashString;
        try {
            int problemHashCode = hash<string>()(problem->toString());
            string stringedProblemHashCode = to_string(problemHashCode);
            afterHashString = stringedProblemHashCode + ".txt";
        }
        catch(...) {
            stringstream s;
            s << problem << ".txt";
            int problemHashCode = hash<string>()(s.str());
            afterHashString = to_string(problemHashCode);
        }
        return afterHashString;
    }
};

#endif //MILESTONE2_CACHEMANAGER_H
