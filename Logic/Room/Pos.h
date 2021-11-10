#ifndef POS_H
#define POS_H

struct Pos {
    int x;
    int y;

    friend int operator == (Pos one, Pos another) {
        return one.x == another.x && one.y == another.y;
    }
};

#endif // POS_H
