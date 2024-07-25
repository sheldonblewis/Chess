#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "player.h"
#include <string>
#include <memory>

class Game {
private:
    Board board;
    std::unique_ptr<Player> whitePlayer;
    std::unique_ptr<Player> blackPlayer;
    Player* currentPlayer;

public:
    Game(std::unique_ptr<Player> white, std::unique_ptr<Player> black);
    void startGame();
    void resign(Player* player);
    bool move(const std::string& input);
    Board& getBoard();
    Player* getCurrentPlayer();
    void switchPlayer();
};

#endif // GAME_H
