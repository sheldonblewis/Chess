#ifndef KING_H
#define KING_H

#include "piece.h"

class King : public Piece {
public:
    King(char color, Coordinate position);
    bool validateMove(Coordinate start, Coordinate end) const override;
    char getSymbol() const override;
};

#endif // KING_H