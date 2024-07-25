#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "player.h"

class Game {
private:
    Board board;
    Player* whitePlayer;
    Player* blackPlayer;

public:
    Game(Player* white, Player* black);
    void startGame();
    void resign(Player* player);
    void move(Coordinate start, Coordinate end);
    void setup();
    void enterSetupMode();
    void exitSetupMode();
};

#endif // GAME_H
