#include "queen.h"

Queen::Queen(char color, Coordinate position) : Piece(color, position) {}

bool Queen::validateMove(Coordinate start, Coordinate end, const Board& board) const {
    int startX = start.getX();
    int startY = start.getY();
    int endX = end.getX();
    int endY = end.getY();

    // calculate x and y movement
    int dx = abs(endX - startX);
    int dy = abs(endY - startY);

    // confirm move is either straight or diagonal
    if (!((dx == 0 || dy == 0) || (dx == dy))) {
        return false;
    }

    // get direction of movement
    int xDirection = (endX - startX) > 0 ? 1 : -1;
    int yDirection = (endY - startY) > 0 ? 1 : -1;

    if (dx == 0) {
        xDirection = 0;
    } else if (dy == 0) {
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

char Queen::getSymbol() const {
    return color == 'W' ? 'Q' : 'q';
}

Piece* Queen::clone() const {
    return new Queen(*this);
}
