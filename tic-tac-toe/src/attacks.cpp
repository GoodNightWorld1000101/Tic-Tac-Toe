#include "raylib.h"
#include "Table.h"
#include "attacks.h"
#include <iostream>
using namespace std;

Attacks::Attacks(float x, float y, float width, float height, float speed, int is_alive, Texture2D pic, Color color)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->speed = speed;
    this->is_alive = is_alive;
    this->picture = pic;
    this->attack_color = color;
    floor = 290;
    ceil = 30;
    rec = {x, y, width, height};
    // bullet.x=x;
    // bullet.y=y;
    algus = 30;
    lopp = 290;
}
void Attacks::draw(int attack)
{
    switch (attack)
    {
    case 0:
        rec = {x, y, width, height};
        DrawTexture(picture, x, y, attack_color);
        break;
    case 1:
        // bullet.x = x;
        // bullet.y = y;
        DrawRectangle(x, y, 20, 20, BLUE);
        break;
    }
}
void Attacks::setXY(float iend, float iy, bool up)
{

    lopp = iend - 20;
    algus = iend + 260;
    if (up)
    {
        y = iy;
    }
    else
    {
        y = iy + 140;
    }
    x = algus;
    rec = {x, y, width, height};
}
void Attacks::attack(int attack, bool down)
{

    switch (attack)
    {
    case 0:
        if (is_alive)
        {
            x -= speed;
            rec.x = x;
            if (x < lopp)
            {
                x = algus;
            }
            if (speed < 4)
            {
                speed += 0.5;
            }
            else
            {
                speed = 2;
            }
        }
        break;
    case 1:
        if (is_alive && down)
        {

            if (y >= floor)
            {
                y -= speed;
            }
            else if (y <= ceil)
            {
                y += speed;
            }
            rec.y = y;
        }
        break;
    }
}
void Attacks::setFloorandCeil(int row, int lahutus)
{
    switch (row)
    {
    case 0:
        floor = 290;
        ceil = 30;
        break;
    case 1:
        floor = 580;
        ceil = 320;
        break;
    case 2:
        floor = 870;
        ceil = 610;
        break;
    }
    x -= lahutus;
}