#ifndef UNIT_H
#define UNIT_H
#include <iterator>
#include <termios.h>
struct Vec2{
    int e1;
    int e2;
    int& x(){ return e1;}
    int& y(){ return e2;}
    int& width(){return e1;}
    int& height(){return e2;}
    Vec2 (int first, int second) : e1(first), e2(second) {}
    Vec2 operator+(Vec2 speed) {
        return Vec2(this->e1 + speed.e1, this->e2 + speed.e2);
    }
    bool operator==(Vec2 check) {
        return (this->e1 == check.e1 && this->e2 == check.e2);
    }
};

using Position = Vec2;

enum Color {BLACK=0, RED, GREEN, YELLOW, BLUE, PINK, CYAN, WHITE, NOCHANGE};

#endif
