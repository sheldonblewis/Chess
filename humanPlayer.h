#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H

#include "player.h"

class HumanPlayer : public Player {
public:
    HumanPlayer(char color);
    void makeMove(Coordinate start, Coordinate end) override;
};

#endif // HUMAN_PLAYER_H
