#ifndef ATTACKS_H
#define ATTACKS_H
#include "raylib.h"
#include "Table.h"
#include <iostream>
using namespace std;
class Bone_attack
{
    Color attack_color;
    Texture2D picture;

public:
    float x, y, speed, width, height;
    int is_alive;
    float start;
    float end;
    float floor;
    float ceil;
    Rectangle rec = {x, y, width, height};
    Bone_attack(float x, float y, float width, float height, float speed, int is_alive, Texture2D pic, Color color);
    void setXY(float iend, float iy, bool up);
    void draw(int attack);
    void attack(int attack, bool down);
    void setFloorandCeil(int row, int dist);
};
#endif