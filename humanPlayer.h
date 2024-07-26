#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H

#include "player.h"

class HumanPlayer : public Player {
public:
    HumanPlayer(char color);
    ~HumanPlayer() override = default;
    std::string getMove(const Board& board) override;
    char getColor() const;
};

#endif // HUMAN_PLAYER_H
