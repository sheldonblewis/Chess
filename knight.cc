#include "knight.h"

Knight::Knight(char color, Coordinate position) : Piece(color, position) {}

bool Knight::validateMove(Coordinate start, Coordinate end, const Board& board) const {
    int startX = start.getX();
    int startY = start.getY();
    int endX = end.getX();
    int endY = end.getY();

    // calculate x and y movement
    int dx = abs(endX - startX);
    int dy = abs(endY - startY);

    // check if the move is an "L" shape: 2 by 1 or 1 by 2
    if (!((dx == 2 && dy == 1) || (dx == 1 && dy == 2))) {
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

char Knight::getSymbol() const {
    return color == 'W' ? 'N' : 'n';
}
