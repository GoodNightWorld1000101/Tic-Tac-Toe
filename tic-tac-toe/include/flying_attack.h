#ifndef FLYING_ATTACK_H
#define FLYING_ATTACK_H
#include "raylib.h"
#include "Table.h"
#include <iostream>
using namespace std;

class Spagetti_attack_object
{
    Color attack_color;
    Texture2D picture;
    int spawn_up[3] = {30, 320, 610};
    int spawn_down[3] = {290, 580, 870};
    float width = 20;
    float height = 20;
    float speed;
    float side_speed = 20;

public:
    float y_border;
    float x, y;
    int is_alive;
    float start;
    float end_point;
    float floor;
    float ceil;
    int counter = 0;
    int direction = 0;
    Rectangle rec;
    Spagetti_attack_object(float ix, float iy, float ifloor, float iceil, int border, float ispeed, int alive, Texture2D pic, Color color);
    void draw();
    void fall_rise();
    void setXY(float ix, float iy, int iborder, float istart, int dist);
    void follower(float ix, float iy);
};

#endif