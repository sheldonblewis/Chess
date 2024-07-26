#include "rook.h"

Rook::Rook(char color, Coordinate position) : Piece(color, position) {}

bool Rook::validateMove(Coordinate start, Coordinate end, const Board& board) const {
    int startX = start.getX();
    int startY = start.getY();
    int endX = end.getX();
    int endY = end.getY();

    // not a straight line
    if (startX != endX && startY != endY) {
        return false;
    }

    // get direction of movement
    int xDirection = (endX - startX) > 0 ? 1 : -1;
    int yDirection = (endY - startY) > 0 ? 1 : -1;

    if (startX == endX) {
        xDirection = 0;
    } else {
        yDirection = 0;
    }

    // check path is clear
    int x = startX + xDirection;
    int y = startY + yDirection;
    while (x != endX || y != endY) {
        if (board.getSquare(Coordinate(x, y)).isOccupied()) {
            return false; // path is not clear
        }
        x += xDirection;
        y += yDirection;
    }

    // check if destination is empty or occupied by an opponent's piece
    if (board.getSquare(end).isOccupied()) {
        Piece* endPiece = board.getSquare(end).getPiece();
        if (endPiece->getColor() == this->color) {
            return false; // destination occupied by own piece
        }
    }

    return true;
}

char Rook::getSymbol() const {
    return color == 'W' ? 'R' : 'r';
}

Piece* Rook::clone() const {
    return new Rook(*this);
}
