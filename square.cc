#include "square.h"

Square::Square() : piece(nullptr) {}

bool Square::isOccupied() const {
    return piece != nullptr;
}

Piece* Square::getPiece() const {
    return piece;
}

void Square::setPiece(Piece* piece) {
    this->piece = piece;
}

void Square::removePiece() {
    piece = nullptr;
}
