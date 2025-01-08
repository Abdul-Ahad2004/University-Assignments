#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <sys/wait.h>
#include <limits>

using namespace std;

const int GRID_SIZE = 5;
const int SHIP_SIZES[3] = {2, 3, 4};
const char EMPTY = '-';
const char SHIP = 'S';
const char HIT = 'H';
const char MISS = 'M';

void initializeGrid(char grid[GRID_SIZE][GRID_SIZE]) {
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            grid[i][j] = EMPTY;
        }
    }
}

bool placeShip(char grid[GRID_SIZE][GRID_SIZE], int size, int row, int col, char direction) {
    if (direction == 'H') {
        if (col + size > GRID_SIZE) return false;
        for (int i = 0; i < size; ++i) {
            if (grid[row][col + i] != EMPTY) return false;
        }
        for (int i = 0; i < size; ++i) {
            grid[row][col + i] = SHIP;
        }
    } else if (direction == 'V') {
        if (row + size > GRID_SIZE) return false;
        for (int i = 0; i < size; ++i) {
            if (grid[row + i][col] != EMPTY) return false;
        }
        for (int i = 0; i < size; ++i) {
            grid[row + i][col] = SHIP;
        }
    }
    return true;
}

void displayGrid(const char grid[GRID_SIZE][GRID_SIZE]) {
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

bool isHit(char grid[GRID_SIZE][GRID_SIZE], int row, int col) {
    if (grid[row][col] == SHIP) {
        grid[row][col] = EMPTY;
        return true;
    }
    return false;
}

int remainingShips(char grid[GRID_SIZE][GRID_SIZE]) {
    int remaining = 0;
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            if (grid[i][j] == SHIP) {
                remaining++;
            }
        }
    }
    return remaining;
}

bool isGameOver(char grid[GRID_SIZE][GRID_SIZE]) {
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            if (grid[i][j] == SHIP) {
                return false;
            }
        }
    }
    return true;
}

void playerTurn(int readPipe, int writePipe, char opponentGrid[GRID_SIZE][GRID_SIZE]) {
    int row, col;
    cout << "\t\t**Enter your guess**" << endl;
    cout << "Enter the row number: ";
    cin >> row;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter the column number: ";
    cin >> col;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    write(writePipe, &row, sizeof(int));
    write(writePipe, &col, sizeof(int));
    char result;
    read(readPipe, &result, sizeof(char));
}

void opponentTurn(int readPipe, int writePipe, char playerGrid[GRID_SIZE][GRID_SIZE]) {
    int row, col;
    read(readPipe, &row, sizeof(int));
    read(readPipe, &col, sizeof(int));
    char result = isHit(playerGrid, row, col) ? HIT : MISS;
    write(writePipe, &result, sizeof(char));
    cout << "Opponent guessed (" << row << ", " << col << ") - " << (result == HIT ? "Hit!" : "Miss!") << endl;
    cout << "Remaining total hits to win the game: " << remainingShips(playerGrid) << endl;
}

int main() {
    int pipe1[2], pipe2[2];
    pid_t pid;
    pipe(pipe1);
    pipe(pipe2);
    char player1Grid[GRID_SIZE][GRID_SIZE], player2Grid[GRID_SIZE][GRID_SIZE];
    initializeGrid(player1Grid);
    initializeGrid(player2Grid);

    cout << "\t\tPlayer 1, place your ships:\n";
    for (int i = 0; i < 3; ++i) {
        int size = SHIP_SIZES[i];
        int row, col;
        char direction;
        bool placed = false;
        while (!placed) {
            cout << "Enter row, col, and direction (H/V) for ship of size " << size << ": ";
            cin >> row >> col >> direction;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            while(direction!='V' && direction!='H')
            {
                cout << "Entered an invalid direction!, Enter again: ";
                cin >> direction;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            placed = placeShip(player1Grid, size, row, col, direction);
            if (!placed) cout << "Invalid placement. Try again.\n";
        }
    }

    cout << "\t\tPlayer 2, place your ships:\n";
    for (int i = 0; i < 3; ++i) {
        int size = SHIP_SIZES[i];
        int row, col;
        char direction;
        bool placed = false;
        while (!placed) {
            cout << "Enter row, col, and direction (H/V) for ship of size " << size << ": ";
            cin >> row >> col >> direction;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
             while(direction!='V' && direction!='H')
            {
                cout << "Entered an invalid direction!, Enter again: ";
                cin >> direction;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            placed = placeShip(player2Grid, size, row, col, direction);
            if (!placed) cout << "Invalid placement. Try again.\n";
        }
    }

    if ((pid = fork()) < 0) {
        cerr << "Fork error" << endl;
        return 1;
    }

    if (pid == 0) {
        close(pipe1[1]);
        close(pipe2[0]);
        cout << "\t\tPlayer 2, your grid:\n";
        displayGrid(player2Grid);

        while (!isGameOver(player1Grid) && !isGameOver(player2Grid)) {
            cout << "\nPlayer 2's turn:\n";
            playerTurn(pipe1[0], pipe2[1], player1Grid);
            if (isGameOver(player1Grid)) break;
            opponentTurn(pipe1[0], pipe2[1], player2Grid);
            cout << "\n\t\tPlayer 2, your grid:\n";
            displayGrid(player2Grid);
        }

        close(pipe1[0]);
        close(pipe2[1]);
    } else {
        close(pipe1[0]);
        close(pipe2[1]);
        cout << "\t\tPlayer 1, your grid:\n";
        displayGrid(player1Grid);

        while (!isGameOver(player1Grid) && !isGameOver(player2Grid)) {
            opponentTurn(pipe2[0], pipe1[1], player1Grid);
            cout << "\n\t\tPlayer 1, your grid:\n";
            displayGrid(player1Grid);
            if (isGameOver(player1Grid)) break;
            cout << "\nPlayer 1's turn:\n";
            playerTurn(pipe2[0], pipe1[1], player2Grid);
        }

        close(pipe1[1]);
        close(pipe2[0]);
        wait(NULL);
    }

    if (isGameOver(player1Grid)) {
        cout << "\n\t**Player 2 wins!**";
    } else if (isGameOver(player2Grid)) {
        cout << "\n\t**Player 1 wins!**";
    }

    return 0;
}

