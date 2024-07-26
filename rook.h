#ifndef ROOK_H
#define ROOK_H

#include "board.h"
#include "piece.h"

class Rook : public Piece {
public:
    Rook(char color, Coordinate position);
    bool validateMove(Coordinate start, Coordinate end, const Board& board) const override;
    char getSymbol() const override;

    Piece* clone() const override;
};

#endif // ROOK_H
