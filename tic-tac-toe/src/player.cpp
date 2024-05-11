#include "raylib.h"
#include "player.h"
#include <iostream>
using namespace std;
Player::Player(float x,float y,float width,float height,Texture2D pic, Color color)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->picture = pic;
    this->player_color = color;
}
void Player::move() // sektor
    {                // switch mis sektoris asub
        int vahe = 260;
        int paksus = 30;
        if (IsKeyDown(KEY_RIGHT))
        {
            if (paksus <= x && x < vahe + paksus - width || vahe + 2 * paksus <= x && x < 2 * (vahe + paksus) - width || vahe * 2 + 3 * paksus <= x && x < (vahe + paksus) * 3 - width)
            {
                x += 2.0f;
            }
        }
        if (IsKeyDown(KEY_LEFT))
        {
            if (paksus < x && x <= vahe + paksus || vahe + 2 * paksus < x && x <= 2 * (vahe + paksus) || vahe * 2 + 3 * paksus < x && x <= (vahe + paksus) * 3)
            {
                x -= 2.0f;
            }
        }
        if (IsKeyDown(KEY_UP))
        {
            if (paksus < y && y <= vahe + paksus || vahe + 2 * paksus < y && y <= 2 * (vahe + paksus) || 2 * (vahe + paksus) + paksus < y && y <= (vahe + paksus) * 3)
            {
                y -= 2.0f;
            }
        }
        if (IsKeyDown(KEY_DOWN))
        {
            if (paksus <= y && y < (vahe + paksus) - width || (vahe + paksus) + paksus <= y && y < (vahe + paksus) * 2 - width || (vahe + paksus) * 2 + paksus <= y && y < (vahe + paksus) * 3 - width)
            {
                y += 2.0f;
            }
        }
    }
void Player::setXY(float ix,float iy)
    {
        x = ix;
        y = iy;
        rec = {x,y,width,height};
    }
void Player::draw()
    {   rec = {x,y,width,height};
        DrawRectangle(x, y, width, height, WHITE);
        DrawTexture(picture, x, y, player_color);
    }
