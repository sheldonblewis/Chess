#include "coordinate.h"

Coordinate::Coordinate(int x, int y) : x(x), y(y) {} // yes i am aware i swapped the logical x and y. was it intentional? no. was it too late to go back and fix my mistake? yes. still works though. and yes, i don't know how i managed to make life this much harder for myself either

int Coordinate::getX() const {
    return x;
}

int Coordinate::getY() const {
    return y;
}

void Coordinate::setX(int x) {
    this->x = x;
}

void Coordinate::setY(int y) {
    this->y = y;
}
