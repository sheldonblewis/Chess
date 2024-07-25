#include "pawn.h"
#include <cmath>

Pawn::Pawn(char color, Coordinate position) : Piece(color, position) {}

bool Pawn::validateMove(Coordinate start, Coordinate end) const {
    int dx = std::abs(end.getX() - start.getX());
    int dy = std::abs(end.getY() - start.getY());

    if (color == 'W') {
        if (dy == 0 && dx == 1 && end.getX() > start.getX()) {
            return true;
        }
        if (start.getX() == 1 && end.getX() == 3 && dy == 0) {
            return true; // initial 2-step move
        }
        if (dy == 1 && dx == 1 && end.getX() > start.getX()) {
            return true; // diagonal capture
        }
    } else {
        if (dy == 0 && dx == 1 && end.getX() < start.getX()) {
            return true;
        }
        if (start.getX() == 6 && end.getX() == 4 && dy == 0) {
            return true; // initial 2-step move
        }
        if (dy == 1 && dx == 1 && end.getX() < start.getX()) {
            return true; // diagonal capture
        }
    }
    return false;
}

void Pawn::promote(Piece* newPiece) {
    // Implement pawn promotion logic
}

char Pawn::getSymbol() const {
    return color == 'W' ? 'P' : 'p';
}
