#include "rook.h"

Rook::Rook(char color, Coordinate position) : Piece(color, position) {}

bool Rook::validateMove(Coordinate start, Coordinate end) const {
    // Implement rook movement logic
    return true;
}

char Rook::getSymbol() const {
    return color == 'W' ? 'R' : 'r';
}
