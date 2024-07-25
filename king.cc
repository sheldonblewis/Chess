#include "king.h"
#include <cmath>

King::King(char color, Coordinate position) : Piece(color, position) {}

bool King::validateMove(Coordinate start, Coordinate end) const {
    int dx = std::abs(end.getX() - start.getX());
    int dy = std::abs(end.getY() - start.getY());
    return (dx <= 1 && dy <= 1);
}

char King::getSymbol() const {
    return color == 'W' ? 'K' : 'k';
}
