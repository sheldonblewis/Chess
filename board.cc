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

    // initial pos - white pieces
    squares[0][0].setPiece(new Rook('W', Coordinate(0, 0)));
    squares[0][1].setPiece(new Knight('W', Coordinate(0, 1)));
    squares[0][2].setPiece(new Bishop('W', Coordinate(0, 2)));
    squares[0][3].setPiece(new Queen('W', Coordinate(0, 3)));
    squares[0][4].setPiece(new King('W', Coordinate(0, 4)));
    squares[0][5].setPiece(new Bishop('W', Coordinate(0, 5)));
    squares[0][6].setPiece(new Knight('W', Coordinate(0, 6)));
    squares[0][7].setPiece(new Rook('W', Coordinate(0, 7)));

    for (int i = 0; i < 8; ++i) {
        squares[1][i].setPiece(new Pawn('W', Coordinate(1, i)));
    }

    // initial pos - black pieces
    squares[7][0].setPiece(new Rook('B', Coordinate(7, 0)));
    squares[7][1].setPiece(new Knight('B', Coordinate(7, 1)));
    squares[7][2].setPiece(new Bishop('B', Coordinate(7, 2)));
    squares[7][3].setPiece(new Queen('B', Coordinate(7, 3)));
    squares[7][4].setPiece(new King('B', Coordinate(7, 4)));
    squares[7][5].setPiece(new Bishop('B', Coordinate(7, 5)));
    squares[7][6].setPiece(new Knight('B', Coordinate(7, 6)));
    squares[7][7].setPiece(new Rook('B', Coordinate(7, 7)));

    for (int i = 0; i < 8; ++i) {
        squares[6][i].setPiece(new Pawn('B', Coordinate(6, i)));
    }
}

void Board::display() const {
    for (int i = 7; i >= 0; --i) {
        std::cout << (i + 1) << " ";
        for (int j = 0; j < 8; ++j) {
            if (squares[i][j].isOccupied()) {
                std::cout << squares[i][j].getPiece()->getSymbol() << " ";
            } else {
                std::cout << ". ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << "  a b c d e f g h" << std::endl;
}

void Board::placePiece(Piece* piece, Coordinate position) {
    squares[position.getX()][position.getY()].setPiece(piece);
}

void Board::removePiece(Coordinate position) {
    squares[position.getX()][position.getY()].removePiece();
}

bool Board::validateMove(Coordinate start, Coordinate end) const {
    // move validation logic
    Piece* piece = squares[start.getX()][start.getY()].getPiece();
    return piece && piece->validateMove(start, end);
}

void Board::movePiece(Coordinate start, Coordinate end) {
    Piece* piece = squares[start.getX()][start.getY()].getPiece();
    removePiece(start);
    piece->setPosition(end);
    placePiece(piece, end);
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
