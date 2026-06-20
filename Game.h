#pragma once

#include "Board.h"
#include "Player.h"

class Game {
public:
    explicit Game(
        GameMode mode,
        CellState firstPlayer = CellState::X,
        CellState humanMark = CellState::X
    );

    // 重置游戏
    void reset();

    Board& getBoard();
    const Board& getBoard() const;

    CellState getCurrentPlayer() const;
    CellState getWinner() const;
    CellState getHumanMark() const;

    bool isGameOver() const;
    bool isDraw() const;

    GameMode getMode() const;

    HumanPlayer& getHumanX();
    HumanPlayer& getHumanO();
    AIPlayer& getAIPlayer();

    // 执行一步落子
    bool makeMove(int row, int col);

    // 判断指定棋子是否获胜
    bool checkWinner(CellState mark) const;

    // 切换当前玩家
    void switchPlayer();

private:
    GameMode mode_;
    Board board_;

    HumanPlayer humanX_;
    HumanPlayer humanO_;
    AIPlayer aiPlayer_;

    CellState firstPlayer_ = CellState::X;
    CellState humanMark_ = CellState::X;
    CellState currentPlayer_ = CellState::X;
    CellState winner_ = CellState::Empty;

    bool gameOver_ = false;
    bool draw_ = false;
};
