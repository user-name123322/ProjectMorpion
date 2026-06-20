#include "Config.h"
#include "GameController.h"

#include <iostream>
#include <limits>
#include <random>
#include <string>

#ifdef _WIN32
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

const char* avatarToName(AvatarType avatar) {
    switch (avatar) {
    case AvatarType::Cat:
        return "小猫";
    case AvatarType::Dog:
        return "小狗";
    case AvatarType::Bird:
        return "小鸟";
    case AvatarType::RedPanda:
        return "小熊猫";
    case AvatarType::Fish:
        return "小鱼";
    default:
        return "未知形象";
    }
}

AvatarType avatarFromChoice(int choice) {
    switch (choice) {
    case 1:
        return AvatarType::Cat;
    case 2:
        return AvatarType::Dog;
    case 3:
        return AvatarType::Bird;
    case 4:
        return AvatarType::RedPanda;
    case 5:
        return AvatarType::Fish;
    default:
        return AvatarType::Cat;
    }
}

void clearInvalidInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int readChoice(int minValue, int maxValue) {
    int choice = 0;

    while (!(std::cin >> choice) || choice < minValue || choice > maxValue) {
        std::cout << "输入无效，请输入 " << minValue << " 到 " << maxValue << "：";
        clearInvalidInput();
    }

    return choice;
}

void showAvatarMenu() {
    std::cout << "请选择你的形象卡：\n";
    std::cout << "1. 小猫\n";
    std::cout << "2. 小狗\n";
    std::cout << "3. 小鸟\n";
    std::cout << "4. 小熊猫\n";
    std::cout << "5. 小鱼\n";
    std::cout << "请输入选择：";
}

AvatarType chooseAvatar(const std::string& prompt) {
    std::cout << prompt << "\n";
    showAvatarMenu();
    return avatarFromChoice(readChoice(1, 5));
}

AvatarType chooseDifferentAvatar(AvatarType usedAvatar) {
    for (int choice = 1; choice <= 5; ++choice) {
        AvatarType avatar = avatarFromChoice(choice);
        if (avatar != usedAvatar) {
            return avatar;
        }
    }

    return AvatarType::Dog;
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
    std::cout << "请输入选择：";

    const int modeChoice = readChoice(1, 2);
    GameMode mode = modeChoice == 1 ? GameMode::HumanVsHuman : GameMode::HumanVsAI;
    CellState humanMark = CellState::X;
    AvatarType playerXAvatar = AvatarType::Cat;
    AvatarType playerOAvatar = AvatarType::Dog;

    if (mode == GameMode::HumanVsHuman) {
        playerXAvatar = chooseAvatar("玩家 X 选择形象卡。");
        std::cout << "玩家 X 选择了：" << avatarToName(playerXAvatar) << "\n";

        playerOAvatar = chooseAvatar("玩家 O 选择形象卡。");
        std::cout << "玩家 O 选择了：" << avatarToName(playerOAvatar) << "\n";
    }
    else {
        std::cout << "请选择你的棋子：\n";
        std::cout << "1. X\n";
        std::cout << "2. O\n";
        std::cout << "请输入选择：";

        const int markChoice = readChoice(1, 2);
        humanMark = markChoice == 1 ? CellState::X : CellState::O;
        const AvatarType humanAvatar = chooseAvatar("请选择你的形象卡。");
        const AvatarType aiAvatar = chooseDifferentAvatar(humanAvatar);

        if (humanMark == CellState::X) {
            playerXAvatar = humanAvatar;
            playerOAvatar = aiAvatar;
        }
        else {
            playerXAvatar = aiAvatar;
            playerOAvatar = humanAvatar;
        }

        std::cout << "你选择了玩家 " << markToChar(humanMark)
            << "（" << avatarToName(humanAvatar) << "）。\n";
        std::cout << "AI 是玩家 "
            << markToChar(humanMark == CellState::X ? CellState::O : CellState::X)
            << "（" << avatarToName(aiAvatar) << "）。\n";
    }

    const CellState firstPlayer = randomFirstPlayer();
    std::cout << "本局随机先手：玩家 " << markToChar(firstPlayer) << "\n";

    GameController controller(mode, firstPlayer, humanMark, playerXAvatar, playerOAvatar);
    controller.run();

    std::cout << "\n按回车键退出程序...";

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();

    return 0;
}
