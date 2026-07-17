# FlappyMon
A RayLib-powered arcade game inspired by Flappy Bird with Pokémon-themed sprites and projectile mechanics.

## Table of Contents
- [Project Overview](#project-overview)
- [Features](#features)
- [Code Structure](#code-structure)
- [How the Game Works](#how-the-game-works)
- [Controls](#controls)
- [Libraries & Assets](#libraries--assets)
- [Build and Run](#build-and-run)
- [Future Updates](#future-updates)

---

## Project Overview
This project is a simple 2D game built using C++ and [RayLib](https://www.raylib.com/). It combines classic Flappy Bird-style movement with a shooting mechanic and enemy targets.

The main game logic lives in `main.cpp`, and the game uses sprite assets stored in `assets/sprites`.

---

## Features
- Main menu with `START` and `EXIT` buttons
- Gameplay screen with flying player character and moving obstacle
- Projectile shooting toward mouse cursor
- Random enemy spawns with scoring for hits and passes
- Game over screen with `PLAY AGAIN` option
- Score rendered using number sprite textures

---

## Code Structure
### `main.cpp`
This file contains the full game implementation.

Key components:
- `Projectile` struct: stores projectile position, velocity, rotation, and active state
- `Enemy` struct: stores enemy position and active state
- `getRand(int min, int max)`: returns a random integer in the specified range using the C++ `<random>` library
- `main()`: sets up the window, loads textures, runs the game loop, and unloads resources

### Game states
The game uses boolean state flags:
- `inMenu`: whether the menu screen is active
- `start`: whether the game is actively running
- `gameOver`: whether the player has lost

---

## How the Game Works
### Initialization
- Window is created with `InitWindow(850, 910, "FlappyMon")`
- Target framerate is set to `60 FPS`
- Textures loaded:
  - `charmander.png` for the player
  - `executor.png` as the pipe obstacle
  - `background-day.png` for the game background
  - `menu.png` and `gameover.png` for menu screens
  - `bulbasaur.png` for the enemy target
  - `ember.png` for projectile sprites
  - number textures `0.png` through `9.png` for score display

### Menu logic
- Displays start and exit buttons
- Clicking `START` resets game state and begins gameplay
- Clicking `EXIT` closes the window

### Gameplay logic
- Player character uses gravity-style movement:
  - Press `SPACE` to jump upward by reducing vertical acceleration
  - Gravity is simulated by increasing `accel` and applying downward movement
- The obstacle pipe scrolls left across the screen
- When the pipe passes a threshold, it resets with a new random vertical position

### Shooting projectiles
- Click the left mouse button to fire an ember projectile from the character position
- Projectile velocity is computed using a normalized direction vector from the player to the mouse cursor
- The projectile rotates to face the firing direction
- Projectiles deactivate when they leave the screen

### Enemy behavior
- A `bulbasaur` enemy spawns every 120 frames and moves leftward
- If the enemy reaches the left edge, it disappears and rewards points
- If a projectile collides with the enemy, the enemy is destroyed and the player scores

### Collision detection
- Collision checks are run between the player and obstacle pipe
- If collision occurs, the game stops and the game over screen appears

---

## Controls
- `SPACE`: make the Charmander character jump
- `Left mouse click`: fire an ember projectile toward the cursor
- `Left mouse click` on menu buttons: select `START`, `EXIT`, or `PLAY AGAIN`

---

## Libraries & Assets
### Libraries used
- `raylib`: 2D graphics, window management, input handling, and texture drawing
- Standard C++ libraries:
  - `<iostream>` for console/debug output support
  - `<random>` for deterministic random spawn values
  - `<math.h>` for trigonometry and square root calculations

### Assets used
- `assets/sprites/charmander.png`
- `assets/sprites/executor.png`
- `assets/sprites/background-day.png`
- `assets/sprites/menu.png`
- `assets/sprites/gameover.png`
- `assets/sprites/bulbasaur.png`
- `assets/sprites/ember.png`
- `assets/sprites/0.png` through `assets/sprites/9.png`

---

## Build and Run
1. Ensure RayLib is installed and configured for your environment.
2. Use `mingw32-make` or your preferred build command to compile `main.cpp`.
3. Run the produced executable.

If you are using the provided workspace tasks, choose either `build debug` or `build release`.

---

## Future Updates
Possible improvements and expansions:
- Add sound effects and background music
- Create a proper level progression and increasing difficulty
- Add more enemy types and power-ups
- Improve collision boxes for more accurate gameplay
- Add a scoreboard or save system
- Add pause functionality and settings menu
- Add animations for player, enemies, and background
- Add mobile or touchscreen controls
- Separate game states into multiple source files for cleaner architecture
- Add health/lives instead of instant game over

---

## Notes
This project is currently implemented as a single-file game engine with everything in `main.cpp`. Modularizing into separate files would make maintenance easier and enable additional features.

