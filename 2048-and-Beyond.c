// "2048 & Beyond" -> Powered by Romaniuc Albert-Iulian

/* Hello! My name is Romaniuc Albert-Iulian, and this is my first personal project.
   It is about the 2048 game, a puzzle game where the player must combine numbers
   to reach a specific goal.

   The rules are simple: the player must use one of the keys 'W', 'A', 'S', or 'D'
   to move the numbers in a certain direction on the board. If two identical numbers
   collide during movement, they will merge into a new number.
   If the player enters an invalid command, an error message will be displayed on the screen.

   The game features two modes:
   1. Classic mode (based on powers of 2) � the goal is to reach 2048.
   2. Alternative mode (based on powers of 3) � the goal is to reach 177147.

   Once the player reaches the target value in either mode, a message will announce
   that they have won the game.

   I hope you enjoy this project! Good luck and have fun playing! */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

// Commands for Windows/Linux
#ifdef _WIN32
#include <windows.h>  // Include Windows functions for console operations
#define CLEAR "cls"   // Command to clear the screen on Windows
#else
#include <unistd.h>   // Include POSIX functions for Linux/macOS
#define CLEAR "clear" // Command to clear the screen on Linux/macOS
#endif



#define SIZE 4

// Initialize the game board with 0 values
void initializeBoard(int board[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = 0;
        }
    }
}

// Copy one board to another
void copyBoard(int source[SIZE][SIZE], int dest[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            dest[i][j] = source[i][j];
        }
    }
}

// Compare two boards to check if they are identical
bool compareBoards(int board1[SIZE][SIZE], int board2[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board1[i][j] != board2[i][j]) {
                return false;
            }
        }
    }
    return true;
}

// Add a random tile (value 2 or 4) to an empty position on the board
void addRandomTile(int board[SIZE][SIZE])
{
    int emptyTiles[SIZE * SIZE][2];
    int emptyCount = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                emptyTiles[emptyCount][0] = i;
                emptyTiles[emptyCount][1] = j;
                emptyCount++;
            }
        }
    }

    if (emptyCount > 0) {
        int randomIndex = rand() % emptyCount;
        int row = emptyTiles[randomIndex][0];
        int col = emptyTiles[randomIndex][1];
        board[row][col] = (rand() % 10 == 0) ? 4 : 2; // 90% chance for 2, 10% for 4
    }
}

// Add a random tile (value 3 or 9) to an empty position on the board
void addRandomTile3(int board[SIZE][SIZE])
{
    int emptyTiles[SIZE * SIZE][2];
    int emptyCount = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                emptyTiles[emptyCount][0] = i;
                emptyTiles[emptyCount][1] = j;
                emptyCount++;
            }
        }
    }

    if (emptyCount > 0) {
        int randomIndex = rand() % emptyCount;
        int row = emptyTiles[randomIndex][0];
        int col = emptyTiles[randomIndex][1];
        board[row][col] = (rand() % 10 == 0) ? 9 : 3; // 90% chance for 3, 10% for 9
    }
}

// Slide and merge values in a row of the board
bool slideAndMergeRow(int row[SIZE], int *score)
{
    bool moved = false;

    // Slide to the left
    for (int i = 0; i < SIZE - 1; i++) {
        for (int j = 0; j < SIZE - 1; j++) {
            if (row[j] == 0 && row[j + 1] != 0) {
                row[j] = row[j + 1];
                row[j + 1] = 0;
                moved = true;
            }
        }
    }

    // Merge equal values
    for (int i = 0; i < SIZE - 1; i++) {
        if (row[i] != 0 && row[i] == row[i + 1]) {
            row[i] *= 2;
            row[i + 1] = 0;
            *score += row[i]; // Add to score
            moved = true;
        }
    }

    // Slide again after merging
    for (int i = 0; i < SIZE - 1; i++) {
        for (int j = 0; j < SIZE - 1; j++) {
            if (row[j] == 0 && row[j + 1] != 0) {
                row[j] = row[j + 1];
                row[j + 1] = 0;
                moved = true;
            }
        }
    }
    return moved;
}

