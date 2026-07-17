/*
 I wrote the main game implementation in this file.
 It uses RayLib for windowing, texture rendering, input handling,
 and simple 2D game logic.
*/
#include "raylib.h" // I use raylib for graphics and input.
#include <iostream> // I keep this include for possible debug output.
#include <random> // I use C++ random utilities for enemy and obstacle placement.
#include <math.h> // I use math functions for projectile direction and rotation.

// I declare the random integer helper before I use it in main.
int getRand(int min, int max);

// I define the projectile structure to store each ember shot.
struct Projectile {
    float x;
    float y;
    float velX;
    float velY;
    float angle;
    bool active;
};

// I define the enemy structure for the Bulbasaur target.
struct Enemy {
    float x;
    float y;
    bool active;
};

const int MAX_PROJECTILES = 10;
Projectile projectiles[MAX_PROJECTILES] = {0};
Enemy bulbasaur = {0};
int bulbasaurSpawnCounter = 0;
const int BULBASAUR_SPAWN_RATE = 120;  // I spawn Bulbasaur every 120 frames at 60 FPS.

int main()
{
    // I configure the game window and initial player state.
    int screenWidth = 850;
    int screenHeight = 910;
    int charbirdX = 100;
    int charbirdY = 400;
    int score = 0;
    float accel = 0;
    bool start = false;
    bool inMenu = true;
    bool gameOver = false;
    // I use these booleans to track the menu state, active gameplay, and game over screen.
    // I create clickable button rectangles for menu interactions.
    Rectangle startButton = {(float)(screenWidth / 2 - 180), (float)(screenHeight - 150), 140.0f, 60.0f};
    Rectangle exitButton = {(float)(screenWidth / 2 + 40), (float)(screenHeight - 150), 140.0f, 60.0f};
    Rectangle playAgainButton = {(float)(screenWidth / 2 - 100), (float)(screenHeight - 180), 200.0f, 70.0f};
    int pipeX = screenWidth;
    int pipeY = screenHeight - getRand(300, 800);
    bool embLoaded = false;
    Texture2D ember = {0};

    InitWindow(screenWidth, screenHeight, "FlappyMon"); // I initialize the game window.
    SetTargetFPS(60); // I cap the game at 60 frames per second.
    Texture2D charmander = LoadTexture("assets/sprites/charmander.png");
    Texture2D executor = LoadTexture("assets/sprites/executor.png");
    Texture2D background = LoadTexture("assets/sprites/background-day.png");
    Texture2D menu = LoadTexture("assets/sprites/menu.png");
    Texture2D gameover = LoadTexture("assets/sprites/gameover.png");
    Texture2D bulbasaurTex = LoadTexture("assets/sprites/bulbasaur.png");
    // I load the main sprite assets used by the player, obstacles, menu, and enemies.
    // I load number textures so I can draw the score using sprite digits.
    Texture2D numbers[10];
    for (int i = 0; i < 10; i++)
    {
        char filename[50];
        snprintf(filename, sizeof(filename), "assets/sprites/%d.png", i);
        numbers[i] = LoadTexture(filename);
    }
    // I prepare rectangles for drawing the menu background at full screen.
    Rectangle menuSourceRec = {0.0f, 0.0f, (float)menu.width, (float)menu.height};
    Rectangle menuDestRec = {0.0f, 0.0f, (float)screenWidth, (float)screenHeight};
    Vector2 menuOrigin = {0.0f, 0.0f};
    // Game over background
    Rectangle gameoverSourceRec = {0.0f, 0.0f, (float)gameover.width, (float)gameover.height};
    Rectangle gameoverDestRec = {0.0f, 0.0f, (float)screenWidth, (float)screenHeight};
    Vector2 gameoverOrigin = {0.0f, 0.0f};
    
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
    // Source crop rectangle for ember (entire texture frame) - will be set when texture loads
    Rectangle embSourceRec = {0.0f, 0.0f, 0.0f, 0.0f};
    // Origin pivot point sets rotation strictly around the ember center - will be set when texture loads
    Vector2 embOrigin = {0.0f, 0.0f};

    while (!WindowShouldClose())
    { // I keep running the game loop until the window is closed.
        Vector2 mousePos = GetMousePosition();
        
        if (inMenu)
        {
            // I handle menu input and check for button clicks.
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                if (CheckCollisionPointRec(mousePos, startButton))
                {
                    inMenu = false;
                    gameOver = false;
                    start = true;
                    // Reset game state when the player starts a new game.
                    charbirdX = 100;
                    charbirdY = 400;
                    accel = 0;
                    pipeX = screenWidth;
                    pipeY = screenHeight - getRand(300, 800);
                    for (int i = 0; i < MAX_PROJECTILES; i++)
                    {
                        projectiles[i].active = false;
                    }
                    bulbasaur.active = false;
                    bulbasaurSpawnCounter = 0;
                    score = 0;
                    if (!embLoaded)
                    {
                        ember = LoadTexture("assets/sprites/ember.png");
                        embSourceRec = {0.0f, 0.0f, (float)ember.width, (float)ember.height};
                        embOrigin = {(float)ember.width / 2.0f, (float)ember.height / 2.0f};
                        embLoaded = true;
                    }
                }
                else if (CheckCollisionPointRec(mousePos, exitButton))
                {
                    // I close the window and exit the game when the user clicks Exit.
                    CloseWindow();
                    return 0;
                }
            }
        }
        else if (gameOver)
        {
            // I handle the game over screen and let the player return to the menu.
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                if (CheckCollisionPointRec(mousePos, playAgainButton))
                {
                    // I reset the state back to the menu for a new run.
                    inMenu = true;
                    gameOver = false;
                    start = false;
                }
            }
        }
        else
        {
            // I process gameplay inputs and update the world while the game is running.
            if (start)
            {
                // 1. Event Checker: jump when the player presses SPACE.
                if (IsKeyPressed(KEY_SPACE))
                {
                    accel = 0;
                    charbirdY -= 120;
                }
                else
                {
                    // I apply gravity by increasing the downward acceleration.
                    charbirdY += 1 + accel;
                    accel += 0.3;
                }

                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    if (!embLoaded)
                    {
                        ember = LoadTexture("assets/sprites/ember.png");
                        embSourceRec = {0.0f, 0.0f, (float)ember.width, (float)ember.height};
                        embOrigin = {(float)ember.width / 2.0f, (float)ember.height / 2.0f};
                        embLoaded = true;
                    }
                    // I fire a projectile from Charmander toward the mouse cursor.
                    for (int i = 0; i < MAX_PROJECTILES; i++)
                    {
                        if (!projectiles[i].active)
                        {
                            projectiles[i].x = charbirdX;
                            projectiles[i].y = charbirdY + 40.0f;
                            float dx = mousePos.x - projectiles[i].x;
                            float dy = mousePos.y - projectiles[i].y;
                            float distance = sqrt(dx * dx + dy * dy);
                            if (distance > 0)
                            {
                                projectiles[i].velX = (dx / distance) * 12.0f;
                                projectiles[i].velY = (dy / distance) * 12.0f;
                                projectiles[i].angle = atan2f(dy, dx) * RAD2DEG;
                                projectiles[i].active = true;
                            }
                            break;  // I only spawn one projectile per click.
                        }
                    }
                }
                // 2. Update Positions
                // I keep Charmander on screen by clamping its vertical position.
                if (charbirdY <= 0 + charmander.height - 150)
                {
                    charbirdY = 0 + charmander.height - 150;
                }
                else if (charbirdY >= screenHeight - charmander.height + 200)
                {
                    charbirdY = screenHeight - charmander.height + 200;
                }
                // I scroll the executor pipe left and reset it once it passes the left edge.
                pipeX -= 8;
                if (charbirdX - 750 > pipeX)
                {
                    pipeY = screenHeight - getRand(300, 800);
                    pipeX = screenWidth;
                }

                // Bulbasaur spawning and movement
                bulbasaurSpawnCounter++;
                if (bulbasaurSpawnCounter >= BULBASAUR_SPAWN_RATE && !bulbasaur.active)
                {
                    bulbasaur.x = screenWidth;
                    bulbasaur.y = getRand(100, screenHeight - 150);
                    bulbasaur.active = true;
                    bulbasaurSpawnCounter = 0;
                }
                if (bulbasaur.active)
                {
                    bulbasaur.x -= 5;  // Move Bulbasaur left across the screen.
                    if (bulbasaur.x < 0)
                    {
                        bulbasaur.active = false;
                        score += 10;  // I reward the player when Bulbasaur safely passes.
                    }
                    
                    // I create a collision box for Bulbasaur and test each projectile.
                    Rectangle bulbasaurRec = {bulbasaur.x + (float)bulbasaurTex.width * 0.2f, 
                                              bulbasaur.y + (float)bulbasaurTex.height * 0.15f, 
                                              (float)bulbasaurTex.width * 0.1f, 
                                              (float)bulbasaurTex.height * 0.15f};
                    for (int i = 0; i < MAX_PROJECTILES; i++)
                    {
                        if (projectiles[i].active)
                        {
                            Rectangle projectileRec = {projectiles[i].x - 2, projectiles[i].y - 2, 4.0f, 4.0f};
                            if (CheckCollisionRecs(bulbasaurRec, projectileRec))
                            {
                                bulbasaur.active = false;
                                projectiles[i].active = false;
                                score += 1;  // I add a point when the player hits Bulbasaur.
                            }
                        }       
                    }
                }
 
                // Update all projectiles
                for (int i = 0; i < MAX_PROJECTILES; i++)
                {
                    if (projectiles[i].active)
                    {
                        projectiles[i].x += projectiles[i].velX;
                        projectiles[i].y += projectiles[i].velY;
                        // Deactivate if off-screen
                        if (projectiles[i].x < 0 || projectiles[i].x > screenWidth || 
                            projectiles[i].y < 0 || projectiles[i].y > screenHeight)
                        {
                            projectiles[i].active = false;
                        }
                    }
                }

                // I detect collisions between Charmander and the executor pipe.
                Rectangle charCollisionRec = {(float)charbirdX - (float)charmander.width * 0.08f, 
                                              (float)charbirdY - (float)charmander.height * 0.06f, 
                                              (float)charmander.width * 0.16f, 
                                              (float)charmander.height * 0.12f};
                Rectangle execCollisionRec = {(float)pipeX + (float)executor.width * 0.2f, 
                                              (float)pipeY, 
                                              (float)executor.width * 0.6f, 
                                              (float)executor.height};
                if (CheckCollisionRecs(charCollisionRec, execCollisionRec))
                {
                    start = false;  // Stop the game
                    gameOver = true;  // Show game over screen
                }
            }
        }

        // 3. Draw: I render the current game screen state each frame.
        BeginDrawing();
        ClearBackground(WHITE);
        
        if (inMenu && !gameOver)
        {
            // I draw the main menu and interactive buttons.
            DrawTexturePro(background, sourceRec, destRec, origin, 0.0f, WHITE);
            
            // Draw start button - red/orange with white border
            DrawRectangleRec(startButton, {220, 100, 50, 255});
            DrawRectangleLinesEx(startButton, 4.0f, {255, 255, 255, 255});
            DrawText("START", (int)(startButton.x + 35), (int)(startButton.y + 15), 28, {255, 255, 255, 255});
            
            // Draw exit button - red/orange with white border
            DrawRectangleRec(exitButton, {220, 100, 50, 255});
            DrawRectangleLinesEx(exitButton, 4.0f, {255, 255, 255, 255});
            DrawText("EXIT", (int)(exitButton.x + 40), (int)(exitButton.y + 15), 28, {255, 255, 255, 255});
        }
        else if (gameOver)
        {
            // Draw game over screen
            DrawTexturePro(gameover, gameoverSourceRec, gameoverDestRec, gameoverOrigin, 0.0f, WHITE);
            
            // Draw play again button
            DrawRectangleRec(playAgainButton, {0, 100, 200, 255});
            DrawRectangleLinesEx(playAgainButton, 3.0f, {0, 0, 0, 255});
            DrawText("PLAY AGAIN", (int)(playAgainButton.x + 30), (int)(playAgainButton.y + 20), 28, {255, 255, 255, 255});
        }
        else
        {
            // Draw game
            DrawTexturePro(background, sourceRec, destRec, origin, 0.0f, WHITE);
            float angle = atan2f(mousePos.y - charbirdY, mousePos.x - charbirdX) * RAD2DEG;
            Rectangle charDestRec = {(float)charbirdX, (float)charbirdY, (float)charmander.width, (float)charmander.height};
            DrawTexturePro(charmander, charSourceRec, charDestRec, charOrigin, angle, WHITE);
            // Draw all active projectiles
            for (int i = 0; i < MAX_PROJECTILES; i++)
            {
                if (projectiles[i].active && embLoaded)
                {
                    Rectangle embDestRec = {projectiles[i].x, projectiles[i].y, (float)ember.width*0.05f, (float)ember.height*0.05f};
                    DrawTexturePro(ember, embSourceRec, embDestRec, embOrigin, projectiles[i].angle, WHITE);
                }
            }
            DrawTexture(executor, pipeX, pipeY, WHITE);
            
            // Draw bulbasaur
            if (bulbasaur.active)
            {
                // I draw Bulbasaur whenever it is active in the game world.
                Rectangle bulbasaurSourceRec = {0.0f, 0.0f, (float)bulbasaurTex.width, (float)bulbasaurTex.height};
                Rectangle bulbasaurDestRec = {bulbasaur.x, bulbasaur.y, (float)bulbasaurTex.width * 0.5f, (float)bulbasaurTex.height * 0.5f};
                DrawTexturePro(bulbasaurTex, bulbasaurSourceRec, bulbasaurDestRec, {0.0f, 0.0f}, 0.0f, WHITE);
            }
            
            // I draw the numeric score in the top-left corner using sprite textures.
            int tempScore = score;
            int scoreDigits[10];
            int digitCount = 0;
            if (tempScore == 0)
            {
                scoreDigits[0] = 0;
                digitCount = 1;
            }
            else
            {
                while (tempScore > 0 && digitCount < 10)
                {
                    scoreDigits[digitCount] = tempScore % 10;
                    tempScore /= 10;
                    digitCount++;
                }
            }
            int xPos = 20;
            for (int i = digitCount - 1; i >= 0; i--)
            {
                DrawTexture(numbers[scoreDigits[i]], xPos, 20, WHITE);
                xPos += 30;  // Adjust spacing between digits
            }
        }
        EndDrawing();
    }
    // I unload textures to free GPU memory when the game ends.
    UnloadTexture(executor);
    UnloadTexture(charmander);
    UnloadTexture(background);
    UnloadTexture(menu);
    UnloadTexture(gameover);
    UnloadTexture(bulbasaurTex);
    for (int i = 0; i < 10; i++)
    {
        UnloadTexture(numbers[i]);
    }
    if (embLoaded)
    {
        UnloadTexture(ember);
    }
    CloseWindow();
} // end of main function

int getRand(int min, int max)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<int> distrib(min, max);
    return distrib(rng);
}