#ifndef QUEEN_H
#define QUEEN_H

#include "board.h"
#include "piece.h"

class Queen : public Piece {
public:
    Queen(char color, Coordinate position);
    bool validateMove(Coordinate start, Coordinate end, const Board& board) const override;
    char getSymbol() const override;

    Piece* clone() const override;
};

#endif // QUEEN_H
