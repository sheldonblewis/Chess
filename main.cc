#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include "board.h"
#include "computerPlayer.h"
#include "game.h"
#include "humanPlayer.h"

bool isValidPlayerType(const std::string& playerType) {
    if (playerType == "human") {
        return true;
    }
    if (playerType.rfind("computer", 0) == 0) { // check if it starts with "computer"
        if (playerType.length() == 11 && isdigit(playerType[9])) { // ensure there's a level number
            int level = playerType[9] - '0';
            return level >= 1 && level <= 4;
        }
    }
    return false;
}

int main() {
    double whiteScore = 0;
    double blackScore = 0;

    while (true) {
        std::string input;
        std::cout << "\nWelcome to Chess! Please enter 'game <white-player> <black-player> to begin a new game (e.g. 'game human computer[3]'), where the parameters <white-player> and <black-player> can be any of:\n\thuman: human player\n\tcomputer[1]: very easy bot\n\tcomputer[2]: easy bot\n\tcomputer[3]: regular bot\n\tcomputer[4]: advanced bot\nEnter (Ctrl-D) to quit." << std::endl;
        if (!std::getline(std::cin, input)) {
            break; // exit loop if input fails (Ctrl-D)
        }

        std::istringstream iss(input);
        std::string command, whitePlayerType, blackPlayerType;
        iss >> command >> whitePlayerType >> blackPlayerType;

        if (command != "game" || !isValidPlayerType(whitePlayerType) || !isValidPlayerType(blackPlayerType)) {
            std::cout << "Invalid command format. Please start the game with the aforementioned format." << std::endl;
            return 1;
        }

        std::unique_ptr<Player> whitePlayer;
        std::unique_ptr<Player> blackPlayer;

        if (whitePlayerType == "human") {
            whitePlayer = std::make_unique<HumanPlayer>('W');
            std::cout << "\nYou chose human vs " << std::ends;
        } else if (whitePlayerType.find("computer") == 0) {
            int level = whitePlayerType[9] - '0';
            whitePlayer = std::make_unique<ComputerPlayer>('W', level);
            std::cout << "\nYou chose a level " << level << " computer vs " << std::ends;
        }

        if (blackPlayerType == "human") {
            blackPlayer = std::make_unique<HumanPlayer>('B');
            std::cout << "human." << std::endl;
        } else if (blackPlayerType.find("computer") == 0) {
            int level = blackPlayerType[9] - '0';
            blackPlayer = std::make_unique<ComputerPlayer>('B', level);
            std::cout << "a level " << level << " computer." << std::endl;
        }

        Game game(std::move(whitePlayer), std::move(blackPlayer));
        game.startGame();

        while (true) {
            game.getBoard().display(game.getCurrentPlayer()->getColor());
            std::cout << "\n" << (game.getCurrentPlayer()->getColor() == 'W' ? "White" : "Black") << "'s turn: ";
            std::getline(std::cin, input);
            if (input == "resign") {
                game.resign(game.getCurrentPlayer());
                whiteScore += game.getCurrentPlayer()->getColor() == 'W' ? 0 : 1;
                blackScore += game.getCurrentPlayer()->getColor() == 'B' ? 0 : 1;
                break;
            }
            if (input == "move") {
                if (auto computerPlayer = dynamic_cast<ComputerPlayer*>(game.getCurrentPlayer())) {
                    std::string computerMove = computerPlayer->getMove(game.getBoard());
                    std::cout << "Computer move: " << computerMove << std::endl;
                    game.move(computerMove);
                } else {
                    std::cout << "Human player cannot use 'move' without arguments." << std::endl;
                }
            } else if (!game.move(input)) {
                std::cout << "Invalid move. Try again." << std::endl;
                continue;
            }
            
            std::cout << std::endl;

            // check for check, checkmate, stalemate
            Board& board = game.getBoard();
            char currColor = game.getCurrentPlayer()->getColor();
            if (board.isCheck(currColor)) {
                std::cout << (currColor == 'W' ? "Black" : "White") << " is in check." << std::endl;

                if (board.isCheckmate(currColor)) {
                    std::cout << "Checkmate! " << (currColor == 'W' ? "Black" : "White") << " wins!\n" << std::endl;
                    whiteScore += currColor == 'W' ? 0 : 1;
                    blackScore += currColor == 'B' ? 0 : 1;
                    game.getBoard().display(currColor);
                    break;
                } else {
                    std::cout << std::endl;
                }
            }
            else if (board.isStalemate(currColor)) {
                std::cout << "Stalemate!\n" << std::endl;
                whiteScore += 0.5;
                blackScore += 0.5;
                game.getBoard().display(currColor);
                break;
            }

            game.switchPlayer();
        }

        std::cout << "Game over. Returning to main menu..." << std::endl;
    }

    std::cout << "\nFinal Score:" << std::endl;
    std::cout << "White: " << whiteScore << std::endl;
    std::cout << "Black: " << blackScore << std::endl;

    return 0;
}
