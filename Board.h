#pragma once

#include "Config.h"

#include <array>

class Board {
public:
    Board();

    void reset();
    bool placeMark(int row, int col, CellState mark);
    CellState getCell(int row, int col) const;
    CellState getCellOrDefault(int row, int col, CellState defaultValue = CellState::Empty) const;
    bool isEmpty(int row, int col) const;
    bool isInside(int row, int col) const;
    bool isFull() const;

private:
    std::array<std::array<CellState, BOARD_SIZE>, BOARD_SIZE> grid_;
};
