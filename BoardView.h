#pragma once

#include "Game.h"

class BoardView {
public:
    void draw(const Game& game) const;
    void drawBoard(const Board& board) const;
    void drawStatus(const Game& game) const;

private:
    void drawColumnHeader() const;
    void drawDivider() const;
    char cellToChar(CellState cell) const;
};
