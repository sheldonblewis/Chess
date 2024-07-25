#include "pawn.h"

Pawn::Pawn(char color, Coordinate position) : Piece(color, position) {}

bool Pawn::validateMove(Coordinate start, Coordinate end) const {
    // Implement pawn movement logic
    return true;
}

void Pawn::promote(Piece* newPiece) {
    // Implement pawn promotion logic
}

char Pawn::getSymbol() const {
    return color == 'W' ? 'P' : 'p';
}
