#include "Player.h"
#include <iostream>
#include <limits>

Player::Player(CellState mark) : mark_(mark) {}

CellState Player::getMark() const {
    return mark_;
}

HumanPlayer::HumanPlayer(CellState mark) : Player(mark) {}

std::pair<int, int> HumanPlayer::play(const Board& board) {
    // TODO 2：
    // 1. 从命令行输入 row 和 col
    // 2. 如果输入非法，需要清理输入流
    // 3. 返回玩家输入的坐标

    return { -1, -1 };
}

AIPlayer::AIPlayer(CellState mark) : Player(mark) {}

std::pair<int, int> AIPlayer::play(const Board& board) {
    // TODO 3：
    // 简单 AI：从左到右、从上到下寻找第一个空格

    return { -1, -1 };
}