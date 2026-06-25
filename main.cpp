#include "Config.h"
#include "ConsoleInput.h"
#include "GameController.h"

#include <iostream>
#include <random>

#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
#endif

namespace {
CellState randomFirstPlayer() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<int> dist(0, 1);

    return dist(gen) == 0 ? CellState::X : CellState::O;
}

char markToChar(CellState mark) {
    return mark == CellState::X ? 'X' : 'O';
}
}

int main() {
#ifdef _WIN32
    // 设置 Windows 控制台输入和输出为 UTF-8，解决中文乱码问题
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    std::cout << "============================\n";
    std::cout << "       Morpion MVC C++      \n";
    std::cout << "============================\n";
    std::cout << "请选择游戏模式：\n";
    std::cout << "1. 双人对战\n";
    std::cout << "2. 人机对战\n";

    const int modeChoice = ConsoleInput::readIntInRange("请输入选择：", 1, 2);
    const GameMode mode = modeChoice == 1 ? GameMode::HumanVsHuman : GameMode::HumanVsAI;
    CellState humanMark = CellState::X;

    if (mode == GameMode::HumanVsAI) {
        std::cout << "请选择你的棋子：\n";
        std::cout << "1. X\n";
        std::cout << "2. O\n";

        const int markChoice = ConsoleInput::readIntInRange("请输入选择：", 1, 2);
        humanMark = markChoice == 1 ? CellState::X : CellState::O;
        std::cout << "你选择了玩家 " << markToChar(humanMark) << "。\n";
        std::cout << "AI 是玩家 "
            << markToChar(humanMark == CellState::X ? CellState::O : CellState::X)
            << "。\n";
    }

    const CellState firstPlayer = randomFirstPlayer();
    std::cout << "本局随机先手：玩家 " << markToChar(firstPlayer) << "\n";

    GameController controller(mode, firstPlayer, humanMark);
    controller.run();

    std::cout << "\n按回车键退出程序...";
    ConsoleInput::clearInvalidInput();
    std::cin.get();

    return 0;
}
