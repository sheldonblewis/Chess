#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "coordinate.h"
#include "piece.h"
#include "square.h"

class Board {
private:
    std::vector<std::vector<Square>> squares;

    // for en passant
    Coordinate lastMoveStart;
    Coordinate lastMoveEnd;

    char currentTurn;

public:
    Board();
    Board(const Board& other);
    ~Board();

    const std::vector<std::vector<Square>>& getSquares() const;
    void display() const;
    void placePiece(Piece* p, Coordinate position);
    void removePiece(Coordinate position);
    bool validateMove(Coordinate start, Coordinate end, char currColor, const Board& board) const;
    void movePiece(Coordinate start, Coordinate end, char PromotionPiece = '\0');
    bool isCheck(char color) const;
    bool isCheckmate(char color) const;
    bool isStalemate(char color) const;
    Square& getSquare(Coordinate coord);
    const Square& getSquare(Coordinate coord) const; // read-only
    void setPiece(Coordinate coord, Piece* piece);
    void setTurn(char color);

    // for castling
    bool canCastle(Coordinate kingStart, Coordinate rookStart, Coordinate kingEnd, Coordinate rookEnd, char kingColor) const;
    void castle(Coordinate kingStart, Coordinate rookStart);
    bool isPathClear(Coordinate start, Coordinate end) const;
    bool isUnderAttack(Coordinate pos, char attackingColor) const;
};

#endif // BOARD_H
