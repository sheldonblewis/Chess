#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "coordinate.h"
#include "piece.h"
#include "square.h"

class Board {
private:
    std::vector<std::vector<Square>> squares;

public:
    Board();
    void display() const;
    void placePiece(Piece* p, Coordinate position);
    void removePiece(Coordinate position);
    bool validateMove(Coordinate start, Coordinate end, const Board& board) const;
    void movePiece(Coordinate start, Coordinate end);
    bool isCheck(char color) const;
    bool isCheckmate() const;
    bool isStalemate() const;
    Square& getSquare(Coordinate coord);
    const Square& getSquare(Coordinate coord) const; // read-only
};

#endif // BOARD_H
