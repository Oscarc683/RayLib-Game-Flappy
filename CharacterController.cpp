// #include "CharacterController.h"

// //Constructor
// //Stores the character and the gravity speed.
// CharacterController::CharacterController(Character character, float gravitySpeed)
// {
//     mCharacter = character;
//     mGraviationSpeed = gravitySpeed;
// }

// CharacterController::~CharacterController() {}

// //Moves the character upward.
// //This is called while the jump button is held.
// void CharacterController::moveUp()
// {
//     //Reset the timer when a new jump starts.
//     if (mCharacter.state != CHAR_STATE_UP)
//         mElapsedTime = 0.0f;

//     mElapsedTime += GetFrameTime();

//     mCharacter.state = CHAR_STATE_UP;

//     //Negative speed moves the character upward.
//     mCharacter.speed = -(mGraviationSpeed * mElapsedTime) - 5.0f;
//     mCharacter.location.y += mCharacter.speed;
// }

// //Applies gravity to pull the character downward.
// void CharacterController::applyGravity()
// {
//     //Reset the timer when the character starts falling.
//     if (mCharacter.state != CHAR_STATE_DOWN)
//         mElapsedTime = 0.0f;

//     mElapsedTime += GetFrameTime();

//     mCharacter.state = CHAR_STATE_DOWN;

//     mCharacter.speed = mGraviationSpeed * mElapsedTime;
//     mCharacter.location.y += mCharacter.speed;
// }

// //Rotates the character by the given angle.
// void CharacterController::rotate(float angle)
// {
//     mCharacter.angle += angle;
// }

// //Draws the correct sprite depending on the character's state.
// void CharacterController::drawCharacter()
// {
//     Texture2D texture = mCharacter.textureMid;

//     if (mCharacter.state == CHAR_STATE_UP)
//         texture = mCharacter.textureUp;
//     else if (mCharacter.state == CHAR_STATE_DOWN)
//         texture = mCharacter.textureDown;

//     Rectangle destination = {
//         mCharacter.location.x,
//         mCharacter.location.y,
//         mCharacter.rectangle.width,
//         mCharacter.rectangle.height
//     };

//     DrawTexturePro(
//         texture,
//         mCharacter.rectangle,
//         destination,
//         {0, 0},
//         0.0f,
//         RAYWHITE
//     );
// }

// //Handles player input.

// //SPACE makes the character move upward.

// //Otherwise gravity is applied.

// void CharacterController::inputHandler()
// {
//     if (IsKeyDown(KEY_SPACE))
//     {
//         moveUp();
//     }
//     else
//     {
//         if (mCharacter.state == CHAR_STATE_UP && mElapsedTime < 0.15f)
//             moveUp();
//         else
//             applyGravity();
//     }
// }

// //Runs every frame.
// //Updates movement and then draws the character.
// void CharacterController::onUpdate()
// {
//     inputHandler();
//     drawCharacter();
// }