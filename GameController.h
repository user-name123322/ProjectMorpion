#pragma once

#include "BoardView.h"
#include "Game.h"

class GameController {
public:
    explicit GameController(
        GameMode mode,
        CellState firstPlayer = CellState::X,
        CellState humanMark = CellState::X
    );

    void run();

private:
    Player& currentPlayer();
    void handleTurn();

private:
    Game game_;
    BoardView view_;
};
