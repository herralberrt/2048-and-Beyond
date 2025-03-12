# 2048 & Beyond

## Description
"2048 & Beyond" is a C-based console game that extends the classic 2048 puzzle. Players can choose between two game modes:
1. **Classic Mode (Powers of 2)** – The goal is to reach 2048.
2. **Alternative Mode (Powers of 3)** – The goal is to reach 177147.

Players slide numbered tiles using directional commands. Identical tiles merge to form larger numbers. The game ends when no moves are possible or when the target number is reached.

## Features
- Two game modes: **Classic (powers of 2)** and **Alternative (powers of 3)**
- Undo functionality (one move per turn)
- Console-based interface with clear instructions
- Randomized tile generation for a dynamic experience
- Support for both Windows and Linux/macOS

## Installation
1. Clone or download the repository.
2. Compile the program using a C compiler (GCC recommended):
   ```sh
   gcc -o 2048_game 2048_game.c
   ```
3. Run the game:
   ```sh
   ./2048_game
   ```

## How to Play
- Use **W, A, S, D** keys to move the tiles.
- Tiles of the same value merge when they collide.
- The game ends when no moves are possible.
- **'R'** allows undoing the last move (only once per turn).
- **'Q'** exits the game.

## Example Gameplay
1. Start the game and choose the mode:
   ```
   What mode do you want to play:
   M2 / M3?
   Press '2' for M2 or '3' for M3
   ```
2. Move the tiles using W, A, S, or D.
3. Merge tiles and try to reach **2048 (M2 mode) or 177147 (M3 mode)**.
4. Win the game or continue playing for a high score!

## License
This project is licensed under the MIT License.

