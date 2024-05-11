/*#include <iostream>
#include <ctime>
#include "raylib.h"
using namespace std;

Color green = {0, 255, 0, 255};
Color red = {255, 0, 0, 255};
Color blue = {0, 0, 255, 255};

int kord = 0;
char playing_for;
char winner = ' ';
char board[3][3]{
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'}};

int board_filled[3][3][2]{
    {{30, 30}, {320, 30}, {610, 30}},
    {{30, 320}, {320, 320}, {610, 320}},
    {{30, 610}, {320, 610}, {610, 610}}};

// Loaded in CPU memory (RAM)
int row_box;
int column_box;
// Image converted to texture, GPU memory (VRAM)
class ball
{
public:
    float x, y;
    int width = 50;
    int height = 50;
    Rectangle rec = {x, y, width, height};
    void ball_move() // sektor
    {                // switch mis sektoris asub
        int vahe = 260;
        int paksus = 30;
        if (IsKeyDown(KEY_RIGHT))
        {
            if (paksus <= x && x < vahe + paksus - 50 || vahe + 2 * paksus <= x && x < 2 * (vahe + paksus) - 50 || vahe * 2 + 3 * paksus <= x && x < (vahe + paksus) * 3 - 20)
            {
                x += 2.0f;
            }
        }
        if (IsKeyDown(KEY_LEFT))
        {
            if (paksus < x && x <= vahe + paksus || vahe + 2 * paksus < x && x <= 2 * (vahe + paksus) || vahe * 2 + 3 * paksus < x && x <= (vahe + paksus) * 3)
            {
                x -= 2.0f;
            }
        }
        if (IsKeyDown(KEY_UP))
        {
            if (paksus < y && y <= vahe + paksus || vahe + 2 * paksus < y && y <= 2 * (vahe + paksus) || 2 * (vahe + paksus) + paksus < y && y <= (vahe + paksus) * 3)
            {
                y -= 2.0f;
            }
        }
        if (IsKeyDown(KEY_DOWN))
        {
            if (paksus <= y && y < (vahe + paksus) - 50 || (vahe + paksus) + paksus <= y && y < (vahe + paksus) * 2 - 50 || (vahe + paksus) * 2 + paksus <= y && y < (vahe + paksus) * 3 - 50)
            {
                y += 2.0f;
            }
        }
    }
    void draw(Texture2D texture)
    {
        DrawRectangle(x, y, width, height, MAROON);
        DrawTexture(texture, x, y, WHITE);
    }
};
class Bones
{
public:
    int x, y;
    int speed;
    bool is_moving;
    int width = 20;
    int height = 120;
    Rectangle rec = {x, y, width, height};
    void draw()
    {
        DrawRectangle(x, y, width, height, RED);
    }
    void move(int lopp)
    {
        if (is_moving)
        {
            x -= speed;
            rec.x = x;
            if (x < lopp)
            {
                x += 260;
            }
        }
    }
};
void Draw_board(int Width, int Height, Texture2D O, Texture2D X)
{
    int vahe = 260;
    int paksus = 30;
    // board outline
    //---------------------------------------------------------
    DrawRectangle(vahe + paksus, 0, paksus, Height, WHITE);
    DrawRectangle(2 * (vahe + paksus), 0, paksus, Height, WHITE);
    DrawRectangle(0, vahe + paksus, Width, paksus, WHITE);
    DrawRectangle(0, 2 * (vahe + paksus), Width, paksus, WHITE);

    DrawRectangle(0, 0, paksus, Width, WHITE);
    DrawRectangle(0, Height - 30, 900, paksus, WHITE);
    DrawRectangle(0, 0, 900, paksus, WHITE);
    DrawRectangle(Width - paksus, 0, paksus + 10, 900, WHITE);
    //---------------------------------------------------------------
    // X and O Drawing on the board
    //---------------------------------------------------------------
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == 'X')
            {
                DrawTexture(X, board_filled[i][j][0], board_filled[i][j][1], WHITE);
                // DrawRectangle(board_filled[i][j][0], board_filled[i][j][1], 260, 260, green);
            }
            else if (board[i][j] == 'O')
            {
                DrawTexture(O, board_filled[i][j][0], board_filled[i][j][1], WHITE);
                // DrawRectangle(board_filled[i][j][0], board_filled[i][j][1], 260, 260, RED);
            }
        }
    }
}

int kontroll()
{
    char check;
    for (int i = 0; i < 3; i++)
    {
        check = board[i][0];
        bool win = true;//------------------------------>>>>>>>>>check
        for (int j = 1; j < 3; j++)
        {
            if (board[i][j] != check)
            {
                win = false;
            }
            else if (j == 2 && win)
            {
                winner = board[i][j];
                return 1;
            }
        }
    }
    for (int i = 0; i < 3; i++)
    {
        check = board[0][i];
        bool win = true;
        for (int j = 0; j < 3; j++)
        {
            if (board[j][i] != check)
            {
                win = false;
            }
            else if (j == 2 && win)
            {
                winner = board[j][i];
                return 1;
            }
        }
    }
    if (board[0][0] == board[1][1] && board[2][2] == board[1][1])
    {
        winner = board[1][1];
        return 1;
    }
    
    if (board[0][2] == board[1][1] && board[2][0] == board[1][1])
    {
        winner = board[1][1];
        return 1;
    }
    return 0;
}
Vector2 check_mouse()
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
        if (board[row][column] != 'O')
        {
            row_box = row;
            column_box = column;
            playing_for = 'X';
            kord++;
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
        if (board[row][column] != 'X')
        {
            row_box = row;
            column_box = column;
            playing_for = 'O';
            kord++;
            return {row, column};
            
        }
    }
    return {9000, 0};
}
//------------------------------------------------------------------------------------
bool play_again_mouse()
{
    if (300 <= GetMousePosition().x && GetMousePosition().x <= 630 && 500 <= GetMousePosition().y && GetMousePosition().y <= 550)
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            int number = 0;
            kord = 0;
            winner = ' ';
            for (int i = 0; i < 3; i++)
            {
                number++;
                for (int j = 0; j < 3; j++)
                {
                    number++;
                    board[i][j] = (char)number;
                }
            }
        }
        return true;
    }
    return false;
}

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 900;
    const int screenHeight = 900;
    InitWindow(screenWidth, screenHeight, "TIC-TAC-TOE");

    Image image = LoadImage("C:\\Users\\subbi\\space-invader\\SPACE INVADER\\SUDA.png");
    //Image image = LoadImage("C:\\Users\\subbi\\Downloads\\pixil-frame-0 (1).png");
    Texture2D texture = LoadTextureFromImage(image);
    UnloadImage(image);
    Image imagebg = LoadImage("C:\\Users\\subbi\\c++\\tic-tac-toe\\build\\endscreen.png");
    Texture2D texture2 = LoadTextureFromImage(imagebg);
    UnloadImage(imagebg);
    // bones
    Image luu = LoadImage("C:\\Users\\subbi\\Witchhunter\\SPACE INVADER\\fucked_hitbox\\bone.png");
    Texture2D bones_pic = LoadTextureFromImage(luu);
    UnloadImage(luu);
    Image luu2 = LoadImage("C:\\Users\\subbi\\Witchhunter\\SPACE INVADER\\fucked_hitbox\\downwardsbone.png");
    Texture2D loo = LoadTextureFromImage(luu2);
    UnloadImage(luu2);
    Image null = LoadImage("C:\\Users\\subbi\\c++\\tic-tac-toe\\build\\pixil-frame-0 (2).png");
    Texture2D nullpilt = LoadTextureFromImage(null);
    UnloadImage(null);
    Image ix = LoadImage("C:\\Users\\subbi\\c++\\tic-tac-toe\\build\\pixil-frame-0 (1).png");
    Texture2D ixpilt = LoadTextureFromImage(ix);
    UnloadImage(ix);
    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
                      //--------------------------------------------------------------------------------------
    Bones bone1;
    Bones bone2;
    ball ball;
    ball.x = 450;
    ball.y = 450;

    bool match_won = false;
    Vector2 kast = {9000, 9000};
    bool fight = false;
    __uint128_t fight_timer;
    bool spawn;
    bool dead = false;

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        if (fight && time(NULL) - fight_timer < 30 && !dead)
        {

            if (CheckCollisionRecs({ball.x, ball.y, ball.width, ball.height}, {bone1.x, bone1.y, bone1.width, bone1.height})||CheckCollisionRecs({ball.x, ball.y, ball.width, ball.height}, {bone2.x, bone2.y, bone2.width, bone2.height}))
            {
                dead = true;
                if (playing_for ==  'X'){playing_for='O';}
                else if (playing_for ==  'O'){playing_for = 'X';}
                board[row_box][column_box] = playing_for;
                playing_for = ' ';
            }
            BeginDrawing();
            ClearBackground(BLACK);
            if (spawn)
            {
                spawn = false;
                bone1.x = board_filled[row_box][column_box][0] + 260;
                bone1.y = board_filled[row_box][column_box][1] + 160;
                bone1.speed = 2;
                bone1.is_moving = true;
                bone2.x = board_filled[row_box][column_box][0] + 260;
                bone2.y = board_filled[row_box][column_box][1] ;
                bone2.speed = 2;
                bone2.is_moving = true;
            }

            bone1.move(board_filled[row_box][column_box][0]);
            bone1.draw();
            if (time(NULL) - fight_timer > 1.167)
            {
            bone2.move(board_filled[row_box][column_box][0]);
            bone2.draw();
            }
           

            ball.ball_move();

            //----------------------------------------------------------------------------------

            //----------------------------------------------------------------
            Draw_board(screenWidth, screenHeight, nullpilt, ixpilt);
            DrawText("TIC - TAC - TOE from hell!", 300, 20, 0, LIGHTGRAY);
            ball.draw(texture);

            EndDrawing();
        }

        else if (kord != 9 && winner == ' ')
        {
            if (playing_for != ' ')
            {
                board[row_box][column_box] = playing_for;
                playing_for = ' ';
            }
            if (kontroll() == 1)
            {
                kord = 9;
            }
            kast = check_mouse();
            if (kast.x != 9000)
            {
                fight = true;
                spawn = true;
                dead = false;
                ball.x = board_filled[(int)kast.x][(int)kast.y][0] + 80;
                ball.y = board_filled[(int)kast.x][(int)kast.y][1] + 80;
                fight_timer = time(NULL);
            }
            
            BeginDrawing();
            ClearBackground(BLACK);

            //----------------------------------------------------------------
            Draw_board(screenWidth, screenHeight, nullpilt, ixpilt);
            DrawText("TIC - TAC - TOE from hell!", 310, 0, 20, LIGHTGRAY);

            
            EndDrawing();
        }
        else
        {
            auto varv = DARKGRAY;
            if (play_again_mouse())
            {
                varv = LIGHTGRAY;
            }
            else
            {
                varv = DARKGRAY;
            }

            BeginDrawing();

            DrawTexture(texture2, 0, 0, WHITE);
            
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
    }
    CloseWindow();
    return 0;
}*/