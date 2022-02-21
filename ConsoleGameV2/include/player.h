#pragma once
#include <snake.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

void Wrap(int& value, int min, int max);

class Player
{
    enum class Direction { UP, DOWN, LEFT, RIGHT, NONE };
    
    void updateDirection(Direction p_dir);
    void updatePosition();
    void updateDisplayChar();

    char chars[4] = { '^','v', '<', '>' };
    int prev_x, prev_y, max_x, max_y;
    Direction dir;
    char displayChar;


public:
    int x, y;
    Snake *head, *last;
    Player(int p_x, int p_y, int max_x, int max_y);
    void update(int* input);
    void addSnakePart();
    char getDisplayChar() { return displayChar; };
};

