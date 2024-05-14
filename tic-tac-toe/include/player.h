#ifndef PLAYER_H
#define PLAYER_H
#include "raylib.h"
#include "Table.h"
#include <iostream>
using namespace std;
class Player
{
    Texture2D picture;
public:
    Color player_color;
    float x, y;
    float width = 32;
    float height = 32;
    Rectangle rec = {x, y, width, height};
    Player(float x,float y,float width,float height,Texture2D pic, Color color);
    void setXY(float ix,float iy);
    void move();
    void draw();
};
#endif