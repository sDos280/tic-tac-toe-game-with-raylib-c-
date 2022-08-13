// to run the program run the following command: ".\run.ps1" in the shell in this directory
// to fix the PowerShell Script Not Digitally Signed problem run the following command: "Set-ExecutionPolicy -Scope Process -ExecutionPolicy Bypass" in the shell in this directory

#include "raylib.h"
#include <string.h>
typedef enum {
    XWIN,
    OWIN,
    DRAW,
    PLAYING
}GameState;
int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    const Color backgroundColor = (Color){20, 189, 172, 255};
    const Color lineColor = (Color){13, 161, 146, 255};

    const Color xColor = (Color){84, 84, 84, 255};
    const Color oColor = (Color){242, 235, 211, 255};

    bool IsXTurn = true;

    GameState state = PLAYING;

    int grid[3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    }; // 1 -> x -1 -> o 0-> nathing

    //int gridStartPositonX = 266;
    //int gridStartPositonY = 92;
    //int gridStartPositonSize = 266;

    char turnText[7] = "  turn";

    int checks[8][3] = {
        {0, 1, 2}, // top row
        {3, 4, 5}, // middle row
        {6, 7, 8}, // bottom row
        {0, 3, 6}, // left column
        {1, 4, 7}, // middle column
        {2, 5, 8}, // right column
        {0, 4, 8}, // topleft to bottomright
        {6, 4, 2}, // bottomright to topright
    };

    InitWindow(screenWidth, screenHeight, "simple window");


    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        Vector2 mousePos = GetMousePosition();

        if (IsMouseButtonPressed(0)){
            if ((266 < mousePos.x && mousePos.x < 532) && (92 < mousePos.y && mousePos.y < 358)){
                // get mouse position in the grid
                int gridX = (int)((mousePos.x - 266) / 88); 
                int gridY = (int)((mousePos.y - 92) / 88);
                //set grid values
                if (grid[gridY][gridX]==0){
                    if (IsXTurn){
                        grid[gridY][gridX] = 1;
                        IsXTurn = !IsXTurn;
                    }else{
                        grid[gridY][gridX] = -1;
                        IsXTurn = !IsXTurn;
                    }
                }
            }
        }

        if (state == PLAYING){

            // check for a winner
            for(int i = 0; i < 8; i++){
                int count = 0;
                for(int j = 0; j < 3; j++){
                    int row = (checks[i][j] / 3);
                    int column = checks[i][j] - row * 3;
                    count += grid[row][column];
                }
                if (count == 3){
                    state = XWIN;
                    break;
                }else if (count == -3){
                    state = OWIN;
                    break;  
                }
            }

            // if no one won check, for draw(is the grid Full) 
            if (state == PLAYING){
                bool isGridFull = true;
                for(int i = 0; i < 3; i++){
                    for(int j = 0; j < 3; j++){
                        if (grid[i][j]==0){
                            isGridFull = false;
                        }
                    }
                }
                // if no zero found and no one won => the game is a draw
                if (isGridFull){
                    state = DRAW;
                }
            }
        }
        
        if (state == PLAYING){
            BeginDrawing();
                ClearBackground(backgroundColor);
                turnText[0] = (IsXTurn)? 'X' : 'O';
                DrawText(turnText, 353, 30, 30, WHITE);
                // vertical lines
                DrawLineEx((Vector2){354, 92}, (Vector2){354, 358}, 10, lineColor);
                DrawLineEx((Vector2){443, 92}, (Vector2){443, 358}, 10, lineColor);
                // horizontal lines
                DrawLineEx((Vector2){266, 180}, (Vector2){532, 180}, 10, lineColor);
                DrawLineEx((Vector2){266, 269}, (Vector2){532, 269}, 10, lineColor);
            
                
                // draw grid values
                for(int i = 0; i < 3; i++){
                    for(int j = 0; j < 3; j++){
                        Vector2 mid = (Vector2){310 + j * 88, 135 + i * 88};
                        if (grid[i][j]==1){
                            DrawLineEx((Vector2){mid.x-27, mid.y-27}, (Vector2){mid.x+27, mid.y+27}, 8, xColor);
                            DrawCircle(mid.x-27, mid.y-27, 4, xColor);
                            DrawCircle(mid.x+27, mid.y+27, 4, xColor);
                            DrawLineEx((Vector2){mid.x-27, mid.y+27}, (Vector2){mid.x+27, mid.y-27}, 8, xColor);
                            DrawCircle(mid.x-27, mid.y+27, 4, xColor);
                            DrawCircle(mid.x+27, mid.y-27, 4, xColor);
                        }else if (grid[i][j]==-1){
                            DrawRing(mid, 20, 30, 0, 360, 360, oColor);
                        }
                    }
                }
            EndDrawing();
        }else if (state == DRAW){
            BeginDrawing();
                ClearBackground(backgroundColor);
                DrawText("X", 325, 130, 120, xColor);
                DrawText("O", 402, 130, 120, oColor);
                DrawText("DRAW!", 330, 300, 50, oColor);
                DrawText("press R to reset game", 226, 390, 30, xColor);
                if (IsKeyPressed(KEY_R)){
                    state = PLAYING;
                    IsXTurn = true;
                    memset(grid[0], 0, 36);
                }
            EndDrawing();
        }else if (state == XWIN){
            BeginDrawing();
                ClearBackground(backgroundColor);
                DrawText("X", 365, 130, 120, xColor);
                DrawText("WINNER!", 300, 300, 50, xColor);
                DrawText("press R to reset game", 226, 390, 30, xColor);
                if (IsKeyPressed(KEY_R)){
                    state = PLAYING;
                    IsXTurn = true;
                    memset(grid[0], 0, 36);
                }
            EndDrawing();
        }else if (state == OWIN){
            BeginDrawing();
                ClearBackground(backgroundColor);
                DrawText("O", 365, 130, 120, oColor);
                DrawText("WINNER!", 300, 300, 50, oColor);
                DrawText("press R to reset game", 226, 390, 30, oColor);
                if (IsKeyPressed(KEY_R)){
                    state = PLAYING;
                    IsXTurn = true;
                    memset(grid[0], 0, 36);
                }
            EndDrawing();
        }
    }

    CloseWindow();

    return 0;
}
