#include "raylib.h"
#include "Table.h"
#define dist 260
#define thickness 30
#define Height 900
#define Width 900
using namespace std;

Table::Table(Texture2D x, Texture2D o)
{
    zero_pic = o;
    x_pic = x;
}

void Table::draw_table() // joonistab laua pildi
{
    playing_for = playing_for;
    row = row;
    column = column;
    fight = fight;
    turn = turn;
    
    // board outline
    //---------------------------------------------------------
    DrawRectangle(dist + thickness, 0, thickness, Height, WHITE);
    DrawRectangle(2 * (dist + thickness), 0, thickness, Height, WHITE);
    DrawRectangle(0, dist + thickness, Width, thickness, WHITE);
    DrawRectangle(0, 2 * (dist + thickness), Width, thickness, WHITE);

    DrawRectangle(0, 0, thickness, Width, WHITE);
    DrawRectangle(0, Height - 30, 900, thickness, WHITE);
    DrawRectangle(0, 0, 900, thickness, WHITE);
    DrawRectangle(Width - thickness, 0, thickness + 10, 900, WHITE);
    //---------------------------------------------------------------
    // X and O Drawing on the board
    //---------------------------------------------------------------
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board_state[i][j] == 'X')
            {
                DrawTexture(x_pic, board_coordinates[i][j][0], board_coordinates[i][j][1], WHITE);
            }
            else if (board_state[i][j] == 'O')
            {
                DrawTexture(zero_pic, board_coordinates[i][j][0], board_coordinates[i][j][1], WHITE);
            }
        }
    }
}

char Table::check_game_state() // kontrollib kas mang on labi voi ei ja tagastab olenevalt voitja margi voi ' ' kui viik ja kui mang veel kaib siis 1
{
    char check;

    for (int i = 0; i < 3; i++)
    {
        check = board_state[i][0];
        bool win = true; //------------------------------>>>>>>>>>rea check
        for (int j = 1; j < 3; j++)
        {

            if (board_state[i][j] != check)
            {
                win = false;
            }
            else if (j == 2 && win)
            {

                return board_state[i][j];
            }
        }
    }
    for (int i = 0; i < 3; i++)
    {
        check = board_state[0][i];
        bool win = true; //------------------------------>>>>>>>>>veeru check
        for (int j = 1; j < 3; j++)
        {
            if (board_state[j][i] != check)
            {
                win = false;
            }
            else if (j == 2 && win)
            {
                return board_state[j][i];
            }
        }
        if (board_state[0][0] == board_state[1][1] && board_state[2][2] == board_state[1][1])
        {
            return board_state[1][1];
        }

        if (board_state[0][2] == board_state[1][1] && board_state[2][0] == board_state[1][1])
        {
            return board_state[1][1];
        }
    }
    if (turn == 9)
    {
        return ' ';
    }

    return '1';
}

void Table::set_mark() // muudab laua maaratud vaartusi
{
    board_state[row][column] = playing_for;
}