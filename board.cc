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
                std::cout << squares[i][j].getPiece()->getSymbol();
            } else {
                // determine square color
                if ((i + j) % 2 == 1) {
                    std::cout << " "; // empty white squares
                } else {
                    std::cout << "_"; // empty black squares
                }
            }
        }
        std::cout << std::endl;
    }
    std::cout << "  abcdefgh" << std::endl;
}

void Board::placePiece(Piece* p, Coordinate position) {
    squares[position.getX()][position.getY()].setPiece(p);
}

void Board::removePiece(Coordinate position) {
    squares[position.getX()][position.getY()].removePiece();
}

bool Board::validateMove(Coordinate start, Coordinate end, char currColor, const Board& board) const {
    // move validation logic
    Piece* p = squares[start.getX()][start.getY()].getPiece();
    if (p->getColor() != currColor) {
        return false; // trying to move opponent's piece or no piece at all
    }
    return p->validateMove(start, end, board);
}

void Board::movePiece(Coordinate start, Coordinate end) {
    Piece* p = squares[start.getX()][start.getY()].getPiece();
    if (p) {
        removePiece(start); // clear piece from start square
        p->setPosition(end); // update pos in 2D-vector
        placePiece(p, end); // place piece in end square
    }
}

bool Board::isCheck(char color) const {
    Coordinate kingPos(-1, -1);
    bool found = false;

    // locate opponent's King
    for (int i = 0; i < 8 && !found; ++i) {
        for (int j = 0; j < 8 && !found; ++j) {
            if (squares[i][j].isOccupied()) {
                Piece* piece = squares[i][j].getPiece();
                if (piece->getColor() != color && dynamic_cast<King*>(piece)) {
                    kingPos = Coordinate(i, j);
                    found = true;
                }
            }
        }
    }

    if (kingPos.getX() == -1) {
        return false; // no king ???
    }

    // check if any of the current player's pieces can attack the opponent's King
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (squares[i][j].isOccupied()) {
                Piece* piece = squares[i][j].getPiece();
                if (piece->getColor() == color) {
                    if (piece->validateMove(Coordinate(i, j), kingPos, *this)) {
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

bool Board::isCheckmate(char color) const {
    char otherColor = color == 'W' ? 'B' : 'W';
    
    // confirm opponent's king is in check
    if (!isCheck(color)) {
        return false;
    }

    // iterate through all of opponent's pieces
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (squares[i][j].isOccupied()) {
                Piece* piece = squares[i][j].getPiece();
                if (piece->getColor() == otherColor) {
                    // try moving each opponent piece to all possible positions on the board
                    for (int x = 0; x < 8; ++x) {
                        for (int y = 0; y < 8; ++y) {
                            Coordinate start(i, j);
                            Coordinate end(x, y);
                            
                            // ensure move is valid and doesn't leave the King in check
                            if (piece->validateMove(start, end, *this)) {
                                // temporarily make the move on a copy of the board
                                Board tempBoard = *this;
                                tempBoard.movePiece(start, end);

                                if (!tempBoard.isCheck(color)) {
                                    return false; // King is no longer in check 
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    // no escape found
    return true;
}

bool Board::isStalemate(char color) const {
    char otherColor = color == 'W' ? 'B' : 'W';

    // confirm opponent's king is not in check
    if (isCheck(color)) {
        return false;
    }

    // iterate through all of current player's pieces
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (squares[i][j].isOccupied()) {
                Piece* piece = squares[i][j].getPiece();
                if (piece->getColor() == otherColor) {
                    // try moving each piece to all possible positions on the board
                    for (int x = 0; x < 8; ++x) {
                        for (int y = 0; y < 8; ++y) {
                            Coordinate start(i, j);
                            Coordinate end(x, y);

                            // ensure move is valid and doesn't put the King in check
                            if (piece->validateMove(start, end, *this)) {
                                // temporarily make the move on a copy of the board
                                Board tempBoard = *this;
                                tempBoard.movePiece(start, end);

                                if (!tempBoard.isCheck(color)) {
                                    return false; // found a legal move
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    // no legal moves found
    return true;
}

Square& Board::getSquare(Coordinate coord) {
    return squares[coord.getX()][coord.getY()];
}

const Square& Board::getSquare(Coordinate coord) const {
    return squares[coord.getX()][coord.getY()];
}
