#ifndef CHARACTERCONTROLLER_H

#define CHARACTERCONTROLLER_H

#include <raylib.h>

// Character States

// These tell us which sprite should be displayed.


constexpr int STATE_UP = 1;

constexpr int STATE_MID = 0;

constexpr int STATE_DOWN = -1;

//Character Data

//This struct stores everything about the player.


struct Character
{
    // Current position on the screen
    Vector2 location;

    //Rotation angle (degrees)
    float angle;

    //Movement speed
    float speed;

    //Different textures depending on movement
   
    Texture2D textureUp;
   
    Texture2D textureMid;
   
    Texture2D textureDown;

    //Rectangle used for drawing or collision
    Rectangle rectangle;

    //Current animation/state
    int state;
};

// CharacterController

// Handles all player movement, input, and drawing.

class CharacterController
{
private:

    //The player object
    Character character;

    //How fast gravity pulls the character down
    float gravitySpeed;

    //Tracks time between frames
    float elapsedTime;

    //Rotates the character sprite
    void rotate(float angle);

    //Calculates the gravity movement each frame
    Vector2 gravityModifier();

public:

    //Constructor
   
    //Creates a controller using a Character and gravity value.
    
    CharacterController(Character character, float gravitySpeed);

    //Destructor
    // Runs automatically when the controller is destroyed.
    ~CharacterController();

    //Moves the character upward.
    //Usually called when the player presses jump.
    Vector2 moveUp();

    //Draws the character to the screen.
    Vector2 drawCharacter();

    //Reads keyboard input and reacts to it.
    Vector2 inputHandler();

    //Updates the character every frame.
    //This should be called inside the game loop.
    void onUpdate();
};

#endif // CHARACTERCONTROLLER_H
 