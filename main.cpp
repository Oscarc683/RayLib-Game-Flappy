/*
Where the main game is located
*/
#include "raylib.h"
#include <iostream>

int main()
{
    InitWindow(300, 600, "FlappyMon");
    SetTargetFPS(60);
    while(WindowShouldClose() == false){
        BeginDrawing();
        
        EndDrawing();
    }

    CloseWindow();
}