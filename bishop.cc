#include "bishop.h"

Bishop::Bishop(char color, Coordinate position) : Piece(color, position) {}

bool Bishop::validateMove(Coordinate start, Coordinate end) const {
    // Implement bishop movement logic
    return true;
}

char Bishop::getSymbol() const {
    return color == 'W' ? 'B' : 'b';
}
