#pragma once

class Snake
{
public:
    Snake* next;
    int x, y, prev_x, prev_y;
    Snake();
    Snake(int x, int y);
    void setPosition(int x, int y);
};