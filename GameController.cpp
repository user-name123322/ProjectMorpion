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

void GameController::handleTurn() {
    bool moved = false;

    while (!moved) {
        Player* player = nullptr;
        const CellState currentPlayer = game_.getCurrentPlayer();

        if (game_.getMode() == GameMode::HumanVsAI &&
            currentPlayer == game_.getAIPlayer().getMark()) {
            player = &game_.getAIPlayer();
        }
        else if (currentPlayer == CellState::X) {
            player = &game_.getHumanX();
        }
        else {
            player = &game_.getHumanO();
        }

        const auto [row, col] = player->play(game_.getBoard());
        moved = game_.makeMove(row, col);

        if (!moved) {
            std::cout << "落子失败，请重新输入。\n";
            view_.draw(game_);
        }
    }
}
