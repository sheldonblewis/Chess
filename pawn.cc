#include "board.h"
#include "pawn.h"
#include <cmath>

Pawn::Pawn(char color, Coordinate position) : Piece(color, position) {}

bool Pawn::validateMove(Coordinate start, Coordinate end, const Board& board) const {
    int startX = start.getX();
    int startY = start.getY();
    int endX = end.getX();
    int endY = end.getY();
    int dx = endX - startX;
    int dy = endY - startY;

    // white pawns move +X
    if (color == 'W') {
        if (dy == 0 && dx == 1 && !board.getSquare(end).isOccupied()) {
            return true; // standard 1-step move
        }
        if (startX == 1 && dx == 2 && dy == 0 && !board.getSquare(end).isOccupied() && !board.getSquare(Coordinate(startX + 1, startY)).isOccupied()) {
            return true; // initial 2-step move
        }
        if (abs(dy) == 1 && dx == 1 && board.getSquare(end).isOccupied() && board.getSquare(end).getPiece()->getColor() == 'B') {
            return true; // diagonal capture
        }
    } else { // black pawns move -X
        if (dy == 0 && dx == -1 && !board.getSquare(end).isOccupied()) {
            return true; // standard 1-step move
        }
        if (startX == 6 && dy == 0 && dx == -2 && !board.getSquare(end).isOccupied() && !board.getSquare(Coordinate(startX - 1, startY)).isOccupied()) {
            return true; // initial 2-step move
        }
        if (dx == -1 && abs(dy) == 1 && board.getSquare(end).isOccupied() && board.getSquare(end).getPiece()->getColor() == 'W') {
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

Piece* Pawn::clone() const {
    return new Pawn(*this);
}
