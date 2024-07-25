#include "queen.h"

Queen::Queen(char color, Coordinate position) : Piece(color, position) {}

bool Queen::validateMove(Coordinate start, Coordinate end) const {
    // Implement queen movement logic
    return true;
}

char Queen::getSymbol() const {
    return color == 'W' ? 'Q' : 'q';
}
