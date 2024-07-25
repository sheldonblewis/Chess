#include "board.h"
#include "king.h"
#include "queen.h"
#include "bishop.h"
#include "knight.h"
#include "rook.h"
#include "pawn.h"
#include <iostream>
#include <vector>

Board::Board() {
    squares.resize(8, std::vector<Square>(8));
    // Initialize squares with pieces in their starting positions
}

void Board::display() const {
    for (const auto& row : squares) {
        for (const auto& square : row) {
            if (square.isOccupied()) {
                std::cout << square.getPiece()->getSymbol() << " ";
            } else {
                std::cout << "_ ";
            }
        }
        std::cout << std::endl;
    }
}

void Board::placePiece(Piece* piece, Coordinate position) {
    squares[position.getX()][position.getY()].setPiece(piece);
}

void Board::removePiece(Coordinate position) {
    squares[position.getX()][position.getY()].removePiece();
}

bool Board::validateMove(Coordinate start, Coordinate end) const {
    // Add logic to validate moves
    return true;
}

bool Board::isCheck() const {
    // Add logic to check if any king is in check
    return false;
}

bool Board::isCheckmate() const {
    // Add logic to check if any king is in checkmate
    return false;
}

bool Board::isStalemate() const {
    // Add logic to check if the game is in stalemate
    return false;
}
