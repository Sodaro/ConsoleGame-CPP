#pragma once

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
    int x, y, max_x, max_y;
    Direction dir;
    char displayChar;

public:
    Player(int p_x, int p_y, int max_x, int max_y);
    void update(int* input);
    char getDisplayChar() { return displayChar; };
    int getX() { return x; };
    int getY() { return y; };

};

