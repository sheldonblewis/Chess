#ifndef PLAYER_H
#define PLAYER_H

#include "coordinate.h"

class Player {
protected:
    char color;

public:
    Player(char color);
    virtual ~Player() = default;
    virtual void makeMove(Coordinate start, Coordinate end) = 0;
    char getColor() const;
};

#endif // PLAYER_H
