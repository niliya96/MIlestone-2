#ifndef MILESTONE2_SEARCHABLE_H
#define MILESTONE2_SEARCHABLE_H
template <class T> class Searchable {
public:

};

class MyPoint {
private:
    int x,y;
public:
    MyPoint(int i, int j) {
        this->x = i;
        this->y = j;
    }
    int getX() {
        return this->x;
    }
    int getY() {
        return this->y;
    }
    void setX(int i) {
        this->x = i;
    }
    void setY(int j) {
        this->y = j;
    }
    MyPoint getPoint() {
        return *this;
    }

};
#endif //MILESTONE2_SEARCHABLE_H
