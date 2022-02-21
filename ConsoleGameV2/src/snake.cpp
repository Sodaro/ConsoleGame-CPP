#include <snake.h>

Snake::Snake()
{
    this->x = 0;
    this->y = 0;
    this->next = nullptr;
    this->prev_x = 0;
    this->prev_y = 0;
}

Snake::Snake(int x, int y)
{
    this->x = x;
    this->y = y;
    this->next = nullptr;
    this->prev_x = x;
    this->prev_y = y;
}

void Snake::setNext(Snake* next)
{
    this->next = next;
}

void Snake::setPosition(int x, int y)
{
    prev_x = this->x;
    prev_y = this->y;
    if (next != nullptr)
    {
        next->setPosition(prev_x, prev_y);
    }

    this->x = x;
    this->y = y;
}