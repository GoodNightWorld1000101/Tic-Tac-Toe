#include "raylib.h"
#include "Table.h"
#include "player.h"
#include "attacks.h"
#include "mouse.h"
#include "flying_attack.h"
#include <cstdio>
#include <chrono>
#include <ctime>

Vector2 destination;
int main(void)
{
    // Initialization

    //--------------------------------------------------------------------------------------SCREEN PARAMETERS
    const int screenWidth = 900;
    const int screenHeight = 900;
    InitWindow(screenWidth, screenHeight, "TIC-TAC-TOE");
    //-------------------------------------------------------------------------------------- IMAGE LOADING
    //---SIIN PEAB IGAS ARVUTIS ALGUS PATHI ÕIGEKS PANEMA(ei osak hetkel fixida seda)
    Image null = LoadImage("..\\pictures\\O_pilt.png");
    Texture2D nullpilt = LoadTextureFromImage(null);
    UnloadImage(null);

    Image ix = LoadImage("..\\pictures\\X_pilt.png");
    Texture2D ixpilt = LoadTextureFromImage(ix);
    UnloadImage(ix);

    Image spagett_pic = LoadImage("..\\pictures\\spagetti.png");
    Texture2D spagetti = LoadTextureFromImage(spagett_pic);
    UnloadImage(spagett_pic);

    Image bone_pic = LoadImage("..\\pictures\\boneoige.png");
    Texture2D bone_tex = LoadTextureFromImage(bone_pic);
    UnloadImage(bone_pic);

    Image x_player_pic = LoadImage("..\\pictures\\player_nohood.png");
    Texture2D x_player = LoadTextureFromImage(x_player_pic);
    UnloadImage(x_player_pic);

    Image endscreen_pic = LoadImage("..\\pictures\\endscreen.png");
    Texture2D endscreen = LoadTextureFromImage(endscreen_pic);
    UnloadImage(endscreen_pic);
    //--------------------------------------------------------------------------------------
    SetTargetFPS(60);

    // KLASSI OBJEKTIDE LOOMINE
    Table grid(ixpilt, nullpilt);
    Player O_player(800, 40, 32, 32, x_player, RED);
    Player X_player(800, 40, 32, 32, x_player, WHITE);
    Attacks bone_1(600, 800, 20, 130, 4, 1, bone_tex, RED);
    Attacks bone_2(0, 140, 20, 130, 4, 1, bone_tex, RED);
    flying_attack meat_1(80, 30, 290, 30, 290, 2, 0, spagetti, WHITE);
    flying_attack meat_2(140, 30, 290, 30, 290, 2, 2, spagetti, WHITE);
    flying_attack meat_3(205, 30, 290, 30, 290, 2, 0, spagetti, WHITE);
    flying_attack meat_4(270, 30, 290, 30, 290, 2, 2, spagetti, WHITE);
    flying_attack meat_5(270, 30, 290, 30, 290, 2, 2, spagetti, RED);

    // WHILE sisesed muutujad
    bool second_bone = false;
    int counter = 0;
    __uint128_t timer;
    bool alive = true;
    bool pasta = false;
    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {

        // game state
        if (grid.fight)
        {
            if (time(NULL) - timer < 30 && alive)
            {
                cout << "time:" << (int)(time(NULL) - timer) << " ja alive:" << alive << endl;
                counter++;
                // late spawn if-s
                if (counter == 34 && !pasta)
                {
                    bone_2.is_alive = true;
                }
                if (counter == 60 && pasta)
                {
                    meat_3.is_alive = 2;
                    meat_1.is_alive = 2;
                }
                // papyrus pasta attack or sans bone attack if
                if (pasta)
                {
                    alive = Fight_phase_1(&grid, &X_player, &meat_1, &meat_2, &meat_3, &meat_4, &meat_5, 0);
                }
                else
                {
                    alive = Fight_phase(&grid, &X_player, &bone_1, &bone_2, 0);
                }
                cout << "Alive after fight:" << alive << endl;
                //
                if (!alive)
                {
                    pasta = false;
                }
                if (!alive || time(NULL) - timer >= 29.9 && time(NULL) - timer < 50)
                {
                    grid.set_mark();
                    grid.fight = false;
                    alive = true;
                    pasta = false;
                }
                else
                {
                    destination = {9000, 0};
                }
            }
        }
        // RUUDU VALIMIS FAAS
        else if (grid.turn < 9 && grid.check_game_state() == '1')
        {
            destination = check_mouse(&grid, &timer);
            if (destination.x != 9000)
            {
                cout << "fight";
                if (destination.x == 0 && destination.y == 0 || destination.x == 2 && destination.y == 0 || destination.x == 0 && destination.y == 2 || destination.x == 2 && destination.y == 2)
                {
                    // PAPYRUSE ATTACKI OBJEKTIDE RESET
                    int row = destination.x;
                    int column = destination.y;
                    pasta = true;
                    meat_1.is_alive = 0;
                    meat_3.is_alive = 0;
                    meat_1.setXY(grid.board_coordinates[row][column][0], grid.board_coordinates[row][column][1], row, grid.board_coordinates[row][column][0], 60);
                    meat_2.setXY(grid.board_coordinates[row][column][0], grid.board_coordinates[row][column][1], row, grid.board_coordinates[row][column][0], 120);
                    meat_3.setXY(grid.board_coordinates[row][column][0], grid.board_coordinates[row][column][1], row, grid.board_coordinates[row][column][0], 180);
                    meat_4.setXY(grid.board_coordinates[row][column][0], grid.board_coordinates[row][column][1], row, grid.board_coordinates[row][column][0], 240);
                    meat_5.setXY(grid.board_coordinates[row][column][0], grid.board_coordinates[row][column][1], row, grid.board_coordinates[row][column][0] + 50, 240);
                }
                else
                {
                    // SANS ATTACKI OBJEKTIDE RESET
                    bone_1.setXY(
                        grid.board_coordinates[(int)(destination.x)]
                                              [(int)((destination.y))][0],
                        grid.board_coordinates[(int)(destination.x)]
                                              [(int)((destination.y))][1],
                        false);
                    bone_2.setXY(
                        grid.board_coordinates[(int)(destination.x)]
                                              [(int)(destination.y)][0],
                        grid.board_coordinates[(int)(destination.x)]
                                              [(int)(destination.y)][1],
                        true);
                    bone_2.is_alive = false;
                    bone_1.setFloorandCeil(destination.x, 100);
                    bone_2.setFloorandCeil(destination.x, 50);
                }
                // aja ja playeri reset
                grid.fight = true;
                X_player.setXY(grid.board_coordinates[(int)(destination.x)][(int)(destination.y)][0], grid.board_coordinates[(int)(destination.x)][(int)(destination.y)][1] + 100);
                timer = time(NULL);
                counter = 0;
                alive = true;
            }

            BeginDrawing();
            ClearBackground(BLACK);
            grid.draw_table();

            EndDrawing();
        }
        else
        {
            // Play again screen
            Game_over_screen(grid.check_game_state(), endscreen, &grid);
        }
    }
    CloseWindow();
    return 0;
}