// Slide and merge values in a row of the board (for 3 - 9)
bool slideAndMergeRow3(int row[SIZE], int *score)
{
    bool moved = false;

    // Slide to the left
    for (int i = 0; i < SIZE - 1; i++) {
        for (int j = 0; j < SIZE - 1; j++) {
            if (row[j] == 0 && row[j + 1] != 0) {
                row[j] = row[j + 1];
                row[j + 1] = 0;
                moved = true;
            }
        }
    }

    // Merge equal values
    for (int i = 0; i < SIZE - 1; i++) {
        if (row[i] != 0 && row[i] == row[i + 1]) {
            row[i] *= 3;
            row[i + 1] = 0;
            *score += row[i]; // Add to score
            moved = true;
        }
    }

    // Slide again after merging
    for (int i = 0; i < SIZE - 1; i++) {
        for (int j = 0; j < SIZE - 1; j++) {
            if (row[j] == 0 && row[j + 1] != 0) {
                row[j] = row[j + 1];
                row[j + 1] = 0;
                moved = true;
            }
        }
    }
    return moved;
}

// Move all rows to the left
bool moveLeft(int board[SIZE][SIZE], int *score)
{
    bool moved = false;
    for (int i = 0; i < SIZE; i++) {
        if (slideAndMergeRow(board[i], score)) {
            moved = true;
        }
    }
    return moved;
}

// Move all rows to the left (for 3 - 9)
bool moveLeft3(int board[SIZE][SIZE], int *score)
{
    bool moved = false;
    for (int i = 0; i < SIZE; i++) {
        if (slideAndMergeRow3(board[i], score)) {
            moved = true;
        }
    }
    return moved;
}

// Move all rows to the right
bool moveRight(int board[SIZE][SIZE], int *score)
{
    bool moved = false;
    for (int i = 0; i < SIZE; i++) {
        int reversedRow[SIZE];
        for (int j = 0; j < SIZE; j++) {
            reversedRow[j] = board[i][SIZE - 1 - j];
        }
        if (slideAndMergeRow(reversedRow, score)) {
            moved = true;
        }
        for (int j = 0; j < SIZE; j++) {
            board[i][SIZE - 1 - j] = reversedRow[j];
        }
    }
    return moved;
}

// Move all rows to the right (for 3 - 9)
bool moveRight3(int board[SIZE][SIZE], int *score)
{
    bool moved = false;
    for (int i = 0; i < SIZE; i++) {
        int reversedRow[SIZE];
        for (int j = 0; j < SIZE; j++) {
            reversedRow[j] = board[i][SIZE - 1 - j];
        }
        if (slideAndMergeRow3(reversedRow, score)) {
            moved = true;
        }
        for (int j = 0; j < SIZE; j++) {
            board[i][SIZE - 1 - j] = reversedRow[j];
        }
    }
    return moved;
}

// Move all columns up
bool moveUp(int board[SIZE][SIZE], int *score)
{
    bool moved = false;
    for (int j = 0; j < SIZE; j++) {
        int column[SIZE];
        for (int i = 0; i < SIZE; i++) {
            column[i] = board[i][j];
        }
        if (slideAndMergeRow(column, score)) {
            moved = true;
        }
        for (int i = 0; i < SIZE; i++) {
            board[i][j] = column[i];
        }
    }
    return moved;
}

// Move all columns up (for 3 - 9)
bool moveUp3(int board[SIZE][SIZE], int *score)
{
    bool moved = false;
    for (int j = 0; j < SIZE; j++) {
        int column[SIZE];
        for (int i = 0; i < SIZE; i++) {
            column[i] = board[i][j];
        }
        if (slideAndMergeRow3(column, score)) {
            moved = true;
        }
        for (int i = 0; i < SIZE; i++) {
            board[i][j] = column[i];
        }
    }
    return moved;
}

// Move all columns down
bool moveDown(int board[SIZE][SIZE], int *score)
{
    bool moved = false;
    for (int j = 0; j < SIZE; j++) {
        int column[SIZE];
        for (int i = 0; i < SIZE; i++) {
            column[i] = board[SIZE - 1 - i][j];
        }
        if (slideAndMergeRow(column, score)) {
            moved = true;
        }
        for (int i = 0; i < SIZE; i++) {
            board[SIZE - 1 - i][j] = column[i];
        }
    }
    return moved;
}

// Move all columns down (for 3 - 9)
bool moveDown3(int board[SIZE][SIZE], int *score)
{
    bool moved = false;
    for (int j = 0; j < SIZE; j++) {
        int column[SIZE];
        for (int i = 0; i < SIZE; i++) {
            column[i] = board[SIZE - 1 - i][j];
        }
        if (slideAndMergeRow3(column, score)) {
            moved = true;
        }
        for (int i = 0; i < SIZE; i++) {
            board[SIZE - 1 - i][j] = column[i];
        }
    }
    return moved;
}

