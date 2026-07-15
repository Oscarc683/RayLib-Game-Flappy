/*
Where the main game is located
*/
#include "raylib.h" //includes the raylib library
#include <iostream>
#include "ObstacleManager.h"
#include "CharacterController.h"

int main()
{
    int screenWidth = 800;
    int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "FlappyMon");// Initializes a window canvas that the game's graphics
    Image backgroundImage = LoadImage("assets/sprites/background-day.png");
    Texture2D backgroundTexture = LoadTextureFromImage(backgroundImage);
    UnloadImage(backgroundImage);

    Image obstacleImage = LoadImage("assets/sprites/executor.png");
    ImageResize(&obstacleImage, (int)(obstacleImage.width * 0.2), (int)(obstacleImage.height * 0.2));

    Image baseImage = LoadImage("assets/sprites/base.png");
    Texture2D baseTexture = LoadTextureFromImage(baseImage);
    UnloadImage(baseImage);

    Image characterImage = LoadImage("assets/sprites/bluebird-midflap.png");
    ImageResize(&characterImage, (int)(characterImage.width * 1.5), (int)(characterImage.height * 1.5));
    Texture2D characterMidTexture = LoadTextureFromImage(characterImage);
    UnloadImage(characterImage);

    characterImage = LoadImage("assets/sprites/bluebird-upflap.png");
    ImageResize(&characterImage, (int)(characterImage.width * 1.5), (int)(characterImage.height * 1.5));
    Texture2D characterUpTexture = LoadTextureFromImage(characterImage);
    UnloadImage(characterImage);

    characterImage = LoadImage("assets/sprites/bluebird-downflap.png");
    ImageResize(&characterImage, (int)(characterImage.width * 1.5), (int)(characterImage.height * 1.5));
    Texture2D characterDownTexture = LoadTextureFromImage(characterImage);
    UnloadImage(characterImage);
    SetTargetFPS(60); // Sets the game to run at 60fps
    float speed = 300, characterSpeed = 25;
    Character character;
    character.location = Vector2{60, (float)screenHeight / 2};
    character.state = CHAR_STATE_MID;
    character.textureUp = characterUpTexture;
    character.textureMid = characterMidTexture;
    character.textureDown = characterDownTexture;
    character.angle = 0;
    character.rectangle = Rectangle{0, 0, (float)characterUpTexture.width, (float)characterUpTexture.height};
    CharacterController characterController(character, characterSpeed);

    float currentBackgroundPosition = 0;
    float currentBasePosition = 0;
    // Vector2 characterPosition = Vector2{60, (float)screenHeight / 2};
    ObstacleManager obstacleManager(obstacleImage, speed, (Vector2){(float)screenWidth, (float)(screenHeight - baseTexture.height)}, 500);
    while (WindowShouldClose() == false) { // checks if user presses esc
        BeginDrawing();
        ClearBackground(RAYWHITE);

        float frameSpeed = GetFrameTime() * speed;
        obstacleManager.setSpeed(frameSpeed);
        DrawFPS(500, 500);
        DrawTextureRec(backgroundTexture, (Rectangle){currentBackgroundPosition, 0, (float)screenWidth, (float)screenHeight}, (Vector2){0, 0}, RAYWHITE);
        DrawTextureRec(baseTexture, (Rectangle){currentBasePosition, 0, (float)screenWidth, (float)baseTexture.height}, (Vector2){0, (float)(screenHeight - baseTexture.height)}, RAYWHITE);
        obstacleManager.generateObstacle(currentBasePosition);
        obstacleManager.drawObstacles();
        characterController.onUpdate();
        currentBackgroundPosition += (frameSpeed / 2);
        currentBasePosition += frameSpeed;
        if (currentBackgroundPosition >= screenWidth)
            currentBackgroundPosition -= screenWidth;
        if (currentBasePosition >= screenWidth)
            currentBasePosition -= screenWidth;
        EndDrawing();
    }
    CloseWindow();
} // end of main function
