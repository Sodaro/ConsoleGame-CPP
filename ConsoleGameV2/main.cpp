#include <iostream>
#include <string>
#include <Windows.h>
#include <conio.h>
#include <thread>
#include <chrono>

const int LENGTH = 20;
const int HEIGHT = 10;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77


enum Direction { UP,DOWN,LEFT,RIGHT, NONE };


void Wrap(int& value, int min, int max)
{
    if (value < min)
        value = max;
    else if (value > max)
        value = min;
}

struct Wave
{
    Wave(int p_x, int p_y, Direction p_dir, WORD p_color)
    {
        x = p_x; y = p_y;
        dir = p_dir;
        color = p_color;

        updateDisplayChar();
    }

    char chars[4] = { '^','v', '<', '>' };
    void updateDisplayChar()
    {
        displayChar = chars[dir];
    }

    WORD color;
    int x = 0, y = 0;
    Direction dir;
    char displayChar;

    void updateDirection(Direction p_dir)
    {
        if (p_dir == Direction::NONE)
            return;

        dir = p_dir;
        updateDisplayChar();
    }

    void updatePosition()
    {
        switch (dir)
        {
        case UP:
            y--;
            Wrap(y, 0, HEIGHT - 1);
            break;
        case DOWN:
            y++;
            Wrap(y, 0, HEIGHT - 1);
            break;
        case LEFT:
            x--;
            Wrap(x, 0, LENGTH - 1);
            break;
        case RIGHT:
            x++;
            Wrap(x, 0, LENGTH - 1);
            break;
        default:
            break;
        }
    }
};

void ClearScreen()
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


void getInput(int* input)
{
    //Direction dir = Direction::DOWN;
    while (true)
    {
        *input = _getch();
    }   
}


uint64_t getTime()
{
   return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}


class Game
{

    enum Color {
        BLACK, BLUE, GREEN, CYAN, RED,
        MAGENTA, BROWN, LGRAY, DGRAY, LBLUE,
        LGREEN, LCYAN, LRED, LMAGENTA, YELLOW, WHITE
    };



    WORD colors[6] = {
        Color::RED, Color::YELLOW, Color::LGREEN,
        Color::GREEN, Color::BLUE, Color::MAGENTA
    };


    std::string consoleOutput;
    HANDLE handle;
    int colorIndex{ 0 };
    Wave* player;
    int* input;

public:
    Game(HANDLE& p_handle, int* p_input)
    {
        handle = p_handle;
        consoleOutput = std::string(LENGTH * HEIGHT, '.');
        
        player = new Wave(2, 5, Direction::DOWN, 2);
        input = p_input;
    }

    void update()
    {
        
        int oldX, oldY;
        oldX = player->x;
        oldY = player->y;

        Direction newDir = Direction::NONE;
        switch (*input)
        {
        case KEY_UP:
            newDir = Direction::UP;
            break;
        case KEY_DOWN:
            newDir = Direction::DOWN;
            break;
        case KEY_LEFT:
            newDir = Direction::LEFT;
            break;
        case KEY_RIGHT:
            newDir = Direction::RIGHT;
            break;
        default:
            break;
        }

        player->updateDirection(newDir);
        player->updatePosition();

        consoleOutput[oldY * LENGTH + oldX] = '.';
        consoleOutput[player->y * LENGTH + player->x] = player->displayChar;
    }

    void render()
    {
        for (int i = 0; i < HEIGHT; i++)
        {
            for (int j = 0; j < LENGTH; j++)
            {
                std::cout << consoleOutput[LENGTH * i + j];
            }
            std::cout << std::endl;
        }

        ClearScreen();
        colorIndex++;
        colorIndex %= 6;
        SetConsoleTextAttribute(handle, colors[colorIndex]);
    }
};

int main()
{

    uint64_t start;
    uint64_t currentTime;

    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    hideCursor(handle);
    int input = 0;

    auto game = new Game(handle, &input);
    start = getTime();

    Direction newDir = Direction::NONE;
    std::thread inputThread(getInput, &input);

    while (true)
    {
        currentTime = getTime();
        if (currentTime - start < 128.f)
        {
            continue;
        }
        game->update();
        game->render();
        start = currentTime;
    }
}