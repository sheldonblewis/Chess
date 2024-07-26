#include "square.h"

Square::Square() : p(nullptr) {}

bool Square::isOccupied() const {
    return p != nullptr;
}

Piece* Square::getPiece() const {
    return p;
}

void Square::setPiece(Piece* p) {
    this->p = p;
}

void Square::removePiece() {
    this->p = nullptr;
}
