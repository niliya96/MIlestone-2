//
// Created by idan on 1/23/20.
//

#ifndef MILESTONE_2_STRING_H
#define MILESTONE_2_STRING_H
#include <string>
using namespace std;
class String {
private:
    string s;
public:
    // string object for strings, so we can operate to_string on them
    String(string newS) {
        this->s = newS;
    }
    string toString() {
        return this->s;
    }
};

#endif //MILESTONE_2_STRING_H
