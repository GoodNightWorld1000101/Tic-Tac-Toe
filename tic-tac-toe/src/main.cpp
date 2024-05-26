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
    Image null = LoadImage("..\\pictures\\O_pilt.png");
    Texture2D null_pic = LoadTextureFromImage(null);
    UnloadImage(null);

    Image ix = LoadImage("..\\pictures\\X_pilt.png");
    Texture2D ix_pic = LoadTextureFromImage(ix);
    UnloadImage(ix);

    Image spagett_pic = LoadImage("..\\pictures\\spagetti.png");
    Texture2D spagetti = LoadTextureFromImage(spagett_pic);
    UnloadImage(spagett_pic);

    Image bone_pic = LoadImage("..\\pictures\\bone_up.png");
    Texture2D bone_up = LoadTextureFromImage(bone_pic);
    UnloadImage(bone_pic);

    Image bone_pic_down = LoadImage("..\\pictures\\bone_down.png");
    Texture2D bone_down = LoadTextureFromImage(bone_pic_down);
    UnloadImage(bone_pic_down);

    Image x_player_pic = LoadImage("..\\pictures\\player_nohood.png");
    Texture2D x_player = LoadTextureFromImage(x_player_pic);
    UnloadImage(x_player_pic);

    Image endscreen_pic = LoadImage("..\\pictures\\endscreen.png");
    Texture2D endscreen = LoadTextureFromImage(endscreen_pic);
    UnloadImage(endscreen_pic);
    //--------------------------------------------------------------------------------------
    SetTargetFPS(60);

    // KLASSI OBJEKTIDE LOOMINE
    Table grid(ix_pic, null_pic);
    Player player_object(800, 40, 32, 32, x_player, WHITE);
    Bone_attack bone_1(600, 800, 20, 130, 4, 1, bone_up, BLUE);
    Bone_attack bone_2(0, 140, 20, 130, 4, 1, bone_down, BLUE);
    Spagetti_attack_object spagetti_1(80, 30, 290, 30, 290, 2, 0, spagetti, WHITE);
    Spagetti_attack_object spagetti_2(140, 30, 290, 30, 290, 2, 2, spagetti, WHITE);
    Spagetti_attack_object spagetti_3(205, 30, 290, 30, 290, 2, 0, spagetti, WHITE);
    Spagetti_attack_object spagetti_4(270, 30, 290, 30, 290, 2, 2, spagetti, WHITE);
    Spagetti_attack_object spagetti_5(270, 30, 290, 30, 290, 2, 2, spagetti, RED);

    // WHILE sisesed muutujad
    int counter = 0;
    __uint128_t timer;
    bool alive = true;
    bool spagetti_attack = false;
    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // game state
        if (grid.fight)
        {
            if (time(NULL) - timer < 30 && alive)
            {
                //cout << "time:" << static_cast<int>(time(NULL) - timer) << " ja alive:" << alive << endl;
                counter++;
                // late spawn if-s
                if (counter == 34 && !spagetti_attack)
                {
                    bone_2.is_alive = true;
                }
                if (counter == 60 && spagetti_attack)
                {
                    spagetti_3.is_alive = 2;
                    spagetti_1.is_alive = 2;
                }
                // papyrus pasta attack or sans bone attack if
                if (spagetti_attack)
                {
                    alive = Papyrus_fight_phase(&grid, &player_object, &spagetti_1, &spagetti_2, &spagetti_3, &spagetti_4, &spagetti_5, 0);
                    
                }
                else
                {
                    alive = Sans_fight_phase(&grid, &player_object, &bone_1, &bone_2, 0);
                    
                }
                //cout << "Alive after fight:" << alive << endl;
                //
                if (!alive)
                {
                    spagetti_attack = false;
                }
                if (!alive || (time(NULL) - timer >= 29.9 && time(NULL) - timer < 50))
                {
                    grid.set_mark();
                    grid.fight = false;
                    alive = true;
                    spagetti_attack = false;
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
                //cout << "fight";
                if ((destination.x == 0 && destination.y == 0) || (destination.x == 2 && destination.y == 0) || (destination.x == 0 && destination.y == 2) || (destination.x == 2 && destination.y == 2))
                {
                    // PAPYRUSE ATTACKI OBJEKTIDE RESET
                    int row = destination.x;
                    int column = destination.y;
                    spagetti_attack = true;
                    spagetti_1.is_alive = 0;
                    spagetti_3.is_alive = 0;
                    spagetti_1.setXY(grid.board_coordinates[row][column][0], grid.board_coordinates[row][column][1], row, grid.board_coordinates[row][column][0], 60);
                    spagetti_2.setXY(grid.board_coordinates[row][column][0], grid.board_coordinates[row][column][1], row, grid.board_coordinates[row][column][0], 120);
                    spagetti_3.setXY(grid.board_coordinates[row][column][0], grid.board_coordinates[row][column][1], row, grid.board_coordinates[row][column][0], 180);
                    spagetti_4.setXY(grid.board_coordinates[row][column][0], grid.board_coordinates[row][column][1], row, grid.board_coordinates[row][column][0], 240);
                    spagetti_5.setXY(grid.board_coordinates[row][column][0], grid.board_coordinates[row][column][1], row, grid.board_coordinates[row][column][0] + 50, 240);
                }
                else
                {
                    // SANS ATTACKI OBJEKTIDE RESET
                    bone_1.setXY(
                        grid.board_coordinates[static_cast<int>(destination.x)]
                                              [static_cast<int>(destination.y)][0],
                        grid.board_coordinates[static_cast<int>(destination.x)]
                                              [static_cast<int>(destination.y)][1],
                        false);
                    bone_2.setXY(
                        grid.board_coordinates[static_cast<int>(destination.x)]
                                              [static_cast<int>(destination.y)][0],
                        grid.board_coordinates[static_cast<int>(destination.x)]
                                              [static_cast<int>(destination.y)][1],
                        true);
                    bone_2.is_alive = false;
                    bone_1.setFloorandCeil(destination.x, 100);
                    bone_2.setFloorandCeil(destination.x, 50);
                }
                // aja ja playeri reset
                grid.fight = true;
                player_object.setXY(grid.board_coordinates[static_cast<int>(destination.x)][static_cast<int>(destination.y)][0], grid.board_coordinates[static_cast<int>(destination.x)][static_cast<int>(destination.y)][1] + 100);
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