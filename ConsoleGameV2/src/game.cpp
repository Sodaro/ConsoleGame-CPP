#pragma once
#include "game.h"

void resetCaretPos()
{
    //move the caret to the beginning, so that when we write it will overwrite the existing output
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
    input = p_input;
    initialize();
}

void Game::update()
{
    if (player == nullptr)
        return;

    int oldX, oldY, newX, newY;
    Snake* last = player->last;
    
    if (last != nullptr)
    {
        oldX = last->x;
        oldY = last->y;
    }
    else
    {
        oldX = player->x;
        oldY = player->y;
    }
    usedPositions[oldY * LENGTH + oldX] = false;
    consoleOutput[oldY * LENGTH + oldX] = '.';
    
    player->update(input);
    newX = player->x;
    newY = player->y;

    int index = newY * LENGTH + newX;
    for (int i = 0; i < sizeof(usedPositions) / sizeof(bool); i++)
    {
        if (usedPositions[i] == false)
            continue;

        if (index == i)
        {
            restart();
            return;
        }
    }

    consoleOutput[index] = player->getDisplayChar();
    usedPositions[index] = true;


    Snake* head = player->head;
    if (head != nullptr)
    {
        Snake* part = head;
        while (part != nullptr)
        {
            newX = part->x;
            newY = part->y;
            usedPositions[newY * LENGTH + newX] = true;
            consoleOutput[newY * LENGTH + newX] = 'o';
            part = part->next;
        }
    }


    updateTicks++;
    if (updateTicks % 10 == 0)
    {
        player->addSnakePart();
    }
}

void Game::render()
{
    resetCaretPos();

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

void Game::restart()
{
    Snake* current = player->head;
    Snake* next = NULL;

    while (current != NULL)
    {
        next = current->next;
        delete current;
        current = next;
    }

    for (int i = 0; i < sizeof(usedPositions) / sizeof(bool); i++)
    {
        usedPositions[i] = false;
    }
    delete player;
    player = nullptr;
    initialize();
}

void Game::initialize()
{
    consoleOutput = std::string(LENGTH * HEIGHT, '.');

    player = new Player(0, 0, LENGTH - 1, HEIGHT - 1);

    renderTicks = colorIndex = 0;

    resetCaretPos();
    hideCursor(handle);
}