#include <iostream>
#include "bishop.h"
#include "board.h"

Bishop::Bishop(char color, Coordinate position) : Piece(color, position) {}

bool Bishop::validateMove(Coordinate start, Coordinate end, const Board& board) const {
    
    int dx = abs(end.getX() - start.getX());
    int dy = abs(end.getY() - start.getY());

    if (dx != dy) { return false; } // move is not diagonal

    // get direction of movement
    int xDirection = (end.getX() - start.getX()) > 0 ? 1 : -1;
    int yDirection = (end.getY() - start.getY()) > 0 ? 1 : -1;

    // check path is clear
    int x = start.getX() + xDirection;
    int y = start.getY() + yDirection;
    while (x != end.getX() && y != end.getY()) {
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

char Bishop::getSymbol() const {
    return color == 'W' ? 'B' : 'b';
}

Piece* Bishop::clone() const {
    return new Bishop(*this);
}
