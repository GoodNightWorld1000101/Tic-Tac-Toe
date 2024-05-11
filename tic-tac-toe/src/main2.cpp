#include "raylib.h"
#include "Table.h"
#include "player.h"
#include "attacks.h"
#include "mouse.h"
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
    Image null = LoadImage("C:\\Users\\subbi\\c++\\tic-tac-toe\\build\\pixil-frame-0 (2).png");
    Texture2D nullpilt = LoadTextureFromImage(null);
    UnloadImage(null);

    Image ix = LoadImage("C:\\Users\\subbi\\c++\\tic-tac-toe\\build\\pixil-frame-0 (1).png");
    Texture2D ixpilt = LoadTextureFromImage(ix);
    UnloadImage(ix);

    Image bone_pic = LoadImage("C:\\Users\\subbi\\c++\\tic-tac-toe\\src\\boneoige.png");
    Texture2D bone_tex = LoadTextureFromImage(bone_pic);
    UnloadImage(bone_pic);

    Image x_player_pic = LoadImage("C:\\Users\\subbi\\c++\\tic-tac-toe\\src\\xplayer.png");
    Texture2D x_player = LoadTextureFromImage(x_player_pic);
    UnloadImage(x_player_pic);

    Image endscreen_pic = LoadImage("C:\\Users\\subbi\\c++\\tic-tac-toe\\src\\endscreen.png");
    Texture2D endscreen = LoadTextureFromImage(endscreen_pic);
    UnloadImage(endscreen_pic);
    //--------------------------------------------------------------------------------------
    SetTargetFPS(60);

    // KLASSI MUUTUJAD
    Table grid(ixpilt, nullpilt);
    Player O_player(800, 40, 32, 32, x_player, RED);
    Player X_player(800, 40, 32, 32, x_player, GREEN);
    Attacks bone_1(600, 800, 20, 130, 4, 1, bone_tex, RED);
    Attacks bone_2(0, 140, 20, 130, 4, 1, bone_tex, RED);
    bool second_bone = false;
    int counter=0;
    __uint128_t timer;
    bool alive = true;
    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        
        // Final product
        if (grid.fight)
        {
            if (time(NULL) - timer < 30 && alive)
            {cout<<"time:" << (int)(time(NULL) - timer) <<" ja alive:"<<alive<<endl;
                counter++;
                if (counter == 34){bone_2.is_alive=true;}
                alive = Fight_phase(&grid, &X_player, &bone_1, &bone_2,0);
                cout<<"Alive after fight:"<<alive<<endl;
                if (!alive || time(NULL) - timer >= 29.9 && time(NULL) - timer < 50)
                {
                    grid.set_mark();
                    grid.fight = false;
                    alive = true;
                    
                }
                else
                {
                    destination = {9000, 0};
                    
                }
            }
        }
        else if (grid.turn < 9 && grid.check_game_state() == '1')
        {
            destination = check_mouse(&grid, &timer);
            //cout << destination.x << "ja y="<< destination.y << endl;
            if (destination.x != 9000)
            {cout<<"fight";
            grid.fight = true;
                X_player.setXY(grid.board_coordinates[(int)(destination.x)][(int)(destination.y)][0], grid.board_coordinates[(int)(destination.x)][(int)(destination.y)][1]);
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
                bone_2.is_alive=false;
                bone_1.setFloorandCeil(destination.x,100);
                bone_2.setFloorandCeil(destination.x,50);
                timer = time(NULL);
                counter = 0;
                alive=true;
            }
            

            BeginDrawing();
            ClearBackground(BLACK);
            grid.draw_table();
         
            EndDrawing();
        }
        else
        {
            Game_over_screen(grid.check_game_state(), endscreen, &grid);
        }
    }
    CloseWindow();
    return 0;
}