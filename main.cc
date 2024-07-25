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
        std::cout << (game.getCurrentPlayer()->getColor() == 'W' ? "White" : "Black") << "'s turn: ";
        std::getline(std::cin, input);
        if (input == "resign") {
            game.resign(game.getCurrentPlayer());
            break;
        }
        if (!game.move(input)) {
            std::cout << "Invalid move. Try again." << std::endl;
            continue; // if invalid, allow another input
        }
        if (game.getBoard().isCheckmate()) {
            std::cout << "Checkmate! " << (game.getCurrentPlayer()->getColor() == 'W' ? "Black" : "White") << " wins!" << std::endl;
            break;
        }
        if (game.getBoard().isStalemate()) {
            std::cout << "Stalemate! The game is a draw." << std::endl;
            break;
        }
        game.switchPlayer();
    }

    return 0;
}
