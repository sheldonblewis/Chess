#ifndef COMPUTER_PLAYER_H
#define COMPUTER_PLAYER_H

#include "board.h"
#include "player.h"
#include <random>

class ComputerPlayer : public Player {
private:
    int difficultyLevel;
    std::mt19937 rng; // RNG
    std::vector<std::pair<Coordinate, Coordinate>> getLegalMoves(const Board& board);

public:
    ComputerPlayer(char color, int level);
    ~ComputerPlayer() override = default;
    int getDifficultyLevel() const;
    std::string getMove(const Board& board) override;
    char getColor() const;
};

#endif // COMPUTER_PLAYER_H
