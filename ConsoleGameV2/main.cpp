#include <chrono>
#include <conio.h>
#include <thread>
#include "game.h"

void getInput(int* input)
{
    while (true)
    {
        *input = _getch();
    }   
}

uint64_t getTime()
{
   using namespace std::chrono;
   return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}


int main()
{
    uint64_t start;
    uint64_t currentTime;

    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

    //hide the console-caret
    hideCursor(handle);
    int input = 0;

    auto game = new Game(handle, &input);

    //use separate thread for non-blocking input
    std::thread inputThread(getInput, &input);

    start = getTime();

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