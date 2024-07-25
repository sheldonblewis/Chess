#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"

class Queen : public Piece {
public:
    Queen(char color, Coordinate position);
    bool validateMove(Coordinate start, Coordinate end) const override;
    char getSymbol() const override;
};

#endif // QUEEN_H
