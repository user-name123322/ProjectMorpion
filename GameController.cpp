#include "GameController.h"
#include <iostream>

GameController::GameController(GameMode mode)
    : game_(mode) {}

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

        if (game_.getCurrentPlayer() == CellState::X) {
            player = &game_.getHumanX();
        }
        else if (game_.getMode() == GameMode::HumanVsAI) {
            player = &game_.getAIPlayer();
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
