#include "raylib.h"
#include "Table.h"
#include "player.h"
#include "attacks.h"
#include "flying_attack.h"
#include <cstdio>
#include <ctime>
using namespace std;

//--------------------MOUSE RELATED FUNCTIONS ------------------------------------
Vector2 check_mouse(Table *field, __uint128_t *timer)
{
    int row{};
    int column{};
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (30<GetMousePosition().y && GetMousePosition().y< 325)
        {
            row = 0;
        }
        else if (325<GetMousePosition().y && GetMousePosition().y < 610)
        {
            row = 1;
        }
        else if (610<GetMousePosition().y && GetMousePosition().y < 870)
        {
            row = 2;
        }

        if (30<GetMousePosition().x && GetMousePosition().x < 325)
        {
            column = 0;
        }
        else if (325<GetMousePosition().x && GetMousePosition().x < 610)
        {
            column = 1;
        }
        else if (610<GetMousePosition().x && GetMousePosition().x < 870)
        {
            column = 2;
        }
        if (field->board_state[row][column] != 'O' && field->board_state[row][column] != 'X')
        {
            cout << "Fighting for X" << endl;
            field->playing_for = 'X';
            field->turn++;
            *timer = time(NULL);
            field->fight = true;
            field->row = row;
            field->column = column;
            return {static_cast<float>(row), static_cast<float>(column)};
        }
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
    {
        if (30<GetMousePosition().y && GetMousePosition().y < 325)
        {
            row = 0;
        }
        else if (325<GetMousePosition().y && GetMousePosition().y < 610)
        {
            row = 1;
        }
        else if (610<GetMousePosition().y && GetMousePosition().y < 870)
        {
            row = 2;
        }
        if (30<GetMousePosition().x && GetMousePosition().x < 325)
        {
            column = 0;
        }
        else if (325<GetMousePosition().x && GetMousePosition().x < 610)
        {
            column = 1;
        }
        else if (610<GetMousePosition().x && GetMousePosition().x < 870)
        {
            column = 2;
        }
        if (field->board_state[row][column] != 'X' && field->board_state[row][column] != 'O')
        {
            cout << "Fighting for O" << endl;
            field->playing_for = 'O';
            field->turn++;
            *timer = time(NULL);
            field->fight = true;
            field->row = row;
            field->column = column;
            return {static_cast<float>(row), static_cast<float>(column)};
        }
    }
    return {9000.0, 0.0};
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
                    field->board_state[i][j] = (char)number;
                }
            }
        }
        return true;
    }
    return false;
}

// ------------------------------------GAME LOOP RELATED FUNCTIONS ------------------------------------------------------------------------
void Game_over_screen(char winner, Texture2D background, Table *field)
{
    auto paint = DARKGRAY;
    if (play_again_mouse(field))
    {
        paint = LIGHTGRAY;
    }
    else
    {
        paint = DARKGRAY;
    }

    BeginDrawing();

    DrawTexture(background, 0, 0, WHITE);

    //----------------------------------------------------------------
    DrawRectangle(300, 500, 330, 50, paint);
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

bool Sans_fight_phase(Table *field, Player *player, Bone_attack *attack_1, Bone_attack *attack_2, int attack)
{

    if (CheckCollisionRecs(player->rec, attack_1->rec) || CheckCollisionRecs(player->rec, attack_2->rec))
    {
        if (field->playing_for == 'X')
        {
            field->playing_for = 'O';
        }
        else if (field->playing_for == 'O')
        {
            field->playing_for = 'X';
        }
        return false;
    }

    BeginDrawing();
    ClearBackground(BLACK);

    attack_1->attack(attack, false);
    attack_2->attack(attack, true);
    player->move();

    //----------------------------------------------------------------------------------

    //----------------------------------------------------------------
    attack_1->draw(attack);
    attack_2->draw(attack);
    field->draw_table();

    player->draw();

    EndDrawing();
    return true;
}
bool Papyrus_fight_phase(Table *field, Player *player, Spagetti_attack_object *attack_1, Spagetti_attack_object *attack_2, Spagetti_attack_object *attack_3, Spagetti_attack_object *attack_4, Spagetti_attack_object *attack_5, int attack)
{

    if (CheckCollisionRecs(player->rec, attack_1->rec) || CheckCollisionRecs(player->rec, attack_2->rec) || CheckCollisionRecs(player->rec, attack_3->rec) || CheckCollisionRecs(player->rec, attack_4->rec) || CheckCollisionRecs(player->rec, attack_5->rec))
    {
        if (field->playing_for == 'X')
        {
            field->playing_for = 'O';
        }
        else if (field->playing_for == 'O')
        {
            field->playing_for = 'X';
        }
        
        return false;
    }

    BeginDrawing();
    ClearBackground(BLACK);

    attack_1->fall_rise();
    attack_2->fall_rise();
    attack_3->fall_rise();
    attack_4->fall_rise();
    attack_5->follower(player->x, player->y);
    player->move();

    //----------------------------------------------------------------------------------

    //----------------------------------------------------------------
    
    attack_1->draw();
    attack_2->draw();
    attack_3->draw();
    attack_4->draw();
    attack_5->draw();
    field->draw_table();

    
    player->draw();

    EndDrawing();
    return true;
}