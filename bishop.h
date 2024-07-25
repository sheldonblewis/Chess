#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"

class Bishop : public Piece {
public:
    Bishop(char color, Coordinate position);
    bool validateMove(Coordinate start, Coordinate end) const override;
    char getSymbol() const override;
};

#endif // BISHOP_H
