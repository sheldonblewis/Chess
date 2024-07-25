#include <iostream>
#include "game.h"
#include "humanPlayer.h"
#include "computerPlayer.h"

int main() {
    HumanPlayer white('W');
    ComputerPlayer black('B', 1);
    Game game(&white, &black);
    game.startGame();

    // Implement game loop to handle commands

    return 0;
}
