#include "knight.h"

Knight::Knight(char color, Coordinate position) : Piece(color, position) {}

bool Knight::validateMove(Coordinate start, Coordinate end) const {
    // Implement knight movement logic
    return true;
}

char Knight::getSymbol() const {
    return color == 'W' ? 'N' : 'n';
}
