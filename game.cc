#include "game.h"
#include <iostream>
#include <sstream>
#include <memory>

Game::Game(std::unique_ptr<Player> white, std::unique_ptr<Player> black) : whitePlayer(std::move(white)), blackPlayer(std::move(black)), currentPlayer(whitePlayer.get()) {}

void Game::startGame() {
    // begin game
    std::cout << "Game started. White goes first." << std::endl;
}

void Game::resign(std::unique_ptr<Player> player) {
    std::cout << (player->getColor() == 'W' ? "White" : "Black") << " resigns." << std::endl;
    std::cout << (player->getColor() == 'W' ? "Black" : "White") << " wins!" << std::endl;
}

bool Game::move(const std::string& input) {
    std::istringstream iss(input);
    std::string start, end;
    iss >> start >> end;

    if (start.length() != 2 || end.length() != 2) {
        std::cout << "Invalid input format." << std::endl;
        return false;
    }

    int startX = start[1] - '1';
    int startY = start[0] - 'a';
    int endX = end[1] - '1';
    int endY = end[0] - 'a';

    if (startX < 0 || startX >= 8 || startY < 0 || startY >= 8 || endX < 0 || endX >= 8 || endY < 0 || endY >= 8) {
        std::cout << "Input coordinates out of bounds." << std::endl;
        return false;
    }

    Coordinate startCoord(startX, startY);
    Coordinate endCoord(endX, endY);

    if (board.validateMove(startCoord, endCoord)) {
        board.movePiece(startCoord, endCoord);
        return true;
    } else {
        std::cout << "Invalid move." << std::endl;
        return false;
    }
}

Board& Game::getBoard() {
    return board;
}

Player* Game::getCurrentPlayer() {
    return currentPlayer;
}

void Game::switchPlayer() {
    currentPlayer = (currentPlayer == whitePlayer.get()) ? blackPlayer.get() : whitePlayer.get();
}
