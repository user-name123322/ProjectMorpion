#include "GameController.h"

#include <iostream>

GameController::GameController(GameMode mode, CellState firstPlayer, CellState humanMark)
    : game_(mode, firstPlayer, humanMark) {}

void GameController::run() {
    while (!game_.isGameOver()) {
        view_.draw(game_);
        handleTurn();
    }

    view_.draw(game_);
}

Player& GameController::currentPlayer() {
    const CellState current = game_.getCurrentPlayer();

    if (game_.getMode() == GameMode::HumanVsAI &&
        current == game_.getAIPlayer().getMark()) {
        return game_.getAIPlayer();
    }

    if (current == CellState::X) {
        return game_.getHumanX();
    }

    return game_.getHumanO();
}

void GameController::handleTurn() {
    bool moved = false;

    while (!moved) {
        Player& player = currentPlayer();
        const auto [row, col] = player.play(game_.getBoard());
        moved = game_.makeMove(row, col);

        if (!moved) {
            std::cout << "落子失败，请重新输入。\n";
            view_.draw(game_);
        }
    }
}
