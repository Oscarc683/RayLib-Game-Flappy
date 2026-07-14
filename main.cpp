/*
Where the main game is located
*/
#include "raylib.h" //raylib library
#include <iostream>

int main()
{
    InitWindow(800, 450, "FlappyMon");
    SetTargetFPS(60);
    while(WindowShouldClose() == false){
        BeginDrawing();
        
        EndDrawing();
    }


CloseWindow();
}//end of main function
    