// Check if there are possible moves on the board
bool canMove(int board[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                return true; // There is at least one empty position
            }
            if (i < SIZE - 1 && board[i][j] == board[i + 1][j]) {
                return true; // There are possible vertical merges
            }
            if (j < SIZE - 1 && board[i][j] == board[i][j + 1]) {
                return true; // There are possible horizontal merges
            }
        }
    }
    return false;
}

// Print text centered in the console
void centerPrint(const char *text)
{
    // Detect console width
    int consoleWidth = 80; // Default size

    #ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    }
    #endif

    // Calculate the necessary padding
    int padding = (consoleWidth - strlen(text)) / 2;
    if (padding < 0) padding = 0;

    // Print spaces and centered text
    for (int i = 0; i < padding; i++) {
        printf(" ");
    }
    printf("%s\n", text);
}

// Introduction to the game and a few things about me
void Presentation()
{
    system(CLEAR);
    int lines = 5;
    printf("\n");
    centerPrint("Powered by Albert-Iulian Romaniuc");
    for (int i = 0; i < lines - 1; i++) {
        printf("\n");
    }

    centerPrint("+-----------------------------------------------------------------+");
    centerPrint("|                                                                 |");
    centerPrint("|       Hello, everyone! My name is Albert-Iulian Romaniuc.       |");
    centerPrint("|                    I am a student at UNSTPB.                    |");
    centerPrint("|    Being very passionate about mathematical games, I decided    |");
    centerPrint("|   to recreate the 2048 game, adding some new features to make   |");
    centerPrint("|                      it more interesting.                       |");
    centerPrint("|  I am really happy to see you here, and I wish you good luck!!  |");
    centerPrint("|                                                                 |");
    centerPrint("+-----------------------------------------------------------------+");

    printf("\n");
    centerPrint("Press ENTER to start.");
    printf("\n");
    centerPrint("Press Q to quit.");
}

// Choosing between playing with powers of 2 or powers of 3
void Choice()
{
    system(CLEAR);
    int lines = 7;
    for (int i = 0; i < lines; i++) {
        printf("\n");
    }

    centerPrint("+--------------------------------+");
    centerPrint("|                                |");
    centerPrint("| What mode do you want to play: |");
    centerPrint("|            M2 / M3?            |");
    centerPrint("|             Press:             |");
    centerPrint("|     '2' -> M2 / '3' -> M3;     |");
    centerPrint("|                                |");
    centerPrint("+--------------------------------+");
}

// Display the welcome message at the start of the game
void printWelcomeMessage()
{
    system(CLEAR);
    int lines = 5;
    printf("\n");
    centerPrint("Welcome to 2048 - The Game!");
    for (int i = 0; i < lines - 1; i++) {
        printf("\n");
    }

    centerPrint("+------------------------------------------------+");
    centerPrint("|                                                |");
    centerPrint("|                     Rules:                     |");
    centerPrint("|                                                |");
    centerPrint("|   Use the W, A, S, D keys to move the tiles.   |");
    centerPrint("|  Two tiles with the same number merge into     |");
    centerPrint("|    one. The goal is to reach the 2048 tile!    |");
    centerPrint("|         Good luck and have fun, fellow!        |");
    centerPrint("|                                                |");
    centerPrint("+------------------------------------------------+");
    printf("\n");
}

// Display the welcome message at the start of the game (for 3 - 9)
void printWelcomeMessage3()
{
    system(CLEAR);
    int lines = 5;
    printf("\n");
    centerPrint("Welcome to 177147 - The Game!");
    for (int i = 0; i < lines - 1; i++) {
        printf("\n");
    }

    centerPrint("+------------------------------------------------+");
    centerPrint("|                                                |");
    centerPrint("|                     Rules:                     |");
    centerPrint("|                                                |");
    centerPrint("|   Use the W, A, S, D keys to move the tiles.   |");
    centerPrint("|  Two tiles with the same number merge into     |");
    centerPrint("|   one. The goal is to reach the 177147 tile!   |");
    centerPrint("|         Good luck and have fun, fellow!        |");
    centerPrint("|                                                |");
    centerPrint("+------------------------------------------------+");
    printf("\n");
}

