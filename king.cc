#include "king.h"
#include <cmath>

King::King(char color, Coordinate position) : Piece(color, position) {}

bool King::validateMove(Coordinate start, Coordinate end, const Board& board) const {
    int startX = start.getX();
    int startY = start.getY();
    int endX = end.getX();
    int endY = end.getY();

    // calculate x and y movement
    int dx = abs(endX - startX);
    int dy = abs(endY - startY);

    // ensure movement is at most 1 in both directions
    if (dx > 1 || dy > 1) {
        return false;
    }

    // check if destination is occupied by own piece
    if (board.getSquare(end).isOccupied()) {
        Piece* endPiece = board.getSquare(end).getPiece();
        if (endPiece->getColor() == this->color) {
            return false; // destination occupied by own piece
        }
    }

    return true;
}

char King::getSymbol() const {
    return color == 'W' ? 'K' : 'k';
}
