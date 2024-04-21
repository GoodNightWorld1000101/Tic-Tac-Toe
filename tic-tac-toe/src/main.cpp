#include <iostream>
#include "raylib.h"
using namespace std;

Color green = {0, 255, 0, 255};
Color red = {255, 0, 0, 255};
Color blue = {0, 0, 255, 255};

char board[3][3]{
    {' ', ' ', ' '},
    {' ', 'X', ' '},
    {' ', ' ', 'O'}};
int board_filled[3][3][2]{{{0, 50}, {0, 325}, {0, 625}},
                          {{325, 50}, {325, 325}, {325, 625}},
                          {{625, 50}, {625, 325}, {625, 625}}};


Image image = LoadImage("HP.png"); // Loaded in CPU memory (RAM)
Texture2D texture = LoadTextureFromImage(image);      // Image converted to texture, GPU memory (VRAM)


void Draw_board(int Width, int Height)
{
    // board outline
    //---------------------------------------------------------
    DrawRectangle(275, 0, 50, Height, blue);
    DrawRectangle(575, 0, 50, Height, blue);
    DrawRectangle(0, 275, Width, 50, blue);
    DrawRectangle(0, 575, Width, 50, blue);
    DrawRectangle(0, 0, 50, Width, blue);
    DrawRectangle(0, Height - 50, 900, 50, blue);
    DrawRectangle(0, 0, 900, 50, blue);
    DrawRectangle(850, 0, 850, 900, blue);
    //---------------------------------------------------------------
    // X and O Drawing on the board
    //---------------------------------------------------------------
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == 'X')
            {
                DrawRectangle(board_filled[i][j][0], board_filled[i][j][1], 250, 250, green);
            }
            else if (board[i][j] == 'O')
            {
                DrawCircleV({board_filled[i][j][0] + 110, board_filled[i][j][1] + 110}, 75, red);
            }
        }
    }
}

//------------------------------------------------------------------------------------
// Program main entry point
Vector2 PlayerPosition = {100, 100};
//------------------------------------------------------------------------------------
// player movement
//------------------------------------------------------------------------------------
void survive_move()
{
    if (IsKeyDown(KEY_RIGHT))
    {
        PlayerPosition.x += 2.0f;
    }
    if (IsKeyDown(KEY_LEFT))
    {
        PlayerPosition.x -= 2.0f;
    }
    if (IsKeyDown(KEY_UP))
    {
        PlayerPosition.y -= 2.0f;
    }
    if (IsKeyDown(KEY_DOWN))
    {
        PlayerPosition.y += 2.0f;
    }
}

//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 900;
    const int screenHeight = 900;

    InitWindow(screenWidth, screenHeight, "TIC-TAC-TOE");

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    const char playerX = 'X';
    const char playerO = 'O'; // if board[c][r]!=' ':>saab sisestada else no

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {

        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        Draw_board(screenWidth, screenHeight);
        ClearBackground(BLACK);
        survive_move();
        DrawText("TIC - TAC - TOE from hell!", 300, 20, 20, LIGHTGRAY);
        DrawTexture(texture, screenWidth/2 - texture.width/2, screenHeight/2 - texture.height/2, WHITE);
        DrawCircleV(PlayerPosition, 15, MAROON);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}