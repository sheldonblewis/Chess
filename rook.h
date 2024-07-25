#ifndef ROOK_H
#define ROOK_H

#include "piece.h"

class Rook : public Piece {
public:
    Rook(char color, Coordinate position);
    bool validateMove(Coordinate start, Coordinate end) const override;
    char getSymbol() const override;
};

#endif // ROOK_H
