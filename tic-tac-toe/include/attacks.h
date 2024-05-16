#ifndef ATTACKS_H
#define ATTACKS_H
#include "raylib.h"
#include "Table.h"
#include <iostream>
using namespace std;
class Attacks
{
    Color attack_color;
    Texture2D picture;

public:
    float x, y, speed, width, height;
    int is_alive;
    float algus;
    float lopp;
    float floor;
    float ceil;
    // Rectangle bullet = {x,y,20,20};
    Rectangle rec = {x, y, width, height};
    Attacks(float x, float y, float width, float height, float speed, int is_alive, Texture2D pic, Color color);
    void setXY(float iend, float iy, bool up);
    void draw(int attack);
    void attack(int attack, bool down);
    void setFloorandCeil(int row, int lahutus);
};
#endif