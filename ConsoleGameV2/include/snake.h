#pragma once

class Snake
{
public:
    Snake* next;
    int x, y, prev_x, prev_y;
    Snake();
    Snake(int x, int y);
    void setNext(Snake* next);
    Snake* getNext(){ return next; };
    void setPosition(int x, int y);
};