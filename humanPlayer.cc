#include "humanPlayer.h"
#include <iostream>

HumanPlayer::HumanPlayer(char color) : Player(color) {}

std::string HumanPlayer::getMove(const Board& board) {
    std::string move;
    std::cout << "Enter your move: ";
    std::getline(std::cin, move);
    return move;
}

char HumanPlayer::getColor() const {
    return this->color;
}
