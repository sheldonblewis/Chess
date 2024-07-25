#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "piece.h"
#include "square.h"

class Board {
private:
    std::vector<std::vector<Square>> squares;

public:
    Board();
    void display() const;
    void placePiece(Piece* piece, Coordinate position);
    void removePiece(Coordinate position);
    bool validateMove(Coordinate start, Coordinate end) const;
    void movePiece(Coordinate start, Coordinate end);
    bool isCheck() const;
    bool isCheckmate() const;
    bool isStalemate() const;
};

#endif // BOARD_H
