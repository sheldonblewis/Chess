#include "computerPlayer.h"

ComputerPlayer::ComputerPlayer(char color, int level) : Player(color), difficultyLevel(level) {}

void ComputerPlayer::makeMove(Coordinate start, Coordinate end) {
    // Implement AI move logic based on difficulty level
}

int ComputerPlayer::getDifficultyLevel() const {
    return difficultyLevel;
}
