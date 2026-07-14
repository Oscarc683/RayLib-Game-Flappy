/*
Where the main game is located
*/
#include "raylib.h"//includes the raylib library
#include <iostream>
#include "ObstacleManager.h"
#include "CharacterController.h"

int main()
{
    Color skyBlue = {135, 206, 250, 255};
    InitWindow(300, 600, "FlappyMon");//Initializes a window canvas that the game's graphics
    SetTargetFPS(60);//Sets the game to run at 60fps
    while(WindowShouldClose() == false){//checks if user presses esc
        BeginDrawing();
        ClearBackground(skyBlue);
        EndDrawing();
    }


CloseWindow();
}//end of main function
    

