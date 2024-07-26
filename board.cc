#include "board.h"
#include "king.h"
#include "queen.h"
#include "bishop.h"
#include "knight.h"
#include "rook.h"
#include "pawn.h"
#include "piece.h"
#include <iostream>
#include <vector>
#include <string>

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

    for (int i = 2; i < 6; ++i) {
        for (int j = 0; j < 8; ++j) {
            squares[i][j] = Square();
        }
    }
}

Board::Board(const Board& other) {
    squares.resize(8, std::vector<Square>(8));
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (other.squares[i][j].isOccupied()) {
                Piece* pieceCopy = other.squares[i][j].getPiece()->clone();
                squares[i][j].setPiece(pieceCopy);
            } else {
                squares[i][j].removePiece();
            }
        }
    }
    lastMoveStart = other.lastMoveStart;
    lastMoveEnd = other.lastMoveEnd;
}

Board::~Board() {
    for (auto& row : squares) {
        for (auto& square : row) {
            if (square.isOccupied()) {
                delete square.getPiece();
                square.removePiece();
            }
        }
    }
}

void Board::display(char currColor) const {
    // swap display for white and black
    // if (currColor == 'W') {
    //     for (int i = 7; i >= 0; --i) {
    //         std::cout << (i + 1) << " ";
    //         for (int j = 0; j < 8; ++j) {
    //             if (squares[i][j].isOccupied()) {
    //                 std::cout << squares[i][j].getPiece()->getSymbol();
    //             } else {
    //                 // determine square color
    //                 if ((i + j) % 2 == 1) {
    //                     std::cout << " "; // empty white squares
    //                 } else {
    //                     std::cout << "_"; // empty black squares
    //                 }
    //             }
    //         }
    //         std::cout << std::endl;
    //     }
    // } else if (currColor == 'B') {
    //     for (int i = 0; i <= 7; ++i) {
    //         std::cout << (i + 1) << " ";
    //         for (int j = 0; j < 8; ++j) {
    //             if (squares[i][j].isOccupied()) {
    //                 std::cout << squares[i][j].getPiece()->getSymbol();
    //             } else {
    //                 // determine square color
    //                 if ((i + j) % 2 == 1) {
    //                     std::cout << " "; // empty white squares
    //                 } else {
    //                     std::cout << "_"; // empty black squares
    //                 }
    //             }
    //         }
    //         std::cout << std::endl;
    //     }
    // }
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
    std::cout << "\n  abcdefgh" << std::endl;
}

void Board::placePiece(Piece* p, Coordinate position) {
    squares[position.getX()][position.getY()].setPiece(p);
}

void Board::removePiece(Coordinate position) {
    squares[position.getX()][position.getY()].removePiece();
}

bool Board::validateMove(Coordinate start, Coordinate end, char currColor, const Board& board) const {
    Piece* p = squares[start.getX()][start.getY()].getPiece();
    if (p->getColor() != currColor) {
        std::cout << "HEY. Hands off your opponent's piece." << std::endl;
        return false; // trying to move opponent's piece or no piece at all
    }

    // check for en passant
    if (dynamic_cast<Pawn*>(p)) {
        if (start.getX() == lastMoveEnd.getX() && std::abs(start.getY() - end.getY()) == 1 && start.getX() == (currColor == 'W' ? 4 : 3)) {
            Piece* lastMovedPiece = squares[lastMoveEnd.getX()][lastMoveEnd.getY()].getPiece();
            if (lastMovedPiece && dynamic_cast<Pawn*>(lastMovedPiece) && lastMovedPiece->getColor() != currColor) {
                if (lastMoveEnd.getX() - lastMoveStart.getX() == 2 || lastMoveEnd.getX() - lastMoveStart.getX() == -2) {
                    return true; // en passant is valid
                }
            }
        }
    }

    // check for castling
    if (dynamic_cast<King*>(p) && std::abs(end.getY() - start.getY()) == 2) {
        Coordinate rookStart = (end.getY() > start.getY()) ? Coordinate(start.getX(), 7) : Coordinate(start.getX(), 0);
        if (canCastle(start, rookStart, end, (end.getY() > start.getY()) ? Coordinate(start.getX(), end.getY() - 1) : Coordinate(start.getX(), end.getY() + 1), currColor)) {
            return true;
        }
    }

    return p->validateMove(start, end, board);
}

