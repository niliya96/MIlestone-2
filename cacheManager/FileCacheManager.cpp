#include <fstream>
#include "CacheManager.h"
template class FileCacheManager<string,string>;

template<class Problem, class Solution>
void FileCacheManager<Problem, Solution>::insert(Problem p, Solution s) {
    //the item is not in the cache
    if(cache->find(p) == cache->end()) {
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
}

template<class Problem, class Solution>
Solution FileCacheManager<Problem, Solution>::get(Problem p) {
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
                string k = orderedList->back().first;
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
}

template<class Problem, class Solution>
bool FileCacheManager<Problem, Solution>::isExist(Problem p) {
    //search in cache
    if(this->cache->find(p) != this->cache->end()) {
        return true;
    }
        //if it's not in cache, search in disk
    else {
        string s = p +".txt";
        ifstream f(s);
        return f.good();
    }
}

template<class Problem, class Solution>
string FileCacheManager<Problem, Solution>::readFile(Problem problem) {
    string s = problem +".txt";
    ifstream in_file(s);
    string solution;
    getline(in_file, solution);
    in_file.close();
    return solution;
}

template<class Problem, class Solution>
void FileCacheManager<Problem, Solution>::writeFile(Problem problem, Solution solution) {
    string s = problem +".txt";
    ofstream out_file;
    out_file.open (s);
    out_file << solution;
    out_file.close();
}
