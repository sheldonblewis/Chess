#ifndef PIECE_H
#define PIECE_H

#include "coordinate.h"

class Piece {
protected:
    Coordinate position;
    char color; // 'W' for white, 'B' for black

public:
    Piece(char color, Coordinate position);
    virtual ~Piece() = default;
    virtual bool validateMove(Coordinate start, Coordinate end) const = 0;
    Coordinate getPosition() const;
    void setPosition(Coordinate newPos);
    char getColor() const;
    virtual char getSymbol() const = 0;
};

#endif // PIECE_H
