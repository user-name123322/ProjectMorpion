#pragma once

#include "Game.h"
#include "BoardView.h"

class GameController {
public:
    explicit GameController(
        GameMode mode,
        CellState firstPlayer = CellState::X,
        CellState humanMark = CellState::X,
        AvatarType playerXAvatar = AvatarType::Cat,
        AvatarType playerOAvatar = AvatarType::Dog
    );

    // 启动游戏主循环
    void run();

private:
    // 处理一个回合
    void handleTurn();

private:
    Game game_;
    BoardView view_;
};
