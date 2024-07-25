#include <iostream>
#include "board.h"
#include "computerPlayer.h"
#include "game.h"
#include "humanPlayer.h"

int main() {
    std::unique_ptr<HumanPlayer> white = std::make_unique<HumanPlayer>('W');
    std::unique_ptr<HumanPlayer> black = std::make_unique<HumanPlayer>('B');
    Game game(std::move(white), std::move(black));
    game.startGame();

    std::string input;
    while (true) {
        game.getBoard().display();
        std::cout << "\n" << (game.getCurrentPlayer()->getColor() == 'W' ? "White" : "Black") << "'s turn: ";
        std::getline(std::cin, input);
        if (input == "resign") {
            game.resign(game.getCurrentPlayer());
            break;
        }
        if (!game.move(input)) {
            continue; // if invalid, input again
        }
        
        std::cout << std::endl;

        // check for check, checkmate, stalemate
        Board& board = game.getBoard();
        char currColor = game.getCurrentPlayer()->getColor();
        if (board.isCheck(currColor)) {
            std::cout << (currColor == 'W' ? "Black" : "White") << " is in check." << std::endl;

            if (board.isCheckmate(currColor)) {
                std::cout << "Checkmate! " << (currColor == 'W' ? "Black" : "White") << " wins!\n" << std::endl;
                game.getBoard().display();
                break;
            } else {
                std::cout << std::endl;
            }
        }
        else if (board.isStalemate(currColor)) {
            std::cout << "Stalemate!\n" << std::endl;
            game.getBoard().display();
            break;
        }

        game.switchPlayer();
    }

    return 0;
}
