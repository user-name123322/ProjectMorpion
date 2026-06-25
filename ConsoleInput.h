#pragma once

#include "Board.h"

#include <string>
#include <utility>

namespace ConsoleInput {
bool clearInvalidInput();
int readIntInRange(const std::string& prompt, int minValue, int maxValue);
std::pair<int, int> readBoardMove(const Board& board, const std::string& prompt);
}
