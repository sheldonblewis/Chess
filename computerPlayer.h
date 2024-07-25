#ifndef COMPUTER_PLAYER_H
#define COMPUTER_PLAYER_H

#include "player.h"

class ComputerPlayer : public Player {
private:
    int difficultyLevel;

public:
    ComputerPlayer(char color, int level);
    void makeMove(Coordinate start, Coordinate end) override;
    int getDifficultyLevel() const;
};

#endif // COMPUTER_PLAYER_H
