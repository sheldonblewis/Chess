#include "computerPlayer.h"
#include "board.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>

ComputerPlayer::ComputerPlayer(char color, int level) : Player(color), difficultyLevel(level), rng(static_cast<unsigned>(std::time(nullptr))) {}

// level 1+
std::vector<std::pair<Coordinate, Coordinate>> ComputerPlayer::getLegalMoves(const Board& board) {
    std::vector<std::pair<Coordinate, Coordinate>> legalMoves;

    // find all pieces belonging to player
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Piece* piece = board.getSquare(Coordinate(i, j)).getPiece();
            if (piece && piece->getColor() == getColor()) {
                for (int x = 0; x < 8; ++x) {
                    for (int y = 0; y < 8; ++y) {
                        if (i == x && j == y) {
                            continue;
                        }
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

// level 2+
std::vector<std::pair<Coordinate, Coordinate>> ComputerPlayer::getCapturingMoves(const std::vector<std::pair<Coordinate, Coordinate>>& legalMoves, const Board& board) {
    std::vector<std::pair<Coordinate, Coordinate>> capturingMoves;
    for (const auto& move : legalMoves) {
        Coordinate end = move.second;
        if (board.getSquare(end).isOccupied() && board.getSquare(end).getPiece()->getColor() != getColor()) { // capture is possible
            capturingMoves.push_back(move);
        }
    }
    return capturingMoves;
}

// level 2+
std::vector<std::pair<Coordinate, Coordinate>> ComputerPlayer::getCheckingMoves(const std::vector<std::pair<Coordinate, Coordinate>>& legalMoves, const Board& board) {
    std::vector<std::pair<Coordinate, Coordinate>> checkingMoves;
    for (const auto& move : legalMoves) {
        Coordinate start = move.first;
        Coordinate end = move.second;
        Board tempBoard = board;
        tempBoard.movePiece(start, end);
        if (tempBoard.isCheck(getColor() == 'W' ? 'B' : 'W')) { // checks the opponent
            checkingMoves.push_back(move);
        }
    }
    return checkingMoves;
}

std::string ComputerPlayer::getMove(const Board& board) {
    auto legalMoves = getLegalMoves(board);
    auto priorityMoves = legalMoves;
    if (legalMoves.empty()) {
        return "resign"; // no legal moves available
    }

    if (difficultyLevel > 1) {
        // prioritize capturing
        auto capturingMoves = getCapturingMoves(legalMoves, board);
        if (!capturingMoves.empty()) {
            priorityMoves = capturingMoves;
        } else {
            // prioritize checking (secondary)
            auto checkingMoves = getCheckingMoves(legalMoves, board);
            if (!checkingMoves.empty()) {
                priorityMoves = checkingMoves;
            }
        }
    }

    // choose random move from priority set
    //    (level 2: capturing -> checking -> legal)
    //    (level 1: legal)
    std::uniform_int_distribution<size_t> dist(0, priorityMoves.size() - 1);
    auto [start, end] = priorityMoves[dist(rng)];

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
