#include "Game.h"

Game::Game(
    GameMode mode,
    CellState firstPlayer,
    CellState humanMark,
    AvatarType playerXAvatar,
    AvatarType playerOAvatar
)
    : mode_(mode),
    humanX_(CellState::X),
    humanO_(CellState::O),
    aiPlayer_(humanMark == CellState::X ? CellState::O : CellState::X),
    firstPlayer_(firstPlayer),
    humanMark_(humanMark),
    playerXAvatar_(playerXAvatar),
    playerOAvatar_(playerOAvatar) {
    reset();
}

void Game::reset() {
    board_.reset();
    currentPlayer_ = firstPlayer_;
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

CellState Game::getHumanMark() const {
    return humanMark_;
}

AvatarType Game::getAvatar(CellState mark) const {
    return mark == CellState::X ? playerXAvatar_ : playerOAvatar_;
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
    for (int i = 0; i < BOARD_SIZE; ++i) {
        if (board_.getCell(i, 0) == mark &&
            board_.getCell(i, 1) == mark &&
            board_.getCell(i, 2) == mark) {
            return true;
        }

        if (board_.getCell(0, i) == mark &&
            board_.getCell(1, i) == mark &&
            board_.getCell(2, i) == mark) {
            return true;
        }
    }

    if (board_.getCell(0, 0) == mark &&
        board_.getCell(1, 1) == mark &&
        board_.getCell(2, 2) == mark) {
        return true;
    }

    if (board_.getCell(0, 2) == mark &&
        board_.getCell(1, 1) == mark &&
        board_.getCell(2, 0) == mark) {
        return true;
    }

    return false;
}

void Game::switchPlayer() {
    currentPlayer_ = currentPlayer_ == CellState::X ? CellState::O : CellState::X;
}
