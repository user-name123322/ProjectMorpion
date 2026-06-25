#include "ConsoleInput.h"

#include <iostream>
#include <limits>

namespace ConsoleInput {
bool clearInvalidInput() {
    if (std::cin.eof()) {
        return false;
    }

    std::cin.clear();
    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
    return true;
}

int readIntInRange(const std::string& prompt, int minValue, int maxValue) {
    int value = 0;

    while (true) {
        std::cout << prompt;

        if (std::cin >> value && value >= minValue && value <= maxValue) {
            clearInvalidInput();
            return value;
        }

        if (std::cin.eof()) {
            return minValue;
        }

        std::cout << "输入无效，请输入 " << minValue << " 到 " << maxValue << " 之间的数字。\n";
        if (!clearInvalidInput()) {
            return minValue;
        }
    }
}

std::pair<int, int> readBoardMove(const Board& board, const std::string& prompt) {
    int row = -1;
    int col = -1;

    while (true) {
        std::cout << prompt;

        if (!(std::cin >> row >> col)) {
            if (std::cin.eof()) {
                return { -1, -1 };
            }

            std::cout << "输入无效，请输入两个数字。\n";
            if (!clearInvalidInput()) {
                return { -1, -1 };
            }
            continue;
        }

        if (!clearInvalidInput()) {
            return { -1, -1 };
        }

        if (!board.isInside(row, col)) {
            std::cout << "坐标超出棋盘范围。\n";
            continue;
        }

        if (!board.isEmpty(row, col)) {
            std::cout << "该位置已经有棋子。\n";
            continue;
        }

        return { row, col };
    }
}
}
