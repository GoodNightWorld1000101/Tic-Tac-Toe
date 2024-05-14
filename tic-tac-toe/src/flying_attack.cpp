#include "raylib.h"
#include "Table.h"
#include <iostream>
#include "flying_attack.h"
using namespace std;


    flying_attack::flying_attack(float ix, float iy,float ifloor,float iceil,int border, float ispeed, int alive, Texture2D pic, Color color)
    {
        x= ix;
        y= iy;
        speed=ispeed;
        is_alive=alive;
        picture=pic;
        attack_color=color;
        floor=ifloor;
        ceil=iceil;
        switch(alive)
        {
            case 1:
            x_border=spawn_down[border];
            break;
            case 2:
            x_border=spawn_up[border];
            break;
        }
    }
    void flying_attack::draw()
    {
        rec={x,y,width,height};
        DrawTexture(picture,x,y,attack_color);
    }
    void flying_attack::fall_rise()
    {   if (counter==2 && x+50<x_border)
        {
            cout<< "suurem kui algus" << endl;
            x+=30;
            counter=0;
        }
        else if (counter == 2 && x_border<=x+50)
        {   cout<< "suurem kui x_border" << endl;
            x-=30;
            counter=0;
        }
        if (x<=30)
        {x=270;
        cout<< "vaiksem kui algus" << endl;}
        //ceil<floor
       if(is_alive==2)
        {
            if(floor > y)
            {y+=speed;}
            else if(floor <= y)
            {
                is_alive=1;
                counter++;
            }
        }
        else if (is_alive==1)
        {
            if( y > ceil)
            {y-=speed;}
            else if(ceil <= y)
            {
                is_alive=2;
                counter++;
            } 
        }
        
        
    }
void flying_attack::setXY(float ix,float iy){x=ix;y=iy;}