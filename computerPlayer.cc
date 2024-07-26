#include "computerPlayer.h"
#include "board.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>

ComputerPlayer::ComputerPlayer(char color, int level) : Player(color), difficultyLevel(level), rng(static_cast<unsigned>(std::time(nullptr))) {}

std::vector<std::pair<Coordinate, Coordinate>> ComputerPlayer::getLegalMoves(const Board& board) {
    std::vector<std::pair<Coordinate, Coordinate>> legalMoves;

    // find all pieces belonging to player
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Piece* piece = board.getSquare(Coordinate(i, j)).getPiece();
            if (piece && piece->getColor() == getColor()) {
                for (int x = 0; x < 8; ++x) {
                    for (int y = 0; y < 8; ++y) {
                        Coordinate start(i, j);
                        Coordinate end(x, y);
                        if (board.validateMove(start, end, getColor(), board)) {
                            legalMoves.push_back({start, end});
                        }
                    }
                }
            }
        }
    }

    return legalMoves;
}

std::string ComputerPlayer::getMove(const Board& board) {
    auto legalMoves = getLegalMoves(board);
    if (legalMoves.empty()) {
        return "resign"; // no legal moves available
    }

    // choose random legal move
    std::uniform_int_distribution<size_t> dist(0, legalMoves.size() - 1);
    auto [start, end] = legalMoves[dist(rng)];

    // format move as string
    std::string move = "move ";
    move += (char)('a' + start.getY());
    move += std::to_string(start.getX() + 1);
    move += " ";
    move += (char)('a' + end.getY());
    move += std::to_string(end.getX() + 1);

    return move;
}

char ComputerPlayer::getColor() const {
    return this->color;
}
