#ifndef SQUARE_H
#define SQUARE_H

#include "piece.h"

class Square {
private:
    Piece* p;

public:
    Square();
    bool isOccupied() const;
    Piece* getPiece() const;
    void setPiece(Piece* p);
    void removePiece();
};

#endif // SQUARE_H
