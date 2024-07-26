#ifndef KING_H
#define KING_H

#include "board.h"
#include "piece.h"

class King : public Piece {
public:
    King(char color, Coordinate position);
    bool validateMove(Coordinate start, Coordinate end, const Board& board) const override;
    char getSymbol() const override;

    Piece* clone() const override;
};

#endif // KING_H
