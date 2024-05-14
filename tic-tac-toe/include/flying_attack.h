#ifndef FLYING_ATTACK_H
#define FLYING_ATTACK_H
#include "raylib.h"
#include "Table.h"
#include <iostream>
using namespace std;

class flying_attack
{       Color attack_color;
        Texture2D picture;
        int spawn_up[3]={30,320,610};
        int spawn_down[3]={290,580,870};
        /*int column_0_borders[2]={30,270};
        int column_1_borders[2]={320,560};
        int column_2_borders[2]={610,850};*/
        float width=20; 
        float height=20;
        float speed;
        float x_border;
    public:
        float x, y;
        int is_alive;
        float algus;
        float lopp;
        float floor;
        float ceil;
        int counter = 0;
        Rectangle rec;
    flying_attack(float ix, float iy,float ifloor,float iceil,int border, float ispeed, int alive, Texture2D pic, Color color);
    void draw();
    void fall_rise();
    void setXY(float ix,float iy);
};

#endif