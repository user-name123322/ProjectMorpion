#include "Player.h"
#include <iostream>
#include <limits>

Player::Player(CellState mark) : mark_(mark) {}

CellState Player::getMark() const {
    return mark_;
}

HumanPlayer::HumanPlayer(CellState mark) : Player(mark) {}

std::pair<int, int> HumanPlayer::play(const Board& board) {
    int row = -1;
    int col = -1;

    std::cout << "请输入行号和列号（0-" << BOARD_SIZE - 1 << "），例如 1 2：";

    if (!(std::cin >> row >> col)) {
        std::cout << "输入无效，请输入两个数字。\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return { -1, -1 };
    }

    if (!board.isInside(row, col)) {
        std::cout << "坐标超出棋盘范围。\n";
    }
    else if (!board.isEmpty(row, col)) {
        std::cout << "该位置已经有棋子。\n";
    }

    return { row, col };
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
