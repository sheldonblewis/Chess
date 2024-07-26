#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include "bishop.h"
#include "board.h"
#include "computerPlayer.h"
#include "coordinate.h"
#include "game.h"
#include "humanPlayer.h"
#include "king.h"
#include "knight.h"
#include "pawn.h"
#include "piece.h"
#include "queen.h"
#include "rook.h"

bool isValidPlayerType(const std::string& playerType);
void placePiece(Board& board, char pieceType, std::string squareStr);
void removePiece(Board& board, std::string squareStr);
void setTurn(Board& board, std::string color);
bool validateBoard(Board& board);
Coordinate parseCoordinate(std::string squareStr);
Piece* createPiece(char pieceType, Coordinate coord);
void enterSetupMode(Board& board);


int main() {
    double whiteScore = 0;
    double blackScore = 0;
    Board board;

    while (true) {
        std::string input;
        std::cout << "\nWelcome to Chess! Please enter 'game <white-player> <black-player> to begin a new game (e.g. 'game human computer[3]'), where the parameters <white-player> and <black-player> can be any of:\n\thuman: human player\n\tcomputer[1]: very easy bot\n\tcomputer[2]: easy bot\n\tcomputer[3]: regular bot\n\tcomputer[4]: aggressive bot\nEnter 'setup' for setup mode.\nEnter (Ctrl-D) to quit." << std::endl;
        if (!std::getline(std::cin, input)) {
            break; // exit loop if input fails (Ctrl-D)
        }

        if (input.substr(0, 5) == "setup") {
            enterSetupMode(board);
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
            game.getBoard().display();
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
                    game.getBoard().display();
                    break;
                } else {
                    std::cout << std::endl;
                }
            }
            else if (board.isStalemate(currColor)) {
                std::cout << "Stalemate!\n" << std::endl;
                whiteScore += 0.5;
                blackScore += 0.5;
                game.getBoard().display();
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

void enterSetupMode(Board& board) {
    std::string command;
    while (true) {
        std::cout << "Enter setup command: ";
        std::getline(std::cin, command);

        if (command.substr(0, 1) == "+") {
            char pieceType = command[2];
            std::string squareStr = command.substr(4, 2);
            placePiece(board, pieceType, squareStr);
        } else if (command.substr(0, 1) == "-") {
            std::string squareStr = command.substr(2, 2);
            removePiece(board, squareStr);
        } else if (command.substr(0, 1) == "=") {
            std::string color = command.substr(2);
            setTurn(board, color);
        } else if (command == "done") {
            if (validateBoard(board)) {
                std::cout << "Setup mode completed.\n";
                break;
            } else {
                std::cout << "Invalid board configuration. Please correct and try again.\n";
            }
        } else {
            std::cout << "Invalid command. Please try again.\n";
        }
    }
}


void placePiece(Board& board, char pieceType, std::string squareStr) {
    Coordinate coord = parseCoordinate(squareStr);
    Piece* newPiece = createPiece(pieceType, coord);
    board.setPiece(coord, newPiece);
    board.display();
}

void removePiece(Board& board, std::string squareStr) {
    Coordinate coord = parseCoordinate(squareStr);
    board.removePiece(coord);
    board.display();
}

void setTurn(Board& board, std::string color) {
    if (color == "white") {
        board.setTurn('W');
    } else if (color == "black") {
        board.setTurn('B');
    } else {
        std::cout << "Invalid color. Use 'white' or 'black'.\n";
    }
}

bool validateBoard(Board& board) {
    int whiteKings = 0, blackKings = 0;
    bool valid = true;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Piece* p = board.getSquare(Coordinate(i, j)).getPiece();
            if (p) {
                if (p->getSymbol() == 'K') ++whiteKings;
                if (p->getSymbol() == 'k') ++blackKings;
                if ((i == 0 || i == 7) && dynamic_cast<Pawn*>(p)) {
                    std::cout << "Pawns cannot be on the first or last row.\n";
                    valid = false;
                }
            }
        }
    }
    if (whiteKings != 1 || blackKings != 1) {
        std::cout << "Board must have exactly one white king and one black king.\n";
        valid = false;
    }
    return valid;
}

Coordinate parseCoordinate(std::string squareStr) {
    int x = squareStr[1] - '1'; // convert '1'-'8' to 0-7
    int y = squareStr[0] - 'a'; // convert 'a'-'h' to 0-7
    return Coordinate(x, y);
}

Piece* createPiece(char pieceType, Coordinate coord) {
    switch (pieceType) {
        case 'K': return new King('W', coord);
        case 'k': return new King('B', coord);
        case 'Q': return new Queen('W', coord);
        case 'q': return new Queen('B', coord);
        case 'R': return new Rook('W', coord);
        case 'r': return new Rook('B', coord);
        case 'N': return new Knight('W', coord);
        case 'n': return new Knight('B', coord);
        case 'B': return new Bishop('W', coord);
        case 'b': return new Bishop('B', coord);
        case 'P': return new Pawn('W', coord);
        case 'p': return new Pawn('B', coord);
        default: return nullptr;
    }
}
