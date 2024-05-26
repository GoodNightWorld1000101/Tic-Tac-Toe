#ifndef TABLE_H
#define TABLE_H
#include "raylib.h"
using namespace std;

class Table
{
private:
    Texture2D zero_pic;
    Texture2D x_pic;

public:
    char playing_for = ' ';
    int row;
    int column;
    bool fight;
    int turn = 0;
    char board_state[3][3]{
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'}};

    int board_coordinates[3][3][2]{
        {{30, 30}, {320, 30}, {610, 30}},
        {{30, 320}, {320, 320}, {610, 320}},
        {{30, 610}, {320, 610}, {610, 610}}};

    Table(Texture2D, Texture2D);
    void draw_table();
    char check_game_state();
    void set_mark();
};
#endif