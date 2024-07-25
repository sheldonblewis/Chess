#ifndef SQUARE_H
#define SQUARE_H

#include "piece.h"

class Square {
private:
    Piece* piece;

public:
    Square();
    bool isOccupied() const;
    Piece* getPiece() const;
    void setPiece(Piece* piece);
    void removePiece();
};

#endif // SQUARE_H
