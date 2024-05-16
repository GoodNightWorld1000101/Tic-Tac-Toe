#include "raylib.h"
#include "Table.h"
#include <iostream>
#include "flying_attack.h"
using namespace std;

flying_attack::flying_attack(float ix, float iy, float ifloor, float iceil, int border, float ispeed, int alive, Texture2D pic, Color color)
{
    x = ix;
    y = iy;
    speed = ispeed;
    is_alive = alive;
    picture = pic;
    attack_color = color;
    floor = ifloor;
    ceil = iceil;
    switch (alive)
    {
    case 1:
        y_border = spawn_down[border];
        break;
    case 2:
        y_border = spawn_up[border];
        break;
    }
}
void flying_attack::draw()
{
    rec = {x, y, width, height};
    DrawTexture(picture, x, y, attack_color);
}
void flying_attack::fall_rise()
{
    if (counter == 1 && direction == 1)
    {
        // cout << "suurem kui algus" << endl;
        x += side_speed;
        counter = 0;
        return;
    }
    else if (counter == 1 && direction == 0)
    {
        // cout << "suurem kui y_border" << endl;
        x -= side_speed;
        counter = 0;
        return;
    }
    if (x <= algus)
    {
        x = lopp;
        direction = 1;
        // cout << "vaiksem kui algus" << endl;
    }
    else if (x >= lopp)
    {
        direction = 0;
    }
    // ceil<floor
    if (is_alive == 2)
    {
        if (floor > y)
        {
            y += speed;
        }
        else if (floor <= y)
        {
            is_alive = 1;
            counter++;
        }
    }
    else if (is_alive == 1)
    {
        if (y > ceil)
        {
            y -= speed;
        }
        else if (ceil <= y)
        {
            is_alive = 2;
            counter++;
        }
    }
}
void flying_attack::setXY(float ix, float iy, int iborder, float ialgus, int vahe)
{
    x = ix + vahe;
    y = iy;
    algus = ialgus;
    lopp = ialgus + 240;
    direction = 0;

    ceil = spawn_up[iborder];
    floor = spawn_up[iborder] + 240;
    counter = 0;
}
void flying_attack::follower(float ix, float iy)
{
    if (1 + ix > x)
    {
        x += 0.3;
    }
    else
    {
        x -= 0.3;
    }
    if (1 + iy > y)
    {
        y += 0.3;
    }
    else
    {
        y -= 0.3;
    }
}