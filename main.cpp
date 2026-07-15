/*
Where the main game is located
*/
#include "raylib.h" //includes the raylib library
#include <iostream>
#include <random>
#include <math.h>

int getRand(int min, int max);

int main()
{
    int screenWidth = 850;
    int screenHeight = 910;
    int charbirdX = 100;
    int charbirdY = 400;
    float accel = 0;
    bool start;
    int pipeX = screenWidth;
    int pipeY = screenHeight - getRand(300, 800);
    int embX = screenWidth;
    int embY = screenHeight;

    InitWindow(screenWidth, screenHeight, "FlappyMon"); // Initializes a window canvas that the game's graphics
    SetTargetFPS(60);
    Texture2D ember = LoadTexture("assets/sprites/ember.png");
    Texture2D charmander = LoadTexture("assets/sprites/charmander.png");
    Texture2D executor = LoadTexture("assets/sprites/executor.png");
    // Load your background texture
    Texture2D background = LoadTexture("assets/sprites/background-day.png");
    Texture2D backgroundNight = LoadTexture("assets/sprites/menu.png");
    // Source rectangle defines the full dimensions of your original image file
    Rectangle sourceRec = {0.0f, 0.0f, (float)background.width, (float)background.height};
    // Destination rectangle stretches the image to fit your window size
    Rectangle destRec = {0.0f, 0.0f, (float)screenWidth, (float)screenHeight};
    // Origin point for rotation (top-left corner)
    Vector2 origin = {0.0f, 0.0f};

    // Source crop rectangle for Charmander (entire texture frame)
    Rectangle charSourceRec = {0.0f, 0.0f, (float)charmander.width, (float)charmander.height};
    // Origin pivot point sets rotation strictly around Charmander's center
    Vector2 charOrigin = {(float)charmander.width / 2.0f, (float)charmander.height / 2.0f};
    // Source crop rectangle for ember (entire texture frame)
    Rectangle embSourceRec = {0.0f, 0.0f, (float)ember.width, (float)ember.height};
    // Origin pivot point sets rotation strictly around the ember center
    Vector2 embOrigin = {(float)ember.width / 2.0f, (float)ember.height / 2.0f};

    while (!WindowShouldClose())
    { // checks if user presses esc
        Vector2 mousePos = GetMousePosition();
        // Compute relative angle between Charmander's current position and mouse coordinates
        float angle = atan2f(mousePos.y - charbirdY, mousePos.x - charbirdX) * RAD2DEG;

        // Dynamic destination mapping rectangle updating with Charmander positions
        Rectangle charDestRec = {(float)charbirdX, (float)charbirdY, (float)charmander.width, (float)charmander.height};
        Rectangle embDestRec = {(float)embX, (float)embY, (float)ember.width*0.05f, (float)ember.height*0.05f};
        if (IsKeyDown(KEY_ENTER))
        {
            start = true;
        }
        if (start)
        {
            // 1.Event Checker
            if (IsKeyPressed(KEY_SPACE))
            {
                accel = 0;
                charbirdY -= 120;
            }
            else
            {
                charbirdY += 1 + accel;
                accel += 0.3;
            }

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                embX = charbirdX;
                embY = charbirdY;
                while (embX < mousePos.x)
                {
                    embX++;
                }
                embX = screenWidth +100;
                embY = screenHeight +100;
            }
            // 2.Update Positions
            if (charbirdY <= 0 + charmander.height - 150)
            {
                charbirdY = 0 + charmander.height - 150;
            }
            else if (charbirdY >= screenHeight - charmander.height + 200)
            {
                charbirdY = screenHeight - charmander.height + 200;
            }
            pipeX -= 8;
            if (charbirdX - 750 > pipeX)
            {
                pipeY = screenHeight - getRand(300, 800);
                pipeX = screenWidth;
            }
        }

        // 3.Draw
        BeginDrawing();
        ClearBackground(WHITE);
        DrawTexturePro(background, sourceRec, destRec, origin, 0.0f, WHITE);
        DrawTexturePro(charmander, charSourceRec, charDestRec, charOrigin, angle, WHITE);
        DrawTexturePro(ember, embSourceRec, embDestRec, embOrigin, angle, WHITE);
        DrawTexture(executor, pipeX, pipeY, WHITE);
        EndDrawing();
    }
    UnloadTexture(executor);
    UnloadTexture(charmander);
    UnloadTexture(background);
    CloseWindow();
} // end of main function

int getRand(int min, int max)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<int> distrib(min, max);
    return distrib(rng);
}