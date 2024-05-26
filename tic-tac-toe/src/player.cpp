#include "raylib.h"
#include "player.h"
#include <iostream>
#define dist 260
#define thick 30
using namespace std;
Player::Player(float x, float y, float width, float height, Texture2D pic, Color color)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->picture = pic;
    this->player_color = color;
    this->rec = {x, y, width, height};
}
void Player::move() // sektor
{                   // switch mis sektoris asub
    if (IsKeyDown(KEY_RIGHT))
    {
        if ((thick <= x && x < dist + thick - width) || (dist + 2 * thick <= x && x < 2 * (dist + thick) - width) || (dist * 2 + 3 * thick <= x && x < (dist + thick) * 3 - width))
        {
            x += 2.0f;
        }
    }
    if (IsKeyDown(KEY_LEFT))
    {
        if ((thick < x && x <= dist + thick) || (dist + 2 * thick < x && x <= 2 * (dist + thick)) || (dist * 2 + 3 * thick < x && x <= (dist + thick) * 3))
        {
            x -= 2.0f;
        }
    }
    if (IsKeyDown(KEY_UP))
    {
        if ((thick < y && y <= dist + thick) || (dist + 2 * thick < y && y <= 2 * (dist + thick)) ||( 2 * (dist + thick) + thick < y && y <= (dist + thick) * 3))
        {
            y -= 2.0f;
        }
    }
    if (IsKeyDown(KEY_DOWN))
    {
        if ((thick <= y && y < (dist + thick) - width )|| ((dist + thick) + thick <= y && y < (dist + thick) * 2 - width )|| ((dist + thick) * 2 + thick <= y && y < (dist + thick) * 3 - width))
        {
            y += 2.0f;
        }
    }
}
void Player::setXY(float ix, float iy)
{
    x = ix;
    y = iy;
    rec = {x, y, width, height};
}
void Player::draw()
{
    rec = {x, y, width, height};
    DrawRectangle(x, y, width, height, BLACK);
    DrawTexture(picture, x, y, player_color);
}
