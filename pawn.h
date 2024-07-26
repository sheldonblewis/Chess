#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class Pawn : public Piece {
public:
    Pawn(char color, Coordinate position);
    bool validateMove(Coordinate start, Coordinate end, const Board& board) const override;
    void promote(Piece* newPiece);
    char getSymbol() const override;

    Piece* clone() const override;
};

#endif // PAWN_H