void Board::movePiece(Coordinate start, Coordinate end, char promotionPiece) {
    Piece* p = squares[start.getX()][start.getY()].getPiece();
    if (p) {
        // en passant capture
        if (dynamic_cast<Pawn*>(p) && start.getX() != end.getX() && !squares[end.getX()][end.getY()].isOccupied()) {
            int captureX = start.getX();
            int captureY = end.getY();
            removePiece(Coordinate(captureX, captureY));
        }

        // normal move
        removePiece(start); // clear piece from start square
        p->setPosition(end); // update pos in 2D-vector

        // track last move for en passant
        lastMoveStart = start;
        lastMoveEnd = end;

        // pawn promotion
        if (dynamic_cast<Pawn*>(p) && (end.getX() == 0 || end.getX() == 7)) {
            Piece* promotedPiece = nullptr;
            switch (promotionPiece) {
                case 'Q':
                    std::cout << "Promoting pawn to Queen." << std::endl;
                    promotedPiece = new Queen(p->getColor(), end);
                    break;
                case 'R':
                    std::cout << "Promoting pawn to rook." << std::endl;
                    promotedPiece = new Rook(p->getColor(), end);
                    break;
                case 'B':
                    std::cout << "Promoting pawn to bishop." << std::endl;
                    promotedPiece = new Bishop(p->getColor(), end);
                    break;
                case 'N':
                    std::cout << "Promoting pawn to knight." << std::endl;
                    promotedPiece = new Knight(p->getColor(), end);
                    break;
                default:
                    promotedPiece = new Queen(p->getColor(), end);
                    break;
            }
            placePiece(promotedPiece, end);
        } else {
            placePiece(p, end);
        }

        // castling
        if (dynamic_cast<King*>(p) && std::abs(end.getY() - start.getY()) == 2) {
            Coordinate rookStart = (end.getY() > start.getY()) ? Coordinate(start.getX(), 7) : Coordinate(start.getX(), 0);
            castle(start, rookStart);
        }
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

bool Board::isPathClear(Coordinate start, Coordinate end) const {
    int startX = start.getX();
    int endX = end.getX();
    int startY = start.getY();
    int endY = end.getY();

    if (startX != endX && startY != endY) return false; // not a straight line

    int xDirection = (endX - startX) ? (endX - startX) / std::abs(endX - startX) : 0;
    int yDirection = (endY - startY) ? (endY - startY) / std::abs(endY - startY) : 0;

    int x = startX + xDirection;
    int y = startY + yDirection;
    while (x != endX || y != endY) {
        if (squares[x][y].isOccupied()) return false;
        x += xDirection;
        y += yDirection;
    }

    return true;
}

bool Board::isUnderAttack(Coordinate pos, char attackingColor) const {
    for (const auto& row : squares) {
        for (const auto& square : row) {
            if (square.isOccupied() && square.getPiece()->getColor() == attackingColor) {
                if (square.getPiece()->validateMove(square.getPiece()->getPosition(), pos, *this)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Board::canCastle(Coordinate kingStart, Coordinate rookStart, Coordinate kingEnd, Coordinate rookEnd, char kingColor) const {
    Piece* king = squares[kingStart.getX()][kingStart.getY()].getPiece();
    Piece* rook = squares[rookStart.getX()][rookStart.getY()].getPiece();

    if (!king || !rook) {
        return false;
    }
    if (!dynamic_cast<King*>(king) || !dynamic_cast<Rook*>(rook)) {
        return false;
    }
    if (king->getHasMoved() || rook->getHasMoved()) {
        return false;
    }
    if (!isPathClear(kingStart, rookStart)) {
        return false;
    }
    int middle = (kingStart.getX() + kingEnd.getX()) / 2;
    char attackingColor = kingColor == 'W' ? 'B' : 'W';
    if (isUnderAttack(kingStart, attackingColor) || isUnderAttack(Coordinate(middle, kingStart.getY()), attackingColor) || isUnderAttack(kingEnd, attackingColor)) {
        return false;
    }

    return true;
}

void Board::castle(Coordinate kingStart, Coordinate rookStart) {
    if (kingStart.getY() < rookStart.getY()) {
        // kingside castling
        movePiece(kingStart, Coordinate(kingStart.getX(), kingStart.getY() + 2));
        movePiece(rookStart, Coordinate(kingStart.getX(), kingStart.getY() + 1));
    } else {
        // queenside castling
        movePiece(kingStart, Coordinate(kingStart.getX(), kingStart.getY() - 2));
        movePiece(rookStart, Coordinate(kingStart.getX(), kingStart.getY() - 1));
    }
}