// Display the game board with current values
void printBoard(int board[SIZE][SIZE], int score)
{
    char scoreMessage[50];
    printf("\n");

    centerPrint("+----------------------+");
    centerPrint("|                      |");
    centerPrint("|    2048 - The Game   |");
    centerPrint("|                      |");
    centerPrint("+----------------------+");

    printf("\n");
    sprintf(scoreMessage, "Score: %d", score);
    centerPrint(scoreMessage);
    printf("\n");
    centerPrint("+-------+-------+-------+-------+");
    for (int i = 0; i < SIZE; i++) {
        char row[100] = "";
        strcat(row, "|");
        for (int j = 0; j < SIZE; j++) {
            char cell[10];
            if (board[i][j] == 0) {
                sprintf(cell, "   .   |");
            } else {
                sprintf(cell, " %5d |", board[i][j]);
            }
            strcat(row, cell);
        }
        centerPrint(row);
        centerPrint("+-------+-------+-------+-------+");
    }
    printf("\n");

    // Read the user command
    centerPrint("Use W/A/S/D to move or R to undo.");
    printf("\n");
    centerPrint("Note: You can use R only once for each move.");
    printf("\n");
    centerPrint("Press Q to quit.");
}

// Display the game board with current values
void printBoard3(int board[SIZE][SIZE], int score)
{
    char scoreMessage[50];
    printf("\n");

    centerPrint("+-------------------------+");
    centerPrint("|                         |");
    centerPrint("|    177147 - The Game    |");
    centerPrint("|                         |");
    centerPrint("+-------------------------+");

    printf("\n");
    sprintf(scoreMessage, "Score: %d", score);
    centerPrint(scoreMessage);
    printf("\n");
    centerPrint("+-------+-------+-------+-------+");
    for (int i = 0; i < SIZE; i++) {
        char row[100] = "";
        strcat(row, "|");
        for (int j = 0; j < SIZE; j++) {
            char cell[10];
            if (board[i][j] == 0) {
                sprintf(cell, "   .   |");
            } else {
                sprintf(cell, " %5d |", board[i][j]);
            }
            strcat(row, cell);
        }
        centerPrint(row);
        centerPrint("+-------+-------+-------+-------+");
    }
    printf("\n");

    // Read the user command
    centerPrint("Use W/A/S/D to move or R to undo.");
    printf("\n");
    centerPrint("Note: You can use R only once for each move.");
    printf("\n");
    centerPrint("Press Q to quit.");
}

// Display congratulations message if 2048 is reached
void printWinMessage()
{
    system(CLEAR);
    printf("\n");

    centerPrint("      +------+      ");
    centerPrint("     /        \     ");
    centerPrint("    /          \    ");
    centerPrint("   /            \   ");
    centerPrint("  /              \  ");
    centerPrint(" /                \ ");
    centerPrint("+ Congratulations! +");
    centerPrint(" \                / ");
    centerPrint("  \              /  ");
    centerPrint("   \            /   ");
    centerPrint("    \          /    ");
    centerPrint("     \        /     ");
    centerPrint("      +------+      ");

    printf("\n\n");

    centerPrint("+---------------+");
    centerPrint("|               |");
    centerPrint("| You got 2048! |");
    centerPrint("|               |");
    centerPrint("+---------------+");
}

// Display congratulations message if 2048 is reached
void printWinMessage3()
{
    system(CLEAR);
    printf("\n");

    centerPrint("      +------+      ");
    centerPrint("     /        \     ");
    centerPrint("    /          \    ");
    centerPrint("   /            \   ");
    centerPrint("  /              \  ");
    centerPrint(" /                \ ");
    centerPrint("+ Congratulations! +");
    centerPrint(" \                / ");
    centerPrint("  \              /  ");
    centerPrint("   \            /   ");
    centerPrint("    \          /    ");
    centerPrint("     \        /     ");
    centerPrint("      +------+      ");

    printf("\n\n");

    centerPrint("+-----------------+");
    centerPrint("|                 |");
    centerPrint("| You got 177147! |");
    centerPrint("|                 |");
    centerPrint("+-----------------+");
}

// Check if the value 2048 has been reached on the board
bool checkWin(int board[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 2048) {
                return true;
            }
        }
    }
    return false;
}

// Check if the value 177147 has been reached on the board (for 3 - 9)
bool checkWin3(int board[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 177147) {
                return true;
            }
        }
    }
    return false;
}

