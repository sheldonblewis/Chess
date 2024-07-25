#include "piece.h"

Piece::Piece(char color, Coordinate position) : color(color), position(position) {}

Coordinate Piece::getPosition() const {
    return position;
}

void Piece::setPosition(Coordinate newPos) {
    position = newPos;
}

char Piece::getColor() const {
    return color;
}
