#pragma once
#include "game.h"

void clearScreen()
{
    COORD cursorPosition;
    cursorPosition.X = 0;
    cursorPosition.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}
void hideCursor(HANDLE& handle)
{
    //https://stackoverflow.com/questions/18028808/remove-blinking-underscore-on-console-cmd-prompt

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(handle, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(handle, &cursorInfo);
}


Game::Game(HANDLE& p_handle, int* p_input)
{
    handle = p_handle;
    consoleOutput = std::string(LENGTH * HEIGHT, '.');

    player = new Player(2, 5, LENGTH - 1, HEIGHT - 1);
    input = p_input;
    renderTicks = colorIndex = 0;

}

void Game::update()
{
    int oldX, oldY;
    oldX = player->getX();
    oldY = player->getY();

    player->update(input);

    consoleOutput[oldY * LENGTH + oldX] = '.';
    consoleOutput[player->getY() * LENGTH + player->getX()] = player->getDisplayChar();
}

void Game::render()
{
    clearScreen();

    //write the output to console
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < LENGTH; j++)
        {
            std::cout << consoleOutput[LENGTH * i + j];
        }
        std::cout << std::endl;
    }

    //update color
    renderTicks++;
    if (renderTicks % 4 == 0)
    {
        colorIndex++;
        colorIndex %= 4;
        SetConsoleTextAttribute(handle, colors[colorIndex]);
    }
}