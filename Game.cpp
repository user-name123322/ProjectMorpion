#include "Game.h"

Game::Game(GameMode mode)
    : mode_(mode),
    humanX_(CellState::X),
    humanO_(CellState::O),
    aiPlayer_(CellState::O) {
    reset();
}

void Game::reset() {
    board_.reset();
    currentPlayer_ = CellState::X;
    winner_ = CellState::Empty;
    gameOver_ = false;
    draw_ = false;
}

Board& Game::getBoard() {
    return board_;
}

const Board& Game::getBoard() const {
    return board_;
}

CellState Game::getCurrentPlayer() const {
    return currentPlayer_;
}

CellState Game::getWinner() const {
    return winner_;
}

bool Game::isGameOver() const {
    return gameOver_;
}

bool Game::isDraw() const {
    return draw_;
}

GameMode Game::getMode() const {
    return mode_;
}

HumanPlayer& Game::getHumanX() {
    return humanX_;
}

HumanPlayer& Game::getHumanO() {
    return humanO_;
}

AIPlayer& Game::getAIPlayer() {
    return aiPlayer_;
}

bool Game::makeMove(int row, int col) {
    if (gameOver_) {
        return false;
    }

    if (!board_.placeMark(row, col, currentPlayer_)) {
        return false;
    }

    if (checkWinner(currentPlayer_)) {
        winner_ = currentPlayer_;
        gameOver_ = true;
        return true;
    }

    if (board_.isFull()) {
        draw_ = true;
        gameOver_ = true;
        return true;
    }

    switchPlayer();
    return true;
}

bool Game::checkWinner(CellState mark) const {
    // TODO 4：
    // 判断横向、纵向、两条对角线是否有三个相同的 mark

    return false;
}

void Game::switchPlayer() {
    // TODO 5：
    // 在 X 和 O 之间切换当前玩家
}