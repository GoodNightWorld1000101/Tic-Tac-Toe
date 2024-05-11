#include "raylib.h"
#include "Table.h"
#include "player.h"
#include "attacks.h"
#include <cstdio>
#include <ctime>
//--------------------MOUSE RELATED FUNCTIONS ------------------------------------
Vector2 check_mouse(Table *field,__uint128_t*timer)
{
    int row;
    int column;
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (GetMousePosition().y < 325)
        {
            row = 0;
        }
        else if (GetMousePosition().y < 610)
        {
            row = 1;
        }
        else if (GetMousePosition().y < 870)
        {
            row = 2;
        }

        if (GetMousePosition().x < 325)
        {
            column = 0;
        }
        else if (GetMousePosition().x < 610)
        {
            column = 1;
        }
        else if (GetMousePosition().x < 870)
        {
            column = 2;
        }
        if (field->board_state[row][column] != 'O' && field->board_state[row][column] != 'X' )
        {
            cout << "Fighting for X"<<endl;
            field->playing_for = 'X';
            field->turn++;
            *timer=time(NULL);
            field->fight = true;
            field->row = row;
            field->column = column;
            return {row, column};
            
            
        }
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
    {
        if (GetMousePosition().y < 325)
        {
            row = 0;
        }
        else if (GetMousePosition().y < 610)
        {
            row = 1;
        }
        else if (GetMousePosition().y < 870)
        {
            row = 2;
        }
        if (GetMousePosition().x < 325)
        {
            column = 0;
        }
        else if (GetMousePosition().x < 610)
        {
            column = 1;
        }
        else if (GetMousePosition().x < 870)
        {
            column = 2;
        }
        if (field->board_state[row][column] != 'X' && field->board_state[row][column] != 'O' )
        {
            cout << "Fighting for O"<<endl;
            field->playing_for = 'O';
            field->turn++;
            *timer = time(NULL);
            field->fight = true;
            field->row = row;
            field->column = column;
            return {row, column};
            
        }
    }
    return {9000, 0};
}

bool play_again_mouse(Table *field)
{
    if (300 <= GetMousePosition().x && GetMousePosition().x <= 630 && 500 <= GetMousePosition().y && GetMousePosition().y <= 550)
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            int number = 0;
            field->turn = 0;
            for (int i = 0; i < 3; i++)
            {
                number++;
                for (int j = 0; j < 3; j++)
                {
                    number++;
                    field -> board_state[i][j] = (char)number;
                }
            }
            
        }
        return true;
    }
    return false;
}

// ------------------------------------GAME LOOP RELATED FUNCTIONS ------------------------------------------------------------------------
void Game_over_screen(char winner, Texture2D background,Table *field){
            auto varv = DARKGRAY;
            if (play_again_mouse(field))
            {
                varv = LIGHTGRAY;
            }
            else
            {
                varv = DARKGRAY;
            }

            BeginDrawing();

            DrawTexture(background, 0, 0, WHITE);
            
            //----------------------------------------------------------------
            DrawRectangle(300, 500, 330, 50, varv);
            DrawText("PLAY AGAIN", 310, 500, 50, BLACK);

            if (winner == 'X')
            {
                DrawText("winner is X", 170, 400, 100, LIGHTGRAY);
            }
            else if (winner == 'O')
            {
                DrawText("winner is O", 170, 400, 100, LIGHTGRAY);
            }
            else
            {
                DrawText("it's a tie!", 170, 400, 100, LIGHTGRAY);
            }
            EndDrawing();
        }

bool Fight_phase(Table *field,Player *player,Attacks *attack_1,Attacks * attack_2,int attack)
        {

            if (CheckCollisionRecs(player->rec, attack_1->rec)||CheckCollisionRecs(player->rec, attack_2->rec))
            {
                if (field -> playing_for ==  'X'){field -> playing_for='O';}
                else if (field -> playing_for ==  'O'){field -> playing_for = 'X';}
                return false;
            }
            if (CheckCollisionRecs(player->rec, attack_1->bullet)||CheckCollisionRecs(player->rec, attack_2->bullet))
            {
                if (field -> playing_for ==  'X'){field -> playing_for='O';}
                else if (field -> playing_for ==  'O'){field -> playing_for = 'X';}
                return false;
            }
            BeginDrawing();
            ClearBackground(BLACK);

            attack_1->attack(attack,false);
            attack_2->attack(attack,true);
            player->move();

            //----------------------------------------------------------------------------------

            //----------------------------------------------------------------
            attack_1->draw(attack);
            attack_2->draw(attack);
            field->draw_table();
            
            DrawText("TIC - TAC - TOE from hell!", 300, 20, 0, LIGHTGRAY);
            player->draw();

            EndDrawing();
            return true;
        }