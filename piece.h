#ifndef PIECE_H
#define PIECE_H

#include "coordinate.h"

class Board;

class Piece {
protected:
    char color; // 'W' for white, 'B' for black
    Coordinate position;
    bool hasMoved;

public:
    Piece(char color, Coordinate position);
    virtual ~Piece() = default;
    
    virtual bool validateMove(Coordinate start, Coordinate end, const Board& board) const = 0;
    Coordinate getPosition() const;
    void setPosition(Coordinate newPos);
    char getColor() const;
    virtual char getSymbol() const = 0;
    bool getHasMoved() const;

    virtual Piece* clone() const = 0;
};

#endif // PIECE_H
