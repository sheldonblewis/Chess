#ifndef PLAYER_H
#define PLAYER_H

#include "board.h"
#include "coordinate.h"
#include <string>

class Player {
protected:
    char color;

public:
    Player(char color);
    virtual ~Player() = default;
    char getColor() const;
    virtual std::string getMove(const Board& board) = 0;
};

#endif // PLAYER_H
