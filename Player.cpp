#include "Player.h"
#include "ConsoleInput.h"

#include <iostream>

Player::Player(CellState mark) : mark_(mark) {}

CellState Player::getMark() const {
    return mark_;
}

HumanPlayer::HumanPlayer(CellState mark) : Player(mark) {}

std::pair<int, int> HumanPlayer::play(const Board& board) {
    return ConsoleInput::readBoardMove(
        board,
        "请输入行号和列号（0-" + std::to_string(BOARD_SIZE - 1) + "），例如 1 2："
    );
}

AIPlayer::AIPlayer(CellState mark) : Player(mark) {}

std::pair<int, int> AIPlayer::play(const Board& board) {
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            if (board.isEmpty(row, col)) {
                std::cout << "AI 选择位置：" << row << " " << col << "\n";
                return { row, col };
            }
        }
    }

    return { -1, -1 };
}
