#include "player.h"

void Wrap(int& value, int min, int max)
{
    if (value < min)
        value = max;
    else if (value > max)
        value = min;
}

Player::Player(int p_x, int p_y, int max_x, int max_y)
{
    x = p_x; y = p_y;
    dir = Direction::DOWN;
    this->max_x = max_x;
    this->max_y = max_y;

    updateDisplayChar();
}

void Player::update(int* input)
{
    Direction newDir = Direction::NONE;
    switch (*input)
    {
        case KEY_UP: newDir = Direction::UP; break;
        case KEY_DOWN: newDir = Direction::DOWN; break;
        case KEY_LEFT: newDir = Direction::LEFT; break;
        case KEY_RIGHT: newDir = Direction::RIGHT;break;
        default:break;
    }
    updateDirection(newDir);
    updatePosition();
}

void Player::updateDirection(Direction p_dir)
{
    if (p_dir == Direction::NONE)
        return;

    dir = p_dir;
    updateDisplayChar();
}

void Player::updatePosition()
{
    switch (dir)
    {
        case Direction::UP: y--; break;
        case Direction::DOWN: y++; break;
        case Direction::LEFT: x--; break;
        case Direction::RIGHT: x++; break;
        default: break;
    }
    Wrap(y, 0, max_y);
    Wrap(x, 0, max_x);
}

void Player::updateDisplayChar()
{
    displayChar = chars[(int)dir];
}