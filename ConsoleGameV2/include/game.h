#pragma once

#include <Windows.h>
#include <string>
#include <iostream>
#include "player.h"

const int LENGTH = 20;
const int HEIGHT = 10;

void clearScreen();
void hideCursor(HANDLE& handle);

class Game
{
    enum Color {
        BLACK, BLUE, GREEN, CYAN, RED,
        MAGENTA, BROWN, LGRAY, DGRAY, LBLUE,
        LGREEN, LCYAN, LRED, LMAGENTA, YELLOW, WHITE
    };

    WORD colors[4] = {
        Color::MAGENTA, Color::LMAGENTA, Color::LBLUE,
        Color::BLUE
    };

    std::string consoleOutput;
    HANDLE handle;
    int colorIndex, renderTicks;
    Player* player;
    int* input;

public:
    Game(HANDLE& p_handle, int* p_input);
    void update();

    void render();
};