int main()
{
    int board[SIZE][SIZE], prevBoard[SIZE][SIZE];
    int score, prevScore;
    char command;
    bool moved;
    char replay;
    bool isModeM2 = true;

    srand(time(NULL));

    do {
        score = 0;

        // Game presentation
        Presentation();
        while (1) {
            command = getchar();
            if (command == 'Q' || command == 'q') {
                centerPrint("You quit. Thank you for playing!");
                return 0;
            } else if (command == '\n') {
                break;
            } else {
                centerPrint("Invalid command! Press ENTER to start or Q to quit.");
                while (getchar() != '\n');
            }
        }

        // Choosing the game mode
        Choice();
        while (1) {
            command = getchar();
            if (command == '2') {
                while (getchar() != '\n');
                printWelcomeMessage();
                printf("\nPress ENTER to continue...\n");
                while (1) {
                    char enterCommand = getchar();
                    if (enterCommand == '\n') break;
                    centerPrint("Invalid command! Press ENTER to continue.");
                    while (getchar() != '\n');
                }
                isModeM2 = true;
                break;
            } else if (command == '3') {
                while (getchar() != '\n');
                printWelcomeMessage3();
                printf("\nPress ENTER to continue...\n");
                while (1) {
                    char enterCommand = getchar();
                    if (enterCommand == '\n') break;
                    centerPrint("Invalid command! Press ENTER to continue.");
                    while (getchar() != '\n');
                }
                isModeM2 = false;
                break;
            } else {
                centerPrint("Invalid command! Press 2 for M2 or 3 for M3.");
                while (getchar() != '\n');
            }
        }

        // Board initialization and adding the first numbers
        initializeBoard(board);
        initializeBoard(prevBoard);
        if (isModeM2) {
            addRandomTile(board);
            addRandomTile(board);
        } else {
            addRandomTile3(board);
            addRandomTile3(board);
        }

        while (1) {
            system(CLEAR);
            if (isModeM2) {
                printBoard(board, score);
            } else {
                printBoard3(board, score);
            }

            // Win check
            if ((isModeM2 && checkWin(board)) || (!isModeM2 && checkWin3(board))) {
                if (isModeM2) {
                    printWinMessage();
                } else {
                    printWinMessage3();
                }
                break;
            }

            // Game over check
            if (!canMove(board)) {
                centerPrint("Game Over!");
                break;
            }

            printf("\nEnter command: ");
            scanf(" %c", &command);
            while (getchar() != '\n');
            moved = false;

            // Processing user input
            if (command == 'Q' || command == 'q') {
                centerPrint("You quit. Thank you for playing!");
                return 0;
            } else if (command == 'W' || command == 'w') {
                copyBoard(board, prevBoard);
                prevScore = score;
                moved = isModeM2 ? moveUp(board, &score) : moveUp3(board, &score);
            } else if (command == 'A' || command == 'a') {
                copyBoard(board, prevBoard);
                prevScore = score;
                moved = isModeM2 ? moveLeft(board, &score) : moveLeft3(board, &score);
            } else if (command == 'S' || command == 's') {
                copyBoard(board, prevBoard);
                prevScore = score;
                moved = isModeM2 ? moveDown(board, &score) : moveDown3(board, &score);
            } else if (command == 'D' || command == 'd') {
                copyBoard(board, prevBoard);
                prevScore = score;
                moved = isModeM2 ? moveRight(board, &score) : moveRight3(board, &score);
            } else if (command == 'R' || command == 'r') {
                if (!compareBoards(board, prevBoard)) {
                    copyBoard(prevBoard, board);
                    score = prevScore;
                    centerPrint("The move was canceled.");
                } else {
                    centerPrint("There is no previous move to cancel.");
                }
                printf("\nPress ENTER to continue...\n");
                while (getchar() != '\n');
                continue;
            } else {
                centerPrint("Invalid command! Use W/A/S/D to move, R to undo, or Q to quit.");
                printf("\nPress ENTER to continue...\n");
                while (getchar() != '\n');
                continue;
            }

            // If the board has changed, add a new tile
            if (moved) {
                if (isModeM2) {
                    addRandomTile(board);
                } else {
                    addRandomTile3(board);
                }
            }
        }

        printf("\nDo you want to play again? (Y/N): ");
        scanf(" %c", &replay);
        while (getchar() != '\n');

    } while (replay == 'Y' || replay == 'y');

    return 0;
}
