#ifndef KNIGHT_H
#define KNIGHT_H

#include "board.h"
#include "piece.h"

class Knight : public Piece {
public:
    Knight(char color, Coordinate position);
    bool validateMove(Coordinate start, Coordinate end, const Board& board) const override;
    char getSymbol() const override;
};

#endif // KNIGHT_H
