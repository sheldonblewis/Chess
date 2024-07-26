#include "game.h"
#include <iostream>
#include <sstream>
#include <memory>

Game::Game(std::unique_ptr<Player> white, std::unique_ptr<Player> black) : whitePlayer(std::move(white)), blackPlayer(std::move(black)), currentPlayer(whitePlayer.get()) {}

void Game::startGame() {
    // begin game
    std::cout << "Game started. White goes first.\n" << std::endl;
}

void Game::resign(Player* player) {
    std::cout << (player->getColor() == 'W' ? "Black" : "White") << " wins!" << std::endl;
}

bool Game::move(const std::string& input) {
    std::istringstream iss(input);
    std::string command, start, end, promotionChoice;
    iss >> command >> start >> end >> promotionChoice;

    if (command != "move" || start.length() != 2 || end.length() != 2) {
        std::cout << "Invalid input format. Please use 'move <start> <end>'." << std::endl;
        return false;
    }

    // convert input to board coords
    int startX = start[1] - '1';
    int startY = start[0] - 'a';
    int endX = end[1] - '1';
    int endY = end[0] - 'a';

    if (startX < 0 || startX >= 8 || startY < 0 || startY >= 8 || endX < 0 || endX >= 8 || endY < 0 || endY >= 8) {
        std::cout << "Coordinates out of bounds. Please use valid board coordinates (a1 to h8)." << std::endl;
        return false;
    }

    Coordinate startCoord(startX, startY);
    Coordinate endCoord(endX, endY);

    // check if there is a piece at the starting location
    Square& startSquare = board.getSquare(startCoord);
    if (!startSquare.isOccupied()) {
        std::cout << "No piece at " << start << ". Try again.\n" << std::endl;
        return false;
    }

    // determine promotion piece if any
    char promotionPiece = '\0';
    if (promotionChoice.length() == 1) {
        promotionPiece = promotionChoice[0];
    }

    // validate and execute move
    if (board.validateMove(startCoord, endCoord, getCurrentPlayer()->getColor(), board)) {
        // checks if already in check
        bool inCheck = false;
        if (board.isCheck(getCurrentPlayer()->getColor())) {
            inCheck = true;
        }

        //simulate move
        Board tempBoard = board;
        tempBoard.movePiece(startCoord, endCoord);

        // check if the move puts or keeps in the current player in check
        char otherColor = getCurrentPlayer()->getColor() == 'W' ? 'B' : 'W';
        if (tempBoard.isCheck(otherColor)) {
            if (inCheck) {
                std::cout << "Still in check. Try again.\n" << std::endl;
            } else {
            std::cout << "This move puts you in check. Try again.\n" << std::endl;
            }
            return false;
        }
        // execute
        board.movePiece(startCoord, endCoord, promotionPiece);
        return true;
    } else {
        std::cout << "Invalid move. Try again\n" << std::endl;
        return false;
    }
}

Board& Game::getBoard() {
    return board;
}

Player* Game::getCurrentPlayer() const {
    return currentPlayer;
}

void Game::switchPlayer() {
    currentPlayer = (currentPlayer == whitePlayer.get()) ? blackPlayer.get() : whitePlayer.get();
}
